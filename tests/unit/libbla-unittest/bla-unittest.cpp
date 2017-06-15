#include <QDir>
#include <QTest>
#include <QTextStream>
#include <QThread>
#include <QDebug>

#include "bla-unittest.h"

#include <bla-mock.h>

using ::testing::AtLeast;
using ::testing::Return;

Bla_unittest::Bla_unittest()
{
    qDebug() << "Bla_unittest";
}



Bla_unittest::~Bla_unittest()
{
    qDebug() << "~Bla_unittest";
}



void Bla_unittest::SetUp()
{
    qDebug() << "SetUp";
}



void Bla_unittest::TearDown()
{
    qDebug() << "TearDown";
}



TEST_F(Bla_unittest, test_1)
{
    qDebug() << "test_1";

    BlaMock mock;
    EXPECT_CALL(mock, blabla())
            .Times(AtLeast(4))
            .WillOnce(Return(QString("BlaBla")))
            .WillOnce(Return(QString("BlaBlub")))
            .WillRepeatedly(Return(QString("Hello")));

    EXPECT_EQ(QString("BlaBla"),mock.blabla());
    EXPECT_EQ(QString("BlaBlub"),mock.blabla());
    EXPECT_EQ(QString("Hello"),mock.blabla());
    EXPECT_EQ(QString("Hello"),mock.blabla());
    EXPECT_TRUE(true);
}



TEST_F(Bla_unittest, test_2)
{
    qDebug() << "test_2";
}
