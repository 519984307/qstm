#pragma once

#include "./qstm_global.h"
#include <QObject>
#include <QVector>
#include <QVariant>
#include <QVariantHash>
#include <QString>
#include <QMetaProperty>
#include <QMutex>
#include <QMutexLocker>


#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
typedef QMutexLocker<QMutex> QMutexLOCKER;
typedef QMetaType::Type QMetaTypeType;
#else
typedef QMutexLocker QMutexLOCKER;
typedef QVariant::Type QMetaTypeType;
#endif

enum QStmRequestMethod {Head=1, Get=2, Post=4, Put=8, Delete=16, Options=32, MaxMethod=Options};

const QHash<int,QString> ___QStmRequestMethodName();
static const auto QStmRequestMethodName = ___QStmRequestMethodName();
static const auto QStmRequestMethodNameList = ___QStmRequestMethodName().values();

const QHash<QString,QStmRequestMethod> ___QStmRequestMethodType();
static const auto QStmRequestMethodType=___QStmRequestMethodType();
enum QStmProtocol {TcpSocket=1, UdpSocket=2, WebSocket=4, Mqtt=8, Amqp=16, Http=32, Https=64};
const QHash<QString,int> ___QStmProtocolType();

const QHash<int, QString> ___QStmProtocolName();

static const auto QStmProtocolName=___QStmProtocolName();
static const auto qStmProtocolType=___QStmProtocolType();
static const auto rpcProtocolMin=QStmProtocol(1);
static const auto rpcProtocolMax=Https;
class QStmListen;
class QStmListenProtocol;


bool ___registerMetaType();

static const auto registerMetaType=___registerMetaType();

static const auto vGET="get";
static const auto vPOST="post";
static const auto vPUT="put";
static const auto vDELETE="delete";

static const auto vObject="object";
static const auto vList="list";

static const auto vActions="actions";
static const auto vAuto="auto";
static const auto vText="text";
static const auto vNumber="number";
static const auto vNumeric="numeric";
static const auto vInt="int";
static const auto vDate="date";
static const auto vTime="time";
static const auto vDatetime="datetime";
static const auto vCurrency="currency";
static const auto vDouble="double";
static const auto vBool="bool";

static const auto vaStart="start";
static const auto vaCenter="center";
static const auto vaEnd="end";

static const auto vpId="id";
static const auto vpName="name";
static const auto vpText="text";
static const auto vpHeaders="headers";
static const auto vpFilters="filters";
static const auto vpItems="items";
static const auto vpLinks="links";
static const auto vpResultInfo="resultInfo";
static const auto vpFlags="flags";
static const auto vpEdit="edit";
static const auto vpPerfumery="perfumerys";
static const auto vpSortBy="sort-by";
static const auto vpSortDesc="sort-desc";

static const auto vpDefault="default";
static const auto vpActions="actions";
static const auto vpOrder="order";
static const auto vpValue="value";
static const auto vpColor="color";
static const auto vpFont="font";
static const auto vpType="type";
static const auto vpLayout="layout";
static const auto vpLength="length";
static const auto vpAlign="align";
static const auto vpWidth="width";
static const auto vpOptions="options";
static const auto vpEditable="editable";
static const auto vpVisible="visible";
static const auto vpFiltrable="filtrable";
static const auto vpFilterStyle="filterStyle";
static const auto vpSortable="sortable";
static const auto vpReadOnly="readOnly";
static const auto vpDefaultValue="defaultValue";
static const auto vpDefaultSelect="defaultSelect";
static const auto vpInputType="inputType";
static const auto vpInputMask="inputMask";
static const auto vtInputLinks="inputlinks";
static const auto vpFiltrableStrategy="searchStrategy";

static const auto vtInputCurrency="inputcurrency";
static const auto vtInputNumber="inputnumber";
static const auto vtInputDouble="inputdouble";
static const auto vtInputText="inputtext";
static const auto vtInputPhone="inputphone";
static const auto vtInputMail="inputemail";
static const auto vtInputTextMask="inputtextmask";
static const auto vtInputTextArea="inputtextarea";
static const auto vtInputDate="inputdate";
static const auto vtInputTime="inputtime";
static const auto vtInputUuid="inputuiid";
static const auto vtInputMd5="inputmd5";
static const auto vtInputDateTime="inputdatetime";
static const auto vtInputCalendar="inputcalendar";
static const auto vtSearchBox="searchbox";
static const auto vtSelectBox="selectbox";
static const auto vtRadioBox="radiobox";
static const auto vtCheckBox="checkbox";
static const auto vtInputAddress="inputaddress";

static const auto vpOutput="output";
static const auto vpRoute="route";

static const auto driver_QODBC="QODBC";
static const auto driver_QSQLITE="QSQLITE";
static const auto driver_QPSQL="QPSQL";
static const auto driver_QOIC="QOIC";
static const auto driver_QMYSQL="QMYSQL";
