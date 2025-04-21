#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/queue-disc.h"
#include "ns3/tcp-davis-linux.h"
#include "ns3/traffic-control-helper.h"
#include <fstream>
#include <map>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("TcpDavisLinuxSimulation");

std::ofstream file("data.csv");
std::map<FlowId, uint64_t> previousRxBytes;

std::vector<std::map<FlowId, double>> getMetrics(Ptr<FlowMonitor> flowMonitor, Ptr<Ipv4FlowClassifier> classifier)
{
    std::vector<std::map<FlowId, double>> metrics(10);
    // std::map<FlowId, double> rttMap;

    std::map<FlowId, FlowMonitor::FlowStats> stats = flowMonitor->GetFlowStats();

    for(NodeContainer::Iterator it = NodeList::Begin(); it != NodeList::End(); ++it)
    {
        Ptr<Node> node = *it;

        for(uint32_t j=0; j<node->GetNApplications(); ++j)
        {
            Ptr<Application> app = node->GetApplication(j);
            // NS_LOG_INFO("Application " << j << " type: " << app->GetInstanceTypeId().GetName());
            Ptr<OnOffApplication> sender = DynamicCast<OnOffApplication>(app);

            if(sender)
            {
                // NS_LOG_INFO("Found OnOffApplication on Node " << node->GetId());
                Ptr<Socket> sock = sender->GetSocket();
                // if (!sock)
                // {
                //     NS_LOG_WARN("OnOffApplication has no socket yet!");
                // }
                // else
                // {
                //     NS_LOG_INFO("OnOffApplication socket type: " << sock->GetInstanceTypeId().GetName());
                // }
                Ptr<TcpSocketBase> tcpSocket = DynamicCast<TcpSocketBase>(sock);

                if(tcpSocket)
                {
                    Ptr<const TcpSocketState> state = tcpSocket->GetTcpState();
                    Ptr<const TcpCongestionOps> congContol = tcpSocket->GetCongestionControl();
                    

                    if(state && congContol)
                    {
                        // NS_LOG_INFO("Congestion Control: " << congContol->GetInstanceTypeId().GetName());
                        Ptr<const TcpDavisLinux> davisTcp = DynamicCast<const TcpDavisLinux>(congContol);

                        // if (davisTcp)
                        // {
                        //     NS_LOG_INFO("Successfully cast to TcpDavisLinux");
                        // }
                        // else
                        // {
                        //     NS_LOG_WARN("TcpDavisLinux cast failed!");
                        // }

                        Time lastRtt = state->m_lastRtt.Get();
                        uint32_t cWnd = state->m_cWnd.Get();
                        DataRate pacingRate = state->m_pacingRate.Get();
                        double minRtt;
                        uint32_t bdp;
                        double mode;
                        uint32_t gainCwnd;
                        bool slowStart;
                        uint32_t ssthresh = state->m_ssThresh.Get();
                        uint32_t lastBdp;

                        if(davisTcp)
                        {
                            minRtt = davisTcp->m_minRTT.GetSeconds();
                            bdp = davisTcp->m_bdp;
                            mode = static_cast<double>(davisTcp->m_mode);
                            gainCwnd = davisTcp->m_gainCwnd;
                            slowStart = davisTcp->m_isInSlowStart;
                            lastBdp = davisTcp->m_lastBdp;
                        }
                        
                        for(const auto &flow : stats)
                        {
                            FlowId flowId = flow.first;
                            Ipv4FlowClassifier::FiveTuple tuple = classifier->FindFlow(flowId);

                            if(tuple.sourceAddress == node->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal())
                            {
                                metrics[0][flowId] = lastRtt.GetSeconds();
                                metrics[1][flowId] = cWnd;
                                metrics[2][flowId] = pacingRate.GetBitRate() / 1e6;
                                metrics[3][flowId] = minRtt;
                                metrics[4][flowId] = bdp;
                                metrics[5][flowId] = mode;
                                metrics[6][flowId] = gainCwnd;
                                if(slowStart== true)
                                {
                                    metrics[7][flowId] = 1;
                                }
                                else
                                {
                                    metrics[7][flowId] = 0;
                                }
                                metrics[8][flowId] = ssthresh;
                                metrics[9][flowId] = lastBdp;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    return metrics;
}

std::map<FlowId, uint32_t> calculatePacketLoss(Ptr<FlowMonitor> monitor, Ptr<Ipv4FlowClassifier> classifier)
{
    std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats();
    std::map<FlowId, uint32_t> packetLossMap;

    for (NodeContainer::Iterator it = NodeList::Begin(); it != NodeList::End(); ++it)
    {
        Ptr<Node> node = *it;

        for (uint32_t j = 0; j < node->GetNApplications(); ++j)
        {
            Ptr<Application> app = node->GetApplication(j);
            Ptr<OnOffApplication> sender = DynamicCast<OnOffApplication>(app);

            if (sender) 
            {
                for (const auto &flow : stats)
                {
                    FlowId flowId = flow.first;
                    Ipv4FlowClassifier::FiveTuple tuple = classifier->FindFlow(flowId);

                    if (tuple.sourceAddress == node->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal())
                    {
                        uint32_t txPackets = flow.second.txPackets;
                        uint32_t rxPackets = flow.second.rxPackets;
                        uint32_t packetLoss = txPackets - rxPackets; 

                        packetLossMap[flowId] = packetLoss;
                    }
                }
            }
        }
    }

    return packetLossMap;
}

std::map<FlowId, double> calculateThroughput(Ptr<FlowMonitor> monitor, 
                                             Ptr<Ipv4FlowClassifier> classifier, 
                                             std::map<FlowId, uint64_t> &previousTxBytes)
{
    std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats();
    double interval = 1.0; // Measurement interval in seconds

    std::map<FlowId, double> throughputMap;

    for (NodeContainer::Iterator it = NodeList::Begin(); it != NodeList::End(); ++it)
    {
        Ptr<Node> node = *it;

        for (uint32_t j = 0; j < node->GetNApplications(); ++j)
        {
            Ptr<Application> app = node->GetApplication(j);
            Ptr<OnOffApplication> sender = DynamicCast<OnOffApplication>(app);

            if (sender)
            {
                for (const auto &flow : stats)
                {
                    FlowId flowId = flow.first;
                    Ipv4FlowClassifier::FiveTuple tuple = classifier->FindFlow(flowId);

                    if (tuple.sourceAddress == node->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal())
                    {
                        uint64_t currentTxBytes = flow.second.txBytes;

                        uint64_t prevTxBytes = 0;
                        auto it = previousTxBytes.find(flowId);
                        if (it != previousTxBytes.end())
                        {
                            prevTxBytes = it->second;
                        }

                        double throughput = (currentTxBytes - prevTxBytes) * 8.0 / (interval * 1e3); // KBits per second
                        previousTxBytes[flowId] = currentTxBytes;

                        throughputMap[flowId] = throughput;
                    }
                }
            }
        }
    }

    return throughputMap;
}


void Logger(Ptr<FlowMonitor> monitor, Ptr<Ipv4FlowClassifier> classifier)
{
    static bool headerWritten = false;

    // Write the header only once
    if (!headerWritten)
    {
        file << "FlowId, Time, RTT, Cwnd, Throughput, Loss, GainCwnd, PacingRate, minRTT, bdp, LastBdp, mode, SlowStart, ssThresh \n";
        headerWritten = true;
    }

    std::vector<std::map<FlowId, double>> metrics = getMetrics(monitor, classifier);
    std::map<FlowId, double> throughputMap = calculateThroughput(monitor, classifier, previousRxBytes);
    std::map<FlowId, uint32_t> lossMap = calculatePacketLoss(monitor, classifier);

    double currentTime = Simulator::Now().GetSeconds();

    for (const auto &entry : metrics[0])
    {
        FlowId flowId = entry.first;
        double rtt = metrics[0][flowId];
        double cWnd = metrics[1][flowId];
        double pacingRate = metrics[2][flowId];
        double minRtt = metrics[3][flowId];
        double bdp = metrics[4][flowId];
        double mode = metrics[5][flowId];
        double gainCwnd = metrics[6][flowId];
        uint32_t slwStart = metrics[7][flowId];
        uint32_t ssThresh = metrics[8][flowId];
        uint32_t lastBdp = metrics[9][flowId];

        double throughput = throughputMap.count(flowId) ? throughputMap[flowId] : 0.0;
        uint32_t packetLoss = lossMap.count(flowId) ? lossMap[flowId] : 0;

        file << flowId << ", " << currentTime << ", " << rtt << ", " << cWnd << ", " 
             << throughput << ", " << packetLoss << ", " << gainCwnd << ", " 
             << pacingRate << ", " << minRtt << ", " << bdp << ", " <<lastBdp << ", " << mode << ", " << slwStart << ", " << ssThresh << "\n";
    }

    Simulator::Schedule(Seconds(1), &Logger, monitor, classifier);
}

int main(int argc, char *argv[])
{
    CommandLine cmd;
    cmd.Parse(argc, argv);

    // Logging
    LogComponentEnable("TcpDavisLinux", LOG_LEVEL_INFO);
    LogComponentEnable("TcpDavisLinuxSimulation", LOG_LEVEL_INFO);
    // LogComponentEnable("PacketSink", LOG_LEVEL_ALL);          
    // LogComponentEnable("TcpL4Protocol", LOG_LEVEL_ALL);    
    // LogComponentEnable("TcpSocketBase", LOG_LEVEL_ALL);

    // Set TCP-DAVIS-LINUX as the socket type
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpDavisLinux::GetTypeId()));

    NS_LOG_INFO("Creating nodes...");
    NodeContainer senders, routers, receivers;
    senders.Create(2);
    routers.Create(2);
    receivers.Create(2);

    NS_LOG_INFO("Setting up links...");
    PointToPointHelper link1, link2, btlneck_link, link3, link4;
    link1.SetDeviceAttribute("DataRate", StringValue("2Gbps"));
    link1.SetChannelAttribute("Delay", StringValue("30ms"));
    link2.SetDeviceAttribute("DataRate", StringValue("2Gbps"));
    link2.SetChannelAttribute("Delay", StringValue("60ms"));
    link3.SetDeviceAttribute("DataRate", StringValue("2Gbps"));
    link3.SetChannelAttribute("Delay", StringValue("0ms"));
    link4.SetDeviceAttribute("DataRate", StringValue("2Gbps"));
    link4.SetChannelAttribute("Delay", StringValue("0ms"));
    btlneck_link.SetDeviceAttribute("DataRate", StringValue("1Gbps"));
    btlneck_link.SetChannelAttribute("Delay", StringValue("0ms"));

    NS_LOG_INFO("Installing the links...");
    NetDeviceContainer device1 = link1.Install(senders.Get(0), routers.Get(0));
    NetDeviceContainer device2 = link2.Install(senders.Get(1), routers.Get(0));
    NetDeviceContainer device3 = link3.Install(routers.Get(1), receivers.Get(0));
    NetDeviceContainer device4 = link4.Install(routers.Get(1), receivers.Get(1));
    NetDeviceContainer btlneck_device = btlneck_link.Install(routers.Get(0), routers.Get(1));

    NS_LOG_INFO("Installing Internet stack...");
    InternetStackHelper stack;
    stack.Install(senders);
    stack.Install(routers);
    stack.Install(receivers);

    NS_LOG_INFO("Assigning IP addresses...");
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces1 = ipv4.Assign(device1);
    ipv4.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces2 = ipv4.Assign(device2);
    ipv4.SetBase("10.1.3.0", "255.255.255.0");
    Ipv4InterfaceContainer btlneck_interface = ipv4.Assign(btlneck_device);
    ipv4.SetBase("10.1.4.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces3 = ipv4.Assign(device3);
    ipv4.SetBase("10.1.5.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces4 = ipv4.Assign(device4);

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // Configure FIFO queue at the senders
    TrafficControlHelper tch0;
    tch0.Uninstall(device1);
    tch0.Uninstall(device2);
    tch0.SetRootQueueDisc("ns3::FifoQueueDisc");
    tch0.Install(device1);
    tch0.Install(device2);

    //  Set buffer size as the maximum BDP of all flows
    uint32_t bufferSize = 15000000; // In Bytes
    TrafficControlHelper tch1;
    tch1.Uninstall(btlneck_device);
    tch1.SetRootQueueDisc("ns3::FifoQueueDisc", "MaxSize", QueueSizeValue(QueueSize(QueueSizeUnit::BYTES, bufferSize)));
    tch1.Install(btlneck_device);

    NS_LOG_INFO("Creating applications...");
    uint16_t port0 = 8080;
    uint16_t port1 = 9090;

    // Create two TCP packet sinks to receive data, one at each receiver
    // Flow0
    Address sinkAddress0(InetSocketAddress(interfaces3.GetAddress(1), port0));
    PacketSinkHelper sinkHelper0("ns3::TcpSocketFactory", sinkAddress0);
    ApplicationContainer sinkApp0 = sinkHelper0.Install(receivers.Get(0));
    sinkApp0.Start(Seconds(0.0));
    sinkApp0.Stop(Seconds(60.0));

    // Flow1
    Address sinkAddress1(InetSocketAddress(interfaces4.GetAddress(1), port1));
    PacketSinkHelper sinkHelper1("ns3::TcpSocketFactory", sinkAddress1);
    ApplicationContainer sinkApp1 = sinkHelper1.Install(receivers.Get(1));
    sinkApp1.Start(Seconds(0.0));
    sinkApp1.Stop(Seconds(60.0));

    // Configure the sending applications
    OnOffHelper onoff0("ns3::TcpSocketFactory", sinkAddress0);
    onoff0.SetAttribute("DataRate", StringValue("2Gbps"));
    // onoff0.SetAttribute("PacketSize", UintegerValue(512));
    ApplicationContainer senderApp0 = onoff0.Install(senders.Get(0));
    senderApp0.Start(Seconds(1.0));
    senderApp0.Stop(Seconds(60.0));

    OnOffHelper onoff1("ns3::TcpSocketFactory", sinkAddress1);
    onoff1.SetAttribute("DataRate", StringValue("2Gbps"));
    // onoff1.SetAttribute("PacketSize", UintegerValue(512));
    ApplicationContainer senderApp1 = onoff1.Install(senders.Get(1));
    senderApp1.Start(Seconds(10.0));
    senderApp1.Stop(Seconds(60.0));

    // Flow monitor for logging
    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.InstallAll();

    Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flowmon.GetClassifier());

    Simulator::Schedule(Seconds(2), &Logger, monitor, classifier);

    // Below ones are just for test
    Simulator::Stop(Seconds(60.0));
    Simulator::Run();

    Simulator::Destroy();
    file.close();

    return 0;
}