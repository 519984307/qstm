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


namespace PrivateOrm {
Q_GLOBAL_STATIC_WITH_ARGS(QByteArray,__static_uuid_base_data,(QUuid::createUuid().toString().toUtf8()));
}

namespace QStm {

static const auto&__static_uuid_base_data =*PrivateOrm::__static_uuid_base_data;
static const auto __static_uuid_delimer=qbl("|");
static const auto __static_md5_delimer=qbl(".");


#define dPvt()\
    auto&p = *reinterpret_cast<ObjectPrv*>(this->p)

class ObjectPrv{
public:
    CachePool*_cachePool=nullptr;
    QByteArray storedMd5;
    ResultValue _result;
    QObject*parent=nullptr;
    explicit ObjectPrv(QObject*parent){
        this->parent=parent;
        _result.setParent(parent);
    }
    virtual ~ObjectPrv(){
    }

    CachePool&cachePool(){
        if(this->_cachePool==nullptr)
            this->_cachePool=&CachePool::instance();
        return*this->_cachePool;
    }

    static const QByteArray toMd5(const QVariant&value){
        VariantUtil vu;
        return vu.toMd5(value);
    }

    QByteArray storedMd5Make() const{
        auto&metaObject = *this->parent->metaObject();
        QVariantHash vBody;
        for(int col = 0; col < metaObject.propertyCount(); ++col) {
            auto property = metaObject.property(col);
            vBody[property.name()]=property.read(this->parent);
        }
        return this->toMd5(vBody);
    }
};

Object::Object(QObject *parent):QObject(parent)
{
    this->p = new ObjectPrv(this);
}

Object::~Object()
{
    dPvt();delete&p;
}

void Object::operator=(ResultValue&value)
{
    this->lastResult().setResult(value);
}

CachePool &Object::cachePool()
{
    dPvt();
    return p.cachePool();
}

void Object::operator =(QSqlError &value)
{
    this->lastResult().setResult(value);
}

void Object::operator=(QVariant &value)
{
    this->lastResult().setResult(value);
}

ResultValue &Object::lr()
{
    dPvt();
    return p._result;
}

ResultValue &Object::lr(const ResultValue&value)
{
    dPvt();
    p._result.setResult(value);
    return p._result;
}

ResultValue &Object::lr(const QSqlError&value)
{
    dPvt();
    if(p._result.returnType() == ResultValue::None)
        p._result.setResult(value);
    return p._result;
}

ResultValue &Object::lr(const QVariant&value)
{
    dPvt();
    if(p._result.returnType() == ResultValue::None)
        p._result.setResult(value);
    return p._result;
}

ResultValue &Object::lr(const QString &value)
{
    return this->lr(QVariant(value));
}

ResultValue &Object::lastResult()
{
    dPvt();
    return p._result;
}

ResultValue &Object::lastResult(const ResultValue&value)
{
    return this->lr(value);
}

ResultValue &Object::lastResult(const QSqlError&value)
{
    return this->lr(value);
}

ResultValue &Object::lastResult(const QVariant&value)
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

ResultValue &Object::setResult(const QVariant&value)
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
    return ObjectPrv::toMd5(value);
}

const QByteArray Object::toMd5(const QString&value)
{
    return ObjectPrv::toMd5(value);
}

const QByteArray Object::toMd5(const QVariant&value)
{
    return ObjectPrv::toMd5(value);
}

const QUuid Object::uuidGenerator()
{
    auto __uuid_base_bytes=__static_uuid_base_data+__static_uuid_delimer+randomGenerator()+__static_uuid_delimer+QString::number(QDateTime::currentDateTimeUtc().toTime_t()).toUtf8()+__static_uuid_delimer;
    return QUuid::createUuidV5(QUuid::createUuid(), __uuid_base_bytes);
}

const QUuid Object::uuidGenerator(const QString &uuidBase)
{
    auto __uuid_base_bytes=__static_uuid_base_data+__static_uuid_delimer+randomGenerator()+__static_uuid_delimer+QString::number(QDateTime::currentDateTimeUtc().toTime_t()).toUtf8()+__static_uuid_delimer+uuidBase;
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
    static const auto listChar=QStringList()<<QStringLiteral("(")<<QStringLiteral(")")<<QStringLiteral(".")<<QStringLiteral(" ")<<QStringLiteral("{")<<QStringLiteral("}")<<QStringLiteral("-");
    QString name=v.toString();
    if(name.contains(QStringLiteral("_QMLTYPE_")))
        name=name.split(QStringLiteral("_QMLTYPE_")).first().trimmed();

    if(name.isEmpty())
        name=QStringLiteral("obj");
    name+=QStringLiteral("_");
    {
        QRandomGenerator r;
        r.seed(++seedRandon);
        auto v=r.generate();
        name+=QString::number(v);
    }
    for(auto&v:listChar){
        name=name.replace(v,QStringLiteral("_"));
    }
    while(name.contains(QStringLiteral("__")))
        name=name.replace(QStringLiteral("__"),QStringLiteral("_"));
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
    auto&metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        __return.insert(property.name(), property.read(this));
    }
    return __return;
}

QVariantHash Object::toHash() const
{
    QVariantHash __return;
    auto&metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        __return.insert(property.name(), property.read(this));
    }
    return __return;
}

QVariant Object::toVar()const
{
    return this->toHash();
}

bool Object::fromMap(const QVariantMap&map)
{
    bool __return=false;
    auto&metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        if(property.write(this, map.value(property.name()))){
            __return=true;
        }
    }
    return __return;
}

bool Object::fromMap(const QVariantHash &map)
{
    bool __return=false;
    auto&metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        if(property.write(this, map.value(property.name()))){
            __return=true;
        }
    }
    return __return;
}

ResultValue &Object::storedProperty()
{
    dPvt();
    p.storedMd5=this->storedMd5Make();
    return this->lr(QVariant(p.storedMd5));
}

bool Object::storedIsChanged()const
{
    auto v1=this->storedMd5();
    auto v2=this->storedMd5Make();
    if(v1==v2)
        return false;
    else
        return true;
}

QByteArray&Object::storedMd5()const
{
    dPvt();
    return p.storedMd5;
}

QByteArray Object::storedMd5Make() const{
    dPvt();
    return p.storedMd5Make();
}

}

