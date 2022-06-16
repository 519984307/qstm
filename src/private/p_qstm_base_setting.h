#pragma once

#include "../qstm_object.h"
#include "../qstm_types.h"
#include "../qstm_util_variant.h"
#include "../qstm_util_date.h"
#include "../qstm_util_meta_object.h"
#include <math.h>
#include <QVariant>
#include <QVariantHash>
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


namespace QStm {


#define SETTING_OBJECT(ClassName)\
public:\
ClassName &operator=(const ClassName &value)\
{\
    this->fromSetting(value);\
    return *this;\
}\
ClassName &operator=(const QVariant &value)\
{\
    this->fromVariant(value);\
    return *this;\
}\
ClassName &operator=(const QVariantMap &value)\
{\
    this->fromMap(value);\
    return *this;\
}\
ClassName &operator=(const QVariantHash &value)\
{\
    this->fromHash(value);\
    return *this;\
}\
ClassName &operator+=(const QVariant &value){\
    this->mergeVariant(value);\
    return *this;\
}\
ClassName &operator+=(const QVariantMap &value)\
{\
    this->mergeVariant(value);\
    return *this;\
}\
ClassName &operator+=(const QVariantHash &value)\
{\
    this->mergeVariant(value);\
    return *this;\
}\
ClassName &operator<<(const QVariant &value)\
{\
    this->mergeVariant(value);\
    return *this;\
}


namespace Private{
    QVariantHash &static_dirs();
    QVariantHash &make_static_variables();
    QVariantHash &static_variables();
    void set_static_variables(const QVariantHash&v);
}

static const auto defaultThreadCount=QThread::idealThreadCount();
static const auto &static_dirs=QStm::Private::static_dirs();

const QByteArray defaultLimit=QByteArrayLiteral("1y");//1 ano
const QByteArray defaultInterval=QByteArrayLiteral("1m");//1minute

//!
//! \brief The SettingBaseTemplate class
//!
template <class T>
class SettingBaseTemplate:public QStm::Object
{
    Q_PROPERTY(QString identification READ identification WRITE setIdentification NOTIFY identificationChanged)
    Q_PROPERTY(QVariantHash variables READ variables WRITE setVariables NOTIFY variablesChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariant memoryLimit READ memoryLimit WRITE setMemoryLimit NOTIFY memoryLimitChanged)
    Q_PROPERTY(QVariant activityLimit READ activityLimit WRITE setActivityLimit NOTIFY activityLimitChanged)
    Q_PROPERTY(QVariant activityInterval READ activityInterval WRITE setActivityInterval NOTIFY activityIntervalChanged)
    Q_PROPERTY(QVariant activityThread READ activityThread WRITE setActivityThread NOTIFY activityThreadChanged)
private:
    class SettingBaseTemplatePrv{
    public:

        QObject*parent=nullptr;
        QString identification;
        QVariantHash variables;
        QString name;
        bool enabled=false;
        QVariant activityLimit=defaultLimit;
        QVariant activityInterval=defaultInterval;
        int activityThread=0;
        QVariant memoryLimit=0;

        static QVariant staticReplaceString(const QVariantHash&static_variables, const QVariant &v)
        {
            QString value;
            auto typeId=qTypeId(v);
            switch (typeId) {
            case QMetaType_QVariantMap:
            case QMetaType_QVariantHash:
            case QMetaType_QVariantList:
            case QMetaType_QStringList:
                value=QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
                break;
            default:
                value=v.toByteArray();
            }

            if(!value.contains(qsl("$")))
                return v;

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

            switch (typeId) {
            case QMetaType_QVariantMap:
            case QMetaType_QVariantHash:
            case QMetaType_QVariantList:
            case QMetaType_QStringList:
                return QJsonDocument::fromJson(value.toUtf8()).toVariant();
            default:
                return value;
            }

        }

        static const QVariant replaceEnvStatic(const QVariant &v)
        {
            auto value=v;
            value=staticReplaceString(QStm::Private::static_variables(), value);
            return value;
        }

        QVariant replaceEnv(const QVariant &v)const
        {
            auto value=v;
            value=staticReplaceString(QStm::Private::static_variables(), value);
            value=staticReplaceString(variables, value);
            return value;
        }

