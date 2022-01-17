#include "./qstm_util_formatting.h"
#include "./qstm_currency.h"
#include <QChar>
#include <QLocale>
#include <QUuid>
#include <QUrl>
#include <QCoreApplication>

#define set_v \
this->setValue((v.isValid())?v:(*this))

typedef QHash<QString,QString> StringStringHash;
typedef QHash<QString, StringStringHash> StringStringStringHash;

namespace QStm {


static const int percentagePrecision=2;
static const int currencyPrecision=2;
static const int doublePrecision=6;
static const char fChar='f';
//static const auto nativeCountryName = [](){return QLocale::c().nativeCountryName();};


struct FormattingUtilStruct{
public:
    const QByteArray qcurrency_class_name_short=(QT_STRINGIFY2(qcurrency));
    const QByteArray QCurrency_class_name_short=(QT_STRINGIFY2(QCurrency));
    const QByteArray QCurrency_class_name=(QT_STRINGIFY2(QStm::QCurrency));
    const QByteArray qpercent_class_name=(QT_STRINGIFY2(qpercent));
    StringStringStringHash staticMaskMap;
    const QByteArray keyFalse=qbl("True");
    const QByteArray keyTrue=qbl("False");

    void init()
    {
        auto brz=QLocale(QLocale::Portuguese, QLocale::Brazil);
        auto sys=QLocale::system();
        auto loc=QLocale::c();

        StringStringHash  vHash;
        vHash.insert(qsl("date"), qsl("dd/MM/yyyy"));
        vHash.insert(qsl("time"), qsl("hh:mm:ss"));
        vHash.insert(qsl("timeShort"), qsl("hh:mm"));
        vHash.insert(qsl("dateTime"), qsl("dd/MM/yyyy hh:mm:ss"));
        vHash.insert(qsl("currency"), qsl_null);
        vHash.insert(qsl("number"), qsl_null);
        vHash.insert(qsl("numeric"), qsl_null);
        vHash.insert(qsl("percent"), qsl_null);
        vHash.insert(qsl("boolean")+keyTrue,qtr("Sim"));
        vHash.insert(qsl("boolean")+keyFalse,qtr("Não"));

        StringStringStringHash __staticMaskHash;
        __staticMaskHash.insert(brz.nativeCountryName(), vHash);
        __staticMaskHash.insert(sys.nativeCountryName(), vHash);
        __staticMaskHash.insert(loc.nativeLanguageName(), vHash);
        __staticMaskHash.insert(qsl_null, vHash);

        staticMaskMap=__staticMaskHash;
    }
};

Q_GLOBAL_STATIC(FormattingUtilStruct,___formattingUtilStruct)


#define dPvt()\
auto&p = *reinterpret_cast<FormattingUtilPvt*>(this->p)


