/*
 * Copyright (c) 2024 IIT Mandi
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Authors: Ayush Gaurav <ayush183gaurav@gmail.com>
 *          Sreelakshmi PM <sreelakshmi@iitmandi.ac.in>
 */

#include "tcp-davis-linux.h"

#include "ns3/log.h"
#include "ns3/simulator.h"
#include <algorithm>
#include <random>

namespace ns3
{
    NS_LOG_COMPONENT_DEFINE("TcpDavisLinux");
    NS_OBJECT_ENSURE_REGISTERED(TcpDavisLinux);

    TypeId
    TcpDavisLinux::GetTypeId()
    {
        static TypeId tid = 
            TypeId("ns3::TcpDavisLinux")
                .SetParent<TcpCongestionOps>()
                .AddConstructor<TcpDavisLinux>()
                .SetGroupName("Internet")
                .AddAttribute("MinCwnd",
                              "Minimum congestion window size",
                              UintegerValue(4),
                              MakeUintegerAccessor(&TcpDavisLinux::m_minCwnd),
                              MakeUintegerChecker<uint8_t>())
                .AddAttribute("MinGainCwnd",
                              "Minimum gain in congestion window",
                              UintegerValue(4),
                              MakeUintegerAccessor(&TcpDavisLinux::m_minGainCwnd),
                              MakeUintegerChecker<uint8_t>())
                .AddAttribute("DrainRtts",
                              "Duration since mode change after which DRAIN mode actually begins",
                              UintegerValue(2),
                              MakeUintegerAccessor(&TcpDavisLinux::m_drainRtts),
                              MakeUintegerChecker<uint8_t>())
                .AddAttribute("GainOneRtts",
                              "Duration since mode change after which GAIN1 mode actually begins",
                              UintegerValue(2),
                              MakeUintegerAccessor(&TcpDavisLinux::m_gainOneRtts),
                              MakeUintegerChecker<uint8_t>())
                .AddAttribute("GainTwoRtts",
                              "Duration since mode change after which GAIN2 mode actually begins",
                              UintegerValue(1),
                              MakeUintegerAccessor(&TcpDavisLinux::m_gainTwoRtts),
                              MakeUintegerChecker<uint8_t>())
                .AddAttribute("RttTimeout",
                              "Time duration after which minRTT measurement must be updated",
                              TimeValue(Seconds(10)),
                              MakeTimeAccessor(&TcpDavisLinux::m_rttTimeout),
                              MakeTimeChecker());
        return tid;
    }

    TcpDavisLinux::TcpDavisLinux() : TcpCongestionOps()
    {
        NS_LOG_FUNCTION(this);
        m_mode = DAVIS_GAIN1;
        m_lastModeChange = Simulator::Now();

        m_deliveredStart = 0;
        m_deliveredStartTime = Simulator::Now();

        m_bdp = m_minCwnd;
        m_lastBdp = 0;
        m_gainCwnd = m_minGainCwnd;

        m_stableRtts = m_stableRttsMin;

        m_lastRTT = Seconds(0);   
        // m_minRTT = Time::Max();
        m_minRTT = RTT_INF;
        m_minRttTime = Simulator::Now();

        m_rand = CreateObject<UniformRandomVariable>();
        m_rand->SetAttribute("Min", DoubleValue(m_stableRttsMin));
        m_rand->SetAttribute("Max", DoubleValue(m_stableRttsMax));
        m_rand->SetStream(reinterpret_cast<long>(this));
        NS_LOG_INFO("TcpDavisLinux: Initializing m_mode = " << m_mode);
    }

