#include "util.h"
#include <QDebug>

Util::Util(QObject *parent) : QStm::Object(parent)
{

}

void Util::usingQCurrency()
{
    QCurrency currency;
    currency=1.5464137891;
    qWarning()<<currency.toString();
    //output is 1.45

    currency=1;
    currency+=0.5464137891;
    qWarning()<<currency.toString();
    //output is 1.45

    currency+=1;
    qWarning()<<currency.toString();
    //output is 2.45

    currency-=1;
    qWarning()<<currency.toString();
    //output is 1.45

    currency+=1;
    currency/=1;
    qWarning()<<currency.toString();
    //output is 1.00
}

void Util::usingVariantUtil()
{
    VariantUtil vu;

    {// json conversion

        //list json bytes
        auto bytesList="{\"row 1\",\"row 2\",\"row 2\"}";

        //identify and convert to QVariantList
        QVariantList vList=vu.toList(bytesList);

        qWarning()<<vList;//output QVariantList

        //identify and convert to QStringList
        QStringList vStringList=vu.toStringList(bytesList);

        qWarning()<<vStringList;//output QStringList


        //object json bytes
        auto bytesMap="{\"rows\":{\"row 1\",\"row 2\",\"row 2\"}}";

        //identify and convert to QVariantHash
        QVariantHash vHash=vu.toHash(bytesMap);
        qWarning()<<vHash;//output QVariantList

        //identify and convert to QVariantList
        QVariantMap vMap=vu.toMap(bytesMap);

        qWarning()<<vMap;//output QStringList
    }

    {// QVariant conversion to QString and bytes JSON

        //QVariantList object
        auto objectList=QVariantList{"row 1","row 2","row 2"};

        qWarning()<<vu.toStr(objectList);//output JSON bytes


        //QVariantHash object
        auto objectMap=QVariantHash{{"rows", QStringList{"row 1","row 2","row 2"}}};

        qWarning()<<vu.toStr(objectMap);//output JSON bytes

        qWarning()<<vu.toStr(QString("abcd"));//output QString using QVariant::toString()

        qWarning()<<vu.toStr(12345);//output QString using QVariant::toString()

        qWarning()<<vu.toStr(12345.6789);//output QString using QVariant::toString()

        qWarning()<<vu.toStr(QUrl("file:///tmp/tmp.txt"));//output QString using QVariant::toUrl().toString()

        qWarning()<<vu.toStr(QUuid::createUuid());//output QString using QVariant::toUuid().toString()

        qWarning()<<vu.toStr(QDate::currentDate());//output QString using QVariant::toDate().toString()

        qWarning()<<vu.toStr(QTime::currentTime());//output QString using QVariant::toTime().toString()

        qWarning()<<vu.toStr(QDateTime::currentDateTime());//output QString using QVariant::toDateTime().toString()
    }


    {// QString conversion to QVariant types

        qWarning()<<vu.toInt("1");//output QVariant::toInt()

        qWarning()<<vu.toLongLong("1");//output QVariant::toLongLong()

        qWarning()<<vu.toLongLong("1");//output QVariant::toLongLong()

        qWarning()<<vu.toDouble("1.1");//output QVariant::toDouble()

        qWarning()<<vu.toDate("1901-01-01");//output QDate::fromString(...);

        qWarning()<<vu.toTime("00:00:01.999");//output QTime::fromString(...);

        qWarning()<<vu.toDateTime("1901-01-01T00:00:01.999");//output QDateTime::fromString(...);
    }

}

void Util::usingFormattingUtil()
{
    FormattingUtil fu;

    qWarning()<<fu.v(12.12);//output identify QVariant type and auto format value

    qWarning()<<fu.toDate(QDate(1901,01,01));//output QVariant::toDate().toString(/*using QLocale::c() masks*/);

    qWarning()<<fu.toTime(QTime(00,00,01,999));//output QVariant::toTime().toString(/*using QLocale::c() masks*/);

    qWarning()<<fu.toDateTime(QDateTime(QDate(1901,01,01),QTime(00,00,01,999)));//output QVariant::toDateTime().toString(/*using QLocale::c() masks*/);

    qWarning()<<fu.toInt(12);//output using QLocale::c().toString(QVariant::toInt(),'f',0)

    qWarning()<<fu.toDouble(12.12);//output using QLocale::c().toString(QVariant::toDouble(),'f',6)

    qWarning()<<fu.toCurrency(12.12);//output using QLocale::c().toString(QVariant::toDouble(),'f',2)
}

void Util::usingDateUtil()
{
    DateUtil du;

}

void Util::usingDoubleUtil()
{
    DoubleUtil dbu;

    {//rearrange values
        double vMin=2;
        double vMax=1;
        qWarning()<<dbu.checkBetween(vMin, vMax);//return true, function arrange max and min values
    }

    {//check and rearrange values
        double vVal=1.5;
        double vMin=2;
        double vMax=1;
        qWarning()<<dbu.checkBetween(vVal, vMin, vMax);//return true, function arrange max/min values and validate value
    }
}
