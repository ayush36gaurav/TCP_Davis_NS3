#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/tcp-davis.h"
#include <fstream>
#include <map>

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("TcpDavisSimulation");

std::ofstream rttFile("rtt-log.txt");
std::ofstream throughputFile("throughput-log.txt");

void RttTracerWithFlowId(uint32_t flowId, Time oldRtt, Time newRtt)
{
    rttFile << Simulator::Now().GetSeconds()
            << "\tFlow " << flowId
            << "\tOld RTT: " << oldRtt.GetMilliSeconds() << " ms"
            << "\tNew RTT: " << newRtt.GetMilliSeconds() << " ms" << std::endl;
}

void ThroughputTracer(Ptr<PacketSink> sink, uint32_t flowId)
{
    static std::map<uint32_t, uint64_t> previousRx;

    uint64_t totalRx = sink->GetTotalRx();
    double throughput = (totalRx - previousRx[flowId]) * 8.0 / 1e6; // Mbps
    previousRx[flowId] = totalRx;

    if (throughputFile.is_open())
    {
        throughputFile << Simulator::Now().GetSeconds() << " " << flowId << " " << throughput << std::endl;
    }

    Simulator::Schedule(Seconds(1.0), &ThroughputTracer, sink, flowId);
}

// Function to send data continuously using a socket
void SendData(Ptr<Socket> socket, uint32_t packetSize, uint32_t maxBytes, uint32_t bytesSent)
{
    if (maxBytes == 0 || bytesSent < maxBytes)
    {
        socket->Send(Create<Packet>(packetSize));
        bytesSent += packetSize;

        // Schedule the next send
        Simulator::Schedule(MilliSeconds(1), &SendData, socket, packetSize, maxBytes, bytesSent);
    }
}

