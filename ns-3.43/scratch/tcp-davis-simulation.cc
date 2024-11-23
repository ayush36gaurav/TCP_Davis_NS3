#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
// #include "ns3/tcp-davis.h"
#include "/home/ayush-gaurav/ns-allinone-3.43/ns-3.43/src/internet/model/tcp-davis.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("TcpDavisSimulation");

int main(int argc, char *argv[])
{
    // Simulation parameters
    uint32_t simulationTime = 30; // seconds
    uint32_t flow1Start = 0;      // seconds
    uint32_t flow2Start = 10;     // seconds

    CommandLine cmd;
    cmd.Parse(argc, argv);

    // Create nodes
    NodeContainer nodes;
    nodes.Create(4); // Left 0, 1; Right 2, 3

    // Point-to-point links
    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("100Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("10ms"));

    NetDeviceContainer devicesLeft, devicesRight, bottleneckDevices;

    devicesLeft = p2p.Install(nodes.Get(0), nodes.Get(2));    // Flow 0 path
    devicesRight = p2p.Install(nodes.Get(1), nodes.Get(3));   // Flow 1 path
    bottleneckDevices = p2p.Install(nodes.Get(2), nodes.Get(3)); // Shared bottleneck

    // Internet stack
    InternetStackHelper stack;
    stack.Install(nodes);

    // Assign IP addresses
    Ipv4AddressHelper address;
    Ipv4InterfaceContainer interfacesLeft, interfacesRight, bottleneckInterfaces;

    address.SetBase("10.1.1.0", "255.255.255.0");
    interfacesLeft = address.Assign(devicesLeft);

    address.SetBase("10.1.2.0", "255.255.255.0");
    interfacesRight = address.Assign(devicesRight);

    address.SetBase("10.1.3.0", "255.255.255.0");
    bottleneckInterfaces = address.Assign(bottleneckDevices);

    // Traffic sources and sinks
    uint16_t port = 50000;
    Address sinkAddress0(InetSocketAddress(bottleneckInterfaces.GetAddress(1), port));
    Address sinkAddress1(InetSocketAddress(bottleneckInterfaces.GetAddress(1), port + 1));

    // Flow 0
    PacketSinkHelper sinkHelper0("ns3::TcpSocketFactory", sinkAddress0);
    ApplicationContainer sinkApp0 = sinkHelper0.Install(nodes.Get(3));
    sinkApp0.Start(Seconds(0));
    sinkApp0.Stop(Seconds(simulationTime));

    BulkSendHelper sourceHelper0("ns3::TcpSocketFactory", sinkAddress0);
    sourceHelper0.SetAttribute("MaxBytes", UintegerValue(0));
    ApplicationContainer sourceApp0 = sourceHelper0.Install(nodes.Get(0));
    sourceApp0.Start(Seconds(flow1Start));
    sourceApp0.Stop(Seconds(simulationTime));

    // Flow 1
    PacketSinkHelper sinkHelper1("ns3::TcpSocketFactory", sinkAddress1);
    ApplicationContainer sinkApp1 = sinkHelper1.Install(nodes.Get(3));
    sinkApp1.Start(Seconds(0));
    sinkApp1.Stop(Seconds(simulationTime));

    BulkSendHelper sourceHelper1("ns3::TcpSocketFactory", sinkAddress1);
    sourceHelper1.SetAttribute("MaxBytes", UintegerValue(0));
    ApplicationContainer sourceApp1 = sourceHelper1.Install(nodes.Get(1));
    sourceApp1.Start(Seconds(flow2Start));
    sourceApp1.Stop(Seconds(simulationTime));

    // Configure TCP Davis
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", StringValue("ns3::TcpDavis"));

    // Flow Monitor
    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.InstallAll();

    Simulator::Stop(Seconds(simulationTime));
    Simulator::Run();

    // Log throughput and RTT metrics
    monitor->SerializeToXmlFile("tcp-davis-results.xml", true, true);

    Simulator::Destroy();

    return 0;
}
