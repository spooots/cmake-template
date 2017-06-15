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
}



Bla_unittest::~Bla_unittest()
{
}



TEST_F(Bla_unittest, test_1)
{
    BlaMock mock;
    EXPECT_CALL(mock, blabla())
            .Times(AtLeast(4))
            .WillOnce(Return(QString("BlaBla")))
            .WillOnce(Return(QString("BlaBlub")))
            .WillRepeatedly(Return(QString("Hello")));

    qInfo() << mock.blabla() << mock.blabla() << mock.blabla();

    qInfo() << "1" << mock.blabla();
    qInfo() << "2" << mock.blabla();
    qInfo() << "3" << mock.blabla();

    EXPECT_EQ(QString("Hello"),mock.blabla());
    EXPECT_TRUE(true);
}
