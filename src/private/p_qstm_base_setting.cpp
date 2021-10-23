#include "./p_qstm_base_setting.h"
#include "./qstm_types.h"
#include "./qstm_util_variant.h"
#include "./qstm_util_date.h"
#include "./qstm_util_meta_object.h"
#include <math.h>
#include <QStandardPaths>
#include <QCoreApplication>
#include <QProcess>
#include <QDebug>
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

namespace PrivateQStm {
Q_GLOBAL_STATIC(QVariantHash, static_dirs)
//    Q_GLOBAL_STATIC(QVariantHash, static_variables)
}

namespace QStm {

auto &static_dirs=*PrivateQStm::static_dirs;
//auto &static_variables=*PrivateQStm::static_variables;

static QVariantHash &make_static_variables()
{
    auto &dir=static_dirs;

#ifndef Q_OS_IOS
    QProcess process;
    auto lst = process.environment();
    for(auto&v:lst){
        auto s=v.split(qsl("="));
        auto env=s.first().trimmed();
        auto value=s.last().trimmed();
        dir.insert(env, value);
    }
#endif
    dir.insert(qsl("$DesktopLocation"      ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation      ) );
    dir.insert(qsl("$DocumentsLocation"    ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation    ) );
    dir.insert(qsl("$FontsLocation"        ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::FontsLocation        ) );
    dir.insert(qsl("$ApplicationsLocation" ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation ) );
    dir.insert(qsl("$MusicLocation"        ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::MusicLocation        ) );
    dir.insert(qsl("$MoviesLocation"       ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::MoviesLocation       ) );
    dir.insert(qsl("$PicturesLocation"     ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::PicturesLocation     ) );
    dir.insert(qsl("$TempLocation"         ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::TempLocation         ) );
    dir.insert(qsl("$HomeLocation"         ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::HomeLocation         ) );
    dir.insert(qsl("$DataLocation"         ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::DataLocation         ) );
    dir.insert(qsl("$CacheLocation"        ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::CacheLocation        ) );
    dir.insert(qsl("$GenericDataLocation"  ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation  ) );
    dir.insert(qsl("$RuntimeLocation"      ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::RuntimeLocation      ) );
    dir.insert(qsl("$ConfigLocation"       ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::ConfigLocation       ) );
    dir.insert(qsl("$DownloadLocation"     ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::DownloadLocation     ) );
    dir.insert(qsl("$GenericCacheLocation" ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation ) );
    dir.insert(qsl("$GenericConfigLocation").trimmed(), QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) );
    dir.insert(qsl("$AppDataLocation"      ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::AppDataLocation      ) );
    dir.insert(qsl("$AppConfigLocation"    ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation    ) );
    dir.insert(qsl("$AppLocalDataLocation" ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation ) );

    dir.insert(qsl("$HOME"),QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    dir.insert(qsl("$TEMPDIR"),QStandardPaths::writableLocation(QStandardPaths::TempLocation));
    dir.insert(qsl("$APPDIR"),QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation));
    dir.insert(qsl("$APPNAME"),qApp->applicationName());

    return dir;
}

static auto &static_variables=make_static_variables();

#define dPvt()\
    auto&p = *reinterpret_cast<BaseSettingPrv*>(this->p)

class BaseSettingPrv{
public:
    QObject*parent=nullptr;
    QString identification;
    QVariantHash variables;
    QString name;
    bool enabled=false;
    QVariant activityLimit=defaultLimit;
    QVariant activityInterval=defaultInterval;
    QVariant activityThread=0;
    QVariant memoryLimit=0;

