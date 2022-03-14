#include "./qstm_types.h"
#include <QCoreApplication>

namespace QStm {
namespace Private {
const QHash<int, QString> &___ProtocolName()
{
    static QHash<int, QString> __return;
    __return.insert(TcpSocket, QT_STRINGIFY2(tcpsocket));
    __return.insert(UdpSocket, QT_STRINGIFY2(udpsocket));
    __return.insert(WebSocket, QT_STRINGIFY2(websocket));
    __return.insert(Mqtt, QT_STRINGIFY2(mqtt));
    __return.insert(Amqp, QT_STRINGIFY2(amqp));
    __return.insert(Http, QT_STRINGIFY2(http));
    __return.insert(Https, QT_STRINGIFY2(https));
    return __return;
}

const QHash<QString, int> &___ProtocolType()
{
    static QHash<QString, int> __return;

    __return.insert(QT_STRINGIFY2(TcpSocket), TcpSocket);
    __return.insert(QT_STRINGIFY2(UdpSocket), UdpSocket);
    __return.insert(QT_STRINGIFY2(WebSocket), WebSocket);
    __return.insert(QT_STRINGIFY2(Mqtt), Mqtt);
    __return.insert(QT_STRINGIFY2(Amqp), Amqp);
    __return.insert(QT_STRINGIFY2(Http), Http);
    __return.insert(QT_STRINGIFY2(Https), Https);

    __return.insert(QT_STRINGIFY2(tcp), TcpSocket);
    __return.insert(QT_STRINGIFY2(udp), UdpSocket);
    __return.insert(QT_STRINGIFY2(wss), WebSocket);
    __return.insert(QT_STRINGIFY2(mqtt), Mqtt);
    __return.insert(QT_STRINGIFY2(amqp), Amqp);
    __return.insert(QT_STRINGIFY2(http), Http);
    __return.insert(QT_STRINGIFY2(https), Https);
    return __return;
}

const QHash<QString, QStm::RequestMethod> &___RequestMethodType()
{
    static QHash<QString, QStm::RequestMethod> __return;
    __return.insert(QT_STRINGIFY2(head), Head);
    __return.insert(QT_STRINGIFY2(get), Get);
    __return.insert(QT_STRINGIFY2(post), Post);
    __return.insert(QT_STRINGIFY2(put), Put);
    __return.insert(QT_STRINGIFY2(delete), Delete);
    __return.insert(QT_STRINGIFY2(options), Options);
    __return.insert(QT_STRINGIFY2(patch), Patch);
    __return.insert(QT_STRINGIFY2(trace), Trace);

    __return.insert(QT_STRINGIFY2(Head), Head);
    __return.insert(QT_STRINGIFY2(Get), Get);
    __return.insert(QT_STRINGIFY2(Post), Post);
    __return.insert(QT_STRINGIFY2(Put), Put);
    __return.insert(QT_STRINGIFY2(Delete), Delete);
    __return.insert(QT_STRINGIFY2(Options), Options);
    __return.insert(QT_STRINGIFY2(Patch), Patch);
    __return.insert(QT_STRINGIFY2(Trace), Trace);
    return __return;
}

const QHash<int, QString> &___RequestMethodName()
{
    static QHash<int, QString> __return;
    __return.insert(Head, QT_STRINGIFY2(Head));
    __return.insert(Get, QT_STRINGIFY2(Get));
    __return.insert(Post, QT_STRINGIFY2(Post));
    __return.insert(Put, QT_STRINGIFY2(Put));
    __return.insert(Delete, QT_STRINGIFY2(Delete));
    __return.insert(Options, QT_STRINGIFY2(Options));
    return __return;
}
} // namespace Private
} // namespace QStm

////initialize statict variables
//QStm::Protocol rpcProtocolMin=QStm::Protocol::TcpSocket;
//QStm::Protocol rpcProtocolMax=QStm::Protocol::Https;
//QHash<int, QString> RequestMethodName = ___RequestMethodName();
//QList<QString> RequestMethodNameList = ___RequestMethodName().values();
//QHash<QString, RequestMethod> RequestMethodType=___RequestMethodType();
//QHash<int, QString> QStm::ProtocolName=___QStm::ProtocolName();
//QHash<QString, int> QStm::ProtocolType=___QStm::ProtocolType();

//void init()
//{
//    RequestMethodName = ___RequestMethodName();
//    RequestMethodNameList = ___RequestMethodName().values();
//    RequestMethodType = ___RequestMethodType();
//    QStm::ProtocolName = ___QStm::ProtocolName();
//    QStm::ProtocolType = ___QStm::ProtocolType();
//}

//Q_COREAPP_STARTUP_FUNCTION(init)
