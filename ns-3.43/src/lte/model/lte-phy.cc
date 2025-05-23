/*
 * Copyright (c) 2010 TELEMATICS LAB, DEE - Politecnico di Bari
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Giuseppe Piro  <g.piro@poliba.it>
 *         Marco Miozzo <mmiozzo@cttc.es>
 */

#include "lte-phy.h"

#include "lte-control-messages.h"
#include "lte-net-device.h"

#include "ns3/spectrum-error-model.h"
#include <ns3/log.h>
#include <ns3/object-factory.h>
#include <ns3/simulator.h>
#include <ns3/waveform-generator.h>

#include <cmath>

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("LtePhy");

NS_OBJECT_ENSURE_REGISTERED(LtePhy);

LtePhy::LtePhy()
{
    NS_LOG_FUNCTION(this);
    NS_FATAL_ERROR("This constructor should not be called");
}

LtePhy::LtePhy(Ptr<LteSpectrumPhy> dlPhy, Ptr<LteSpectrumPhy> ulPhy)
    : m_downlinkSpectrumPhy(dlPhy),
      m_uplinkSpectrumPhy(ulPhy),
      m_tti(0.001),
      m_ulBandwidth(0),
      m_dlBandwidth(0),
      m_rbgSize(0),
      m_dlEarfcn(0),
      m_ulEarfcn(0),
      m_macChTtiDelay(0),
      m_cellId(0),
      m_componentCarrierId(0)
{
    NS_LOG_FUNCTION(this);
}

TypeId
LtePhy::GetTypeId()
{
    static TypeId tid = TypeId("ns3::LtePhy").SetParent<Object>().SetGroupName("Lte");
    return tid;
}

LtePhy::~LtePhy()
{
    NS_LOG_FUNCTION(this);
}

void
LtePhy::DoDispose()
{
    NS_LOG_FUNCTION(this);
    m_packetBurstQueue.clear();
    m_controlMessagesQueue.clear();
    m_downlinkSpectrumPhy->Dispose();
    m_downlinkSpectrumPhy = nullptr;
    m_uplinkSpectrumPhy->Dispose();
    m_uplinkSpectrumPhy = nullptr;
    m_netDevice = nullptr;
    Object::DoDispose();
}

void
LtePhy::SetDevice(Ptr<LteNetDevice> d)
{
    NS_LOG_FUNCTION(this << d);
    m_netDevice = d;
}

Ptr<LteNetDevice>
LtePhy::GetDevice() const
{
    NS_LOG_FUNCTION(this);
    return m_netDevice;
}

Ptr<LteSpectrumPhy>
LtePhy::GetDownlinkSpectrumPhy()
{
    return m_downlinkSpectrumPhy;
}

Ptr<LteSpectrumPhy>
LtePhy::GetUplinkSpectrumPhy()
{
    return m_uplinkSpectrumPhy;
}

void
LtePhy::SetDownlinkChannel(Ptr<SpectrumChannel> c)
{
    NS_LOG_FUNCTION(this << c);
    m_downlinkSpectrumPhy->SetChannel(c);
}

void
LtePhy::SetUplinkChannel(Ptr<SpectrumChannel> c)
{
    NS_LOG_FUNCTION(this << c);
    m_uplinkSpectrumPhy->SetChannel(c);
}

void
LtePhy::SetTti(double tti)
{
    NS_LOG_FUNCTION(this << tti);
    m_tti = tti;
}

double
LtePhy::GetTti() const
{
    NS_LOG_FUNCTION(this << m_tti);
    return m_tti;
}

