/*
 * Copyright (c) 2024 IIT Mandi
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Authors: Ayush Gaurav <ayush183gaurav@gmail.com>
 *          Sreelakshmi PM <sreelakshmi@iitmandi.ac.in>
 */

#include "tcp-davis.h"

#include "ns3/log.h"
#include "ns3/simulator.h"

namespace ns3
{
    NS_LOG_COMPONENT_DEFINE("TcpDavis");
    NS_OBJECT_ENSURE_REGISTERED(TcpDavis);

    TypeId
    TcpDavis::GetTypeId()
    {
        static TypeId tid = 
            TypeId("ns3::TcpDavis")
                .SetParent<TcpCongestionOps>()
                .AddConstructor<TcpDavis>()
                .SetGroupName("Internet")
                .AddAttribute("MinCwnd",
                              "Minimum congestion window size",
                              UintegerValue(4),
                              MakeUintegerAccessor(&TcpDavis::m_minCwnd),
                              MakeUintegerChecker<uint8_t>())
                .AddAttribute("MinGainCwnd",
                              "Minimum gain in congestion window",
                              UintegerValue(4),
                              MakeUintegerAccessor(&TcpDavis::m_minGainCwnd),
                              MakeUintegerChecker<uint8_t>())
                .AddAttribute("DrainRtts",
                              "Duration since mode change after which DRAIN mode actually begins",
                              UintegerValue(2),
                              MakeUintegerAccessor(&TcpDavis::m_drainRtts),
                              MakeUintegerChecker<uint8_t>())
                .AddAttribute("GainOneRtts",
                              "Duration since mode change after which GAIN1 mode actually begins",
                              UintegerValue(2),
                              MakeUintegerAccessor(&TcpDavis::m_gainOneRtts),
                              MakeUintegerChecker<uint8_t>())
                .AddAttribute("GainTwoRtts",
                              "Duration since mode change after which GAIN2 mode actually begins",
                              UintegerValue(1),
                              MakeUintegerAccessor(&TcpDavis::m_gainTwoRtts),
                              MakeUintegerChecker<uint8_t>())
                .AddAttribute("RttTimeout",
                              "Time duration after which minRTT measurement must be updated",
                              TimeValue(Seconds(10)),
                              MakeTimeAccessor(&TcpDavis::m_rttTimeout),
                              MakeTimeChecker());
        return tid;
    }

    TcpDavis::TcpDavis() : TcpCongestionOps()
    {
        NS_LOG_FUNCTION(this);
        m_mode = DAVIS_GAIN1;
        m_lastModeChange = Simulator::Now();

        m_bdp = m_minCwnd;
        m_lastBdp = 0;
        m_gainCwnd = m_minGainCwnd;

        m_lastRTT = Seconds(0); 
        m_minRTT = Time::Max();

        m_minRttTime = Simulator::Now();
    }

    TcpDavis::TcpDavis(const TcpDavis& sock) : TcpCongestionOps(sock),
                                                m_minCwnd(sock.m_minCwnd),
                                                m_minGainCwnd(sock.m_minGainCwnd),
                                                m_drainRtts(sock.m_drainRtts),
                                                m_gainOneRtts(sock.m_gainOneRtts),
                                                m_gainTwoRtts(sock.m_gainTwoRtts),
                                                m_rttTimeout(sock.m_rttTimeout)
    {
        NS_LOG_FUNCTION(this);
    }

    const char* const TcpDavis::DavisModeName[DAVIS_GAIN2 + 1] = {
        "DAVIS_DRAIN",
        "DAVIS_GAIN1",
        "DAVIS_GAIN2",
    };

    std::string
    TcpDavis::GetName() const
    {
        return "TcpDavis";
    }

    bool
    TcpDavis::HasCongControl() const
    {
        NS_LOG_FUNCTION(this);
        return true;
    }