    static QVariant staticReplaceString(const QVariantHash&static_variables, const QVariant&v){
        QString value;
        if(v.type()==v.Map || v.type()==v.Hash || v.type()==v.List || v.type()==v.StringList){
            value=QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
        }
        else{
            value=v.toByteArray();
        }

        if(value.contains(qsl("$"))){
            {//static dir
                QHashIterator<QString, QVariant> i(static_variables);
                while (i.hasNext()) {
                    i.next();
                    auto key=i.key();
                    const auto k=QString(qsl("$")+key)
                                       .replace(qsl("$$"),qsl("$"))
                                       .replace(qsl("${%1}").arg(key), qsl("$%1").arg(key));
                    const auto v=i.value().toString().trimmed();
                    value=value.replace(k,v);
                }
            }
        }

        if(v.type()==v.Map || v.type()==v.Hash || v.type()==v.List || v.type()==v.StringList){
            auto v=QJsonDocument::fromJson(value.toUtf8()).toVariant();
            return v;
        }

        return value;
    }

    static const QVariant replaceEnvStatic(const QVariant&v){
        auto value=v;
        value=staticReplaceString(static_variables, value);
        return value;
    }

    QVariant replaceEnv(const QVariant&v)const{
        auto value=v;
        value=staticReplaceString(static_variables, value);
        value=staticReplaceString(variables, value);
        return value;
    }

    static const QVariant getAlpha(const QVariant&v){
        auto num=qsl("0123456789,.");
        QString r;
        auto ss=v.toString();
        for(auto&v:ss){
            if(!num.contains(v))
                r+=v;
        }
        return r;
    }

    static const QVariant getNumber(const QVariant&v){
        auto num=qsl("0123456789,.");
        QString r,ss;
        if(v.type()==v.Double)
            ss=QString::number(v.toDouble(),'f',11);
        else if(v.toLongLong()>0)
            ss=QString::number(v.toLongLong(),'f',0);
        else
            ss=v.toString();

        for(auto&c:ss){
            if(num.contains(c))
                r+=c;
        }
        return r;
    }

    static QVariant getInterval(const QVariant&v, const QVariant&defaultV=QVariant()){
        Q_DECLARE_DU;
        return du.parseInterval(v,defaultV);
    }

    QVariant getMemoryBytes(const QVariant&v, const QVariant&defaultV=QVariant()){
        if(v.isNull() || !v.isValid() || v.toLongLong()<0)
            return defaultV;
        else if(v.type()==v.LongLong || v.type()==v.ULongLong || v.type()==v.Int || v.type()==v.UInt || v.type()==v.Double)
            return v;
        else{
            qlonglong scale=1;
            static qlonglong KB=1024;
            static qlonglong K=1024;

            auto a=getAlpha(v).toString().toLower();
            if(a==qsl("kb"))
                scale=1;
            else if(a==qsl("mb"))
                scale=2;
            else if(a==qsl("gb"))
                scale=3;
            else if(a==qsl("tb"))
                scale=4;
            else if(a==qsl("pb"))
                scale=5;
            else if(a==qsl("eb"))
                scale=6;
            else if(a==qsl("zb"))
                scale=7;
            else if(a==qsl("yb"))
                scale=8;
            else
                scale=1;//ms

            auto iN=getNumber(v);
            auto i=iN.toLongLong();
            i*=KB*pow(K, scale);
            if(i<=0)
                i=getMemoryBytes(defaultV).toLongLong();
            return i;
        }
        return 0;
    }


    explicit BaseSettingPrv(QObject*parent){
        this->parent=parent;
    }
    virtual ~BaseSettingPrv(){
    }
};


BaseSetting::BaseSetting(QObject *parent):QStm::Object(parent){
    this->p = new BaseSettingPrv(this);
}

BaseSetting::~BaseSetting(){
    dPvt();delete&p;
}

void BaseSetting::print()const
{
    VariantUtil vu;
    auto vMap=toHash();
    if(!vMap.isEmpty()){
        sInfo()<<qsl_fy(settings);
        QHashIterator<QString, QVariant> i(vMap);
        while (i.hasNext()){
            i.next();
            sInfo()<<qsl("      %1:%2").arg(i.key(), vu.toByteArray(i.value()));
        }
        sInfo()<<qsl_space;
    }
}

