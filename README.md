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
>void run()
>{
>     ...more
>}
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
>>#include <QStm>
>
>void run()
>{
>     ...more
>}
>```
>## QStm::VariantUtil
>Based on ***QVariant***, used to manipulate ***QVariant*** types.
>>Simplify conversion of json values em ***QVariantList*** and ***QVariantHash***.
>>Simplify conversion of ***QVariant*** to others ***QVariant*** types.
>>Functions to handle md5 and uuid values ​​for ***QVariant***
>```c++
>>#include <QStm>
>
>void run()
>{
>     ...more
>}
>```
>## QStm::FormattingUtil
>Based on ***QVariant***, using masks to manipulate ***QVariant*** formatting values to especific types ***QDateTime, QDate, QTime, QCurrence, Double, Int, ....*** .
>```c++
>>#include <QStm>
>
>void run()
>{
>     ...more
>}
>```
>## QStm::DateUtil
>Based on ***QVariant***, use to manipulate then types ***QDateTime, QDate, QTime***, contains functions to calculate datestime, ex: months, years, ranges and others. 
>```c++
>>#include <QStm>
>
>void run()
>{
>     ...more
>}
>```
>## QStm::DoubleUtil
>Based on ***QVariant***, use to manipulate then types ***QCurrence, double, int, qlonglong***, contains functions to calculate numeric values, ex: conversions, ranges and others. 
>```c++
>>#include <QStm>
>
>void run()
>{
>     ...more
>}
>```