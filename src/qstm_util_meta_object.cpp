#include "./qstm_util_meta_object.h"
#include "./qstm_vvm.h"
#include <QCoreApplication>
#include <QUuid>
#include <QUrl>
#include <QBitArray>
#include <QStringList>
#include <QJsonDocument>
#include <QDateTime>

namespace QStm {

#define dPvt()\
auto&p = *reinterpret_cast<MetaObjectUtilPvt*>(this->p)

          class MetaObjectUtilPvt{
public:
    MetaObjectUtil*parent=nullptr;
    QList<const QMetaObject*> metaObjectList;
    explicit MetaObjectUtilPvt(MetaObjectUtil*parent){
        this->parent=parent;
    }
    virtual ~MetaObjectUtilPvt(){
    }

    bool writeProperty(QObject*object, const QMetaProperty&property, const QVariant&value){
        auto type = qTypeId(property);
        QVariant vValue=value;

        if(property.write(object, vValue))
            return true;

        static const auto listString=QList<int>{QMetaType_QUuid, QMetaType_QString, QMetaType_QByteArray, QMetaType_QChar, QMetaType_QBitArray};
        static const auto listNumber=QList<int>{QMetaType_LongLong, QMetaType_Int, QMetaType_UInt, QMetaType_ULongLong, QMetaType_Double};
        static const auto listClass=QList<int>{QMetaType_QUrl, QMetaType_QVariantMap, QMetaType_QVariantHash, QMetaType_QVariantList, QMetaType_QStringList};
        static const auto listJson=QList<int>{QMetaType_QVariantMap, QMetaType_QVariantHash, QMetaType_QVariantList, QMetaType_QStringList};
        static const auto listDates=QList<int>{QMetaType_QDate, QMetaType_QDateTime, QMetaType_QTime};
        static const auto listBool=QList<int>{QMetaType_Bool};

        if(listString.contains(type)){
            QVariant v;
            if(listJson.contains(qTypeId(value)))
                v=QJsonDocument::fromVariant(vValue).toJson(QJsonDocument::Compact);
            else
                v=vValue.toByteArray();


            if((type==QMetaType_QUuid) && (property.write(object, vValue.toUuid())))
                return true;
            if((type==QMetaType_QString) && (property.write(object, v.toString())))
                return true;
            if((type==QMetaType_QByteArray) && (property.write(object, v.toByteArray())))
                return true;
            if((type==QMetaType_QChar) && (property.write(object, v.toChar())))
                return true;
            if((type==QMetaType_QBitArray) && (property.write(object, v.toBitArray())))
                return true;

        }
        else if(listNumber.contains(type)){//ints
            if((type==QMetaType_LongLong) && (property.write(object, static_cast<qlonglong>(QLocale::c().toDouble(vValue.toString())))))
                return true;
            if((type==QMetaType_Int) && (property.write(object, QLocale::c().toInt(vValue.toString()))))
                return true;
            if((type==QMetaType_UInt) && (property.write(object, QLocale::c().toInt(vValue.toString()))))
                return true;
            if((type==QMetaType_UInt) && (property.write(object, QLocale::c().toUInt(vValue.toString()))))
                return true;
            if((type==QMetaType_ULongLong) && (property.write(object, QLocale::c().toLongLong(vValue.toString()))))
                return true;
            if((type==QMetaType_ULongLong) && (property.write(object, QLocale::c().toLongLong(vValue.toString()))))
                return true;
            if((type==QMetaType_Double) && (property.write(object, QLocale::c().toDouble(vValue.toString()))))
                return true;
        }
        else if(listClass.contains(type)){
            if((type==QMetaType_QUrl) && (property.write(object, vValue.toUrl())))
                return true;
            if((type==QMetaType_QVariantMap) && (property.write(object, vValue.toHash())))
                return true;
            if((type==QMetaType_QVariantHash) && (property.write(object, vValue.toHash())))
                return true;
            if((type==QMetaType_QVariantList) && (property.write(object, vValue.toList())))
                return true;
            if((type==QMetaType_QStringList) && (property.write(object, vValue.toStringList())))
                return true;
        }
        else if(listDates.contains(type)){
            if((type==QMetaType_QDate) && (property.write(object, vValue.toDate())))
                return true;
            if((type==QMetaType_QDateTime) && (property.write(object, vValue.toDateTime())))
                return true;
            if((type==QMetaType_QTime) && (property.write(object, vValue.toTime())))
                return true;
        }
        else if(listBool.contains(type) || listBool.contains(qTypeId(value))){
            auto&v=vValue;
            if((type==QMetaType_Bool) && (property.write(object, vValue.toBool())))
                return true;
            if(qTypeId(v)==QMetaType_Bool){
                if(qTypeId(v)==QMetaType_Bool && property.write(object, vValue.toBool()))
                    return true;
                if(qTypeId(v)==QMetaType_Int || qTypeId(v)==QMetaType_UInt || qTypeId(v)==QMetaType_ULongLong || qTypeId(v)==QMetaType_LongLong || qTypeId(v)==QMetaType_Double){
                    if(property.write(object, (vValue.toInt()==1)))
                        return true;
                }
            }
            if(qTypeId(v)==QMetaType_QString || qTypeId(v)==QMetaType_QByteArray || qTypeId(v)==QMetaType_QChar){
                auto vv=vValue.toString().toLower();
                bool vBool=(vv==qsl("true"));
                if(property.write(object, vBool))
                    return true;
            }
        }
        return false;
    }


};

MetaObjectUtil::MetaObjectUtil()
{
    this->p = new MetaObjectUtilPvt(this);
}

MetaObjectUtil::MetaObjectUtil(const QMetaObject &metaObject)
{
    this->p = new MetaObjectUtilPvt(this);
    dPvt();
    p.metaObjectList.clear();
    p.metaObjectList.append(&metaObject);
}

MetaObjectUtil::~MetaObjectUtil()
{
    dPvt();
    delete&p;
}

MetaObjectUtil &MetaObjectUtil::operator=(const QMetaObject &v)
{
    dPvt();
    p.metaObjectList.clear();
    p.metaObjectList.append(&v);
    return*this;
}

MetaObjectUtil &MetaObjectUtil::operator+=(const QMetaObject &v)
{
    dPvt();
    p.metaObjectList.clear();
    p.metaObjectList.append(&v);
    return*this;
}

MetaObjectUtil &MetaObjectUtil::operator-=(const QMetaObject &v)
{
    dPvt();
    Q_UNUSED(v)
    p.metaObjectList.clear();
    p.metaObjectList<<&QObject::staticMetaObject;
    return*this;
}

MetaObjectUtil &MetaObjectUtil::operator<<(const QMetaObject &v)
{
    dPvt();
    p.metaObjectList.clear();
    p.metaObjectList.append(&v);
    return*this;
}

QObject *MetaObjectUtil::newInstance(QObject*parent){
    dPvt();
    auto&__metaObject=*p.metaObjectList.first();
    auto object=__metaObject.newInstance(Q_ARG(QObject*, parent));
    return object;
}

QObject *MetaObjectUtil::newInstance(const QMetaObject &metaObject, QObject *parent)
{
    auto&__metaObject=metaObject;
    auto object=__metaObject.newInstance(Q_ARG(QObject*, parent));
    return object;
}

QMetaMethod MetaObjectUtil::method(const QString &name)
{
    dPvt();
    auto __name=name.toLower().trimmed();
    for(auto&metaObject:p.metaObjectList){
        for(int i = 0; i < metaObject->methodCount(); ++i) {
            auto method = metaObject->method(i);
            auto name__=method.name().toLower();
            if(name__ != __name)
                continue;

            return method;
        }
    }
    return QMetaMethod();
}

QMetaProperty MetaObjectUtil::property(const QByteArray &name)
{
    dPvt();
    auto __name=name.toLower().trimmed();
    for(auto&metaObject:p.metaObjectList){
        for(int i = 0; i < metaObject->propertyCount(); ++i) {
            auto property = metaObject->property(i);
            auto name__=QByteArray(property.name()).toLower();
            if(name__ != __name)
                continue;

            return property;
        }
    }
    return QMetaProperty();
}

const QVariantMap MetaObjectUtil::toMap(const QObject *object) const
{
    return QVariant(this->toHash(object)).toMap();
}

const QVariantHash MetaObjectUtil::toHash(const QObject *object)const
{
    QVariantHash __return;
    auto&metaObject = *object->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        __return.insert(property.name(), property.read(object));
    }
    return __return;
}