    TcpDavisLinux::TcpDavisLinux(const TcpDavisLinux& sock) 
    : TcpCongestionOps(sock),
      m_minRTT(sock.m_minRTT),
      m_mode(sock.m_mode),
      m_bdp(sock.m_bdp),
      m_gainCwnd(sock.m_gainCwnd),
      m_isInSlowStart(sock.m_isInSlowStart),
        m_lastBdp(sock.m_lastBdp),
      m_minCwnd(sock.m_minCwnd),
      m_maxCwnd(sock.m_maxCwnd),
      m_minGainCwnd(sock.m_minGainCwnd),
      m_reactivity(sock.m_reactivity),
      m_sensitivity(sock.m_sensitivity),
      m_drainRtts(sock.m_drainRtts),
      m_stableRttsMin(sock.m_stableRttsMin),
      m_stableRttsMax(sock.m_stableRttsMax),
      m_gainOneRtts(sock.m_gainOneRtts),
      m_gainTwoRtts(sock.m_gainTwoRtts),
      RTT_INF(sock.RTT_INF),
      m_rttTimeout(sock.m_rttTimeout),
      m_lastModeChange(sock.m_lastModeChange),
      m_minRttTime(sock.m_minRttTime),
      m_deliveredStartTime(sock.m_deliveredStartTime),
      m_deliveredStart(sock.m_deliveredStart),
    //   m_lastBdp(sock.m_lastBdp),
      m_stableRtts(sock.m_stableRtts),
      m_lastRTT(sock.m_lastRTT),
      m_delivered(sock.m_delivered),
      m_interval(sock.m_interval),
      m_rand(sock.m_rand),
      m_mss(sock.m_mss)
    {
        NS_LOG_FUNCTION(this);
    }


    const char* const TcpDavisLinux::DavisModeName[DAVIS_GAIN2 + 1] = {
        "DAVIS_DRAIN",
        "DAVIS_STABLE",
        "DAVIS_GAIN1",
        "DAVIS_GAIN2",
    };

    std::string
    TcpDavisLinux::GetName() const
    {
        return "TcpDavisLinux";
    }

    bool
    TcpDavisLinux::HasCongControl() const
    {
        NS_LOG_FUNCTION(this);
        return true;

    }

    void
    TcpDavisLinux::Init(Ptr<TcpSocketState> tcb [[maybe_unused]])
    {
        NS_LOG_FUNCTION(this << tcb);
        // tcb->m_segmentSize = m_mss;
        tcb->m_cWnd.Set(m_minCwnd);
        // tcb->m_ssThresh.Set(TCP_INFINITE_SSTHRESH);
        tcb->m_ssThresh.Set(m_maxCwnd);
        
        tcb->m_pacing = false;
        tcb->m_pacingRate.Set(DataRate("0bps"));

        tcb->m_useEcn = TcpSocketState::UseEcn_t::On;
        tcb->m_ecnState.Set(TcpSocketState::EcnState_t::ECN_IDLE); 

        // tcb->m_lastRtt.Set(Seconds(0));
    }

    uint32_t
    TcpDavisLinux::GetSsThresh(Ptr<const TcpSocketState> tcb, uint32_t bytesInFlight)
    {
        NS_LOG_FUNCTION(this << tcb << bytesInFlight);
        return tcb->m_ssThresh.Get();
    }

    void 
    TcpDavisLinux::CongControl(Ptr<TcpSocketState> tcb,
                     const TcpRateOps::TcpRateConnection& rc,
                     const TcpRateOps::TcpRateSample& rs)
    {
        NS_LOG_FUNCTION(this << tcb << rs);

        // if(tcb->m_ecnState.Get() == TcpSocketState::ECN_CE_RCVD || tcb->m_congState.Get() == TcpSocketState::CA_RECOVERY)
        // {
        //     // tcb->m_ssThresh.Set(0);
        //     ExitSlowStart(tcb);
        // }
        // if(rs.m_bytesLoss!=0)
        // {
        //     // tcb->m_ssThresh.Set(0);
        //     ExitSlowStart(tcb);
        // }

        if(tcb->m_lastRtt.Get().GetSeconds() > 0)
        {
           m_lastRTT = tcb->m_lastRtt.Get();
           
           if(tcb->m_lastRtt.Get().GetSeconds() <= m_minRTT.GetSeconds())
           {
                m_minRTT = tcb->m_lastRtt.Get();
                m_minRttTime = Simulator::Now();
           }
        }

        if(tcb->m_cWnd.Get() < tcb->m_ssThresh.Get())
        {
            m_isInSlowStart = true;
            SlowStart(tcb, rc, rs);
        }
        else
        {
            m_isInSlowStart = false;
            CongestionAvoidance(tcb, rc, rs);
        }

        // tcb->m_cWnd = std::clamp(tcb->m_cWnd.Get(), static_cast<uint32_t>(m_minCwnd), static_cast<uint32_t>(MAX_TCP_WINDOW));
        tcb->m_cWnd.Set(std::clamp(tcb->m_cWnd.Get(), static_cast<uint32_t>(m_minCwnd), static_cast<uint32_t>(m_maxCwnd)));
        tcb->m_pacing = false;
        tcb->m_pacingRate.Set(DataRate("0bps"));
    }

