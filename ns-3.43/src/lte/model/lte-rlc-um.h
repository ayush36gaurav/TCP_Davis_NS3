/*
 * Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Manuel Requena <manuel.requena@cttc.es>
 */

#ifndef LTE_RLC_UM_H
#define LTE_RLC_UM_H

#include "lte-rlc-sequence-number.h"
#include "lte-rlc.h"

#include <ns3/event-id.h>

#include <deque>
#include <map>

namespace ns3
{

/**
 * LTE RLC Unacknowledged Mode (UM), see 3GPP TS 36.322
 */
class LteRlcUm : public LteRlc
{
  public:
    LteRlcUm();
    ~LteRlcUm() override;
    /**
     * \brief Get the type ID.
     * \return the object TypeId
     */
    static TypeId GetTypeId();
    void DoDispose() override;

    /**
     * RLC SAP
     *
     * \param p packet
     */
    void DoTransmitPdcpPdu(Ptr<Packet> p) override;

    /**
     * MAC SAP
     *
     * \param txOpParams the LteMacSapUser::TxOpportunityParameters
     */
    void DoNotifyTxOpportunity(LteMacSapUser::TxOpportunityParameters txOpParams) override;
    void DoNotifyHarqDeliveryFailure() override;
    void DoReceivePdu(LteMacSapUser::ReceivePduParameters rxPduParams) override;

  private:
    /// Expire reordering timer
    void ExpireReorderingTimer();
    /// Expire RBS timer
    void ExpireRbsTimer();

    /**
     * Is inside reordering window function
     *
     * \param seqNumber the sequence number
     * \returns true if inside the window
     */
    bool IsInsideReorderingWindow(SequenceNumber10 seqNumber);

    /// Reassemble outside window
    void ReassembleOutsideWindow();
    /**
     * Reassemble SN interval function
     *
     * \param lowSeqNumber the low sequence number
     * \param highSeqNumber the high sequence number
     */
    void ReassembleSnInterval(SequenceNumber10 lowSeqNumber, SequenceNumber10 highSeqNumber);

    /**
     * Reassemble and deliver function
     *
     * \param packet the packet
     */
    void ReassembleAndDeliver(Ptr<Packet> packet);

    /// Report buffer status
    void DoReportBufferStatus();

  private:
    uint32_t m_maxTxBufferSize; ///< maximum transmit buffer status
    uint32_t m_txBufferSize;    ///< transmit buffer size

    /**
     * \brief Store an incoming (from layer above us) PDU, waiting to transmit it
     */
    struct TxPdu
    {
        /**
         * \brief TxPdu default constructor
         * \param pdu the PDU
         * \param time the arrival time
         */
        TxPdu(const Ptr<Packet>& pdu, const Time& time)
            : m_pdu(pdu),
              m_waitingSince(time)
        {
        }

        TxPdu() = delete;

        Ptr<Packet> m_pdu;   ///< PDU
        Time m_waitingSince; ///< Layer arrival time
    };

    std::deque<TxPdu> m_txBuffer;               ///< Transmission buffer
    std::map<uint16_t, Ptr<Packet>> m_rxBuffer; ///< Reception buffer
    std::vector<Ptr<Packet>> m_reasBuffer;      ///< Reassembling buffer

    std::list<Ptr<Packet>> m_sdusBuffer; ///< List of SDUs in a packet

    /**
     * State variables. See section 7.1 in TS 36.322
     */
    SequenceNumber10 m_sequenceNumber; ///< VT(US)

    SequenceNumber10 m_vrUr; ///< VR(UR)
    SequenceNumber10 m_vrUx; ///< VR(UX)
    SequenceNumber10 m_vrUh; ///< VR(UH)

    /**
     * Constants. See section 7.2 in TS 36.322
     */
    uint16_t m_windowSize; ///< windows size

    /**
     * Timers. See section 7.3 in TS 36.322
     */
    Time m_reorderingTimerValue;        ///< reordering timer value
    EventId m_reorderingTimer;          ///< reordering timer
    EventId m_rbsTimer;                 ///< RBS timer
    bool m_enablePdcpDiscarding{false}; //!< whether to use the PDCP discarding (perform discarding
                                        //!< at the moment of passing the PDCP SDU to RLC)
    uint32_t m_discardTimerMs{0};       //!< the discard timer value in milliseconds

    /**
     * Reassembling state
     */
    enum ReassemblingState_t
    {
        NONE = 0,
        WAITING_S0_FULL = 1,
        WAITING_SI_SF = 2
    };

    ReassemblingState_t m_reassemblingState; ///< reassembling state
    Ptr<Packet> m_keepS0;                    ///< keep S0

    /**
     * Expected Sequence Number
     */
    SequenceNumber10 m_expectedSeqNumber;
};

} // namespace ns3

#endif // LTE_RLC_UM_H