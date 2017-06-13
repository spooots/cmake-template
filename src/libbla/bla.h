#ifndef BLA_H
#define BLA_H

#include <QObject>
#include <QString>

#ifdef GTEST
#include "gtest/gtest_prod.h"
#endif //GTEST

class Bla : public QObject
{
    Q_OBJECT

    #ifdef GTEST
    friend class bla_unittest;
    FRIEND_TEST(bla_unittest, test_blabla);
    #endif

public:
    explicit Bla(QObject *parent = 0):QObject(parent){}
    virtual ~Bla() = default;

    QString blabla() { return "BlaBla"; }

public slots:

signals:

protected:

private:

};

#endif // BLA_H
