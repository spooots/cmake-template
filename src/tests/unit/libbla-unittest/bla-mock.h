#ifndef BLA_MOCK_H
#define BLA_MOCK_H

#include <gmock/gmock.h>

#include <bla.h>

using ::testing::AtLeast;
using ::testing::Return;

class BlaMock : public Bla
{
public:
    BlaMock():Bla(0){}
    MOCK_METHOD0( blabla, QString() );
};

#endif // BLA_MOCK_H
