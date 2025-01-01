/*
 * Copyright (c) 2024 IIT Mandi
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Authors: Ayush Gaurav <ayush183gaurav@gmail.com>
 *          Sreelakshmi PM <sreelakshmi@iitmandi.ac.in>
 */

#ifndef TCPDAVISLINUX_H
#define TCPDAVISLINUX_H

#include "tcp-congestion-ops.h" // tcp-socket-state and tcp-rate-ops are included in this file
#include "ns3/traced-value.h"
#include "ns3/nstime.h"
#include <limits>
#include <cstdint>

#define MAX_TCP_WINDOW 0xFFFF 
#define DAVIS_ONE 1024

class TcpDavisLinuxCheckGainValuesTest;

namespace ns3
{
    class TcpDavisLinux : public TcpCongestionOps
    {
        public:
            // Get the type ID
            static TypeId GetTypeId();

            // Contructor
            TcpDavisLinux();

            // Copy Constructor
            TcpDavisLinux(const TcpDavisLinux& sock);

            // The modes of Davis
            enum DavisMode_t
            {
                DAVIS_DRAIN,
                DAVIS_STABLE,
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
            friend class TcpDavisLinuxCheckGainValuesTest;

            void SlowStart(Ptr<TcpSocketState> tcb, const TcpRateOps::TcpRateConnection& rc, const TcpRateOps::TcpRateSample& rs);
            void CongestionAvoidance(Ptr<TcpSocketState> tcb, const TcpRateOps::TcpRateConnection& rc, const TcpRateOps::TcpRateSample& rs);
            void EnterDrain();
            void EnterGain1();
            void EnterGain2(); 
            void UpdateGainCwnd();
            void EnterSlowStart(Ptr<TcpSocketState> tcb);
            void ExitSlowStart(Ptr<TcpSocketState> tcb);

        private:
            //  Static variables in the Linux module
            uint32_t m_minCwnd{4};

            uint32_t m_minGainCwnd{4};
            uint32_t m_reactivity{DAVIS_ONE/8};
            uint32_t m_sensitivity{DAVIS_ONE/64};

            uint32_t m_drainRtts{2};
            uint32_t m_stableRttsMin{3};
            uint32_t m_stableRttsMax{6};
            uint32_t m_gainOneRtts{2};
            uint32_t m_gainTwoRtts{1};

            const uint32_t RTT_INF = std::numeric_limits<uint32_t>::max();
            Time m_rttTimeout{Seconds(10)}; // Check if this need to be kept in milliseconds
            

            // Part of the Davis structure
            DavisMode_t m_mode{DAVIS_GAIN1};
            Time m_lastModeChange;
            Time m_minRttTime;
            Time m_deliveredStartTime;

            uint32_t m_deliveredStart; // Keeps the number of packets delivered at the start of the mode

            uint32_t m_bdp;
            uint32_t m_lastBdp;
            uint32_t m_gainCwnd;

            uint32_t m_stableRtts;

            Time m_lastRTT;
            Time m_minRTT; // m_minRtt and m_minlastRtt also there in tcp-socket-state.h

            // Control variables
            const uint32_t TCP_INFINITE_SSTHRESH = std::numeric_limits<uint32_t>::max();
            bool m_isInSlowStart{false};

            uint64_t m_delivered{0}; // Number of packets delivered and it is used to find BDP using the interval
            Time m_interval{Seconds(0)};
    };
}
#endif // TCPDAVIS_H