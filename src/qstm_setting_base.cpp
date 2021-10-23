#include "./qstm_setting_base.h"
#include "./qstm_types.h"
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

    explicit SettingBasePrv(QObject*parent){
        this->parent=parent;
    }
    virtual ~SettingBasePrv(){
    }
};


SettingBase::SettingBase(QObject *parent):BaseSetting(parent){
    this->p = new SettingBasePrv(this);
}

SettingBase::~SettingBase(){
    dPvt();delete&p;
}

QVariant SettingBase::url()const
{
    dPvt();
    QVariantList vList;
    for(auto&v:this->routeList()){
        auto route=v.toString().trimmed();
        auto url=qsl("%1:%2/%3").arg(p.hostName).arg(p.port).arg(route);
        while(url.contains(qsl("//")))
            url=url.replace(qsl("//"), qsl("/"));
        if(p.protocol.canConvert(p.protocol.Map) || p.protocol.canConvert(p.protocol.List)){
            auto record=p.protocol.toList();
            for(const auto&v:record){
                QString protocol;
                if(v.canConvert(v.Int))
                    protocol=QStmProtocol(v.toInt());
                else if(v.canConvert(v.String))
                    protocol=v.toString().toLower();
                else
                    continue;

                vList<<qsl("%1://%2").arg(protocol,url);
            }
        }
        else{
            const auto protocol=p.protocol.toString();
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

void SettingBase::setService(const QString &value)
{
    this->setIdentification(value);
}

QVariantHash SettingBase::headers() const
{
    dPvt();
    return p.headers;
}

void SettingBase::setHeaders(const QVariantHash &value)
{
    dPvt();
    p.headers = value;
}

QVariant SettingBase::protocol() const
{
    dPvt();
    return p.protocol;
}

void SettingBase::setProtocol(const QVariant &value)
{
    dPvt();
    if(value.type()==value.Int || value.type()==value.UInt || value.type()==value.Double || value.type()==value.LongLong || value.type()==value.ULongLong){
        auto v=value.toInt();
        auto i=QStmProtocol(v);
        p.protocol=QStmProtocolType.key(i);
    }
    else{
        p.protocol=value;
    }
}

QString SettingBase::method() const
{
    dPvt();
    return p.method;
}

void SettingBase::setMethod(const QString &value)
{
    dPvt();
    p.method=value;
}

QString SettingBase::driverName() const
{
    dPvt();
    return p.driverName;
}

void SettingBase::setDriverName(const QString &value)
{
    dPvt();
    p.driverName=value;
}

QString SettingBase::hostName() const
{
    dPvt();
    return this->parseVariables(p.hostName).toString();
}

void SettingBase::setHostName(const QString &value)
{
    dPvt();
    p.hostName = value.trimmed();
}

QString SettingBase::userName() const
{
    dPvt();
    return this->parseVariables(p.userName).toString();
}

void SettingBase::setUserName(const QString &value)
{
    dPvt();
    p.userName = value.trimmed();
}

QString SettingBase::password() const
{
    dPvt();
    return p.password;
}

void SettingBase::setPassword(const QString &value)
{
    dPvt();
    p.password = value.trimmed();
}

int SettingBase::port() const
{
    dPvt();
    return p.port;
}

void SettingBase::setPort(int value)
{
    dPvt();
    p.port = value;
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

void SettingBase::setRoute(const QVariant &value)
{
    dPvt();
    p.route = value;
}

QString SettingBase::path() const
{
    dPvt();
    return this->parseVariables(p.path).toString();
}

void SettingBase::setPath(const QString &value)
{
    dPvt();
    p.path = value.trimmed();
}

QVariantHash SettingBase::parameters() const
{
    dPvt();
    return p.parameters;
}

void SettingBase::setParameters(const QVariantHash &value)
{
    dPvt();
    p.parameters=value;
}

QVariant SettingBase::body() const
{
    dPvt();
    return p.body;
}

void SettingBase::setBody(const QVariant &value)
{
    dPvt();
    p.body=value;
}

int SettingBase::cacheInterval() const
{
    dPvt();
    return this->parseInterval(p.cacheInterval, defaultInterval).toInt();
}

void SettingBase::setCacheInterval(const QVariant &value)
{
    dPvt();
    p.cacheInterval=value.toInt();
}

bool SettingBase::cacheCleanup() const
{
    dPvt();
    return p.cacheCleanup;
}

void SettingBase::setCacheCleanup(const QVariant &value)
{
    dPvt();
    p.cacheCleanup=value.toBool();
}

int SettingBase::cacheCleanupInterval() const
{
    dPvt();
    return this->parseInterval(p.cacheCleanupInterval).toInt();
}

void SettingBase::setCacheCleanupInterval(const QVariant &value)
{
    dPvt();
    p.cacheCleanupInterval=value.toInt();
}

}

