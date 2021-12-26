#include "./qstm_vvm.h"
#include "./qstm_util_variant.h"
#include <QJsonDocument>

const static QString toBytes(const QVariant &v)
{
    if(qTypeId(v)==QMetaType_QVariantList || qTypeId(v)==QMetaType_QStringList || qTypeId(v)==QMetaType_QVariantMap || qTypeId(v)==QMetaType_QVariantHash)
        return QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
    
    if(qTypeId(v)==QMetaType_QUuid)
        return v.toUuid().toString();
    
    if(qTypeId(v)==QMetaType_QUrl)
        return v.toUrl().toString();

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