int main(int argc, char *argv[])
{
    CommandLine cmd;
    cmd.Parse(argc, argv);

    // Enable logging
    // LogComponentEnable("TcpDavisSimulation", LOG_LEVEL_INFO);
    // LogComponentEnable("PacketSink", LOG_LEVEL_ALL);          
    // LogComponentEnable("TcpL4Protocol", LOG_LEVEL_ALL);    
    LogComponentEnable("TcpSocketBase", LOG_LEVEL_ALL);
    
    NS_LOG_INFO("Creating nodes...");
    NodeContainer senders, router, receiver;
    senders.Create(2);
    router.Create(1);
    receiver.Create(1);

    NS_LOG_INFO("Setting up links...");
    PointToPointHelper senderToRouterLink0, senderToRouterLink1, routerToReceiverLink;
    senderToRouterLink0.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    senderToRouterLink0.SetChannelAttribute("Delay", StringValue("10ms"));
    senderToRouterLink1.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    senderToRouterLink1.SetChannelAttribute("Delay", StringValue("25ms"));
    routerToReceiverLink.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    routerToReceiverLink.SetChannelAttribute("Delay", StringValue("5ms"));

    NS_LOG_INFO("Installing the links...");
    NetDeviceContainer devices0 = senderToRouterLink0.Install(senders.Get(0), router.Get(0));
    NetDeviceContainer devices1 = senderToRouterLink1.Install(senders.Get(1), router.Get(0));
    NetDeviceContainer bottleneckDevices = routerToReceiverLink.Install(router.Get(0), receiver.Get(0));

    NS_LOG_INFO("Installing Internet stack...");
    InternetStackHelper stack;
    stack.Install(senders);
    stack.Install(router);
    stack.Install(receiver);

    NS_LOG_INFO("Assigning IP addresses...");
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces0 = ipv4.Assign(devices0);
    ipv4.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces1 = ipv4.Assign(devices1);
    ipv4.SetBase("10.1.3.0", "255.255.255.0");
    Ipv4InterfaceContainer bottleneckInterfaces = ipv4.Assign(bottleneckDevices);

    std::cout << "Receiver IP: " << bottleneckInterfaces.GetAddress(1) << std::endl;

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // Set TCP-DAVIS as the socket type
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpDavis::GetTypeId()));
    // Config::SetDefault("ns3::TcpSocket::InitialCwnd", UintegerValue(10));

    // Create and bind packet sink for flow0 at the receiver
    uint16_t port0 = 8080;
    Address sinkAddress0(InetSocketAddress(bottleneckInterfaces.GetAddress(1), port0));
    PacketSinkHelper sinkHelper0("ns3::TcpSocketFactory", sinkAddress0);
    ApplicationContainer sinkApp0 = sinkHelper0.Install(receiver.Get(0));
    sinkApp0.Start(Seconds(0.0));
    sinkApp0.Stop(Seconds(600.0));

    // Create and bind packet sink for flow1 at the receiver
    uint16_t port1 = 8081;
    Address sinkAddress1(InetSocketAddress(bottleneckInterfaces.GetAddress(1), port1));
    PacketSinkHelper sinkHelper1("ns3::TcpSocketFactory", sinkAddress1);
    ApplicationContainer sinkApp1 = sinkHelper1.Install(receiver.Get(0));
    sinkApp1.Start(Seconds(0.0));
    sinkApp1.Stop(Seconds(600.0));

    // Flow 0
    Ptr<Socket> socket0 = Socket::CreateSocket(senders.Get(0), TcpSocketFactory::GetTypeId());
    Simulator::Schedule(Seconds(0.1), &Socket::Connect, socket0, InetSocketAddress(bottleneckInterfaces.GetAddress(1), port0));

    // Flow 1
    Ptr<Socket> socket1 = Socket::CreateSocket(senders.Get(1), TcpSocketFactory::GetTypeId());
    Simulator::Schedule(Seconds(0.1), &Socket::Connect, socket1, InetSocketAddress(bottleneckInterfaces.GetAddress(1), port1));

    // Enable RTT tracing
    AsciiTraceHelper ascii;
    Ptr<OutputStreamWrapper> rttStream = ascii.CreateFileStream("rtt-log.txt");
    socket0->TraceConnectWithoutContext("LastRTT", MakeBoundCallback(&RttTracerWithFlowId, 0));
    socket1->TraceConnectWithoutContext("LastRTT", MakeBoundCallback(&RttTracerWithFlowId, 1));

    // Schedule data sending
    Simulator::Schedule(Seconds(1.0), &SendData, socket0, 1024, 0, 0);
    Simulator::Schedule(Seconds(11.0), &SendData, socket1, 1024, 0, 0);

    // Enable throughput tracing
    Simulator::Schedule(Seconds(1.0), &ThroughputTracer, DynamicCast<PacketSink>(sinkApp0.Get(0)), 0);
    Simulator::Schedule(Seconds(1.0), &ThroughputTracer, DynamicCast<PacketSink>(sinkApp1.Get(0)), 1);

    // Enable flow monitor for throughput and RTT analysis
    FlowMonitorHelper flowMonitor;
    Ptr<FlowMonitor> monitor = flowMonitor.InstallAll();

    Simulator::Stop(Seconds(600.0));
    Simulator::Run();

    monitor->CheckForLostPackets();
    monitor->SerializeToXmlFile("davis-paper-simulation.xml", true, true);

    // Calculate throughput for Flow 0
    Ptr<PacketSink> sink0 = DynamicCast<PacketSink>(sinkApp0.Get(0));
    std::cout << "Flow 0 Throughput: " << (sink0->GetTotalRx() * 8.0) / (600.0 * 1e6) << " Mbps" << std::endl;

    // Calculate throughput for Flow 1
    Ptr<PacketSink> sink1 = DynamicCast<PacketSink>(sinkApp1.Get(0));
    std::cout << "Flow 1 Throughput: " << (sink1->GetTotalRx() * 8.0) / (600.0 * 1e6) << " Mbps" << std::endl;

    // Cleanup
    Simulator::Destroy();
    NS_LOG_INFO("Simulation complete!");
    
    // Close log files
    rttFile.close();
    throughputFile.close();
    std::cout << "RTT log saved to rtt-log.txt" << std::endl;
    std::cout << "Throughput log saved to throughput-log.txt" << std::endl;

    return 0;
}