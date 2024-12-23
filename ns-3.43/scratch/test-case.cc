#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/tcp-davis.h"
#include <fstream>
// #include "ns3/queue-disc.h"
// #include "ns3/traffic-control-helper.h"
using namespace ns3;

NS_LOG_COMPONENT_DEFINE("TcpDavisSimulation");
std::ofstream throughputLog("throughput-log.txt");
std::ofstream rttLog("rtt-log.txt");

void LogLastRtt(Ptr<OutputStreamWrapper> stream, std::string context, Time newRtt)
{
    std::size_t nodeStart = context.find("NodeList/") + 9;
    std::size_t nodeEnd = context.find("/", nodeStart);
    std::string nodeId = context.substr(nodeStart, nodeEnd - nodeStart);

    *stream->GetStream() << Simulator::Now().GetSeconds() << " Node: " << nodeId << " RTT: " << newRtt.GetMilliSeconds() << "\n";
}

void CalculateThroughput(Ptr<FlowMonitor> flowMonitor, FlowMonitorHelper &flowHelper, double interval, double &time, std::map<FlowId, uint64_t> &lastRxBytes)
{
    flowMonitor->CheckForLostPackets();
    std::map<FlowId, FlowMonitor::FlowStats> stats = flowMonitor->GetFlowStats();
    // Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flowHelper.GetClassifier());

    for(auto it = stats.begin(); it!=stats.end(); ++it)
    {
        FlowId flowId = it->first;
        FlowMonitor::FlowStats flowStats = it->second;
        // Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(flowId);

        uint64_t currentRxBytes = flowStats.rxBytes;
        double throughput = 0.0;
        // std::cout<< flowStats.timeLastRxPacket.GetSeconds() << " " << time << std::endl;
        // if (flowStats.timeLastRxPacket.GetSeconds() > time)
        // {
            // throughput = (flowStats.rxBytes * 8.0) /
            //              (flowStats.timeLastRxPacket.GetSeconds() - flowStats.timeFirstTxPacket.GetSeconds()) /
            //              1e6;
        // }
        if(lastRxBytes.find(flowId) != lastRxBytes.end())
        {
            throughput = ((currentRxBytes - lastRxBytes[flowId]) * 8.0) / (interval * 1e6);
        }

        lastRxBytes[flowId] = currentRxBytes;

        throughputLog << static_cast<int>(time) << " " << flowId - 1 << " " << throughput << "\n";
    }

    time += interval;
    Simulator::Schedule(Seconds(interval), &CalculateThroughput, flowMonitor, std::ref(flowHelper), interval, std::ref(time), std::ref(lastRxBytes));
}


int main(int argc, char *argv[])
{
    CommandLine cmd;
    cmd.Parse(argc, argv);

    // Logging
    // LogComponentEnable("TcpDavis", LOG_LEVEL_INFO);
    LogComponentEnable("TcpDavisSimulation", LOG_LEVEL_INFO);
    // LogComponentEnable("PacketSink", LOG_LEVEL_ALL);          
    // LogComponentEnable("TcpL4Protocol", LOG_LEVEL_ALL);    
    // LogComponentEnable("TcpSocketBase", LOG_LEVEL_ALL);

    NS_LOG_INFO("Creating nodes...");
    NodeContainer senders, routers, receivers;
    senders.Create(2);
    routers.Create(2);
    receivers.Create(2);

    NS_LOG_INFO("Setting up links...");
    PointToPointHelper link1, link2, btlneck_link, link3, link4;
    link1.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    link1.SetChannelAttribute("Delay", StringValue("5ms"));
    link2.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    link2.SetChannelAttribute("Delay", StringValue("10ms"));
    link3.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    link3.SetChannelAttribute("Delay", StringValue("5ms"));
    link4.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    link4.SetChannelAttribute("Delay", StringValue("15ms"));
    btlneck_link.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    btlneck_link.SetChannelAttribute("Delay", StringValue("5ms"));

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

    // Set TCP-DAVIS as the socket type
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpDavis::GetTypeId()));

    NS_LOG_INFO("Creating applications...");
    uint16_t port0 = 8080;
    uint16_t port1 = 9090;

    // Flow0
    Address sinkAddress0(InetSocketAddress(interfaces3.GetAddress(1), port0));
    PacketSinkHelper sinkHelper0("ns3::TcpSocketFactory", sinkAddress0);
    ApplicationContainer sinkApp0 = sinkHelper0.Install(receivers.Get(0));
    sinkApp0.Start(Seconds(0.0));
    sinkApp0.Stop(Seconds(600.0));

    BulkSendHelper sourceHelper0("ns3::TcpSocketFactory", sinkAddress0);
    sourceHelper0.SetAttribute("MaxBytes", UintegerValue(0));
    ApplicationContainer sourceApp0 = sourceHelper0.Install(senders.Get(0));
    sourceApp0.Start(Seconds(0.0));
    sourceApp0.Stop(Seconds(600.0));

    // Flow1
    Address sinkAddress1(InetSocketAddress(interfaces4.GetAddress(1), port1));
    PacketSinkHelper sinkHelper1("ns3::TcpSocketFactory", sinkAddress1);
    ApplicationContainer sinkApp1 = sinkHelper1.Install(receivers.Get(1));
    sinkApp1.Start(Seconds(0.0));
    sinkApp1.Stop(Seconds(600.0));

    BulkSendHelper sourceHelper1("ns3::TcpSocketFactory", sinkAddress1);
    sourceHelper1.SetAttribute("MaxBytes", UintegerValue(0));
    ApplicationContainer sourceApp1 = sourceHelper1.Install(senders.Get(1));
    sourceApp1.Start(Seconds(10.0));
    sourceApp1.Stop(Seconds(600.0));

    // AsciiTraceHelper ascii;
    // Ptr<OutputStreamWrapper> rttStream = ascii.CreateFileStream("rtt-log.txt");
    // Config::Connect("/NodeList/*/$ns3::TcpL4Protocol/SocketList/*/LastRTT", MakeBoundCallback(&LogLastRtt, rttStream));

    // Install FlowMonitor
    FlowMonitorHelper flowHelper;
    Ptr<FlowMonitor> FlowMonitor = flowHelper.InstallAll();

    NS_LOG_INFO("Starting simulation...");

    double time = 1.0;
    std::map<FlowId, uint64_t> lastRxBytes;
    Simulator::Schedule(Seconds(time), &CalculateThroughput, FlowMonitor, std::ref(flowHelper), 1.0, std::ref(time), std::ref(lastRxBytes));
    // Simulator::Schedule(Seconds(time), &CalculateThroughput, FlowMonitor, std::ref(flowHelper), 1.0, std::ref(time));

    Simulator::Stop(Seconds(600.0));
    Simulator::Run();

    throughputLog.close();
    rttLog.close();

    Simulator::Destroy();
    NS_LOG_INFO("Simulation complete!");
    return 0;
}