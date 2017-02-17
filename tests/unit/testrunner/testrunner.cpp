#include <gtest/gtest.h>

#include <NCoreApplication>
#include <QTimer>

#include "testrunner.h"

TestRunner::TestRunner(int argc, char** argv)
    : QObject()
    , ac(argc)
    , av(argv)
{
    QTimer::singleShot(0, this, &TestRunner::start);
}

void TestRunner::start()
{
    ::testing::InitGoogleTest(&ac, av);
    nApp->exit(RUN_ALL_TESTS());
}

int main(int argc, char **argv)
{
    nare::NCoreApplication::setLogInfo("QGTR", "TestRunner", nare::NLogLevel::Debug, "%{category}%{message}");
    nare::NCoreApplication app(argc, argv);
    TestRunner runner(argc, argv);
    int ret = app.exec();
    return ret;
}
