#include "./qstm_setting_base.h"
#include "./qstm_types.h"
#include "./qstm_meta_types.h"
#include <QStandardPaths>
#include <QProcess>
#include <QDateTime>
#include <QVariantHash>
#include <QVariantList>
#include <QVariantHash>
#include <QStringList>
#include <QFile>
#include <QSettings>
#include <QMetaMethod>
#include <QMetaProperty>
#include <QJsonDocument>
#include <QJsonObject>

namespace QStm {

#define dPvt()\
    auto&p = *reinterpret_cast<SettingBasePrv*>(this->p)

class SettingBasePrv{
public:
    QObject*parent=nullptr;
    QVariantHash headers;
    QVariantHash parameters;
    QVariant body;
    QString method;
    QVariant protocol;
    QString driverName;
    QString hostName;
    QVariant route;
    QString path;
    QString userName;
    QString password;
    int port=-1;
    int cacheInterval=0;
    bool cacheCleanup=false;
    int cacheCleanupInterval=0;

    explicit SettingBasePrv(QObject*parent)
    {
        this->parent=parent;
    }

    virtual ~SettingBasePrv()
    {
    }
};


SettingBase::SettingBase(QObject *parent):SettingBaseTemplate<SettingBase>(parent)
{
    this->p = new SettingBasePrv(this);
}

SettingBase::~SettingBase()
{
    dPvt();delete&p;
}

QVariant SettingBase::url()const
{
    QVariantList vList;
    auto vRouteList=this->routeList();
    if(vRouteList.isEmpty() && !this->route().toString().isEmpty())
        vRouteList<<this->route();

    for(auto&v:vRouteList){
        auto route=v.toString().trimmed();
        auto url=qsl("%1:%2/%3").arg(this->hostName()).arg(this->port()).arg(route);
        while(url.contains(qsl("//")))
            url=url.replace(qsl("//"), qsl("/"));


        switch (qTypeId(protocol())) {
        case QMetaType_QVariantList:
        case QMetaType_QStringList:
        {
            auto record=this->protocol().toList();
            for(const auto&v:record){
                QString protocol;
                switch (qTypeId(v)) {
                case QMetaType_Int:
                    protocol=QStmProtocolName.value(v.toInt());
                    break;
                case QMetaType_QString:
                case QMetaType_QByteArray:
                    protocol=v.toString().toLower();
                    break;
                default:
                    continue;
                }
                vList<<qsl("%1://%2").arg(protocol,url);
            }
            break;
        }
        default:
            const auto protocol=this->protocol().toString();
            vList<<qsl("%1://%2").arg(protocol,url);;
        }
    }
    QVariant __return=(vList.size()==1)?vList.first():vList;
    return __return;
}

QString SettingBase::service() const
{
    return this->identification();
}

SettingBase &SettingBase::setService(const QString &value)
{
    this->setIdentification(value);
    return*this;
}

QVariantHash SettingBase::headers() const
{
    dPvt();
    return p.headers;
}

SettingBase &SettingBase::setHeaders(const QVariantHash &value)
{
    dPvt();
    p.headers = value;
    return*this;
}

QVariant SettingBase::protocol() const
{
    dPvt();
    return p.protocol;
}

SettingBase &SettingBase::setProtocol(const QVariant &value)
{
    dPvt();
    switch (qTypeId(value)) {
    case QMetaType_Int:
    case QMetaType_UInt:
    case QMetaType_Double:
    case QMetaType_LongLong:
    case QMetaType_ULongLong:
        p.protocol=QStmProtocolName.value(value.toInt());
        break;
    default:
        p.protocol=value;
    }
    return*this;
}

QString SettingBase::method() const
{
    dPvt();
    return p.method;
}

SettingBase &SettingBase::setMethod(const QString &value)
{
    dPvt();
    p.method=value;
    return*this;
}

QString SettingBase::driverName() const
{
    dPvt();
    return p.driverName;
}

SettingBase &SettingBase::setDriverName(const QString &value)
{
    dPvt();
    p.driverName=value;
    return*this;
}

QString SettingBase::hostName() const
{
    dPvt();
    return this->parseVariables(p.hostName).toString();
}

SettingBase &SettingBase::setHostName(const QString &value)
{
    dPvt();
    p.hostName = value.trimmed();
    return*this;
}

QString SettingBase::userName() const
{
    dPvt();
    return this->parseVariables(p.userName).toString();
}

SettingBase &SettingBase::setUserName(const QString &value)
{
    dPvt();
    p.userName = value.trimmed();
    return*this;
}

QString SettingBase::password() const
{
    dPvt();
    return p.password;
}

SettingBase &SettingBase::setPassword(const QString &value)
{
    dPvt();
    p.password = value.trimmed();
    return*this;
}

int SettingBase::port() const
{
    dPvt();
    return p.port;
}

SettingBase &SettingBase::setPort(int value)
{
    dPvt();
    p.port = value;
    return*this;
}

QVariant SettingBase::route() const
{
    dPvt();
    return this->parseVariables(p.route).toString();
}

QVariantList SettingBase::routeList() const
{
    dPvt();
    const auto&vRoute=p.route;
    QVariantList vRouteList=vRoute.toList();
    if(vRouteList.isEmpty()){
        auto route=vRoute.toString().trimmed();
        if(!route.isEmpty())
            vRouteList<<route;
    }
    for(auto&v:vRouteList)
        v=this->parseVariables(v.toString().trimmed());
    return vRouteList;
}

SettingBase &SettingBase::setRoute(const QVariant &value)
{
    dPvt();
    p.route = value;
    return*this;
}

QString SettingBase::path() const
{
    dPvt();
    return this->parseVariables(p.path).toString();
}

SettingBase &SettingBase::setPath(const QString &value)
{
    dPvt();
    p.path = value.trimmed();
    return*this;
}

QVariantHash SettingBase::parameters() const
{
    dPvt();
    return p.parameters;
}

SettingBase &SettingBase::setParameters(const QVariantHash &value)
{
    dPvt();
    p.parameters=value;
    return*this;
}

QVariant SettingBase::body() const
{
    dPvt();
    return p.body;
}

SettingBase &SettingBase::setBody(const QVariant &value)
{
    dPvt();
    p.body=value;
    return*this;
}

int SettingBase::cacheInterval() const
{
    dPvt();
    return this->parseInterval(p.cacheInterval, defaultInterval).toInt();
}

SettingBase &SettingBase::setCacheInterval(const QVariant &value)
{
    dPvt();
    p.cacheInterval=value.toInt();
    return*this;
}

bool SettingBase::cacheCleanup() const
{
    dPvt();
    return p.cacheCleanup;
}

SettingBase &SettingBase::setCacheCleanup(const QVariant &value)
{
    dPvt();
    p.cacheCleanup=value.toBool();
    return*this;
}

int SettingBase::cacheCleanupInterval() const
{
    dPvt();
    return this->parseInterval(p.cacheCleanupInterval).toInt();
}

SettingBase &SettingBase::setCacheCleanupInterval(const QVariant &value)
{
    dPvt();
    p.cacheCleanupInterval=value.toInt();
    return*this;
}

}