        static const QVariant getAlpha(const QVariant &v)
        {
            auto num=qsl("0123456789,.");
            QString r;
            auto ss=v.toString();
            for(auto &v:ss){
                if(!num.contains(v))
                    r+=v;
            }
            return r;
        }

        static const QVariant getNumber(const QVariant &v)
        {
            auto num=qsl("0123456789,.");
            QString r,ss;

            switch (qTypeId(v)) {
            case QMetaType_LongLong:
            case QMetaType_ULongLong:
            case QMetaType_Int:
            case QMetaType_UInt:
                ss=QString::number(v.toLongLong(),'f',0);
                break;
            case QMetaType_Double:
                ss=QString::number(v.toDouble(),'f',11);
                break;
            default:
                if(v.toLongLong()>0){
                    ss=QString::number(v.toLongLong(),'f',0);
                    break;
                }
                ss=v.toString();
            }

            for(auto &c:ss){
                if(num.contains(c))
                    r+=c;
            }
            return r;
        }

        static QVariant getInterval(const QVariant &v, const QVariant&defaultV=QVariant())
        {
            Q_DECLARE_DU;
            return du.parseInterval(v,defaultV);
        }

        QVariant getMemoryBytes(const QVariant &v, const QVariant&defaultV=QVariant())
        {
            if(v.isNull() || !v.isValid() || v.toLongLong()<0)
                return defaultV;

            switch (qTypeId(v)) {
            case QMetaType_LongLong:
            case QMetaType_ULongLong:
            case QMetaType_Int:
            case QMetaType_UInt:
            case QMetaType_Double:
                return v;
            default:
                if(v.toLongLong()>0)
                    return v.toLongLong();
            }

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


        explicit SettingBaseTemplatePrv(QObject*parent)
        {
            this->parent=parent;
        }

        virtual ~SettingBaseTemplatePrv()
        {
        }

    };

public:

    //!
    //! \brief SettingBaseTemplate
    //! \param parent
    //!
    explicit SettingBaseTemplate(QObject*parent=nullptr):QStm::Object{parent}
    {
        this->p = new SettingBaseTemplatePrv(this);
    }

    ~SettingBaseTemplate()
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);delete&p;
    }

    //!
    //! \brief print
    //!
    virtual void print()const
    {
        Q_DECLARE_VU;
        auto vHash=toHash();
        if(vHash.isEmpty())
            return;

        sInfo()<<qsl_fy(settings);
        QHashIterator<QString, QVariant> i(vHash);
        while (i.hasNext()){
            i.next();
            sInfo()<<qsl("      %1:%2").arg(i.key(), vu.toByteArray(i.value()));
        }
        sInfo()<<qsl_space;
    }

