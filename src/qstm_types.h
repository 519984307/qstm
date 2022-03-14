#pragma once

#include "./qstm_global.h"
#include "./qstm_types_const.h"
#include <QObject>
#include <QVector>
#include <QVariant>
#include <QVariantHash>
#include <QString>
#include <QMetaProperty>
#include <QMutex>
#include <QMutexLocker>

//class QStmListen;
//class QStmListenProtocol;

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
typedef QMutexLocker<QMutex> QMutexLOCKER;
typedef QMetaType::Type QMetaTypeType;
#else
typedef QMutexLocker QMutexLOCKER;
typedef QVariant::Type QMetaTypeType;
#endif

namespace QStm {

//!
//! \brief The RequestMethod enum
//!
enum RequestMethod {Head=1, Get=2, Post=4, Put=8, Delete=16, Options=32, Patch=64, Trace=128, MaxMethod=Trace};

//!
//! \brief The QStm::Protocol enum
//!
enum Protocol {TcpSocket=1, UdpSocket=2, WebSocket=4, Mqtt=8, Amqp=16, Http=32, Https=64, rpcProtocolMin=TcpSocket, rpcProtocolMax=Https};

namespace Private {
const QHash<int, QString> &___ProtocolName();
const QHash<QString, int> &___ProtocolType();
const QHash<QString, QStm::RequestMethod> &___RequestMethodType();
const QHash<int, QString> &___RequestMethodName();
}

//!
//! \brief RequestMethodName
//!
static const auto &RequestMethodName=QStm::Private::___RequestMethodName();

//!
//! \brief RequestMethodNameList
//!
static const auto &RequestMethodNameList=RequestMethodName.values();

//!
//! \brief RequestMethodType
//!
static const auto &RequestMethodType=QStm::Private::___RequestMethodType();

//!
//! \brief QStm::ProtocolName
//!
static const auto &ProtocolName=QStm::Private::___ProtocolName();

//!
//! \brief QStm::ProtocolType
//!
static const auto &ProtocolType=QStm::Private::___ProtocolType();

}










