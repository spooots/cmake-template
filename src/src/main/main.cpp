/*****************************************************************
 * Project        Harman Car Multimedia System
 * Copyright (C)  2009, 2011-2013, 2016 Harman Becker Automotive
 *                Systems GmbH.
 *                Authors: Andreas Schedel
 * Secrecy Level  STRICTLY CONFIDENTIAL
 ****************************************************************/

#include <signal.h>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QString>

#include <bla.h>
#include "foo.h"

static int setup_unix_signal_handlers()
{
    qInfo() << "setup linux INT signal handler";
    struct sigaction INT;
    INT.sa_handler = Foo::intSignalHandler;
    sigemptyset(&INT.sa_mask);
    INT.sa_flags |= SA_RESTART;

    if (sigaction(SIGINT, &INT, 0))
       return 2;

    return 0;
}



int main(int argc, char* argv[])
{
    setup_unix_signal_handlers();
    QCoreApplication app(argc,argv);

    // Configure commandline parser
    QCommandLineParser parser;
    parser.setApplicationDescription("foo main application");
    const QCommandLineOption helpOption = parser.addHelpOption();
    const QCommandLineOption versionOption = parser.addVersionOption();
    const QCommandLineOption pmode ( QStringList() << "p" << "performance-mode",
        QCoreApplication::translate("main", "Set performance mode:\nnormal, kpi, hwq, lpm"),
        QCoreApplication::translate("main", "performance")
    );
    parser.addOption(pmode);
    parser.parse(app.arguments());

    if (parser.isSet(helpOption))
    {
        parser.showHelp();
        exit(0);
    }
    else if (parser.isSet(versionOption))
    {
        QString version = "V" + QString::number(0) + "." + QString::number(1) + "." + QString::number(0);
        qDebug() << "soc-configuration" <<  version;
        exit(0);
    }

    #ifdef BLA
    Bla bla(nullptr);
    qDebug() << bla.blabla();
    #endif

    Foo foo(nullptr);

    return app.exec();
}
