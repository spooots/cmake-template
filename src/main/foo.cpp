#include <sys/socket.h>
#include <unistd.h>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>


#include "foo.h"

int Foo::sigIntFd[2];

Foo::Foo(QObject *parent) : QObject(parent)
{
    snInt = new QSocketNotifier(sigIntFd[1], QSocketNotifier::Read, this);
    QObject::connect(snInt, &QSocketNotifier::activated, this, &Foo::onSigInt);
}

Foo::~Foo()
{
    ::close(sigIntFd[0]);
    ::close(sigIntFd[1]);
}



void Foo::intSignalHandler(int sig)
{
    qDebug() << sig;
    char a = 2;
    ::write(sigIntFd[0], &a, sizeof(a));
}

void Foo::onSigInt()
{
    snInt->setEnabled(false);
    char tmp;
    ::read(sigIntFd[1], &tmp, sizeof(tmp));

    // do Qt stuff
    qInfo() << "program interrupted:" << QString(tmp);

    QCoreApplication::quit();

    snInt->setEnabled(true);
}