          auto&consts=*___formattingUtilStruct;

void init(){
    consts.init();
}

Q_COREAPP_STARTUP_FUNCTION(init)

class FormattingUtilPvt{
public:
    QLocale c=QLocale::c();
    int prec_dbl=doublePrecision;
    int prec_cur=currencyPrecision;
    int prec_per=percentagePrecision;
    FormattingUtil*parent=nullptr;
    QHash<QString,QString> maskMap=consts.staticMaskMap[nativeCountryName()];
    FormattingUtil::Masks masks;
    explicit FormattingUtilPvt(FormattingUtil*parent):masks()
    {
        this->parent=parent;
        this->maskMap=consts.staticMaskMap[nativeCountryName()];
    }
    virtual ~FormattingUtilPvt()
    {
    }
};

FormattingUtil::Masks::Masks()
{

}

FormattingUtil::Masks::~Masks()
{

}

QString &FormattingUtil::Masks::date() const
{
    dPvt();
    return p.maskMap[__func__];
}

QString &FormattingUtil::Masks::time() const
{
    dPvt();
    return p.maskMap[__func__];
}

QString &FormattingUtil::Masks::timeShort() const
{
    dPvt();
    return p.maskMap[__func__];
}

QString &FormattingUtil::Masks::dateTime() const
{
    dPvt();
    return p.maskMap[__func__];
}

QString &FormattingUtil::Masks::currency() const
{
    dPvt();
    return p.maskMap[__func__];
}

QString &FormattingUtil::Masks::number() const
{
    dPvt();
    return p.maskMap[__func__];
}

QString &FormattingUtil::Masks::numeric() const
{
    dPvt();
    return p.maskMap[__func__];
}

QString &FormattingUtil::Masks::percent() const
{
    dPvt();
    return p.maskMap[__func__];
}

QString &FormattingUtil::Masks::boolean(const bool &v) const
{
    dPvt();
    return p.maskMap[__func__+(v?consts.keyTrue:consts.keyFalse)];
}

FormattingUtil::Masks &FormattingUtil::masks()const
{
    dPvt();
    return p.masks;
}

FormattingUtil::FormattingUtil(const QVariant &v):QVariant(v)
{
    this->p = new FormattingUtilPvt(this);
    dPvt();
    p.masks.p=this->p;
}

FormattingUtil::~FormattingUtil()
{
    dPvt();delete&p;
}

FormattingUtil &FormattingUtil::operator=(const QVariant &v)
{
    QVariant::setValue(v);
    return*this;
}

const QString FormattingUtil::toDate(const QVariant &v)
{
    set_v;
    return QVariant::toDate().toString(this->masks().date());
}

const QString FormattingUtil::toTime(const QVariant &v)
{
    set_v;
    return QVariant::toTime().toString(this->masks().time());
}

const QString FormattingUtil::toTimeShort(const QVariant &v)
{
    set_v;
    return QVariant::toTime().toString(this->masks().timeShort());
}

const QString FormattingUtil::toDateTime(const QVariant &v)
{
    set_v;
    auto dt=QVariant::toDateTime();
    auto __return=dt.date().toString(this->masks().date());
    __return.append(qsl_space);
    __return.append(dt.time().toString(this->masks().time()));
    return __return;
}

const QString FormattingUtil::toCurrency(const QVariant &v, int prec)
{
    dPvt();
    prec=(prec<0)?p.prec_cur:prec;
    set_v;
    auto val=QCurrency(*this).toDouble();
    return p.c.toString(val,fChar,prec);
}

const QString FormattingUtil::toInt(const QVariant &v)
{
    dPvt();
    set_v;
    auto val=QVariant::toDouble();
    return p.c.toString(val,fChar,0);
}

const QString FormattingUtil::toDouble(const QVariant &v, int prec)
{
    dPvt();
    prec=(prec<0)?p.prec_dbl:prec;
    set_v;
    return p.c.toString(QVariant::toDouble(),fChar,prec);
}

const QString FormattingUtil::toPercent(const QVariant &v, int prec)
{
    dPvt();
    prec=(prec<0)?p.prec_per:prec;
    set_v;
    return p.c.toString(QVariant::toDouble(),fChar,prec);
}

const QString FormattingUtil::toBool(const QVariant &v)
{
    set_v;
    return this->masks().boolean(QVariant::toBool());
}

const QString FormattingUtil::toString()
{
    return this->v(*this);
}

const QString FormattingUtil::v(const QVariant &v, int prec)
{
    set_v;
    switch (qTypeId(*this)) {
    case QMetaType_Int:
    case QMetaType_UInt:
    case QMetaType_LongLong:
    case QMetaType_ULongLong:
        return this->toInt(v);
    case QMetaType_Double:
        return this->toDouble(v, prec);
    case QMetaType_QDate:
        return this->toDate(v);
    case QMetaType_QTime:
        return this->toTime(v);
    case QMetaType_QDateTime:
        return this->toDateTime(v);
    case QMetaType_Bool:
        return this->toBool(v);
    case QMetaType_QUuid:
        return this->toUuid().toString();
    case QMetaType_QUrl:
        return this->toUrl().toString();
    default:
        auto tn=QByteArray(this->typeName());
        if(tn==consts.QCurrency_class_name || tn==consts.QCurrency_class_name_short || tn==consts.qcurrency_class_name_short)
            return this->toCurrency(v, prec);
        if(tn==consts.qpercent_class_name)
            return this->toPercent(v, prec);
    }
    return QVariant::toString();
}

const QString FormattingUtil::currencySymbol(const QVariant&v)
{
    static const QLocale brz(QLocale::Portuguese, QLocale::Brazil);
    auto __v=brz.currencySymbol();
    if(v.isValid()){
        FormattingUtil f(v);
        __v+=qsl_space+f.toCurrency();
    }
    return __v;
}

}