    //!
    //! \brief parseVariables
    //! \param v
    //! \return
    //!
    QVariant parseVariables(const QVariant &v) const
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        return p.replaceEnv(v);
    }

    //!
    //! \brief staticParseVariables
    //! \param v
    //! \return
    //!
    static const QVariant staticParseVariables(const QVariant &v)
    {
        auto value=SettingBaseTemplatePrv::replaceEnvStatic(v);
        return value;
    }

    //!
    //! \brief variable
    //! \param v
    //! \return
    //!
    QVariant variable(const QString &v) const
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        auto var=p.variables.value(v);
        return var.isValid()?var:p.replaceEnv(var);
    }

    //!
    //! \brief parseAlpha
    //! \param v
    //! \return
    //!
    static const QVariant parseAlpha(const QVariant &v)
    {
        return SettingBaseTemplatePrv::getAlpha(v);
    }

    //!
    //! \brief parseNumber
    //! \param v
    //! \return
    //!
    static const QVariant parseNumber(const QVariant &v)
    {
        return SettingBaseTemplatePrv::getNumber(v);
    }

    //!
    //! \brief parseInterval
    //! \param v
    //! \return
    //!
    static const QVariant parseInterval(const QVariant &v)
    {
        return SettingBaseTemplatePrv::getInterval(v, QVariant());
    }

    //!
    //! \brief parseInterval
    //! \param v
    //! \param interval
    //! \return
    //!
    static const QVariant parseInterval(const QVariant &v, const QVariant &interval)
    {
        return SettingBaseTemplatePrv::getInterval(v, interval);
    }

    //!
    //! \brief staticVariables
    //! \return
    //!
    const QVariantHash &staticVariables()
    {
        return QStm::Private::static_variables();
    }

    //!
    //! \brief setStaticVariables
    //! \param v
    //!
    T &setStaticVariables(const QVariantHash&v)
    {
        QStm::Private::set_static_variables(v);
        return *dynamic_cast<T*>(this);
    }

    //!
    //! \brief macth
    //! \param name
    //! \return
    //!
    virtual bool macth(const QString &name)
    {
        auto i_name=this->name();
        auto startWith=i_name.contains(qbl("*"));

        if(startWith)
            i_name=i_name.split(qbl("*")).first();

        if(startWith && name.startsWith(i_name))
            return true;

        if((name==i_name))
            return true;

        return false;
    }

    //!
    //! \brief clear
    //!
    virtual T &clear()
    {
        for (int row = 0; row < this->metaObject()->propertyCount(); ++row) {
            auto property=this->metaObject()->property(row);
            if(QByteArray(property.name())==QT_STRINGIFY2(objectName))
                continue;

            switch (qTypeId(property)) {
            case QMetaType_Int:
            case QMetaType_UInt:
            case QMetaType_LongLong:
            case QMetaType_ULongLong:
            case QMetaType_Double:
                property.write(this,0);
                break;
            case QMetaType_QDate:
                property.write(this,QDate());
                break;
            case QMetaType_QTime:
                property.write(this,QTime());
                break;
            case QMetaType_QDateTime:
                property.write(this,QDateTime());
                break;
            case QMetaType_QVariantHash:
                property.write(this,QVariantHash());
                break;
            case QMetaType_QVariantMap:
                property.write(this,QVariant());
                break;
            case QMetaType_QVariantList:
                property.write(this,QVariantList());
                break;
            case QMetaType_QStringList:
                property.write(this,QStringList());
                break;
            case QMetaType_QString:
            case QMetaType_QByteArray:
            case QMetaType_QChar:
            case QMetaType_QBitArray:
                property.write(this,qbl_null);
                break;
            default:
                property.write(this,QVariant());
            }
        }
        return *dynamic_cast<T*>(this);
    }

    //!
    //! \brief isValid
    //! \return
    //!
    virtual bool isValid() const
    {
        for (int row = 0; row < this->metaObject()->propertyCount(); ++row) {
            auto property=this->metaObject()->property(row);
            if(QByteArray(property.name())==QT_STRINGIFY2(objectName))
                continue;

            auto vGet = property.read(this);
            if(!vGet.isValid())
                continue;

            auto t=qTypeId(vGet);
            switch (t) {
            case QMetaType_QString:
            case QMetaType_QByteArray:
            case QMetaType_QChar:
            case QMetaType_QBitArray:
            {
                if(vGet.toString().trimmed().isEmpty())
                    continue;
                break;
            }
            case QMetaType_Double:
            case QMetaType_Int:
            case QMetaType_UInt:
            case QMetaType_LongLong:
            case QMetaType_ULongLong:
            {
                if(vGet.toLongLong()<=0)
                    continue;
                break;
            }
            case QMetaType_QVariantMap:
            case QMetaType_QVariantHash:
            {
                if(vGet.toHash().isEmpty())
                    continue;
                break;
            }
            case QMetaType_QVariantList:
            case QMetaType_QStringList:
            {
                if(vGet.toList().isEmpty())
                    continue;
                break;
            }
            default:
                break;
            }
            return true;
        }
        return false;
    }

    //!
    //! \brief toMap
    //! \return
    //!
    virtual QVariantMap toMap() const
    {
        if(!this->isValid())
            return {};

        QVariantMap __return;
        for (int row = 0; row < this->metaObject()->propertyCount(); ++row) {
            auto property=this->metaObject()->property(row);
            if(QByteArray(property.name())==QT_STRINGIFY2(objectName))
                continue;

            const auto key=property.name();
            const auto value = property.read(this);
            if(!value.isNull())
                __return.insert(key, value);
        }
        return __return;

    }

    //!
    //! \brief toHash
    //! \return
    //!
    virtual QVariantHash toHash() const
    {
        if(!this->isValid())
            return {};

        QVariantHash __return;
        for (int row = 0; row < this->metaObject()->propertyCount(); ++row) {
            auto property=this->metaObject()->property(row);
            if(QByteArray(property.name())==QT_STRINGIFY2(objectName))
                continue;

            const auto key=property.name();
            const auto value = property.read(this);
            if(!value.isNull())
                __return.insert(key, value);
        }
        return __return;

    }

    //!
    //! \brief fromSetting
    //! \param v
    //! \return
    //!
    virtual bool fromSetting(const T &v)
    {
        auto o=&v;
        if(o!=nullptr)
            return this->fromHash(v.toHash());

        return false;
    }

    //!
    //! \brief fromHash
    //! \param v
    //! \return
    //!
    virtual bool fromHash(const QVariantHash &v)
    {
        this->clear();
        Q_DECLARE_VU;
        QVariantHash vHash;
        QHashIterator<QString, QVariant> i(v);
        while (i.hasNext()){
            i.next();
            vHash.insert(i.key().toLower(), i.value());
        }

        auto metaObject = this->metaObject();
        QStm::MetaObjectUtil metaObjectUtil(*metaObject);
        auto propertyList=metaObjectUtil.toPropertyList();
        bool __return=!v.isEmpty();
        for(auto &property:propertyList){
            if(QByteArray(property.name())==QT_STRINGIFY2(objectName))
                continue;

            auto key = QString::fromUtf8(property.name()).toLower();

            auto value = vHash.value(key);
            if(value.isNull() || !value.isValid())
                continue;

            if(property.write(this,value))
                continue;

            switch (qTypeId(property)) {
            case QMetaType_Int:
            case QMetaType_UInt:
                property.write(this,value.toInt());
                break;
            case QMetaType_LongLong:
            case QMetaType_ULongLong:
                property.write(this,value.toLongLong());
                break;
            case QMetaType_Double:
                property.write(this,value.toDouble());
                break;
            case QMetaType_QVariantHash:
                property.write(this, vu.toHash(value));
                break;
            case QMetaType_QVariantMap:
                property.write(this, vu.toMap(value));
                break;
            case QMetaType_QVariantList:
                property.write(this, vu.toList(value));
                break;
            case QMetaType_QStringList:
                property.write(this, vu.toStringList(value));
                break;
            default:
                __return=false;
            }
        }
        return __return;
    }

    //!
    //! \brief fromMap
    //! \param v
    //! \return
    //!
    virtual bool fromMap(const QVariantMap &v)
    {
        return this->fromHash(QVariant(v).toHash());
    }

    //!
    //! \brief fromVariant
    //! \param v
    //! \return
    //!
    virtual bool fromVariant(const QVariant &v)
    {
        Q_DECLARE_VU;
        auto vv=vu.toVariantObject(v);
        switch (qTypeId(vv)) {
        case QMetaType_QVariantHash:
        case QMetaType_QVariantMap:
            return this->fromHash(vv.toHash());
        case QMetaType_QVariantList:{
            for(auto &h:vv.toList())
                if(!this->fromHash(h.toHash()))
                    return false;
            return true;
        }
        default:
            return true;
        }
    }

    //!
    //! \brief mergeHash
    //! \param v
    //! \return
    //!
    virtual bool mergeHash(const QVariantHash &v)
    {
        Q_DECLARE_VU;
        QVariantHash vHash;
        QHashIterator<QString, QVariant> i(v);
        while (i.hasNext()){
            i.next();
            vHash.insert(i.key().toLower(), i.value());
        }

        bool __return=false;
        auto metaObject = this->metaObject();
        QStm::MetaObjectUtil metaObjectUtil(*metaObject);
        auto propertyList=metaObjectUtil.toPropertyList();
        for(auto &property:propertyList){
            auto key = QString::fromUtf8(property.name()).toLower();

            if(key==QT_STRINGIFY2(objectName))
                continue;

            auto value = vHash.value(key);
            if(value.isNull() || !value.isValid())
                continue;

            if(property.write(this, value)){
                __return=true;
                continue;
            }

            switch (qTypeId(property)) {
            case QMetaType_Int:
            case QMetaType_UInt:
            {
                property.write(this,value.toInt());
                break;
            }
            case QMetaType_LongLong:
            case QMetaType_ULongLong:
            {
                if(property.write(this,value.toLongLong()))
                    __return=true;
                break;
            }
            case QMetaType_Double:
            {
                if(property.write(this,value.toDouble()))
                    __return=true;
                break;
            }
            case QMetaType_QVariantHash:
            {
                if(property.write(this, vu.toHash(value)))
                    __return=true;
                break;
            }
            case QMetaType_QVariantMap:
            {
                if(property.write(this, vu.toMap()))
                    __return=true;
                break;
            }
            case QMetaType_QVariantList:
            {
                if(property.write(this, vu.toList()))
                    __return=true;
                break;
            }
            case QMetaType_QStringList:{
                if(property.write(this, vu.toStringList()))
                    __return=true;
                break;
            }
            default:
                break;
            }
        }
        return __return;
    }

    //!
    //! \brief mergeMap
    //! \param v
    //! \return
    //!
    virtual bool mergeMap(const QVariantMap &v)
    {
        return this->mergeHash(QVariant(v).toHash());
    }

    //!
    //! \brief mergeVariant
    //! \param v
    //! \return
    //!
    virtual bool mergeVariant(const QVariant &v)
    {
        Q_DECLARE_VU;
        auto vv=vu.toVariantObject(v);
        switch (qTypeId(vv)) {
        case QMetaType_QVariantHash:
        case QMetaType_QVariantMap:
            return this->mergeHash(vv.toHash());
        case QMetaType_QVariantList:
        {
            for(auto &h:vv.toList())
                if(!this->mergeHash(h.toHash()))
                    return false;
            break;
        }
        default:
            break;
        }
        return true;
    }

