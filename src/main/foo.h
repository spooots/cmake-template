#ifndef FOO_H
#define FOO_H

#include <QObject>
#include <QSocketNotifier>

class Foo : public QObject
{
    Q_OBJECT

public:
    explicit Foo(QObject *parent = 0);
    virtual ~Foo();

    static void intSignalHandler(int unused);

signals:

public slots:
    void onSigInt();

public:
    static int sigIntFd[2];
    QSocketNotifier* snInt;
};

#endif // FOO_H
