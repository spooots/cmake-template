#ifndef SOCPERFCTRLTESTPROXY_H
#define SOCPERFCTRLTESTPROXY_H

#include <memory>

#include <QObject>

#include <CommonAPI/CommonAPI.hpp>
#include <v1/de/bmw/infotainment/socctrl/soccontroller/SoCPerformanceCtrlInstanceIds.hpp>
#include <v1/de/bmw/infotainment/socctrl/soccontroller/SoCPerformanceCtrlProxy.hpp>

using namespace ::v1::de::bmw::infotainment::socctrl::soccontroller;

namespace CommonAPI
{
class Runtime;
}


class SocPerfCtrlTestProxy : public QObject
{
    Q_OBJECT

public:
    explicit SocPerfCtrlTestProxy(std::shared_ptr<CommonAPI::Runtime> runtime, QObject *parent = 0);
    virtual ~SocPerfCtrlTestProxy();

    inline bool isConnected(){return connected;}

signals:
    void cpuThrottleStateChanged(const bool& state); ///< emitted, if SoCPerformance module's throttle state changed
    void gpuThrottleStateChanged(const bool& state); ///< emitted, if SoCPerformance module's throttle state changed

public slots:
    int setCPUThrottleState(const bool throttle);  ///< set throttle state change at SoCPerformance module blocking
    int setGPUThrottleState(const bool throttle);  ///< set throttle state change at SoCPerformance module blocking
    void getCPUThrottleStateAsync();  ///< get current throttle state - blocking
    void getGPUThrottleStateAsync();  ///< get current throttle state - blocking

    void requestCPUThrottleState(bool throttle);  ///< request throttle state change at SoCPerformance module
    void requestGPUThrottleState(bool throttle);  ///< request throttle state change at SoCPerformance module
    int getCPUThrottleState(bool& value);  ///< get current throttle state
    int getGPUThrottleState(bool& value);  ///< get current throttle state

private:
    std::shared_ptr<CommonAPI::Runtime> capiRuntime{std::shared_ptr<CommonAPI::Runtime>()};

    bool connected{false};
    std::shared_ptr<CommonAPI::Runtime> runtime{nullptr};
    std::shared_ptr<::v1::de::bmw::infotainment::socctrl::soccontroller::SoCPerformanceCtrlProxy<>> proxy{nullptr};

    void socPerformanceControlAvailStatus(const CommonAPI::AvailabilityStatus& _status);
    std::function<void(const CommonAPI::AvailabilityStatus&)> socPerformanceControlAvailStatusListener{nullptr};

    CommonAPI::ProxyStatusEvent::Subscription availableStatusSubscription{0};
    CommonAPI::ProxyStatusEvent::Subscription cpuThrottleStateSubscription{0};
    CommonAPI::ProxyStatusEvent::Subscription gpuThrottleStateSubscription{0};

    CommonAPI::CallInfo callInfo; ///< call info for setting attributes
    CommonAPI::Attribute<bool>::AttributeAsyncCallback getCpuThrottleStateAsyncCallback;
    CommonAPI::Attribute<bool>::AttributeAsyncCallback getGpuThrottleStateAsyncCallback;
};

#endif // SOCPERFCTRLTESTPROXY_H
