#include "./qstm_object.h"
#include "./qstm_util_variant.h"
#include <QRandomGenerator>
#include <QCryptographicHash>
#include <QMetaObject>
#include <QMetaProperty>
#include <QJsonDocument>
#include <QUuid>
#include <QDateTime>
#include <QUrl>

namespace QStm {

Q_GLOBAL_STATIC_WITH_ARGS(QByteArray,__static_uuid_base_data,(QUuid::createUuid().toString().toUtf8()))
Q_GLOBAL_STATIC_WITH_ARGS(QByteArray,__static_uuid_delimer,("|"))

class ObjectPvt{
public:
    CachePool*_cachePool=nullptr;
    QByteArray storedMd5;
    ResultValue result;
    QObject*parent=nullptr;
    explicit ObjectPvt(QObject*parent)
    {
        this->parent=parent;
        result.setParent(parent);
    }

    virtual ~ObjectPvt()
    {
    }

    CachePool &cachePool()
    {
        if(this->_cachePool==nullptr)
            this->_cachePool=&CachePool::instance();
        return*this->_cachePool;
    }

    static const QByteArray toMd5(const QVariant &value)
    {
        Q_DECLARE_VU;
        return vu.toMd5(value);
    }

    QByteArray storedMd5Make() const
    {
        auto &metaObject = *this->parent->metaObject();
        QVariantHash vBody;
        for(int col = 0; col < metaObject.propertyCount(); ++col) {
            auto property = metaObject.property(col);
            vBody[property.name()]=property.read(this->parent);
        }
        return this->toMd5(vBody);
    }
};

Object::Object(QObject *parent):QObject{parent}
{
    this->p = new ObjectPvt(this);
}

Object::~Object()
{
    delete p;
}

void Object::operator=(ResultValue &value)
{
    this->lastResult().setResult(value);
}

void Object::operator =(QSqlError &value)
{
    this->lastResult().setResult(value);
}

void Object::operator=(QVariant &value)
{
    this->lastResult().setResult(value);
}

CachePool &Object::cachePool()
{

    return p->cachePool();
}

ResultValue &Object::lr()
{

    return p->result;
}

ResultValue &Object::lr(const ResultValue&value)
{

    p->result.setResult(value);
    return p->result;
}

ResultValue &Object::lr(const QSqlError&value)
{

    if(p->result.returnType() == ResultValue::None)
        p->result.setResult(value);
    return p->result;
}

ResultValue &Object::lr(const QVariant &value)
{

    if(p->result.returnType() == ResultValue::None)
        p->result.setResult(value);
    return p->result;
}

ResultValue &Object::lr(const QString &value)
{
    return this->lr(QVariant(value));
}

ResultValue &Object::lastResult()
{

    return p->result;
}

ResultValue &Object::lastResult(const ResultValue&value)
{
    return this->lr(value);
}

ResultValue &Object::lastResult(const QSqlError&value)
{
    return this->lr(value);
}

ResultValue &Object::lastResult(const QVariant &value)
{
    return this->lr(value);
}

ResultValue &Object::lastResult(const QString &value)
{
    return this->lr(value);
}

ResultValue &Object::setResult(const ResultValue&value)
{
    return this->lastResult().setResult(value);
}

ResultValue &Object::setResult(const QSqlError&value)
{
    return this->lastResult().setResult(value);
}

ResultValue &Object::setResult(const QVariant &value)
{
    return this->lastResult().setResult(value);
}

ResultValue &Object::setResult(const QString &value)
{
    return this->lastResult().setResult(QVariant(value));
}

const QDateTime Object::now()
{
    return QDateTime::currentDateTime();
}

const QByteArray Object::toMd5(const QByteArray&value)
{
    return ObjectPvt::toMd5(value);
}

const QByteArray Object::toMd5(const QString &value)
{
    return ObjectPvt::toMd5(value);
}

const QByteArray Object::toMd5(const QVariant &value)
{
    return ObjectPvt::toMd5(value);
}

const QUuid Object::uuidGenerator()
{
    auto __uuid_base_bytes=*__static_uuid_base_data+*__static_uuid_delimer+randomGenerator()+*__static_uuid_delimer+QString::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch()).toUtf8()+*__static_uuid_delimer;
    return QUuid::createUuidV5(QUuid::createUuid(), __uuid_base_bytes);
}

