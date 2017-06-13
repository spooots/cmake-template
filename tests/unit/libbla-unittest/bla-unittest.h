#ifndef SOCPERFCTRLSERVER_UNITTEST_H
#define SOCPERFCTRLSERVER_UNITTEST_H

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

protected:
    Bla_unittest();
    virtual ~Bla_unittest();
private slots:

public:
};

#endif // SOCPERFCTRLSERVER_UNITTEST_H
