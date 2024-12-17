#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/tcp-davis.h"  // Use TCP-DAVIS

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("TcpDavisSimulation");

int main(int argc, char *argv[]) {
    // Enable logging
    LogComponentEnable("TcpDavisSimulation", LOG_LEVEL_INFO);
    LogComponentEnable("BulkSendApplication", LOG_LEVEL_ALL); 
    LogComponentEnable("PacketSink", LOG_LEVEL_ALL);          
    LogComponentEnable("TcpL4Protocol", LOG_LEVEL_ALL);       

    NS_LOG_INFO("Creating nodes...");
    NodeContainer senders, routers, receivers;
    senders.Create(1);
    routers.Create(2);
    receivers.Create(1);

    NS_LOG_INFO("Setting up links...");
    PointToPointHelper accessLink, bottleneckLink;
    accessLink.SetDeviceAttribute("DataRate", StringValue("1Gbps"));
    accessLink.SetChannelAttribute("Delay", StringValue("30ms"));
    bottleneckLink.SetDeviceAttribute("DataRate", StringValue("100Mbps"));
    bottleneckLink.SetChannelAttribute("Delay", StringValue("10ms"));

    NetDeviceContainer d1 = accessLink.Install(senders.Get(0), routers.Get(0));
    NetDeviceContainer d2 = bottleneckLink.Install(routers.Get(0), routers.Get(1));
    NetDeviceContainer d3 = accessLink.Install(routers.Get(1), receivers.Get(0));

    NS_LOG_INFO("Installing Internet stack...");
    InternetStackHelper stack;
    stack.Install(senders);
    stack.Install(routers);
    stack.Install(receivers);

    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.0.0.0", "255.255.255.0");
    ipv4.Assign(d1);
    ipv4.SetBase("10.0.1.0", "255.255.255.0");
    ipv4.Assign(d2);
    ipv4.SetBase("10.0.2.0", "255.255.255.0");
    Ipv4InterfaceContainer receiverInterfaces = ipv4.Assign(d3);

    std::cout << "Receiver IP: " << receiverInterfaces.GetAddress(1) << std::endl;

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // 🔥 Set TCP-DAVIS as the socket type
    Config::SetDefault("ns3::TcpL4Protocol::SocketType", TypeIdValue(TcpDavis::GetTypeId()));
    Config::SetDefault("ns3::TcpSocket::InitialCwnd", UintegerValue(10));

    uint16_t port = 50000;
    Address sinkAddress(InetSocketAddress(Ipv4Address::GetAny(), port));

    // Create and bind PacketSink
    PacketSinkHelper sinkHelper("ns3::TcpSocketFactory", sinkAddress);
    ApplicationContainer sinkApp = sinkHelper.Install(receivers.Get(0));
    sinkApp.Start(Seconds(0.0));
    sinkApp.Stop(Seconds(200.0)); 

    // Create BulkSendApplication
    BulkSendHelper bulkSender("ns3::TcpSocketFactory", InetSocketAddress(receiverInterfaces.GetAddress(1), port));
    bulkSender.SetAttribute("SendSize", UintegerValue(1024));
    bulkSender.SetAttribute("MaxBytes", UintegerValue(0)); 
    ApplicationContainer senderApp = bulkSender.Install(senders.Get(0));
    senderApp.Start(Seconds(1.0)); 
    senderApp.Stop(Seconds(200.0)); 

    FlowMonitorHelper flowMonitor;
    Ptr<FlowMonitor> monitor = flowMonitor.InstallAll();

    Simulator::Stop(Seconds(200.0));
    Simulator::Run();

    monitor->CheckForLostPackets();
    monitor->SerializeToXmlFile("davis-results.xml", true, true);  // Save results as "davis-results.xml"

    Simulator::Destroy();
    NS_LOG_INFO("Simulation complete!");

    return 0;
}