    void
    TcpDavisLinux::CongestionStateSet(Ptr<TcpSocketState> tcb,
                                 const TcpSocketState::TcpCongState_t newState)
    {
        NS_LOG_FUNCTION(this << tcb << newState);
        if(newState == TcpSocketState::TcpCongState_t::CA_LOSS) // CA_LOSS is trigerred after timeout period has passed and ACK is not received. So, packet is assumed to be lost and flow is restarted.
        {
            tcb->m_ssThresh.Set(m_maxCwnd);
            // tcb->m_ssThresh.Set(TCP_INFINITE_SSTHRESH);
            // m_isInSlowStart = false;
            EnterSlowStart(tcb);
        }
        else if(newState == TcpSocketState::TcpCongState_t::CA_RECOVERY || newState == TcpSocketState::TcpCongState_t::CA_CWR) // CA_RECOVERY is triggered when as soon as a loss has occured.This loss is detected via duplicate ACKs received.
        {                                                                                                                       // CA_CWR is triggered when cWnd was reduced due to some Congestion Notification event. It can be ECN, ICMP source quench, local device congestion. Not used in NS-3 right now.
            // tcb->m_ssThresh.Set(0);
            // ExitSlowStart(tcb);
            m_mode = DAVIS_DRAIN;
            m_lastModeChange = Simulator::Now();

            tcb->m_cWnd.Set(m_minCwnd);
            tcb->m_ssThresh.Set(m_minCwnd);
        }
    }

    void
    TcpDavisLinux::CwndEvent(Ptr<TcpSocketState> tcb, const TcpSocketState::TcpCAEvent_t event)
    {
        NS_LOG_FUNCTION(this << tcb << event);
        // if(event == TcpSocketState::TcpCAEvent_t::CA_EVENT_LOSS || event == TcpSocketState::TcpCAEvent_t::CA_EVENT_CWND_RESTART) // CA_EVENT_LOSS indicates that a packet loss was detected due to a timeout (RTO expiration). This event is typically associated with CA_LOSS in the congestion control state machine.
        if(event == TcpSocketState::TcpCAEvent_t::CA_EVENT_LOSS)
        {
            // tcb->m_ssThresh.Set(TCP_INFINITE_SSTHRESH);
            tcb->m_ssThresh.Set(m_maxCwnd);
            // m_isInSlowStart = false;
            EnterSlowStart(tcb);
        }
        else if(event == TcpSocketState::TcpCAEvent_t::CA_EVENT_ECN_IS_CE)
        {
            // tcb->m_ssThresh.Set(0);
            // ExitSlowStart(tcb);
            m_mode = DAVIS_DRAIN;
            m_lastModeChange = Simulator::Now();

            tcb->m_cWnd.Set(m_minCwnd);
            tcb->m_ssThresh.Set(m_minCwnd);
        }
    }

    void
    TcpDavisLinux::EnterSlowStart(Ptr<TcpSocketState> tcb)
    {
        NS_LOG_FUNCTION(this);
        m_mode = DAVIS_GAIN1;
        m_lastModeChange = Simulator::Now();

        m_bdp = m_minCwnd;
        m_lastBdp = 0;

        tcb->m_cWnd.Set(m_minCwnd);

        m_minRTT = m_lastRTT;
    }