QVariant BaseSetting::parseVariables(const QVariant &v)const
{
    dPvt();
    return p.replaceEnv(v);
}

const QVariant BaseSetting::staticParseVariables(const QVariant &v)
{
    auto value=BaseSettingPrv::replaceEnvStatic(v);
    return value;
}

QVariant BaseSetting::variable(const QString &v) const
{
    dPvt();
    auto var=p.variables.value(v);
    return var.isValid()?var:p.replaceEnv(var);
}

const QVariant BaseSetting::parseAlpha(const QVariant &v)
{
    return BaseSettingPrv::getAlpha(v);
}

const QVariant BaseSetting::parseNumber(const QVariant &v)
{
    return BaseSettingPrv::getNumber(v);
}

const QVariant BaseSetting::parseInterval(const QVariant &v)
{
    return BaseSettingPrv::getInterval(v, QVariant());
}

const QVariant BaseSetting::parseInterval(const QVariant &v, const QVariant&interval)
{
    return BaseSettingPrv::getInterval(v, interval);
}

const QVariantHash&BaseSetting::staticVariables()
{
    return static_variables;
}

void BaseSetting::setStaticVariables(const QVariantHash &v)
{
    static_variables=v;
    QHashIterator<QString, QVariant> i(static_dirs);
    while (i.hasNext()){
        i.next();
        static_variables.insert(i.key(), i.value());
    }
    static_variables.clear();
}

bool BaseSetting::macth(const QString &name)
{
    auto i_name=this->name();
    auto startWith=i_name.contains(qbl("*"));
    if(startWith){
        i_name=i_name.split(qbl("*")).first();
    }
    if(startWith && name.startsWith(i_name))
        return true;
    else if((name==i_name))
        return true;
    else
        return false;
}

void BaseSetting::clear()
{
    for (int row = 0; row < this->metaObject()->propertyCount(); ++row) {
        auto property=this->metaObject()->property(row);
        if(QByteArray(property.name())==QT_STRINGIFY2(objectName))
            continue;
        else{
            auto type=property.type();
            if((type==QVariant::Int) || (type==QVariant::UInt) || (type==QVariant::LongLong) || (type==QVariant::ULongLong) || (type==QVariant::Double))
                property.write(this,0);
            else if(type==QVariant::Date)
                property.write(this,QDate());
            else if(type==QVariant::Time)
                property.write(this,QTime());
            else if(type==QVariant::DateTime)
                property.write(this,QDateTime());
            else if(type==QVariant::Hash)
                property.write(this,QVariantHash());
            else if(type==QVariant::Map)
                property.write(this,QVariant());
            else if(type==QVariant::List)
                property.write(this,QVariantList());
            else if(type==QVariant::StringList)
                property.write(this,QStringList());
            else if(type==QVariant::String || type==QVariant::ByteArray || type==QVariant::Char || type==QVariant::BitArray)
                property.write(this,qbl_null);
            else if(type==QVariant::LongLong || type==QVariant::ULongLong || type==QVariant::Int || type==QVariant::UInt || type==QVariant::Double)
                property.write(this,0);
            else if(type==QVariant::StringList)
                property.write(this,QStringList());
            else if(type==QVariant::StringList)
                property.write(this,QStringList());
            else
                property.write(this,QVariant());
        }
    }
}

bool BaseSetting::isValid()const
{
    for (int row = 0; row < this->metaObject()->propertyCount(); ++row) {
        auto property=this->metaObject()->property(row);
        if(QByteArray(property.name())==QT_STRINGIFY2(objectName))
            continue;
        else{
            auto vGet = property.read(this);
            if(vGet.isValid()){
                auto t=vGet.type();
                if((t==vGet.String || t==vGet.ByteArray || t==vGet.Char) && vGet.toString().trimmed().isEmpty())
                    continue;
                else if((t==vGet.Double || t==vGet.Int || t==vGet.UInt || t==vGet.LongLong || t==vGet.ULongLong) && vGet.toLongLong()>0)
                    continue;
                else if((t==vGet.Map || t==vGet.Hash) && vGet.toHash().isEmpty())
                    continue;
                else if((t==vGet.List || t==vGet.StringList) && vGet.toList().isEmpty())
                    continue;
                else
                    return true;
            }
        }
    }
    return false;
}