const QUuid Object::uuidGenerator(const QString &uuidBase)
{
    auto __uuid_base_bytes=*__static_uuid_base_data+*__static_uuid_delimer+randomGenerator()+*__static_uuid_delimer+QString::number(QDateTime::currentDateTimeUtc().toMSecsSinceEpoch()).toUtf8()+*__static_uuid_delimer+uuidBase;
    return QUuid::createUuidV5(QUuid::createUuid(), __uuid_base_bytes);
}

const QUuid Object::uuidGenCheck(const QUuid &uuid)
{
    return uuid.isNull()?uuidGenerator():uuid;
}

const QUuid Object::uuidGenCheck(const QUuid &uuid, const QUuid &uuidDefault)
{
    return !uuid.isNull()?uuid:(uuidDefault.isNull()?uuidGenerator():uuidDefault);
}

const QByteArray Object::hashGenerator()
{
    auto value=uuidGenerator().toString().toUtf8();
    return QCryptographicHash::hash(value, QCryptographicHash::Md5).toHex();
}

const QString Object::makeObjectName(const QVariant &v)
{
    static int seedRandon=1;
    static const auto listChar=QStringList{qsl("("),qsl(")"),qsl("."),qsl(" "),qsl("{"),qsl("}"),qsl("-")};
    QString name=v.toString();
    if(name.contains(qsl("_QMLTYPE_")))
        name=name.split(qsl("_QMLTYPE_")).first().trimmed();

    if(name.isEmpty())
        name=qsl("obj");
    name+=qsl("_");
    {
        QRandomGenerator r;
        r.seed(++seedRandon);
        auto v=r.generate();
        name+=QString::number(v);
    }
    for(auto &v:listChar){
        name=name.replace(v,qsl("_"));
    }
    while(name.contains(qsl("__")))
        name=name.replace(qsl("__"),qsl("_"));
    return name;
}

const QByteArray Object::randomGenerator()
{
    static int seedRandon=1;
    QRandomGenerator r;
    r.seed(++seedRandon);
    auto v=r.generate();
    return QString::number(v).toUtf8();
}

QVariantMap Object::toMap()const
{
    QVariantMap __return;
    auto &metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        QVariant value;
        switch (qTypeId(property)) {
        case QMetaType_User:
            value=property.read(this).toInt();
            break;
        default:
            value=property.read(this);
        }
        __return.insert(property.name(), value);
    }
    return __return;
}

QVariantHash Object::toHash() const
{
    QVariantHash __return;
    auto &metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        QVariant value;
        switch (qTypeId(property)) {
        case QMetaType_User:
            value=property.read(this).toInt();
            break;
        default:
            value=property.read(this);
        }
        __return.insert(property.name(), value);
    }
    return __return;
}

QVariant Object::toVar()const
{
    return this->toHash();
}

bool Object::fromVar(const QVariant &v)
{
    QVariantHash vHash;
    switch (qTypeId(v)) {
    case QMetaType_QString:
    case QMetaType_QByteArray:
        vHash=QJsonDocument::fromJson(v.toByteArray()).toVariant().toHash();
        break;
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        vHash=v.toHash();
        break;
    default:
        break;
    }
    return this->fromHash(vHash);
}

bool Object::fromMap(const QVariantMap&map)
{
    bool __return=false;
    auto &metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        if(!property.write(this, map.value(property.name())))
            continue;
        __return=true;
    }
    return __return;
}

bool Object::fromHash(const QVariantHash &map)
{
    bool __return=false;
    auto &metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        if(!property.write(this, map.value(property.name())))
            continue;
        __return=true;
    }
    return __return;
}

ResultValue &Object::storedProperty()
{

    p->storedMd5=this->storedMd5Make();
    return this->lr(QVariant(p->storedMd5));
}

bool Object::storedIsChanged()const
{
    auto v1=this->storedMd5();
    auto v2=this->storedMd5Make();
    if(v1==v2)
        return false;
    return true;
}

QByteArray&Object::storedMd5()const
{

    return p->storedMd5;
}

QByteArray Object::storedMd5Make() const{

    return p->storedMd5Make();
}

}

