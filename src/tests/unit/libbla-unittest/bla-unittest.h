#ifndef BLA_UNITTEST_H
#define BLA_UNITTEST_H

#include <memory>

#include <gtest/gtest.h>

#include <QByteArray>
#include <QObject>
#include <QString>


#include <bla.h>

class Bla_unittest
    : public QObject
    , public ::testing::Test
{
    Q_OBJECT

public:
    virtual void SetUp();   // set up the test fixture
    virtual void TearDown();// tead down the test fixture
    std::shared_ptr<Bla> bla;

protected:
    Bla_unittest();
    virtual ~Bla_unittest();
private slots:

private:

};

#endif // BLA_UNITTEST_H