    void
    TcpDavis::Init(Ptr<TcpSocketState> tcb [[maybe_unused]])
    {
        NS_LOG_FUNCTION(this << tcb);
        tcb->m_cWnd = m_minCwnd;
        tcb->m_ssThresh = TCP_INFINITE_SSTHRESH;
        
        tcb->m_pacing = false;

        tcb->m_useEcn = TcpSocketState::On;
    }

    uint32_t
    TcpDavis::GetSsThresh(Ptr<const TcpSocketState> tcb, uint32_t bytesInFlight)
    {
        NS_LOG_FUNCTION(this << tcb << bytesInFlight);
        return tcb->m_ssThresh;
    }

    void 
    TcpDavis::CongControl(Ptr<TcpSocketState> tcb,
                     const TcpRateOps::TcpRateConnection& rc,
                     const TcpRateOps::TcpRateSample& rs)
    {
        NS_LOG_FUNCTION(this << tcb << rs);

        if(tcb->m_ecnState == TcpSocketState::ECN_CE_RCVD || tcb->m_congState == TcpSocketState::CA_RECOVERY)
        {
            tcb->m_ssThresh = 0;
        }
        if(rs.m_bytesLoss!=0)
        {
            tcb->m_ssThresh = 0;
        }

        if(tcb->m_cWnd < tcb->m_ssThresh)
        {
            SlowStart(tcb, rc, rs);
        }
        else
        {
            CongestionAvoidance(tcb, rc, rs);
        }
    }

    void
    TcpDavis::CongestionStateSet(Ptr<TcpSocketState> tcb,
                                 const TcpSocketState::TcpCongState_t newState)
    {
        NS_LOG_FUNCTION(this << tcb << newState);
        if(newState == TcpSocketState::CA_LOSS)
        {
            tcb->m_ssThresh = TCP_INFINITE_SSTHRESH;
        }
        else if(newState == TcpSocketState::CA_RECOVERY || newState == TcpSocketState::CA_CWR)
        {
            tcb->m_ssThresh = 0;
        }
    }

    void
    TcpDavis::CwndEvent(Ptr<TcpSocketState> tcb, const TcpSocketState::TcpCAEvent_t event)
    {
        NS_LOG_FUNCTION(this << tcb << event);
        if(event == TcpSocketState::CA_EVENT_LOSS)
        {
            tcb->m_ssThresh = TCP_INFINITE_SSTHRESH;
        }
        else if(event == TcpSocketState::CA_EVENT_ECN_IS_CE)
        {
            tcb->m_ssThresh = 0;
        }
    }

    void
    TcpDavis::SlowStart(Ptr<TcpSocketState> tcb,
                     const TcpRateOps::TcpRateConnection& rc,
                     const TcpRateOps::TcpRateSample& rs)
    {
        if(!m_isInSlowStart)
        {
            m_isInSlowStart = true;

            m_mode = DAVIS_GAIN1;
            m_lastModeChange = Simulator::Now();

            m_bdp = m_minCwnd;
            m_lastBdp = 0;

            tcb->m_cWnd = m_minCwnd;

            m_minRTT = m_lastRTT; // I doubt the correctness of this line because just before last RTT is set to 0, so I doubt if this is correct but as per module this should be.
        }

        if(tcb->m_lastRtt.Get().GetSeconds() < m_minRTT.GetSeconds())
        {
            m_minRTT = tcb->m_lastRtt.Get();
            m_minRttTime = Simulator::Now();
        }

        switch (m_mode)
        {
            case DAVIS_GAIN1:
                if(Simulator::Now() - m_lastModeChange > tcb->m_lastRtt.Get() * m_gainOneRtts)
                {
                    m_deliveredStart = rc.m_delivered;
                    m_deliveredStartTime = Simulator::Now();
                    EnterGain2();
                }
                break;
            case DAVIS_GAIN2:
                if(Simulator::Now() - m_lastModeChange > tcb->m_lastRtt.Get() * m_gainTwoRtts)
                {
                    m_delivered = rc.m_delivered - m_deliveredStart;
                    m_interval = Simulator::Now() - m_deliveredStartTime;

                    if(m_interval.GetSeconds() > 0)
                    {
                        m_lastBdp = m_bdp;
                        uint32_t deliveryRate = m_delivered / m_interval.GetSeconds();
                        m_bdp = deliveryRate * m_minRTT.GetSeconds(); // Check which minRTT variable to use
                        m_gainCwnd = std::max(4U, m_bdp/2);
                    }

                    if(m_bdp <= m_lastBdp)
                    {
                        tcb->m_ssThresh = 0;
                        ExitSlowStart();
                    }
                    else
                    {
                        tcb->m_cWnd = m_bdp + m_gainCwnd;
                        EnterGain1();
                    }
                }
                break;
            case DAVIS_DRAIN:
                NS_LOG_WARN("Slow Start entered DRAIN mode");
                break;
        }
    }

