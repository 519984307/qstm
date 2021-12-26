#include "./qstm_currency.h"
#include "./bcmath.h"
#include <QLocale>

namespace PrivateQStm {
typedef QHash<QString, QHash<QString,QString>> StringStringStringMap;
Q_GLOBAL_STATIC_WITH_ARGS(QByteArray,  qcurrency_class_name_short, (QT_STRINGIFY2(qcurrency)));
Q_GLOBAL_STATIC_WITH_ARGS(QByteArray,  QCurrency_class_name_short, (QT_STRINGIFY2(QCurrency)));
Q_GLOBAL_STATIC_WITH_ARGS(QByteArray,  QCurrency_class_name, (QT_STRINGIFY2(QStm::QCurrency)));
Q_GLOBAL_STATIC_WITH_ARGS(QByteArray,  qpercent_class_name, (QT_STRINGIFY2(qpercent)));
Q_GLOBAL_STATIC(StringStringStringMap, staticMaskMap);
}

namespace QStm {


static const auto &qcurrency_class_name_short=*PrivateQStm::qcurrency_class_name_short;
static const auto &QCurrency_class_name_short=*PrivateQStm::QCurrency_class_name_short;
static const auto &QCurrency_class_name=*PrivateQStm::QCurrency_class_name;
static const auto &qpercent_class_name=*PrivateQStm::qpercent_class_name;
static auto &staticMaskMap=*PrivateQStm::staticMaskMap;

#define dPvt()\
    auto&p = *reinterpret_cast<QCurrencyPvt*>(this->p)

class QCurrencyPvt{
public:
    QBCMath qbcmath;
    QCurrency*parent=nullptr;
    int precision=2;
    explicit QCurrencyPvt(QCurrency*parent){
        this->parent=parent;
    }
    virtual ~QCurrencyPvt(){

    }

    auto&setValue(const QVariant &value)
    {
        auto&v=*dynamic_cast<QVariant*>(this->parent);
        this->qbcmath.setValue(value.toString());
        this->qbcmath.round(this->precision);
        v.setValue(qbcmath.toString());
        return*this->parent;
    }
};

QCurrency::QCurrency(const QVariant &v, const QVariant &precision):QVariant(v)
{
    this->p = new QCurrencyPvt(this);
    dPvt();
    if(precision.isValid())
        p.precision=precision.toInt();
    p.setValue(v);
}

QCurrency::~QCurrency()
{
}


QCurrency &QCurrency::operator =(const qlonglong &v)
{
    dPvt();
    return p.setValue(v);
}

QCurrency&QCurrency::operator =(const int &v)
{
    dPvt();
    return p.setValue(v);
}

QCurrency &QCurrency::operator =(const double &v)
{
    dPvt();
    return p.setValue(v);
}

QCurrency &QCurrency::operator +(const QCurrency &o)
{
    dPvt();
    p.qbcmath+o.toDouble();
    p.setValue(p.qbcmath.toDouble());
    return*this;
}

QCurrency &QCurrency::operator -(const QCurrency &o) {
    dPvt();
    p.qbcmath-o.toDouble();
    p.setValue(p.qbcmath.toDouble());
    return*this;
}

QCurrency &QCurrency::operator *(const QCurrency &o) {
    dPvt();
    p.qbcmath*o.toDouble();
    p.setValue(p.qbcmath.toDouble());
    return*this;
}

QCurrency &QCurrency::operator /(const QCurrency &o) {
    dPvt();
    p.qbcmath/o.toDouble();
    p.setValue(p.qbcmath.toDouble());
    return*this;
}

QCurrency &QCurrency::operator %(const QCurrency &o) {
    dPvt();
    p.qbcmath%o.toDouble();
    p.setValue(p.qbcmath.toDouble());
    return*this;
}

QCurrency &QCurrency::operator ^(const QCurrency &o) {
    dPvt();
    p.qbcmath^o.toDouble();
    p.setValue(p.qbcmath.toDouble());
    return*this;
}

void QCurrency::operator+=(const QVariant &o) {
    dPvt();
    p.qbcmath+=o.toDouble();
    p.setValue(p.qbcmath.toDouble());
}

void QCurrency::operator-=(const QVariant &o) {
    dPvt();
    p.qbcmath-=o.toDouble();
    p.setValue(p.qbcmath.toDouble());
}

void QCurrency::operator*=(const QVariant &o) {
    dPvt();
    p.qbcmath*=o.toDouble();
    p.setValue(p.qbcmath.toDouble());
}

void QCurrency::operator/=(const QVariant &o) {
    dPvt();
    p.qbcmath/=o.toDouble();
    p.setValue(p.qbcmath.toDouble());
}

void QCurrency::operator^=(const QVariant &o) {
    dPvt();
    p.qbcmath^=o.toDouble();
    p.setValue(p.qbcmath.toDouble());
}

bool QCurrency::operator >(const QCurrency &o) {
    dPvt();
    return p.qbcmath>o.toDouble();
}

bool QCurrency::operator >=(const QCurrency &o) {
    dPvt();
    return p.qbcmath>=o.toDouble();
}

bool QCurrency::operator ==(const QCurrency &o) {
    dPvt();
    return p.qbcmath==o.toDouble();
}

bool QCurrency::operator <(const QCurrency &o) {
    dPvt();
    return p.qbcmath<o.toDouble();
}

bool QCurrency::operator <=(const QCurrency &o) {
    dPvt();
    return p.qbcmath<=o.toDouble();
}

QCurrency &QCurrency::setValue(const QVariant &value)
{
    dPvt();
    return p.setValue(value);
}

double QCurrency::toDouble() const
{
    dPvt();
    return p.qbcmath.toDouble();
}

}
