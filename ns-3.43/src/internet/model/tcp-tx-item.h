/*
 * Copyright (c) 2018 Natale Patriciello <natale.patriciello@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 */
#ifndef TCP_TX_ITEM_H
#define TCP_TX_ITEM_H

#include "ns3/nstime.h"
#include "ns3/packet.h"
#include "ns3/sequence-number.h"

namespace ns3
{
/**
 * \ingroup tcp
 *
 * \brief Item that encloses the application packet and some flags for it
 */
class TcpTxItem
{
  public:
    // Default constructor, copy-constructor, destructor

    /**
     * \brief Print the time
     * \param os ostream
     * \param unit Time::Unit
     */
    void Print(std::ostream& os, Time::Unit unit = Time::S) const;

    /**
     * \brief Get the size in the sequence number space
     *
     * \return 1 if the packet size is 0 or there's no packet, otherwise the size of the packet
     */
    uint32_t GetSeqSize() const;

    /**
     * \brief Is the item sacked?
     * \return true if the item is sacked, false otherwise
     */
    bool IsSacked() const;

    /**
     * \brief Is the item retransmitted?
     * \return true if the item have been retransmitted
     */
    bool IsRetrans() const;

    /**
     * \brief Get a copy of the Packet underlying this item
     * \return a copy of the Packet
     */
    Ptr<Packet> GetPacketCopy() const;

    /**
     * \brief Get the Packet underlying this item
     * \return a pointer to a const Packet
     */
    Ptr<const Packet> GetPacket() const;

    /**
     * \brief Get a reference to the time the packet was sent for the last time
     * \return a reference to the last sent time
     */
    const Time& GetLastSent() const;

    /**
     * \brief Various rate-related information, can be accessed by TcpRateOps.
     *
     * Note: This is not enforced through C++, but you developer must honour
     * this description.
     */
    struct RateInformation
    {
        uint64_t m_delivered{0}; //!< Connection's delivered data at the time the packet was sent
        Time m_deliveredTime{
            Time::Max()}; //!< Connection's delivered time at the time the packet was sent
        Time m_firstSent{
            Time::Max()}; //!< Connection's first sent time at the time the packet was sent
        bool m_isAppLimited{false}; //!< Connection's app limited at the time the packet was sent
    };

    /**
     * \brief Get (to modify) the Rate Information of this item
     *
     * \return A reference to the rate information.
     */
    RateInformation& GetRateInformation();

    bool m_retrans{false}; //!< Indicates if the segment is retransmitted

  private:
    // Only TcpTxBuffer is allowed to touch this part of the TcpTxItem, to manage
    // its internal lists and counters
    friend class TcpTxBuffer;

    SequenceNumber32 m_startSeq{0}; //!< Sequence number of the item (if transmitted)
    Ptr<Packet> m_packet{nullptr};  //!< Application packet (can be null)
    bool m_lost{false};             //!< Indicates if the segment has been lost (RTO)
    Time m_lastSent{
        Time::Max()};     //!< Timestamp of the time at which the segment has been sent last time
    bool m_sacked{false}; //!< Indicates if the segment has been SACKed

    RateInformation m_rateInfo; //!< Rate information of the item
};

} // namespace ns3

#endif /* TCP_TX_ITEM_H */