public:

    //!
    //! \brief identification
    //! \return
    //!
    virtual QString identification() const
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        return p.identification;
    }
    virtual T &setIdentification(const QString &value)
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        p.identification=value;
        return *dynamic_cast<T*>(this);
    }

    //!
    //! \brief name
    //! \return
    //!
    virtual QString name() const
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        return p.name;
    }
    virtual T &setName(const QString &value)
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        p.name = value.trimmed();
        return *dynamic_cast<T*>(this);
    }

    //!
    //! \brief variables
    //! \return
    //!
    virtual QVariantHash &variables() const
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        return p.variables;
    }

    virtual T &setVariables(const QVariantHash &value)
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        p.variables=value;
        return *dynamic_cast<T*>(this);
    }

    //!
    //! \brief enabled
    //! \return
    //!
    virtual bool enabled() const
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        return p.enabled;
    }
    virtual T &setEnabled(const bool &value)
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        p.enabled=value;
        return *dynamic_cast<T*>(this);
    }

    //!
    //! \brief activityLimit
    //! \return
    //!
    virtual qlonglong activityLimit() const
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        return p.getInterval(p.activityLimit, defaultLimit).toLongLong();
    }
    virtual T &setActivityLimit(const QVariant &value)
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        p.activityLimit=value;
        return *dynamic_cast<T*>(this);
    }

    //!
    //! \brief activityInterval
    //! \return
    //!
    virtual qlonglong activityInterval() const
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        return p.getInterval(p.activityInterval, defaultInterval).toLongLong();
    }
    virtual T &setActivityInterval(const QVariant &value)
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        p.activityInterval=value;
        return *dynamic_cast<T*>(this);
    }

    //!
    //! \brief activityThread
    //! \return
    //!
    virtual int activityThread() const
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        return p.activityThread>0?p.activityThread:QThread::idealThreadCount();
    }
    virtual T &setActivityThread(const QVariant &value)
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        p.activityThread=value.toInt();
        return *dynamic_cast<T*>(this);
    }

    //!
    //! \brief memoryLimit
    //! \return
    //!
    virtual qlonglong memoryLimit() const
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        return p.getMemoryBytes(p.memoryLimit, 0).toLongLong();
    }
    virtual T &setMemoryLimit(const QVariant &value)
    {
        auto &p = *reinterpret_cast<SettingBaseTemplatePrv*>(this->p);
        p.memoryLimit=value;
        return *dynamic_cast<T*>(this);
    }

private:
    void*p=nullptr;
signals:
    void nameChanged();
    void variablesChanged();
    void enabledChanged();
    void activityLimitChanged();
    void activityIntervalChanged();
    void activityThreadChanged();
    void memoryLimitChanged();

};

}
