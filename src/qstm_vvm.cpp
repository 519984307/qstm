#include "./qstm_vvm.h"
#include "./qstm_util_variant.h"
#include <QJsonDocument>

const static QString toBytes(const QVariant &v)
{
    if(v.type()==QVariant::List || v.type()==QVariant::StringList || v.type()==QVariant::Map || v.type()==QVariant::Hash)
        return QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
    else if(v.type()==QVariant::Uuid)
        return v.toUuid().toString();
    else if(v.type()==QVariant::Url)
        return v.toUrl().toString();
    else
        return v.toByteArray();
}

QVVM::QVVM():QVariantHash()
{
}

QVVM::QVVM(const QVariant &other):QVariantHash(other.toHash())
{
}

QVVM::QVVM(const QVariant &key, const QVariant &value):QVariantHash()
{
    QVariantHash::insert(toBytes(key), toBytes(value));
}

QVVM::~QVVM()
{

}

QVVM &QVVM::operator=(const QVariant &v)
{
    QStm::VariantUtil vu;
    auto vMap=vu.toHash(v);
    QVariantHash::clear();
    QHashIterator<QString, QVariant> i(vMap);
    while (i.hasNext()) {
        i.next();
        this->insert(i.key(), i.value());
    }
    return*this;
}

QVVM &QVVM::operator+=(const QVariantHash &v)
{
    QStm::VariantUtil vu;
    QHashIterator<QString, QVariant> i(v);
    while (i.hasNext()) {
        i.next();
        this->insert(i.key(), i.value());
    }
    return*this;
}

QVVM &QVVM::operator+=(const QVariantMap &v)
{
    QMapIterator<QString, QVariant> i(v);
    while (i.hasNext()) {
        i.next();
        this->insert(i.key(), i.value());
    }
    return*this;
}

QVVM QVVM::from(const QVariantHash &v)
{
    QVVM vvm;
    vvm+=v;
    return vvm;
}

QVVM QVVM::from(const QVariantMap &v)
{
    QVVM vvm;
    vvm+=v;
    return vvm;
}

void QVVM::insert(const QVariant &key, const QVariant &value)
{
    QVariantHash::insert(toBytes(key), toBytes(value));
}

void QVVM::remove(const QVariant &key)
{
    QVariantHash::remove(toBytes(key));
}

QVariant QVVM::value(const QVariant &key) const
{
    return QVariantHash::value(toBytes(key));
}
