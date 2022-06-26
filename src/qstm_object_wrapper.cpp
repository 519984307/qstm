#include "./qstm_object_wrapper.h"
#include <QMetaProperty>
#include <QJsonDocument>
#include <QVariantHash>
#include <QMetaType>
#include <QFile>

namespace QStm {


typedef QVector<QByteArray> PropertyNames;
Q_GLOBAL_STATIC_WITH_ARGS(PropertyNames, staticIgnoreMethods,({"objectName","values","measures","asJson", "measures", "baseValues", "clearOnSetFail"}))

ObjectWrapper::ObjectWrapper(QObject *parent)
    : QObject{parent}
{
    QObject::connect(this, &ObjectWrapper::changed, this, [this](){this->_values.clear();});
}

void ObjectWrapper::printProperties()
{
    auto propList=this->toPropList();
    qInfo()<<"Properties of "<<this->metaObject()->className();
    for(auto&p:propList){
        qInfo()<<"  "<<p.name()<<"=="<<p.read(this);
    }
}

bool ObjectWrapper::isValid() const
{
    return true;
}

void ObjectWrapper::readFrom(const QVariant &values)
{
    QVariantHash v=ObjectWrapper::parserVariant(values).toHash();
    this->setValues(v);
}

void ObjectWrapper::readFrom(const QObject *object)
{
    this->setValues(QVariant::fromValue(object));
}

void ObjectWrapper::mergeFrom(const QVariant &values)
{
    auto vHash=this->toHash();
    QVariantHash v=ObjectWrapper::parserVariant(values).toHash();
    QHashIterator<QString, QVariant> i(v);
    while(i.hasNext()){
        i.next();
        vHash.insert(i.key(), i.value());
    }
    this->setValues(vHash);
}

void ObjectWrapper::mergeFrom(const QObject *object)
{
    this->mergeFrom(QVariant::fromValue(object));
}

void ObjectWrapper::clear()
{
    auto&metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);

        if(!property.isWritable())
            continue;

        if(!property.isResettable())
            continue;

        auto pName=QByteArray(property.name());

        if(staticIgnoreMethods->contains(pName))
            continue;

        auto obj=property.read(this).value<QObject*>();
        if(obj){
            obj->setProperty(QByteArrayLiteral("values"), {});
            continue;
        }

        property.reset(this);
    }
    emit cleared();
}

const QString ObjectWrapper::toJson()
{
    auto hash=this->toHash();
    if(hash.isEmpty())
        return {};
    return QJsonDocument::fromVariant(hash).toJson(QJsonDocument::Compact);
}

const QVariantHash ObjectWrapper::toHash()
{
    auto __return=extractHash(this);
    return __return;
}

QVector<QMetaProperty> ObjectWrapper::toPropList() const
{
    return this->extractProperty(this);
}

QVariant ObjectWrapper::values() const
{
    return this->extractHash(this);
}

bool ObjectWrapper::setValues(const QVariant &v)
{
    QVariantHash vParser=ObjectWrapper::parserVariant(v).toHash();

    if(vParser.isEmpty()){
        this->clear();
        emit valuesChanged();
    }

    bool __return=false;
    auto propList=this->toPropList();

    for(auto&property:propList) {

        if(!property.isWritable())
            continue;

        auto value=vParser.value(property.name());

        if(!beforeSetProperty(property, value))
            continue;

        auto isObject=[&property](){
            const auto &metaType=property.metaType().metaObject();
            if(!metaType)
                return false;
            return false;
        };


        if(!isObject()){
            switch(value.typeId()){
            case QMetaType::UnknownType:
                property.reset(this);
                break;
            default:
                if(property.write(this, value))
                    __return=true;
                break;
            }
        }
        else{
            auto objReady=property.read(this).value<QObject*>();
            switch(value.typeId()){
            case QMetaType::UnknownType:
            {
                {
                    auto obj=dynamic_cast<ObjectWrapper*>(objReady);
                    if(obj && this->_clearOnSetFail){
                        obj->clear();
                        break;
                    }
                }

                property.reset(this);
                break;
            }
            case QMetaType::QVariantHash:
            case QMetaType::QVariantMap:
            case QMetaType::QVariantList:
            case QMetaType::QStringList:
            {
                {
                    auto obj=dynamic_cast<ObjectWrapper*>(objReady);
                    if(obj){
                        obj->setValues(value);
                        break;
                    }
                }

                break;
            }
            default:
                if(property.write(this, value))
                    __return=true;
            }
        }
        afterSetProperty(property, value);
    }

    if(__return)
        emit changed();
    emit valuesChanged();
    return __return;
}

bool ObjectWrapper::setValues(const QObject *v)
{
    if(!v){
        this->clear();
        return {};
    }
    return this->setValues(extractHash(v));
}

bool ObjectWrapper::beforeSetProperty(const QMetaProperty &property, QVariant &value)
{
    Q_UNUSED(property)
    Q_UNUSED(value)
    return true;
}

bool ObjectWrapper::afterSetProperty(const QMetaProperty &property, const QVariant &value)
{
    Q_UNUSED(property)
    Q_UNUSED(value)
    return true;
}

const QVariant ObjectWrapper::parserVariant(const QVariant &v)
{
    const auto o=v.value<QObject*>();
    if(o){
        auto v=ObjectWrapper::extractHash(o);
        return v;
    }

    switch (v.typeId()) {
    case QMetaType::QVariantHash:
    case QMetaType::QVariantMap:
        return v.toHash();
    case QMetaType::QVariantList:
    case QMetaType::QStringList:
        return v.toList();
    default:
    {
        {
            auto bytes=v.toByteArray().trimmed();
            if(!bytes.isEmpty()){
                {
                    if(bytes.at(0)=='{' || bytes.at(0)=='['){
                        return QJsonDocument::fromJson(bytes).toVariant();
                    }
                }
                QFile file(bytes);
                if(file.exists() && file.open(file.ReadOnly)){
                    auto bytes=file.readAll();
                    file.close();
                    return QJsonDocument::fromJson(bytes).toVariant();
                }
            }
        }

        {
            auto vOut=v.value<QObject*>();
            if(vOut)
                return QVariant::fromValue<QObject*>(vOut);
        }

        {
            auto vOut=v.toHash();
            if(!vOut.isEmpty())
                return vOut;
        }

        {
            auto vOut=v.toList();
            if(!vOut.isEmpty())
                return vOut;
        }
        return v;
    }
    }
}

const QVector<QMetaProperty> ObjectWrapper::extractProperty(const QObject *object)
{
    QVector<QMetaProperty> __return;

    auto&metaObject = *object->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);

        if(staticIgnoreMethods->contains(QByteArray{property.name()}))
            continue;

        __return.append(property);
    }
    return __return;
}

const QVariantHash ObjectWrapper::extractHash(const QObject *object)
{
    QVariantHash __return;
    auto metaObject = object->metaObject();

    for(int col = 0; col < metaObject->propertyCount(); ++col) {

        auto property = metaObject->property(col);

        if(!property.isReadable())
            continue;

        if(staticIgnoreMethods->contains(QByteArray{property.name()}))
            continue;

        auto value=property.read(object);

        auto obj=value.value<QObject*>();
        if(obj)
            value = extractHash(obj);

        switch (value.typeId()) {
        case QMetaType::QUuid:
            value=value.toUuid().toString();
            break;
        case QMetaType::QUrl:
            value=value.toUrl().toString();
            break;
        default:
            break;
        }
        __return.insert(property.name(), value);
    }
    return __return;
}

} // namespace QMFE
