/*
 * Copyright (c) 2004 Francisco J. Ros
 * Copyright (c) 2007 INESC Porto
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Authors: Francisco J. Ros  <fjrm@dif.um.es>
 *          Gustavo J. A. M. Carneiro <gjc@inescporto.pt>
 */

#ifndef OLSR_STATE_H
#define OLSR_STATE_H

#include "olsr-repositories.h"

namespace ns3
{
namespace olsr
{

/// \ingroup olsr
/// This class encapsulates all data structures needed for maintaining internal state of an OLSR
/// node.
class OlsrState
{
    //  friend class Olsr;

  protected:
    LinkSet m_linkSet;                     //!< Link Set (\RFC{3626}, section 4.2.1).
    NeighborSet m_neighborSet;             //!< Neighbor Set (\RFC{3626}, section 4.3.1).
    TwoHopNeighborSet m_twoHopNeighborSet; //!< 2-hop Neighbor Set (\RFC{3626}, section 4.3.2).
    TopologySet m_topologySet;             //!< Topology Set (\RFC{3626}, section 4.4).
    MprSet m_mprSet;                       //!< MPR Set (\RFC{3626}, section 4.3.3).
    MprSelectorSet m_mprSelectorSet;       //!< MPR Selector Set (\RFC{3626}, section 4.3.4).
    DuplicateSet m_duplicateSet;           //!< Duplicate Set (\RFC{3626}, section 3.4).
    IfaceAssocSet m_ifaceAssocSet;         //!< Interface Association Set (\RFC{3626}, section 4.1).
    AssociationSet m_associationSet; //!< Association Set (\RFC{3626}, section12.2). Associations
                                     //!< obtained from HNA messages generated by other nodes.
    Associations m_associations;     //!< The node's local Host Network Associations that will be
                                     //!< advertised using HNA messages.

  public:
    OlsrState()
    {
    }

    // MPR selector

    /**
     * Gets the MPR selectors.
     * \returns The MPR selectors.
     */
    const MprSelectorSet& GetMprSelectors() const
    {
        return m_mprSelectorSet;
    }

    /**
     * Finds a MPR selector tuple.
     * \param mainAddr The MPR selector main address.
     * \returns The MPR selector, if found. Else it returns a null pointer.
     */
    MprSelectorTuple* FindMprSelectorTuple(const Ipv4Address& mainAddr);

    /**
     * Erases a MPR selector tuple.
     * \param tuple The MPR selector tuple.
     */
    void EraseMprSelectorTuple(const MprSelectorTuple& tuple);

    /**
     * Erases all MPR selector tuples belonging to the same address.
     * \param mainAddr The MPR selector main address.
     */
    void EraseMprSelectorTuples(const Ipv4Address& mainAddr);

    /**
     * Inserts a MPR selector tuple
     * \param tuple The MPR selector tuple.
     */
    void InsertMprSelectorTuple(const MprSelectorTuple& tuple);

    /**
     * Prints the MPR selector sets.
     * \return a string with the output data.
     */
    std::string PrintMprSelectorSet() const;

    // Neighbor

    /**
     * Gets the neighbor set.
     * \returns The neighbor set.
     */
    const NeighborSet& GetNeighbors() const
    {
        return m_neighborSet;
    }

    /**
     * Gets the neighbor set.
     * \returns The neighbor set.
     */
    NeighborSet& GetNeighbors()
    {
        return m_neighborSet;
    }

    /**
     * Finds a neighbor tuple.
     * \param mainAddr The neighbor tuple main address.
     * \returns The neighbor tuple, if found. Else it returns a null pointer.
     */
    NeighborTuple* FindNeighborTuple(const Ipv4Address& mainAddr);

    /**
     * Finds a symmetrical neighbor tuple.
     * \param mainAddr The neighbor tuple main address.
     * \returns The neighbor tuple, if found. Else it returns a null pointer.
     */
    const NeighborTuple* FindSymNeighborTuple(const Ipv4Address& mainAddr) const;

    /**
     * Finds a neighbor tuple.
     * \param mainAddr The neighbor tuple main address.
     * \param willingness The neighbor willingness.
     * \returns The neighbor tuple, if found. Else it returns a null pointer.
     */
    NeighborTuple* FindNeighborTuple(const Ipv4Address& mainAddr, Willingness willingness);

    /**
     * Erases a neighbor tuple.
     * \param neighborTuple The neighbor tuple.
     */
    void EraseNeighborTuple(const NeighborTuple& neighborTuple);
    /**
     * Erases a neighbor tuple.
     * \param mainAddr The neighbor tuple main address.
     */
    void EraseNeighborTuple(const Ipv4Address& mainAddr);

