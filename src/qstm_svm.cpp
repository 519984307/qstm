#include "./qstm_svm.h"
#include "./qstm_util_variant.h"

QSVM::QSVM():QVariantHash()
{
}

QSVM::QSVM(const QVariant &other):QVariantHash(other.toHash())
{

}

QSVM::~QSVM()
{

}

QSVM &QSVM::operator=(const QVariant &v)
{
    Q_DECLARE_VU;
    auto vMap=vu.toHash(v);
    QVariantHash::clear();
    Q_V_HASH_ITERATOR (vMap){
        i.next();
        this->insert(i.key(), i.value());
    }
    return*this;
}

QSVM &QSVM::operator+=(const QVariant &v)
{
    Q_DECLARE_VU;
    auto vMap=vu.toHash(v);
    Q_V_HASH_ITERATOR (vMap){
        i.next();
        this->insert(i.key(), i.value());
    }
    return*this;
}

QSVM &QSVM::operator+=(const QPair<QString,QVariant> &v)
{
    QVariantHash::insert(v.first,v.second);
    return*this;
}

QSVM &QSVM::operator-=(const QVariant &v)
{
    Q_DECLARE_VU;
    auto vMap=vu.toHash(v);
    Q_V_HASH_ITERATOR (vMap){
        i.next();
        QVariantHash::remove(i.key());
    }
    return*this;
}

QSVM &QSVM::operator<<(const QVariant &v)
{
    Q_DECLARE_VU;
    auto vMap=vu.toHash(v);
    Q_V_HASH_ITERATOR (vMap){
        i.next();
        if(QVariantHash::contains(i.key()))
            this->insert(i.key(), i.value());
    }
    return*this;
}

QSVM&QSVM::insert(const QVariant &key, const QVariant &value)
{
    QVariantHash::insert(key.toString(),value);
    return*this;
}

QVariant QSVM::remove(const QVariant &key)
{
    return QVariantHash::remove(key.toString());
}

QVariant QSVM::take(const QVariant &key)
{
    return QVariantHash::take(key.toString());
}

QVariant QSVM::value(const QVariant &key) const
{
    return QVariantHash::value(key.toString());
}

QSVM &QSVM::operator<<(const QPair<QString, QVariant> &v)
{
    if(!QVariantHash::contains(v.first))
        QVariantHash::insert(v.first,v.second);
    return*this;
}
