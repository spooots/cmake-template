#include <CommonAPI/CommonAPI.hpp>

#include <NLogging>

#include "socperfctrltestproxy.h"

SocPerfCtrlTestProxy::SocPerfCtrlTestProxy(std::shared_ptr<CommonAPI::Runtime> runtime, QObject *parent) :
    QObject(parent),
    capiRuntime(runtime)
{
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "()";

    if (!capiRuntime)
    {
        capiRuntime = CommonAPI::Runtime::get();
    }

    socPerformanceControlAvailStatusListener = std::bind(&SocPerfCtrlTestProxy::socPerformanceControlAvailStatus, this, std::placeholders::_1);

    if ( proxy = capiRuntime->buildProxy<SoCPerformanceCtrlProxy>("local", SoCPerformanceCtrl_SoCPerformanceCtrl) )
    {
        availableStatusSubscription = proxy->getProxyStatusEvent().subscribe(socPerformanceControlAvailStatusListener);
        cpuThrottleStateSubscription = proxy->getCpuThrottleStateAttribute().getChangedEvent().subscribe(
                        [this](const bool& throttled)
                        {
                            emit cpuThrottleStateChanged(throttled);
                        }
                    );
        gpuThrottleStateSubscription = proxy->getGpuThrottleStateAttribute().getChangedEvent().subscribe(
                        [this](const bool& throttled)
                        {
                            emit cpuThrottleStateChanged(throttled);
                        }

                    );
    }

    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "() --> created";
}



SocPerfCtrlTestProxy::~SocPerfCtrlTestProxy()
{
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "()";
    if(proxy && connected)
    {
        proxy->getProxyStatusEvent().unsubscribe(availableStatusSubscription);
        proxy->getCpuThrottleStateAttribute().getChangedEvent().unsubscribe(cpuThrottleStateSubscription);
        proxy->getGpuThrottleStateAttribute().getChangedEvent().unsubscribe(gpuThrottleStateSubscription);
    }
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "() --> destroyed";
}



void SocPerfCtrlTestProxy::socPerformanceControlAvailStatus(const CommonAPI::AvailabilityStatus& status)
{
    switch(status)
    {
        case CommonAPI::AvailabilityStatus::AVAILABLE:
            logInfo() << "SocPerfCtrlProxy AVAILABLE";
            connected = true;
            break;
        default:
            logInfo() << "SoCPerfCtrlProxy not available";
            connected = false;
            break;
    }
}



int SocPerfCtrlTestProxy::setCPUThrottleState(const bool throttle)
{
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "(): throttle =" << throttle;
    if(proxy)
    {
        CommonAPI::CallStatus callStatus;
        bool throttled;

        proxy->getCpuThrottleStateAttribute().setValue( throttle, callStatus, throttled);
        if ( CommonAPI::CallStatus::SUCCESS == callStatus )
        {
            logInfo() << "successfully set CPU throttle state:" << throttled;
            emit cpuThrottleStateChanged(throttled);
        }
        else
        {
            logWarn() << "CAPI failure: set CPU throttle state: callStatus =" << static_cast<int32_t>(callStatus);
            return -1;
        }
    }
    else
    {
        logWarn() << "proxy missing";
        return -1;
    }
    return 0;
}



int SocPerfCtrlTestProxy::setGPUThrottleState(const bool throttle)
{
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "(): throttle =" << throttle;
    if(proxy)
    {
        CommonAPI::CallStatus callStatus;
        bool throttled;

        proxy->getGpuThrottleStateAttribute().setValue( throttle, callStatus, throttled);
        if ( CommonAPI::CallStatus::SUCCESS == callStatus )
        {
            logInfo() << "successfully set GPU throttle state:" << throttled;
            emit gpuThrottleStateChanged(throttled);
        }
        else
        {
            logWarn() << "CAPI failure: set GPU throttle state: callStatus =" << static_cast<int32_t>(callStatus);
            return -1;
        }
    }
    else
    {
        logWarn() << "proxy missing";
        return -1;
    }
    return 0;
}