uint16_t
LtePhy::GetSrsPeriodicity(uint16_t srcCi) const
{
    // from 3GPP TS 36.213 table 8.2-1 UE Specific SRS Periodicity
    uint16_t SrsPeriodicity[9] = {0, 2, 5, 10, 20, 40, 80, 160, 320};
    uint16_t SrsCiLow[9] = {0, 0, 2, 7, 17, 37, 77, 157, 317};
    uint16_t SrsCiHigh[9] = {0, 1, 6, 16, 36, 76, 156, 316, 636};
    uint8_t i;
    for (i = 8; i > 0; i--)
    {
        if ((srcCi >= SrsCiLow[i]) && (srcCi <= SrsCiHigh[i]))
        {
            break;
        }
    }
    return SrsPeriodicity[i];
}

uint16_t
LtePhy::GetSrsSubframeOffset(uint16_t srcCi) const
{
    // from 3GPP TS 36.213 table 8.2-1 UE Specific SRS Periodicity
    uint16_t SrsSubframeOffset[9] = {0, 0, 2, 7, 17, 37, 77, 157, 317};
    uint16_t SrsCiLow[9] = {0, 0, 2, 7, 17, 37, 77, 157, 317};
    uint16_t SrsCiHigh[9] = {0, 1, 6, 16, 36, 76, 156, 316, 636};
    uint8_t i;
    for (i = 8; i > 0; i--)
    {
        if ((srcCi >= SrsCiLow[i]) && (srcCi <= SrsCiHigh[i]))
        {
            break;
        }
    }
    return (srcCi - SrsSubframeOffset[i]);
}

uint8_t
LtePhy::GetRbgSize() const
{
    return m_rbgSize;
}

void
LtePhy::SetMacPdu(Ptr<Packet> p)
{
    m_packetBurstQueue.at(m_packetBurstQueue.size() - 1)->AddPacket(p);
}

Ptr<PacketBurst>
LtePhy::GetPacketBurst()
{
    if (m_packetBurstQueue.at(0)->GetSize() > 0)
    {
        Ptr<PacketBurst> ret = m_packetBurstQueue.at(0)->Copy();
        m_packetBurstQueue.erase(m_packetBurstQueue.begin());
        m_packetBurstQueue.push_back(CreateObject<PacketBurst>());
        return ret;
    }
    else
    {
        m_packetBurstQueue.erase(m_packetBurstQueue.begin());
        m_packetBurstQueue.push_back(CreateObject<PacketBurst>());
        return nullptr;
    }
}

void
LtePhy::SetControlMessages(Ptr<LteControlMessage> m)
{
    // In uplink the queue of control messages and packet are of different sizes
    // for avoiding TTI cancellation due to synchronization of subframe triggers
    m_controlMessagesQueue.at(m_controlMessagesQueue.size() - 1).push_back(m);
}

std::list<Ptr<LteControlMessage>>
LtePhy::GetControlMessages()
{
    NS_LOG_FUNCTION(this);
    if (!m_controlMessagesQueue.at(0).empty())
    {
        std::list<Ptr<LteControlMessage>> ret = m_controlMessagesQueue.at(0);
        m_controlMessagesQueue.erase(m_controlMessagesQueue.begin());
        std::list<Ptr<LteControlMessage>> newlist;
        m_controlMessagesQueue.push_back(newlist);
        return ret;
    }
    else
    {
        m_controlMessagesQueue.erase(m_controlMessagesQueue.begin());
        std::list<Ptr<LteControlMessage>> newlist;
        m_controlMessagesQueue.push_back(newlist);
        std::list<Ptr<LteControlMessage>> emptylist;
        return emptylist;
    }
}

void
LtePhy::DoSetCellId(uint16_t cellId)
{
    m_cellId = cellId;
    m_downlinkSpectrumPhy->SetCellId(cellId);
    m_uplinkSpectrumPhy->SetCellId(cellId);
}

void
LtePhy::SetComponentCarrierId(uint8_t index)
{
    m_componentCarrierId = index;
    m_downlinkSpectrumPhy->SetComponentCarrierId(index);
    m_uplinkSpectrumPhy->SetComponentCarrierId(index);
}

uint8_t
LtePhy::GetComponentCarrierId() const
{
    return m_componentCarrierId;
}

} // namespace ns3
