#include <NCoreApplication>
#include <NLogging>

#include <CommonAPI/CommonAPI.hpp>

#include <QDir>
#include <QTest>
#include <QTextStream>
#include <QThread>

#include <socperfctrlserver.h>
#include "socperfctrltestproxy.h"

#include "socperfctrlserver-unittest.h"

using namespace ::v1::de::bmw::infotainment::socctrl::soccontroller;

SoCPerfCtrlServer_unittest::SoCPerfCtrlServer_unittest()
{
    #define LOGINFO "%{category}%{pid}|%{threadid}|%{function}@%{line} %{message}"
    //#define LOGINFO "%{function}:%{line}: %{message}"
    nare::NCoreApplication::setOrganizationDomain("os");
    nare::NCoreApplication::setLogInfo("SOCC", "SoC performance controller", nare::NLogLevel::Debug, LOGINFO); //TODO: change default loglevel to info
    nare::NCoreApplication::setDefaultLogContext("SOCC", "SoC controller log context");

    capiRuntime = CommonAPI::Runtime::get();

    logInfo() << "register soc performance control server at CAPI runtime";
    socPerfServer = std::make_shared<SocPerfCtrlServer>(capiRuntime, this) ;
    logInfo() << "register server";
    capiRuntime->registerService("local", SoCPerformanceCtrl_SoCPerformanceCtrl, socPerfServer);

    socPerfProxy = std::make_shared<SocPerfCtrlTestProxy>(capiRuntime, this);
    while(!socPerfProxy->isConnected())
    {
        QThread::msleep(50);
    }
}



SoCPerfCtrlServer_unittest::~SoCPerfCtrlServer_unittest()
{
    if (capiRuntime)
    {
        logInfo() << "unregister server";
        capiRuntime->unregisterService("local",
                                       v1::de::bmw ::infotainment::socctrl::soccontroller::SoCPerformanceCtrl::getInterface(),
                                       v1::de::bmw ::infotainment::socctrl::soccontroller::SoCPerformanceCtrl_SoCPerformanceCtrl
                                       );
        socPerfProxy.reset();
    }
}



TEST_F(SoCPerfCtrlServer_unittest, test_blockingInterfaces_CPU)
{
    EXPECT_TRUE(nullptr != socPerfServer.get());
    EXPECT_TRUE(nullptr != socPerfProxy.get());

    bool throttled = true;
    int result = socPerfProxy->setCPUThrottleState(throttled);
    EXPECT_EQ (result, 0);
    result = socPerfProxy->getCPUThrottleState(throttled);
    EXPECT_EQ (result, 0);
    EXPECT_TRUE(throttled);

    throttled = false;
    result = socPerfProxy->setCPUThrottleState(throttled);
    EXPECT_EQ (result, 0);
    result = socPerfProxy->getCPUThrottleState(throttled);
    EXPECT_EQ (result, 0);
    EXPECT_FALSE(throttled);
}



TEST_F(SoCPerfCtrlServer_unittest, test_blockingInterfaces_GPU)
{
    EXPECT_TRUE(nullptr != socPerfServer.get());
    EXPECT_TRUE(nullptr != socPerfProxy.get());

    bool throttled = true;
    int result = socPerfProxy->setGPUThrottleState(throttled);
    EXPECT_EQ (result, 0);
    result = socPerfProxy->getGPUThrottleState(throttled);
    EXPECT_EQ (result, 0);
    EXPECT_TRUE(throttled);

    throttled = false;
    result = socPerfProxy->setGPUThrottleState(throttled);
    EXPECT_EQ (result, 0);
    result = socPerfProxy->getGPUThrottleState(throttled);
    EXPECT_EQ (result, 0);
    EXPECT_FALSE(throttled);
}