void SocPerfCtrlTestProxy::requestCPUThrottleState(bool throttle)
{
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "(): throttle =" << throttle;
    if(proxy)
    {
        static_cast<void>( proxy->getCpuThrottleStateAttribute()
                               .setValueAsync(  throttle,
                                                [this](const CommonAPI::CallStatus& callStatus, bool value)
                                                {
                                                    if ( CommonAPI::CallStatus::SUCCESS == callStatus )
                                                    {
                                                        logInfo() << "successfully set CPU throttle state:" << value;
                                                        emit cpuThrottleStateChanged(value);
                                                    }
                                                    else
                                                    {
                                                        logWarn() << "CAPI failure: set CPU throttle state: callStatus =" << static_cast<int32_t>(callStatus);
                                                    }
                                                },
                                                &callInfo)
                           );
    }
}



void SocPerfCtrlTestProxy::requestGPUThrottleState(bool throttle)
{
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "(): throttle =" << throttle;
    if(proxy)
    {
        static_cast<void>( proxy->getGpuThrottleStateAttribute()
                                .setValueAsync( throttle,
                                                [this](const CommonAPI::CallStatus& callStatus, bool value)
                                                {
                                                    if ( CommonAPI::CallStatus::SUCCESS == callStatus )
                                                    {
                                                        logInfo() << "successfully set GPU throttle state:" << value;
                                                        emit gpuThrottleStateChanged(value);
                                                    }
                                                    else
                                                    {
                                                        logWarn() << "CAPI failure: set GPU throttle state: callStatus =" << static_cast<int32_t>(callStatus);
                                                    }
                                                },
                                                &callInfo)
                           );
    }
}



void SocPerfCtrlTestProxy::getCPUThrottleStateAsync()
{
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "()";
    if(proxy)
    {
        static_cast<void>( proxy->getCpuThrottleStateAttribute().getValueAsync( [this](const CommonAPI::CallStatus& callStatus, bool value)
                                                                                {
                                                                                    if ( CommonAPI::CallStatus::SUCCESS == callStatus )
                                                                                    {
                                                                                        logInfo() << "current CPU throttle state:" << value;
                                                                                        emit cpuThrottleStateChanged(value);
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        logWarn() << "CAPI failure: set CPU throttle state: callStatus =" << static_cast<int32_t>(callStatus);
                                                                                    }
                                                                                },
                                                                                &callInfo) );
    }
}



void SocPerfCtrlTestProxy::getGPUThrottleStateAsync()
{
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "()";
    if(proxy)
    {
        static_cast<void>( proxy->getGpuThrottleStateAttribute().getValueAsync( [this](const CommonAPI::CallStatus& callStatus, bool value)
                                                                                {
                                                                                    if ( CommonAPI::CallStatus::SUCCESS == callStatus )
                                                                                    {
                                                                                        logInfo() << "current GPU throttle state:" << value;
                                                                                        emit gpuThrottleStateChanged(value);
                                                                                    }
                                                                                    else
                                                                                    {
                                                                                        logWarn() << "CAPI failure: set GPU throttle state: callStatus =" << static_cast<int32_t>(callStatus);
                                                                                    }
                                                                                },
                                                                                &callInfo) );
    }
}



int SocPerfCtrlTestProxy::getCPUThrottleState( bool& throttled )
{
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "()";
    if(proxy)
    {
        CommonAPI::CallStatus callStatus;
        bool value;
        proxy->getCpuThrottleStateAttribute().getValue (callStatus, value);
        if ( CommonAPI::CallStatus::SUCCESS == callStatus )
        {
            logInfo() << "current CPU throttle state:" << value;
            throttled = value;
        }
        else
        {
            logWarn() << "CAPI failure: set CPU throttle state: callStatus =" << static_cast<int32_t>(callStatus);
            return -1;
        }
    }
    else
    {
        return -1;
    }
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "(): throttled =" << throttled;
    return 0;
}



int SocPerfCtrlTestProxy::getGPUThrottleState( bool& throttled )
{
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "()";
    if(proxy)
    {
        CommonAPI::CallStatus callStatus;
        bool value;
        proxy->getGpuThrottleStateAttribute().getValue (callStatus, value);
        if ( CommonAPI::CallStatus::SUCCESS == callStatus )
        {
            logInfo() << "current GPU throttle state:" << value;
            throttled = value;
        }
        else
        {
            logWarn() << "CAPI failure: set GPU throttle state: callStatus =" << static_cast<int32_t>(callStatus);
            return -1;
        }
    }
    else
    {
        return -1;
    }
    logInfo() <<"SocPerfCtrlTestProxy::"<< __func__ << "(): throttled =" << throttled;
    return 0;
}