QVariantMap BaseSetting::toMap()const
{
    if(!this->isValid())
        return QVariantMap();
    else{
        QVariantMap RETURN;
        for (int row = 0; row < this->metaObject()->propertyCount(); ++row) {
            auto property=this->metaObject()->property(row);
            if(QByteArray(property.name())==QT_STRINGIFY2(objectName))
                continue;
            else{
                const auto key=property.name();
                const auto value = property.read(this);
                if(!value.isNull())
                    RETURN.insert(key, value);
            }
        }
        return RETURN;
    }
}

QVariantHash BaseSetting::toHash() const
{
    if(!this->isValid())
        return QVariantHash();
    else{
        QVariantHash RETURN;
        for (int row = 0; row < this->metaObject()->propertyCount(); ++row) {
            auto property=this->metaObject()->property(row);
            if(QByteArray(property.name())==QT_STRINGIFY2(objectName))
                continue;
            else{
                const auto key=property.name();
                const auto value = property.read(this);
                if(!value.isNull())
                    RETURN.insert(key, value);
            }
        }
        return RETURN;
    }
}

bool BaseSetting::fromSetting(const BaseSetting &v)
{
    auto o=&v;
    if(o!=nullptr)
        return this->fromHash(v.toHash());
    else
        return false;
}

bool BaseSetting::fromHash(const QVariantHash &v)
{
    this->clear();
    VariantUtil vu;
    QVariantHash vMap;
    QHashIterator<QString, QVariant> i(v);
    while (i.hasNext()){
        i.next();
        vMap.insert(i.key().toLower(), i.value());
    }

    auto metaObject = this->metaObject();
    QStm::MetaObjectUtil metaObjectUtil(*metaObject);
    auto propertyList=metaObjectUtil.toPropertyList();
    bool __return=!v.isEmpty();
    for(auto&property:propertyList){
        if(QByteArray(property.name())==QT_STRINGIFY2(objectName))
            continue;
        else{
            auto key = QString(property.name()).toLower();
            auto value = vMap.value(key);
            auto type=property.type();
            if(value.isNull() || !value.isValid())
                continue;
            else if(property.write(this,value))
                continue;
            else if(type==QVariant::Int || type==QVariant::UInt)
                property.write(this,value.toInt());
            else if(type==QVariant::LongLong || type==QVariant::ULongLong)
                property.write(this,value.toLongLong());
            else if(type==QVariant::Double)
                property.write(this,value.toDouble());
            else if(type==QVariant::Hash)
                property.write(this, vu.toHash(value));
            else if(type==QVariant::Map)
                property.write(this, vu.toMap());
            else if(type==QVariant::List)
                property.write(this, vu.toList());
            else if(type==QVariant::StringList)
                property.write(this, vu.toStringList());
            else
                __return=false;

        }
    }
    return __return;
}

bool BaseSetting::fromMap(const QVariantMap &v)
{
    return this->fromHash(QVariant(v).toHash());
}

bool BaseSetting::fromVariant(const QVariant&v)
{
    bool __return=true;
    VariantUtil vu;
    auto vv=vu.toVariantObject(v);
    if((vv.type()==vv.Hash) || (vv.type()==vv.Map)){
        __return=this->fromHash(vv.toHash());
    }
    else if((vv.type()==vv.List)){
        for(auto&h:vv.toList())
            if(!this->fromHash(h.toHash()))
                __return=false;
    }
    else{
        __return=false;
    }
    return __return;
}

