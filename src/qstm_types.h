#pragma once

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QString>
#include <QTemporaryFile>

typedef QVector<int> QStmVTypesList;

static const QStmVTypesList QStmTypesListString=QStmVTypesList()<<QVariant::Uuid<<QVariant::String<<QVariant::ByteArray<<QVariant::Char<<QVariant::BitArray;
static const QStmVTypesList QStmTypesListNumeric=QStmVTypesList()<<QVariant::LongLong<<QVariant::Int<<QVariant::UInt<<QVariant::ULongLong<<QVariant::Double;
static const QStmVTypesList QStmTypesListIntergers=QStmVTypesList()<<QVariant::LongLong<<QVariant::Int<<QVariant::UInt<<QVariant::ULongLong<<QVariant::Double;
static const QStmVTypesList QStmTypesListClass=QStmVTypesList()<<QVariant::Url<<QVariant::Map<<QVariant::Hash<<QVariant::List<<QVariant::StringList;
static const QStmVTypesList QStmTypesListObjects=QStmVTypesList()<<QVariant::Map<<QVariant::Hash<<QVariant::List<<QVariant::StringList;
static const QStmVTypesList QStmTypesListDates=QStmVTypesList()<<QVariant::Date<<QVariant::DateTime<<QVariant::Time;
static const QStmVTypesList QStmTypesListBool=QStmVTypesList()<<QVariant::Bool;

enum QStmRequestMethod {Head=1, Get=2, Post=4, Put=8, Delete=16, Options=32, MaxMethod=Options};

static const QHash<int,QString> ___QStmRequestMethodName(){
    QHash<int, QString> r;
    r.insert(Head,QT_STRINGIFY2(Head));
    r.insert(Get,QT_STRINGIFY2(Get));
    r.insert(Post,QT_STRINGIFY2(Post));
    r.insert(Put,QT_STRINGIFY2(Put));
    r.insert(Delete,QT_STRINGIFY2(Delete));
    r.insert(Options,QT_STRINGIFY2(Options));
    return r;
}
static const auto QStmRequestMethodName = ___QStmRequestMethodName();
static const auto QStmRequestMethodNameList = ___QStmRequestMethodName().values();

static const QHash<QString,QStmRequestMethod> ___QStmRequestMethodType(){
    QHash<QString,QStmRequestMethod> r;
    r.insert(QT_STRINGIFY2(head),Head);
    r.insert(QT_STRINGIFY2(get),Get);
    r.insert(QT_STRINGIFY2(post),Post);
    r.insert(QT_STRINGIFY2(put),Put);
    r.insert(QT_STRINGIFY2(delete),Delete);
    r.insert(QT_STRINGIFY2(options),Options);

    r.insert(QT_STRINGIFY2(Head),Head);
    r.insert(QT_STRINGIFY2(Get),Get);
    r.insert(QT_STRINGIFY2(Post),Post);
    r.insert(QT_STRINGIFY2(Put),Put);
    r.insert(QT_STRINGIFY2(Delete),Delete);
    r.insert(QT_STRINGIFY2(Options),Options);
    return r;
}
static const auto QStmRequestMethodType=___QStmRequestMethodType();
enum QStmProtocol {TcpSocket=1, UdpSocket=2, WebSocket=4, Mqtt=8, Amqp=16, Http=32, Https=64};
static const QHash<QString,QStmProtocol> ___QStmProtocolType(){
    QHash<QString,QStmProtocol> r;

    r.insert(QT_STRINGIFY2(TcpSocket),TcpSocket  );
    r.insert(QT_STRINGIFY2(UdpSocket),UdpSocket  );
    r.insert(QT_STRINGIFY2(WebSocket),WebSocket  );
    r.insert(QT_STRINGIFY2(Mqtt)     ,Mqtt       );
    r.insert(QT_STRINGIFY2(Amqp)     ,Amqp       );
    r.insert(QT_STRINGIFY2(Http)     ,Http       );
    r.insert(QT_STRINGIFY2(Https)    ,Https      );

    r.insert(QT_STRINGIFY2(tcp)      ,TcpSocket  );
    r.insert(QT_STRINGIFY2(udp)      ,UdpSocket  );
    r.insert(QT_STRINGIFY2(wss)      ,WebSocket  );
    r.insert(QT_STRINGIFY2(mqtt)     ,Mqtt       );
    r.insert(QT_STRINGIFY2(amqp)     ,Amqp       );
    r.insert(QT_STRINGIFY2(http)     ,Http       );
    r.insert(QT_STRINGIFY2(https)    ,Https      );
    return r;
}

static const QMap<QStmProtocol, QString> ___QStmProtocolName(){
    QMap<QStmProtocol, QString> r;
    r.insert(TcpSocket , QT_STRINGIFY2(tcpsocket));
    r.insert(UdpSocket , QT_STRINGIFY2(udpsocket));
    r.insert(WebSocket , QT_STRINGIFY2(websocket));
    r.insert(Mqtt      , QT_STRINGIFY2(mqtt)     );
    r.insert(Amqp      , QT_STRINGIFY2(amqp)     );
    r.insert(Http      , QT_STRINGIFY2(http)     );
    r.insert(Https     , QT_STRINGIFY2(https)    );
    return r;
}

static const QMap<QStmProtocol, QString> QStmProtocolName=___QStmProtocolName();
static const QHash<QString,QStmProtocol> QStmProtocolType=___QStmProtocolType();
static const QStmProtocol rpcProtocolMin=QStmProtocol(1);
static const QStmProtocol rpcProtocolMax=Https;
class QStmListen;
class QStmListenProtocol;


static bool ___registerMetaType(){
    return true;
}

static const auto registerMetaType=___registerMetaType();

static const auto vGET=/*QVariant*/("get");
static const auto vPOST=/*QVariant*/("post");
static const auto vPUT=/*QVariant*/("put");
static const auto vDELETE=/*QVariant*/("delete");

static const auto vObject=/*QVariant*/("object");
static const auto vList=/*QVariant*/("list");

static const auto vActions=/*QVariant*/("actions");
static const auto vAuto=/*QVariant*/"auto";
static const auto vText=/*QVariant*/("text");
static const auto vNumber=/*QVariant*/("number");
static const auto vNumeric=/*QVariant*/("numeric");
static const auto vInt=/*QVariant*/("int");
static const auto vDate=/*QVariant*/("date");
static const auto vTime=/*QVariant*/("time");
static const auto vDatetime=/*QVariant*/("datetime");
static const auto vCurrency=/*QVariant*/("currency");
static const auto vDouble=/*QVariant*/("double");
static const auto vBool=/*QVariant*/("bool");

static const auto vaStart=/*QVariant*/("start");
static const auto vaCenter=/*QVariant*/("center");
static const auto vaEnd=/*QVariant*/("end");

static const auto vpId="id";
static const auto vpName="name";
static const auto vpText="text";
static const auto vpHeaders="headers";
static const auto vpFilters="filters";
static const auto vpItems="items";
static const auto vpLinks="links";
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

static const auto driver_QODBC=("QODBC");
static const auto driver_QSQLITE=("QSQLITE");
static const auto driver_QPSQL=("QPSQL");
static const auto driver_QOIC=("QOIC");
static const auto driver_QMYSQL=("QMYSQL");