bool MetaObjectUtil::writeMap(QObject *object, const QVariantMap &v)
{
    dPvt();
    bool __return=false;
    auto vProperty=this->toPropertyMap(object);
    Q_V_MAP_ITERATOR(v){
        i.next();
        auto k=i.key().toUtf8();
        auto&v=i.value();
        auto property=vProperty.value(k);
        if(p.writeProperty(object, property, v))
            __return=true;
    }
    return __return;
}

bool MetaObjectUtil::writeHash(QObject *object, const QVariantHash &v)
{
    dPvt();
    bool __return=false;
    auto vProperty=this->toPropertyMap(object);
    Q_V_HASH_ITERATOR(v){
        i.next();
        auto k=i.key().toUtf8();
        auto&v=i.value();
        auto property=vProperty.value(k);
        if(p.writeProperty(object, property, v))
            __return=true;
    }
    return __return;
}

const QList<QMetaProperty> MetaObjectUtil::toPropertyList(const QObject *object) const
{
    dPvt();
    QList<const QMetaObject*> __metaObject;
    if(object!=nullptr){
        __metaObject<<object->metaObject();
    }
    else{
        __metaObject=p.metaObjectList;
    }
    auto&metaObject =*__metaObject.first();

    QList<QMetaProperty> __return;
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        __return<<property;
    }
    return __return;
}

const QHash<QByteArray, QMetaProperty> MetaObjectUtil::toPropertyMap(const QObject *object) const
{
    dPvt();
    auto __metaObject=p.metaObjectList;
    if(object!=nullptr){
        __metaObject.clear();
        __metaObject<<object->metaObject();
    }
    auto&metaObject =*__metaObject.first();
    QHash<QByteArray, QMetaProperty> __return;
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        __return[property.name()]=property;
    }
    return __return;
}

}