    /**
     * Inserts a neighbor tuple.
     * \param tuple The neighbor tuple.
     */
    void InsertNeighborTuple(const NeighborTuple& tuple);

    // Two-hop neighbor

    /**
     * Gets the 2-hop neighbor set.
     * \returns The 2-hop neighbor set.
     */
    const TwoHopNeighborSet& GetTwoHopNeighbors() const
    {
        return m_twoHopNeighborSet;
    }

    /**
     * Gets the 2-hop neighbor set.
     * \returns The 2-hop neighbor set.
     */
    TwoHopNeighborSet& GetTwoHopNeighbors()
    {
        return m_twoHopNeighborSet;
    }

    /**
     * Finds a 2-hop neighbor tuple.
     * \param neighbor The neighbor main address.
     * \param twoHopNeighbor The 2-hop neighbor main address.
     * \returns The 2-hop neighbor tuple, if found. Else it returns a null pointer.
     */
    TwoHopNeighborTuple* FindTwoHopNeighborTuple(const Ipv4Address& neighbor,
                                                 const Ipv4Address& twoHopNeighbor);

    /**
     * Erases a 2-hop neighbor tuple.
     * \param tuple The 2-hop neighbor tuple.
     */
    void EraseTwoHopNeighborTuple(const TwoHopNeighborTuple& tuple);
    /**
     * Erases the 2-hop neighbor tuples with the same 1-hop neighbor.
     * \param neighbor The neighbor address.
     */
    void EraseTwoHopNeighborTuples(const Ipv4Address& neighbor);
    /**
     * Erases the 2-hop neighbor tuples with matching predicates.
     * \param neighbor The neighbor address.
     * \param twoHopNeighbor The 2-hop neighbor main address.
     */
    void EraseTwoHopNeighborTuples(const Ipv4Address& neighbor, const Ipv4Address& twoHopNeighbor);
    /**
     * Inserts a 2-hop neighbor tuple.
     * \param tuple The 2-hop neighbor tuple.
     */
    void InsertTwoHopNeighborTuple(const TwoHopNeighborTuple& tuple);

    // MPR

    /**
     * Checks if there's an MPR with a specific address.
     * \param address The address to test.
     * \return True if a MPR with the specified address exists.
     */
    bool FindMprAddress(const Ipv4Address& address);

    /**
     * Sets the MPR set to the one specified.
     * \param mprSet The new MPR set.
     */
    void SetMprSet(MprSet mprSet);

    /**
     * Gets the MPR set.
     * \return The MPR set.
     */
    MprSet GetMprSet() const;

    // Duplicate

    /**
     * Finds a duplicate tuple.
     * \param address The duplicate tuple address.
     * \param sequenceNumber The duplicate tuple sequence number.
     * \returns The duplicate tuple, or a null pointer if no match.
     */
    DuplicateTuple* FindDuplicateTuple(const Ipv4Address& address, uint16_t sequenceNumber);

    /**
     * Erases a duplicate tuple.
     * \param tuple The tuple to erase.
     */
    void EraseDuplicateTuple(const DuplicateTuple& tuple);
    /**
     * Inserts a duplicate tuple.
     * \param tuple The tuple to insert.
     */
    void InsertDuplicateTuple(const DuplicateTuple& tuple);

    // Link

    /**
     * Gets the Link set.
     * \return The Link set.
     */
    const LinkSet& GetLinks() const
    {
        return m_linkSet;
    }

    /**
     * Finds a link tuple.
     * \param ifaceAddr The interface address of the link.
     * \returns The link tuple, or a null pointer if no match.
     */
    LinkTuple* FindLinkTuple(const Ipv4Address& ifaceAddr);
    /**
     * Finds a symmetrical link tuple.
     * \param ifaceAddr The interface address of the link.
     * \param time The time at which the link should be considered symmetrical.
     * \returns The link tuple, or a null pointer if no match.
     */
    LinkTuple* FindSymLinkTuple(const Ipv4Address& ifaceAddr, Time time);
    /**
     * Erases a link tuple.
     * \param tuple The tuple to erase.
     */
    void EraseLinkTuple(const LinkTuple& tuple);
    /**
     * Inserts a link tuple.
     * \param tuple The tuple to insert.
     * \returns A reference to the inserted tuple.
     */
    LinkTuple& InsertLinkTuple(const LinkTuple& tuple);

    // Topology