    void
    TcpDavisLinux::SlowStart(Ptr<TcpSocketState> tcb,
                     const TcpRateOps::TcpRateConnection& rc,
                     const TcpRateOps::TcpRateSample& rs)
    {
        // if(!m_isInSlowStart)
        // {
        //     m_isInSlowStart = true;

        //     EnterSlowStart(tcb);

            // m_mode = DAVIS_GAIN1;
            // m_lastModeChange = Simulator::Now();

            // m_bdp = m_minCwnd;
            // m_lastBdp = 0;

            // tcb->m_cWnd.Set(m_minCwnd);

            // m_minRTT = m_lastRTT;
            // m_minRTT = tcb->m_lastRtt.Get();

            // m_minRTT = m_lastRTT; // I doubt the correctness of this line because just before last RTT is set to 0, so I doubt if this is correct but as per module this should be.
        // }

        // if(tcb->m_lastRtt.Get().GetSeconds() < m_minRTT.GetSeconds())
        // {
        //     m_minRTT = tcb->m_lastRtt.Get();
        //     m_minRttTime = Simulator::Now();
        // }

        // Time RTT;
        // Time oneJiffy = Seconds(0.001);
        // Time zero = Seconds(0);

        // if(tcb->m_lastRtt.Get().GetSeconds() > oneJiffy.GetSeconds())
        // {
        //     RTT = tcb->m_lastRtt.Get();
        // }
        // else
        // {
        //     RTT = tcb->m_srtt.Get();
        // }
        
        // if(RTT.GetSeconds() > zero.GetSeconds())
        // {
        //     m_lastRTT = RTT;
        //     if(RTT.GetSeconds() < m_minRTT.GetSeconds())
        //     {
        //         m_minRTT = RTT;
        //         m_minRttTime = Simulator::Now();
        //     }
        // }

        switch (m_mode)
        {
            case DAVIS_GAIN1:
                if(Simulator::Now() - m_lastModeChange > m_lastRTT * m_gainOneRtts)
                {
                    m_mode = DAVIS_GAIN2;
                    m_lastModeChange = Simulator::Now();

                    m_deliveredStart = rc.m_delivered;
                    m_deliveredStartTime = Simulator::Now();
                    // m_deliveredStartTime = rc.m_deliveredTime;
                    // EnterGain2();
                }
                break;
            case DAVIS_GAIN2:
                if(Simulator::Now() - m_lastModeChange > m_lastRTT * m_gainTwoRtts)
                {
                    m_delivered = rc.m_delivered - m_deliveredStart;
                    // m_interval = rc.m_deliveredTime - m_deliveredStartTime;
                    m_interval = Simulator::Now() - m_deliveredStartTime;

                    m_bdp = static_cast<uint32_t>(std::ceil(static_cast<double>(m_delivered) * m_minRTT.GetSeconds() / m_interval.GetSeconds()));

                    // if(m_interval.GetSeconds() > 0)
                    // {
                        // m_lastBdp = m_bdp;
                        // uint64_t deliveryRate = m_delivered / m_interval.GetSeconds();
                        // m_bdp = deliveryRate * m_minRTT.GetSeconds(); // Check which minRTT variable to use
                        // m_gainCwnd = std::max(4U, m_bdp/2);

                        // if(m_bdp <= m_lastBdp)
                        // {
                        //     tcb->m_ssThresh.Set(0);
                        //     ExitSlowStart(tcb);
                        // }
                        // else
                        // {
                        //     tcb->m_cWnd.Set(m_bdp + m_gainCwnd);
                        //     EnterGain1();
                        // }
                    // }

                    if(m_bdp > m_lastBdp)
                    {
                        m_mode = DAVIS_GAIN1;
                        m_lastModeChange = Simulator::Now();

                        tcb->m_cWnd.Set(1.5 * m_bdp);
                        m_lastBdp = m_bdp;

                        // EnterGain1();
                    }
                    else
                    {
                        // ExitSlowStart(tcb);
                        m_mode = DAVIS_DRAIN;
                        m_lastModeChange = Simulator::Now();

                        tcb->m_cWnd.Set(m_minCwnd);
                        tcb->m_ssThresh.Set(m_minCwnd);
                    }
                }
                break;
            // case DAVIS_DRAIN:
            //     NS_LOG_WARN("Slow Start entered DRAIN mode");
            //     break;
            default:
                EnterSlowStart(tcb);
                break;
        }
    }

