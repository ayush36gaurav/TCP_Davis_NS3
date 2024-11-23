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

    void TcpDavis::PktsAcked(Ptr<TcpSocketState> tcb, uint32_t segmentsAcked, const Time& rtt)
    {
        NS_LOG_FUNCTION(this << tcb << segmentsAcked << rtt);
        m_packetsDelivered += segmentsAcked;
        m_deliveredMStamp = Simulator::Now();
    }

    void
    TcpDavis::EnterSlowStart(Ptr<TcpSocketState> tcb)
    {
        if(!m_isInitializationDone)
        {
            m_mode = DAVIS_GAIN1;
            m_lastModeChange = Simulator::Now();

            tcb->m_cWnd = m_minCwnd;
            tcb->m_ssThresh = TCP_INFINITE_SSTHRESH;

            m_deliveredStart = m_packetsDelivered;
            m_deliveredStartTime = m_deliveredMStamp;

            m_bdp = m_minCwnd;
            m_lastBdp = 0;
            m_gainCwnd = m_minGainCwnd;

            tcb->m_pacing = false;

            m_lastRTT = Seconds(0); 
            m_minRTT = Time::Max();

            m_minRttTime = Simulator::Now();

            tcb->m_useEcn = TcpSocketState::On;
            
            m_isInitializationDone = true;
        }

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
    }

    void
    TcpDavis::SlowStart(Ptr<TcpSocketState> tcb)
    {
        // uint32_t currentBdp = CalculateBdp(tcb);
        // m_gainCwnd = std::max(4U, currentBdp/2);

        if(tcb->m_minRtt.GetSeconds() < m_minRTT.GetSeconds())
        {
            m_minRTT = tcb->m_minRtt;
            m_minRttTime = Simulator::Now();
        }

        switch (m_mode)
        {
            case DAVIS_GAIN1:
                if(Simulator::Now() - m_lastModeChange > m_minRTT * m_gainOneRtts)
                {
                    m_deliveredStart = m_packetsDelivered;
                    m_deliveredStartTime = m_deliveredMStamp;
                    EnterGain2();
                }
                break;
            case DAVIS_GAIN2:
                if(Simulator::Now() - m_lastModeChange > m_minRTT * m_gainTwoRtts)
                {
                    m_delivered = m_packetsDelivered - m_deliveredStart;
                    m_interval = m_deliveredMStamp - m_deliveredStartTime;

                    if(m_interval.GetSeconds() > 0)
                    {
                        m_lastBdp = m_bdp;
                        uint32_t deliveryRate = m_delivered / m_interval.GetSeconds();
                        m_bdp = deliveryRate * m_minRTT.GetSeconds(); // Check which minRTT variable to use
                        m_gainCwnd = std::max(4U, m_bdp/2);
                    }
                }

                if(m_bdp <= m_lastBdp || tcb->m_congState == TcpSocketState::CA_LOSS || tcb->m_congState == TcpSocketState::ECN_CE_RCVD) // Check if the condition used is correct
                {
                    ExitSlowStart();
                }
                else
                {
                    tcb->m_cWnd = m_bdp + m_gainCwnd;
                    EnterGain1();
                }
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

    uint32_t TcpDavis::CalculateGainCwnd(uint32_t currentBdp, uint32_t lastBdp)
    {
        uint32_t deviation = std::abs((int)currentBdp - (int)lastBdp);
        return 4 + std::min(2 * deviation, currentBdp);
    }

            uint32_t CalculateBdp(Ptr<TcpSocketState> tcb);
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
    TcpDavis::CongestionAvoidance(Ptr<TcpSocketState> tcb)
    {
        if(m_isInSlowStart)
        {
            SlowStart(tcb);
            return;
        }

        if(tcb->m_minRtt.GetSeconds() < m_minRTT.GetSeconds())
        {
            m_minRTT = tcb->m_minRtt;
            m_minRttTime = Simulator::Now();
        }
        
        Time timeSinceLastModeChange = Simulator::Now() - m_lastModeChange;

                    m_delivered = m_packetsDelivered - m_deliveredStart;
                    m_interval = m_deliveredMStamp - m_deliveredStartTime;

                    if(m_interval.GetSeconds() > 0)
                    {
                        m_lastBdp = m_bdp;
                        uint32_t deliveryRate = m_delivered / m_interval.GetSeconds();
                        m_bdp = deliveryRate * m_minRTT.GetSeconds(); // Check which minRTT variable to use
                        m_gainCwnd = std::max(4U, m_bdp/2);
                    }
        // Adjust the factors i.e. multipliers to RTT values
        switch (m_mode)
        {
            case DAVIS_DRAIN:
                if(timeSinceLastModeChange > m_minRTT * m_drainRtts) // Check whether m_minRTT is appropriate to use here
                {
                    tcb->m_cWnd = m_bdp + m_gainCwnd;
                    EnterGain1();
                }
                break;
            
            case DAVIS_GAIN1:
                if(timeSinceLastModeChange > m_minRTT * m_gainOneRtts)
                {
                    m_deliveredStart = m_packetsDelivered;
                    m_deliveredStartTime = m_deliveredMStamp;
                    EnterGain2();
                }
                break;

            case DAVIS_GAIN2:
                if(timeSinceLastModeChange > m_minRTT * m_gainTwoRtts)
                {
                    
                    m_delivered = m_packetsDelivered - m_deliveredStart;
                    m_interval = m_deliveredMStamp - m_deliveredStartTime;

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