    /**
     * Gets the topology set.
     * \returns The topology set.
     */
    const TopologySet& GetTopologySet() const
    {
        return m_topologySet;
    }

    /**
     * Finds a topology tuple.
     * \param destAddr The destination address.
     * \param lastAddr The address of the node previous to the destination.
     * \returns The topology tuple, or a null pointer if no match.
     */
    TopologyTuple* FindTopologyTuple(const Ipv4Address& destAddr, const Ipv4Address& lastAddr);
    /**
     * Finds a topology tuple.
     * \param lastAddr The address of the node previous to the destination.
     * \param ansn The Advertised Neighbor Sequence Number.
     * \returns The topology tuple, or a null pointer if no match.
     */
    TopologyTuple* FindNewerTopologyTuple(const Ipv4Address& lastAddr, uint16_t ansn);
    /**
     * Erases a topology tuple.
     * \param tuple The tuple to erase.
     */
    void EraseTopologyTuple(const TopologyTuple& tuple);
    /**
     * Erases a topology tuple.
     * \param lastAddr The address of the node previous to the destination.
     * \param ansn The Advertised Neighbor Sequence Number.
     */
    void EraseOlderTopologyTuples(const Ipv4Address& lastAddr, uint16_t ansn);
    /**
     * Inserts a topology tuple.
     * \param tuple The tuple to insert.
     */
    void InsertTopologyTuple(const TopologyTuple& tuple);

    // Interface association

    /**
     * Gets the interface association set.
     * \returns The interface association set.
     */
    const IfaceAssocSet& GetIfaceAssocSet() const
    {
        return m_ifaceAssocSet;
    }

    /**
     * Gets a mutable reference to the interface association set.
     * \returns The interface association set.
     */
    IfaceAssocSet& GetIfaceAssocSetMutable()
    {
        return m_ifaceAssocSet;
    }

    /**
     * Finds a interface association tuple.
     * \param ifaceAddr The interface address.
     * \returns The interface association  tuple, or a null pointer if no match.
     */
    IfaceAssocTuple* FindIfaceAssocTuple(const Ipv4Address& ifaceAddr);
    /**
     * Finds a interface association tuple.
     * \param ifaceAddr The interface address.
     * \returns The interface association  tuple, or a null pointer if no match.
     */
    const IfaceAssocTuple* FindIfaceAssocTuple(const Ipv4Address& ifaceAddr) const;
    /**
     * Erases a interface association tuple.
     * \param tuple The tuple to erase.
     */
    void EraseIfaceAssocTuple(const IfaceAssocTuple& tuple);
    /**
     * Inserts a interface association tuple.
     * \param tuple The tuple to insert.
     */
    void InsertIfaceAssocTuple(const IfaceAssocTuple& tuple);

    // Host-Network Association
    /**
     * Gets the association set known to the node.
     * \returns The association set known to the node.
     */
    const AssociationSet& GetAssociationSet() const // Associations known to the node
    {
        return m_associationSet;
    }

    /**
     * Gets the association set the node has.
     * \returns The association set the node has.
     */
    const Associations& GetAssociations() const // Set of associations that the node has
    {
        return m_associations;
    }

    /**
     * Finds an association tuple.
     * \param gatewayAddr The gateway address.
     * \param networkAddr The network address.
     * \param netmask The network mask.
     * \returns The association  tuple, or a null pointer if no match.
     */
    AssociationTuple* FindAssociationTuple(const Ipv4Address& gatewayAddr,
                                           const Ipv4Address& networkAddr,
                                           const Ipv4Mask& netmask);
    /**
     * Erases a known association tuple.
     * \param tuple The tuple to erase.
     */
    void EraseAssociationTuple(const AssociationTuple& tuple);
    /**
     * Inserts a known association tuple.
     * \param tuple The tuple to insert.
     */
    void InsertAssociationTuple(const AssociationTuple& tuple);
    /**
     * Erases an association.
     * \param tuple The tuple to erase.
     */
    void EraseAssociation(const Association& tuple);
    /**
     * Inserts an association tuple.
     * \param tuple The tuple to insert.
     */
    void InsertAssociation(const Association& tuple);

    /**
     * Returns a vector of all interfaces of a given neighbor, with the
     * exception of the "main" one.
     * \param neighborMainAddr The neighbor main address
     * \returns A container of the neighbor addresses (excluding the main one).
     */
    std::vector<Ipv4Address> FindNeighborInterfaces(const Ipv4Address& neighborMainAddr) const;
};

} // namespace olsr
} // namespace ns3

#endif /* OLSR_STATE_H */