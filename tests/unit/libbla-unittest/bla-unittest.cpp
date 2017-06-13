#include <QDir>
#include <QTest>
#include <QTextStream>
#include <QThread>

#include "bla-unittest.h"

Bla_unittest::Bla_unittest()
{
}



Bla_unittest::~Bla_unittest()
{
}



TEST_F(Bla_unittest, test_1)
{
    EXPECT_TRUE(true);
}
