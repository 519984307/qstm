# QStm

**Set of classes and utilities for configuring and working with Qt types.**


## Working architecture

>## Support
> Qt5, Qt6

## Prerequisits
>```bash
> mkdir myproject;
> cd myproject;
> git clone git@github.com:flaviomarcio/qstm.git;
>```
>Check example in QStm/example/*


## CMake Build information

>```
>## initial CMake parameters 
>
>-GNinja
>-DCMAKE_BUILD_TYPE:STRING=Debug
>-DCMAKE_PROJECT_INCLUDE_BEFORE:PATH=%{IDE:ResourcePath}/package-manager/auto-setup.cmake
>-DQT_QMAKE_EXECUTABLE:STRING=%{Qt:qmakeExecutable}
>-DCMAKE_PREFIX_PATH:STRING=%{Qt:QT_INSTALL_PREFIX}
>-DCMAKE_C_COMPILER:STRING=%{Compiler:Executable:C}
>-DCMAKE_CXX_COMPILER:STRING=%{Compiler:Executable:Cxx}
>-DCMAKE_INSTALL_PREFIX=~/build/myproject/install/Debug
>```

>```bash
> cd qstm
> mkdir build;
> cd build;
> cmake ..
> make;
> make install;
>```

## QMake Build information

>```bash
> cd qstm
> qmake qstm.pro
> make;
> make install;
> ls -l;
>```

## Configure QMake project

>```c++
>CONFIG += c++17
>CONFIG += console
>CONFIG += silent
>CONFIG -= debug_and_release
>QT += gui core widgets
>
>TEMPLATE = app
>TARGET = demo
>
>include($$PWD/../../../qstm/qstm.pri)
>```

## Classes

>## QStm::MetaObjectUtil
>Class contains functions to convert create ***QObject*** using ***QMetaObject*** read ***QMetaProperty*** and set in ***QVariant*** and write in ***QMetaProperty*** using ***QVariant*** or ***JSON*** 
>```c++
>#include <QStm>
>
>void run()
>{
>     ...more
>}
>```
>## QStm::ResultValue
>Based on ***QObject***, use for simultaneous transport of values ​​and function result.
>Avoid instances of classes using New, she transport values ​​with no need to create classes.
>```c++
>#include <QStm>
>
>class SimpleObject : public QStm::Object {
>    Q_OBJECT
>public:
>    ResultValue&hashMd5(const QVariant&bytes)
>    {
>        if(bytes.isNull())
>            return this->lr()=false;//return false and without error
>
>        if(bytes.toString().trimmed().isEmpty())
>            return this->lr().setBadRequest("Invalid data");//return false and with error
>
>        QStm::VariantUtil vu;
>        QVariant md5=vu.toByteArray(bytes);
>        return this->lr(md5);//return success and return value
>    }
>};
>
>void check()
>{
>    SimpleObject simpleObject;
>
>    QByteArray bytes("1234567890");
>
>    if(!simpleObject.hashMd5(bytes)){
>        qWarning()<<simpleObject.lr().returnCode();//error code
>        qWarning()<<simpleObject.lr().returnText();//error text
>        return;
>    }
>    
>    qWarning()<<simpleObject.lr().resultByteArray();
>}
>```
>Others conversion basead in QVariant
>```c++
>//to bytes
>qWarning()<<simpleObject.lr().resultByteArray();
>
>//to int
>qWarning()<<simpleObject.lr().resultInt();
>
>//to Double
>qWarning()<<simpleObject.lr().resultDouble();
>
>//to QString
>qWarning()<<simpleObject.lr().resultString();
>
>//to QDate
>qWarning()<<simpleObject.lr().resultDate();
>
>//to QTime
>qWarning()<<simpleObject.lr().resultTime();
>
>//to QDateTime
>qWarning()<<simpleObject.lr().resultDateTime();
>
>//to QUrl
>qWarning()<<simpleObject.lr().resultUrl();
>
>//to QUuid
>qWarning()<<simpleObject.lr().resultUuid();
>
>//to QVariantList
>qWarning()<<simpleObject.lr().resultList();
>
>//to QStringList
>qWarning()<<simpleObject.lr().resultStringList();
>
>//to QVariantHash
>qWarning()<<simpleObject.lr().resultHash();
>
>//to QVariantMap
>qWarning()<<simpleObject.lr().resultMap();
>
>//to void*
>qWarning()<<simpleObject.lr().resultObject();
>
>//to QObject
>qWarning()<<simpleObject.lr().resultObject<QObject*>()>
>```
>## QStm::Object
>Based on ***QObject*** contains functions to convert to type ***QVariant*** and assigned values ​​of ***QVariantHash***
>```c++
>#include <QStm>
>
>void run()
>{
>     ...more
>}
>```
>## QStm::QCurrency
>Based on ***bcmath*** is a ***QVariant*** type, used to manipulate currency values ​​without difficulty the type ***double***
>```c++
>#include <QStm>
>
>void Util::usingQCurrency()
>{
>    QCurrency currency;
>    currency=1.5464137891;
>    qWarning()<<currency.toString();
>    //output is 1.45
>   
>    currency=1;
>    currency+=0.5464137891;
>    qWarning()<<currency.toString();
>    //output is 1.45
>  
>    currency+=1;
>    qWarning()<<currency.toString();
>    //output is 2.45
>    
>    currency-=1;
>    qWarning()<<currency.toString();
>    //output is 1.45
>    
>    currency+=1;
>    currency/=1;
>    qWarning()<<currency.toString();
>    //output is 1.00
>}
>```
>## QStm::VariantUtil
>Based on ***QVariant***, used to manipulate ***QVariant*** types.
>>Simplify conversion of json values em ***QVariantList*** and ***QVariantHash***.
>>Simplify conversion of ***QVariant*** to others ***QVariant*** types.
>>Functions to handle md5 and uuid values ​​for ***QVariant***
>```c++
>#include <QStm>
>
>void Util::usingVariantUtil()
>{
>    VariantUtil vu;
>
>    {// json conversion
>
>        //list json bytes
>        auto bytesList="{\"row 1\",\"row 2\",\"row 2\"}";
>
>        //identify and convert to QVariantList
>        QVariantList vList=vu.toList(bytesList);
>
>        qWarning()<<vList;//output QVariantList
>
>        //identify and convert to QStringList
>        QStringList vStringList=vu.toStringList(bytesList);
>
>        qWarning()<<vStringList;//output QStringList
>
>
>        //object json bytes
>        auto bytesMap="{\"rows\":{\"row 1\",\"row 2\",\"row 2\"}}";
>
>        //identify and convert to QVariantHash
>        QVariantHash vHash=vu.toHash(bytesMap);
>        qWarning()<<vHash;//output QVariantList
>
>        //identify and convert to QVariantList
>        QVariantMap vMap=vu.toMap(bytesMap);
>
>        qWarning()<<vMap;//output QStringList
>    }
>
>    {// QVariant conversion to QString and bytes JSON
>
>        //QVariantList object
>        auto objectList=QVariantList{"row 1","row 2","row 2"};
>
>        qWarning()<<vu.toStr(objectList);//output JSON bytes
>
>        //QVariantHash object
>        auto objectMap=QVariantHash{{"rows", QStringList{"row 1","row 2","row 2"}}};
>
>        qWarning()<<vu.toStr(objectMap);//output JSON bytes
>
>        qWarning()<<vu.toStr(QString("abcd"));//output QString using QVariant::toString()
>
>        qWarning()<<vu.toStr(12345);//output QString using QVariant::toString()
>
>        qWarning()<<vu.toStr(12345.6789);//output QString using QVariant::toString()
>
>        qWarning()<<vu.toStr(QUrl("file:///tmp/tmp.txt"));//output QString using QVariant::toUrl().toString()
>
>        qWarning()<<vu.toStr(QUuid::createUuid());//output QString using QVariant::toUuid().toString()
>
>        qWarning()<<vu.toStr(QDate::currentDate());//output QString using QVariant::toDate().toString()
>
>        qWarning()<<vu.toStr(QTime::currentTime());//output QString using QVariant::toTime().toString()
>
>        qWarning()<<vu.toStr(QDateTime::currentDateTime());//output QString using QVariant::toDateTime().toString()
>    }
>
>    {// QString conversion to QVariant types
>
>        qWarning()<<vu.toInt("1");//output QVariant::toInt()
>
>        qWarning()<<vu.toLongLong("1");//output QVariant::toLongLong()
>
>        qWarning()<<vu.toLongLong("1");//output QVariant::toLongLong()
>
>        qWarning()<<vu.toDouble("1.1");//output QVariant::toDouble()
>
>        qWarning()<<vu.toDate("1901-01-01");//output QDate::fromString(...);
>
>        qWarning()<<vu.toTime("00:00:01.999");//output QTime::fromString(...);
>
>        qWarning()<<vu.toDateTime("1901-01-01T00:00:01.999");//output QDateTime::fromString(...);
>    }
>}
>```
>## QStm::FormattingUtil
>Based on ***QVariant***, using masks to manipulate ***QVariant*** formatting values to especific types ***QDateTime, QDate, QTime, QCurrence, Double, Int, ....*** .
>```c++
>#include <QStm>
>
>void Util::usingFormattingUtil()
>{
>    FormattingUtil fu;
>
>    qWarning()<<fu.v(12.12);//output identify QVariant type and auto format value
>
>    qWarning()<<fu.toDate(QDate(1901,01,01));//output QVariant::toDate().toString(/*using QLocale::c() masks*/);
>
>    qWarning()<<fu.toTime(QTime(00,00,01,999));//output QVariant::toTime().toString(/*using QLocale::c() masks*/);
>
>    qWarning()<<fu.toDateTime(QDateTime(QDate(1901,01,01),QTime(00,00,01,999)));//output QVariant::toDateTime().toString(/*using QLocale::c() masks*/);
>
>    qWarning()<<fu.toInt(12);//output using QLocale::c().toString(QVariant::toInt(),'f',0)
>
>    qWarning()<<fu.toDouble(12.12);//output using QLocale::c().toString(QVariant::toDouble(),'f',6)
>
>    qWarning()<<fu.toCurrency(12.12);//output using QLocale::c().toString(QVariant::toDouble(),'f',2)
>}
>```
>## QStm::DateUtil
>Based on ***QVariant***, use to manipulate then types ***QDateTime, QDate, QTime***, contains functions to calculate datestime, ex: months, years, ranges and others. 
>```c++
>#include <QStm>
>
>void run()
>{
>     ...more
>}
>```
>## QStm::DoubleUtil
>Based on ***QVariant***, use to manipulate then types ***QCurrency, double, int, qlonglong***, contains functions to calculate numeric values, ex: conversions, ranges and others. 
>```c++
>#include <QStm>
>
>void Util::usingDoubleUtil()
>{
>    DoubleUtil dbu;
>
>    {//rearrange values
>        double vMin=2;
>        double vMax=1;
>        qWarning()<<dbu.checkBetween(vMin, vMax);//return true, function arrange max and min values
>    }
>
>    {//check and rearrange values
>        double vVal=1.5;
>        double vMin=2;
>        double vMax=1;
>        qWarning()<<dbu.checkBetween(vVal, vMin, vMax);//return true, function arrange max/min values and validate value
>    }
>}
>```