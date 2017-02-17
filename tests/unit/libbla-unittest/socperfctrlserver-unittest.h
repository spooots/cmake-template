#ifndef SOCPERFCTRLSERVER_UNITTEST_H
#define SOCPERFCTRLSERVER_UNITTEST_H

#include <memory>

#include <gtest/gtest.h>

#include <QByteArray>
#include <QObject>
#include <QString>

namespace CommonAPI
{
class Runtime;
}

class SocPerfCtrlTestProxy;
class SocPerfCtrlServer;

class SoCPerfCtrlServer_unittest
    : public QObject
    , public ::testing::Test
{
    Q_OBJECT

protected:
    SoCPerfCtrlServer_unittest();
    virtual ~SoCPerfCtrlServer_unittest();
private slots:

public:
    std::shared_ptr<CommonAPI::Runtime> capiRuntime{std::shared_ptr<CommonAPI::Runtime>()};
    std::shared_ptr<SocPerfCtrlTestProxy> socPerfProxy{std::shared_ptr<SocPerfCtrlTestProxy>()};
    std::shared_ptr<SocPerfCtrlServer> socPerfServer{std::shared_ptr<SocPerfCtrlServer>()};
};

#endif // SOCPERFCTRLSERVER_UNITTEST_H
