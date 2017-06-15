#ifndef BLA_UNITTEST_H
#define BLA_UNITTEST_H

#include <memory>

#include <gtest/gtest.h>

#include <QByteArray>
#include <QObject>
#include <QString>


class Bla_unittest
    : public QObject
    , public ::testing::Test
{
    Q_OBJECT

public:
    virtual void SetUp();   // set up the test fixture
    virtual void TearDown();// tead down the test fixture

protected:
    Bla_unittest();
    virtual ~Bla_unittest();
private slots:

};

#endif // BLA_UNITTEST_H