    // void
    // TcpDavisLinux::ExitSlowStart(Ptr<TcpSocketState> tcb)
    // {
    //     NS_LOG_FUNCTION(this);
    //     m_isInSlowStart = false;

    //     tcb->m_cWnd.Set(m_minCwnd);
    //     tcb->m_ssThresh.Set(m_minCwnd);
        
    //     EnterDrain();
    // }

    // void
    // TcpDavisLinux::EnterDrain()
    // {
    //     NS_LOG_FUNCTION(this);
    //     m_mode = DAVIS_DRAIN;
    //     m_lastModeChange = Simulator::Now();
    // }

    // void
    // TcpDavisLinux::EnterGain1()
    // {
    //     NS_LOG_FUNCTION(this);
    //     m_mode = DAVIS_GAIN1;
    //     m_lastModeChange = Simulator::Now();
    // }

    // Some correction required
    // void
    // TcpDavisLinux::EnterGain2()
    // {
    //     NS_LOG_FUNCTION(this);
    //     m_mode = DAVIS_GAIN2;
    //     m_lastModeChange = Simulator::Now();
    // }

    void
    TcpDavisLinux::UpdateGainCwnd()
    {
        uint32_t gain;
        double alpha;
        double beta;

        if(m_sensitivity < 0)
        {
            m_sensitivity = 0;
        }

        if(m_reactivity <= m_sensitivity)
        {
            // NS_LOG_DEBUG("Reactivity is less than sensitivity");
            m_reactivity = m_sensitivity + 1.0e-3;
        }

        // alpha = DAVIS_ONE + m_reactivity - ((m_sensitivity*DAVIS_ONE)/m_reactivity);
        alpha = 1 + m_reactivity - (m_sensitivity/m_reactivity);
        beta = m_sensitivity - alpha;

        gain = alpha * m_bdp + beta * m_lastBdp;
        // gain = std::max(static_cast<int32_t>(gain), static_cast<int32_t>(m_sensitivity * m_bdp));
        // gain = std::max(static_cast<int32_t>(gain), static_cast<int32_t>(m_minGainCwnd*DAVIS_ONE));
        // gain = std::max(static_cast<int32_t>(gain), static_cast<int32_t>(m_minGainCwnd));
        double gain1 = m_sensitivity * m_bdp;
        double gain2 = static_cast<double>(m_minGainCwnd);
        gain = static_cast<uint32_t>(std::max({static_cast<double>(gain), gain1, gain2}));

        // m_gainCwnd = gain / DAVIS_ONE;
        m_gainCwnd = gain;
    }

