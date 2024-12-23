/*
 * Copyright (c) 2024 IIT Mandi
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Authors: Ayush Gaurav <ayush183gaurav@gmail.com>
 *          Sreelakshmi PM <sreelakshmi@iitmandi.ac.in>
 */

#ifndef TCPDAVIS_H
#define TCPDAVIS_H

#include "tcp-congestion-ops.h" // tcp-socket-state and tcp-rate-ops are included in this file
#include "ns3/traced-value.h"
#include "ns3/nstime.h"
#include <limits>

class TcpDavisCheckGainValuesTest;

namespace ns3
{
    class TcpDavis : public TcpCongestionOps
    {
        public:
            // Get the type ID
            static TypeId GetTypeId();

            // Contructor
            TcpDavis();

            // Copy Constructor
            TcpDavis(const TcpDavis& sock);

            // The modes of Davis
            enum DavisMode_t
            {
                DAVIS_DRAIN,
                DAVIS_GAIN1,
                DAVIS_GAIN2,
            };

            static const char* const DavisModeName[DAVIS_GAIN2 + 1];

            // Functions from the TcpCongestionOps
            std::string GetName() const override;
            void Init(Ptr<TcpSocketState> tcb [[maybe_unused]]) override;
            uint32_t GetSsThresh(Ptr<const TcpSocketState> tcb, uint32_t bytesInFlight) override;
            void CongestionStateSet(Ptr<TcpSocketState> tcb, const TcpSocketState::TcpCongState_t newState) override;
            void CwndEvent(Ptr<TcpSocketState> tcb, const TcpSocketState::TcpCAEvent_t event) override;
            bool HasCongControl() const override;
            void CongControl(Ptr<TcpSocketState> tcb, const TcpRateOps::TcpRateConnection& rc, const TcpRateOps::TcpRateSample& rs) override;
            Ptr<TcpCongestionOps> Fork() override;
            // Only two functions increaseWindow and PktsAcked are not overridden here

        protected:
            // Make the test class as friend
            friend class TcpDavisCheckGainValuesTest;

            void SlowStart(Ptr<TcpSocketState> tcb, const TcpRateOps::TcpRateConnection& rc, const TcpRateOps::TcpRateSample& rs);
            void CongestionAvoidance(Ptr<TcpSocketState> tcb, const TcpRateOps::TcpRateConnection& rc, const TcpRateOps::TcpRateSample& rs);
            void EnterDrain();
            void EnterGain1();
            void EnterGain2(); 
            void ExitSlowStart();

        private:
            //  Static variables in the Linux module
            uint8_t m_minCwnd{4};
            // uint8_t m_minGainCwnd{4};
            uint8_t m_drainRtts{2};
            uint8_t m_gainOneRtts{2};
            uint8_t m_gainTwoRtts{1};
            Time m_rttTimeout{Seconds(10)}; 
            

            // Part of the Davis structure
            DavisMode_t m_mode{DAVIS_GAIN1};
            Time m_lastModeChange;
            Time m_minRttTime;
            Time m_deliveredStartTime;

            uint64_t m_deliveredStart{0}; // Keeps the number of packets delivered at the start of the mode

            uint32_t m_bdp{4};
            uint32_t m_lastBdp{0};
            uint32_t m_gainCwnd{4};

            Time m_minRTT{Time::Max()}; // m_minRtt and m_minlastRtt also there in tcp-socket-state.h
            // Time m_lastRTT{Seconds(0)};

            // Control variables
            const uint32_t TCP_INFINITE_SSTHRESH = std::numeric_limits<uint32_t>::max();
            bool m_isInSlowStart{true};

            uint64_t m_delivered{0}; // Number of packets delivered and it is used to find BDP using the interval
            Time m_interval{Seconds(0)};
    };
}
#endif // TCPDAVIS_H