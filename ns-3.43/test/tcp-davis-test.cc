#include "ns3/test.h"
#include "ns3/tcp-davis.h"

using namespace ns3;

class TcpDavisTestCase : public TestCase
{
public:
    TcpDavisTestCase() : TestCase("Test TcpDavis basic functionality") {}
    virtual void DoRun()
    {
        Ptr<TcpDavis> davis = CreateObject<TcpDavis>();
        NS_TEST_ASSERT_MSG_EQ(davis->GetName(), "TcpDavis", "Name should match");
    }
};

class TcpDavisTestSuite : public TestSuite
{
public:
    TcpDavisTestSuite() : TestSuite("tcp-davis", UNIT)
    {
        AddTestCase(new TcpDavisTestCase, TestCase::QUICK);
    }
};

static TcpDavisTestSuite g_tcpDavisTestSuite;