    void
    TcpDavisLinux::CongestionAvoidance(Ptr<TcpSocketState> tcb,
                     const TcpRateOps::TcpRateConnection& rc,
                     const TcpRateOps::TcpRateSample& rs)
    {
        // if(tcb->m_lastRtt.Get().GetSeconds() < m_minRTT.GetSeconds())
        // {
        //     m_minRTT = tcb->m_lastRtt.Get();
        //     m_minRttTime = Simulator::Now();
        // }

        // Time RTT;
        // Time oneJiffy = Seconds(0.001);
        // Time zero = Seconds(0);

        // if(tcb->m_lastRtt.Get().GetSeconds() > oneJiffy.GetSeconds())
        // {
        //     RTT = tcb->m_lastRtt.Get();
        // }
        // else
        // {
        //     RTT = tcb->m_srtt.Get();
        // }
        
        // if(RTT.GetSeconds() > zero.GetSeconds())
        // {
        //     m_lastRTT = RTT;
        //     if(RTT.GetSeconds() < m_minRTT.GetSeconds())
        //     {
        //         m_minRTT = RTT;
        //         m_minRttTime = Simulator::Now();
        //     }
        // }

        Time timeSinceLastModeChange = Simulator::Now() - m_lastModeChange;

        switch (m_mode)
        {
            case DAVIS_DRAIN:
                if(timeSinceLastModeChange > m_lastRTT * m_drainRtts) // Check whether m_minRTT is appropriate to use here
                {
                    // tcb->m_cWnd.Set(m_bdp + m_gainCwnd);
                    // EnterGain1();
                    m_mode = DAVIS_STABLE;
                    m_lastModeChange = Simulator::Now();

                    tcb->m_cWnd.Set(m_bdp);
                }
                break;

            case DAVIS_STABLE:
                if(timeSinceLastModeChange > m_stableRtts * m_lastRTT)
                {
                    m_mode = DAVIS_GAIN1;
                    m_lastModeChange = Simulator::Now();

                    tcb->m_cWnd.Set(m_bdp + m_gainCwnd);
                    // EnterGain1();
                }
            
            case DAVIS_GAIN1:
                if(timeSinceLastModeChange > m_lastRTT * m_gainOneRtts)
                {
                    m_mode = DAVIS_GAIN2;
                    m_lastModeChange = Simulator::Now();

                    m_deliveredStart = rc.m_delivered;
                    m_deliveredStartTime = Simulator::Now();
                    // m_deliveredStartTime = rc.m_deliveredTime;
                    // EnterGain2();
                }
                break;

            case DAVIS_GAIN2:
                if(timeSinceLastModeChange > m_lastRTT * m_gainTwoRtts)
                {
                    m_delivered = rc.m_delivered - m_deliveredStart;
                    m_interval = Simulator::Now() - m_deliveredStartTime;
                    // m_interval = rc.m_deliveredTime - m_deliveredStartTime;

                    m_lastBdp = m_bdp;
                    m_bdp = static_cast<uint32_t>(std::ceil(static_cast<double>(m_delivered) * m_minRTT.GetSeconds() / m_interval.GetSeconds()));

                    // if(m_interval.GetSeconds() > 0)
                    // {
                    //     uint64_t deliveryRate = m_delivered / m_interval.GetSeconds();
                    //     m_bdp = deliveryRate * m_minRTT.GetSeconds(); 
                        // m_lastBdp = m_bdp;
                        // uint32_t deliveryRate = m_delivered / m_interval.GetSeconds();
                        // m_bdp = deliveryRate * m_minRTT.GetSeconds(); // Check which minRTT variable to use
                        // uint32_t deviation = std::abs((int)m_bdp - (int)m_lastBdp);
                        // m_gainCwnd = 4 + std::min(2 * deviation, m_bdp);
                    // }

                    UpdateGainCwnd();

                    if(Simulator::Now() - m_minRttTime > m_rttTimeout)
                    {
                        m_mode = DAVIS_DRAIN;
                        m_lastModeChange = Simulator::Now();
                        
                        tcb->m_cWnd.Set(m_minCwnd);
                        m_minRTT = m_lastRTT;
                        // m_minRTT = tcb->m_lastRtt.Get();
                        m_minRttTime = Simulator::Now();

                        // EnterDrain();
                    }
                    else
                    {
                        // uint32_t RTT_diff = m_stableRttsMax - m_stableRttsMin;

                        m_mode = DAVIS_STABLE;
                        m_lastModeChange = Simulator::Now();

                        m_stableRtts = m_rand->GetInteger();

                        // m_stableRtts = m_stableRttsMin;
                        // std::random_device rd;
                        // std::mt19937 gen(rd());
                        // std::uniform_int_distribution<uint32_t> dist(0, RTT_diff);
                        // m_stableRtts += dist(gen);

                        // tcb->m_cWnd.Set(m_bdp + m_gainCwnd);
                        // EnterGain1();
                        tcb->m_cWnd.Set(m_bdp);
                    }
                }
                break;
            default:
                NS_LOG_WARN("Invalid mode");
                
                m_mode = DAVIS_DRAIN;
                m_lastModeChange = Simulator::Now();

                tcb->m_cWnd.Set(m_minCwnd);
        }

        // tcb->m_cWnd = std::clamp(tcb->m_cWnd.Get(), static_cast<uint32_t>(m_minCwnd), static_cast<uint32_t>(MAX_TCP_WINDOW));
    }

    Ptr<TcpCongestionOps>
    TcpDavisLinux::Fork()
    {
        return CopyObject<TcpDavisLinux>(this);
    }
}