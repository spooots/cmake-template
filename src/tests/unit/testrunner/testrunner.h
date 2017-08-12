#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <QObject>

class TestRunner
    : public QObject
{
    Q_OBJECT

public:
    TestRunner(int argc, char **argv);
    ~TestRunner() = default;
private slots:
    void start();
private:
    int ac;
    char** av;
};

#endif //TESTRUNNER_H
