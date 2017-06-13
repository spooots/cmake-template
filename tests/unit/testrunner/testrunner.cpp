#include <memory>
#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QTimer>

#include "testrunner.h"

static std::shared_ptr<QCoreApplication> app;

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
    app->exit(RUN_ALL_TESTS());
}



int main(int argc, char **argv)
{
    app = std::make_shared<QCoreApplication>(argc, argv);
    TestRunner runner(argc, argv);
    int ret = app->exec();
    return ret;
}
