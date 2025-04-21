#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("SimpleDebugExample");

int main(int argc, char *argv[])
{
    LogComponentEnable("SimpleDebugExample", LOG_LEVEL_INFO);

    NS_LOG_INFO("Starting Simulation...");

    NodeContainer nodes;
    nodes.Create(2);

    NS_LOG_INFO("Created " << nodes.GetN() << " nodes.");

    InternetStackHelper internet;
    internet.Install(nodes);

    NS_LOG_INFO("Internet stack installed.");

    NS_LOG_INFO("Simulation Complete!");
    return 0;
}