bool BaseSetting::mergeHash(const QVariantHash &v)
{
    VariantUtil vu;
    QVariantHash vMap;
    QHashIterator<QString, QVariant> i(v);
    while (i.hasNext()){
        i.next();
        vMap.insert(i.key().toLower(), i.value());
    }

    bool __return=false;
    auto metaObject = this->metaObject();
    QStm::MetaObjectUtil metaObjectUtil(*metaObject);
    auto propertyList=metaObjectUtil.toPropertyList();
    for(auto&property:propertyList){
        if(QByteArray(property.name())==QT_STRINGIFY2(objectName))
            continue;
        else{
            auto key = QString(property.name()).toLower();
            auto value = vMap.value(key);
            auto type=property.type();
            if(value.isNull() || !value.isValid())
                continue;
            else if(!property.write(this,value)){
                if(type==QVariant::Int || type==QVariant::UInt)
                    property.write(this,value.toInt());
                else if(type==QVariant::LongLong || type==QVariant::ULongLong)
                    property.write(this,value.toLongLong());
                else if(type==QVariant::Double)
                    property.write(this,value.toDouble());
                else if(type==QVariant::Hash)
                    property.write(this, vu.toHash(value));
                else if(type==QVariant::Map)
                    property.write(this, vu.toMap());
                else if(type==QVariant::List)
                    property.write(this, vu.toList());
                else if(type==QVariant::StringList)
                    property.write(this, vu.toStringList());
            }
            __return=true;
        }
    }
    return __return;
}

bool BaseSetting::mergeMap(const QVariantMap &v)
{
    return this->mergeHash(QVariant(v).toHash());
}

bool BaseSetting::mergeVariant(const QVariant &v)
{
    bool __return=true;
    VariantUtil vu;
    auto vv=vu.toVariantObject(v);
    if((vv.type()==vv.Hash) || (vv.type()==vv.Map)){
        __return=this->mergeHash(vv.toHash());
    }
    else if((vv.type()==vv.List)){
        for(auto&h:vv.toList())
            if(!this->mergeHash(h.toHash()))
                __return=false;
    }
    else{
        __return=false;
    }
    return __return;
}

QString BaseSetting::identification() const
{
    dPvt();
    return p.identification;
}

void BaseSetting::setIdentification(const QString &value)
{
    dPvt();
    p.identification=value;
}

QString BaseSetting::name() const
{
    dPvt();
    return p.name;
}

void BaseSetting::setName(const QString &value)
{
    dPvt();
    p.name = value.trimmed();
}

QVariantHash&BaseSetting::variables() const
{
    dPvt();
    return p.variables;
}

void BaseSetting::setVariables(const QVariantHash &value)
{
    dPvt();
    p.variables=value;
}

bool BaseSetting::enabled()const
{
    dPvt();
    return p.enabled;
}

void BaseSetting::setEnabled(const bool &value)
{
    dPvt();
    p.enabled=value;
}

qlonglong BaseSetting::activityLimit()const
{
    dPvt();
    return p.getInterval(p.activityLimit, defaultLimit).toLongLong();
}

void BaseSetting::setActivityLimit(const QVariant &value)
{
    dPvt();
    p.activityLimit=value;
}

qlonglong BaseSetting::activityInterval()const
{
    dPvt();
    return p.getInterval(p.activityInterval, defaultInterval).toLongLong();
}

void BaseSetting::setActivityInterval(const QVariant &value)
{
    dPvt();
    p.activityInterval=value;
}

int BaseSetting::activityThread() const
{
    dPvt();
    return p.activityThread.toInt();
}

void BaseSetting::setActivityThread(const QVariant &value)
{
    dPvt();
    p.activityThread=value;
}

qlonglong BaseSetting::memoryLimit() const
{
    dPvt();
    return p.getMemoryBytes(p.memoryLimit, 0).toLongLong();
}

void BaseSetting::setMemoryLimit(const QVariant &value)
{
    dPvt();
    p.memoryLimit=value;
}



}