    void
    TcpDavis::ExitSlowStart()
    {
        NS_LOG_FUNCTION(this);
        m_isInSlowStart = false;
        EnterDrain();
    }

    void
    TcpDavis::EnterDrain()
    {
        NS_LOG_FUNCTION(this);
        m_mode = DAVIS_DRAIN;
        m_lastModeChange = Simulator::Now();
    }

    void
    TcpDavis::EnterGain1()
    {
        NS_LOG_FUNCTION(this);
        m_mode = DAVIS_GAIN1;
        m_lastModeChange = Simulator::Now();
    }

    // Some correction required
    void
    TcpDavis::EnterGain2()
    {
        NS_LOG_FUNCTION(this);
        m_mode = DAVIS_GAIN2;
        m_lastModeChange = Simulator::Now();
    }

    void
    TcpDavis::CongestionAvoidance(Ptr<TcpSocketState> tcb,
                     const TcpRateOps::TcpRateConnection& rc,
                     const TcpRateOps::TcpRateSample& rs)
    {
        if(tcb->m_lastRtt.Get().GetSeconds() < m_minRTT.GetSeconds())
        {
            m_minRTT = tcb->m_lastRtt.Get();
            m_minRttTime = Simulator::Now();
        }
        
        Time timeSinceLastModeChange = Simulator::Now() - m_lastModeChange;

        switch (m_mode)
        {
            case DAVIS_DRAIN:
                if(timeSinceLastModeChange > tcb->m_lastRtt.Get() * m_drainRtts) // Check whether m_minRTT is appropriate to use here
                {
                    tcb->m_cWnd = m_bdp + m_gainCwnd;
                    EnterGain1();
                }
                break;
            
            case DAVIS_GAIN1:
                if(timeSinceLastModeChange > tcb->m_lastRtt.Get() * m_gainOneRtts)
                {
                    m_deliveredStart = rc.m_delivered;
                    m_deliveredStartTime = Simulator::Now();
                    EnterGain2();
                }
                break;

            case DAVIS_GAIN2:
                if(timeSinceLastModeChange > tcb->m_lastRtt.Get() * m_gainTwoRtts)
                {
                    m_delivered = rc.m_delivered - m_deliveredStart;
                    m_interval = Simulator::Now() - m_deliveredStartTime;

                    if(m_interval.GetSeconds() > 0)
                    {
                        m_lastBdp = m_bdp;
                        uint32_t deliveryRate = m_delivered / m_interval.GetSeconds();
                        m_bdp = deliveryRate * m_minRTT.GetSeconds(); // Check which minRTT variable to use
                        uint32_t deviation = std::abs((int)m_bdp - (int)m_lastBdp);
                        m_gainCwnd = 4 + std::min(2 * deviation, m_bdp);
                    }

                    if(Simulator::Now() - m_minRTT > m_rttTimeout)
                    {
                        tcb->m_cWnd = 4;
                        m_minRTT = tcb->m_lastRtt;
                        EnterDrain();
                    }
                    else
                    {
                        tcb->m_cWnd = m_bdp + m_gainCwnd;
                        EnterGain1();
                    }
                }
                break;
        }
    }

    Ptr<TcpCongestionOps>
    TcpDavis::Fork()
    {
        return CopyObject<TcpDavis>(this);
    }
}