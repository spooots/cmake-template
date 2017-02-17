#include<QDebug>

#include "bla.h"

Bla::Bla(QObject *parent)
    :   QObject(parent)
{
    qDebug() << "Bla";
}



Bla::~Bla()
{
    qDebug() << "~Bla";
}



QString Bla::blabla()
{
    return "BlaBla";
}
