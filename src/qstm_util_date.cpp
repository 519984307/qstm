#include "./qstm_util_date.h"
#include "./qstm_vvm.h"
#include <QCoreApplication>

namespace QStm {

#define dPvt()\
    auto&p = *reinterpret_cast<DateUtilPvt*>(this->p)

namespace QStmPvt {
    Q_GLOBAL_STATIC_WITH_ARGS(QTime         , static_minTime        , (QTime(00,00,00,000))             );//
    Q_GLOBAL_STATIC_WITH_ARGS(QTime         , static_maxTime        , (QTime(23,59,59,999))             );//
    Q_GLOBAL_STATIC_WITH_ARGS(QStringList   , static_paramDelimiter , (qvsl_null<<","<<"|")             );//
}

static const auto&static_minTime=*QStmPvt::static_minTime;
static const auto&static_maxTime=*QStmPvt::static_maxTime;
static const auto&static_paramDelimiter=*QStmPvt::static_paramDelimiter;

//static void initConsts(){
//}
//Q_COREAPP_STARTUP_FUNCTION(initConsts)


class DateUtilPvt:public QObject{
public:
    QVVM vvm;
    FormattingUtil formatting;
    DateUtil*parent=nullptr;
    explicit DateUtilPvt(DateUtil*v):QObject(nullptr){
        this->parent=v;
    }
    virtual ~DateUtilPvt(){
    }

    void clear(){
        this->vvm=QVVM();
        this->parent->setValue(QVariant());
    }

    static const QVariant getAlpha(const QVariant&v){
        auto num=qsl("0123456789,.");
        QString r,ss;
        if(v.type()==v.Double)
            ss=QString::number(v.toDouble(),'f',6);
        else if(v.type()==v.LongLong)
            ss=QString::number(v.toLongLong(),'f',0);
        else
            ss=v.toString();

        for(auto&c:ss){
            if(!num.contains(c))
                r+=c;
        }
        return r;
    }

    static const QVariant getNumber(const QVariant&v){
        auto num=qsl("0123456789,.");
        QString r,ss;
        if(v.type()==v.Double)
            ss=QString::number(v.toDouble(),'f',6);
        else if(v.type()==v.LongLong)
            ss=QString::number(v.toLongLong(),'f',0);
        else
            ss=v.toString();

        for(auto&c:ss){
            if(num.contains(c))
                r+=c;
        }
        return r;
    }

    QVariant parseInterval(const QVariant&v, const QVariant&defaultV=QVariant()){
        if(v.isNull() || !v.isValid() || v.toLongLong()<0)
            return defaultV;
        else if(v.type()==v.LongLong || v.type()==v.ULongLong || v.type()==v.Int || v.type()==v.UInt || v.type()==v.Double)
            return v;
        else{
            qlonglong scale=1;
            auto a=getAlpha(v).toString().toLower();
            if(a==qsl("s") || a==qsl("sc") || a==qsl("second"))
                scale=1;
            else if(a==qsl("m") || a==qsl("mn") || a==qsl("minute"))
                scale=60;
            else if(a==qsl("h") || a==qsl("hr") || a==qsl("hour"))
                scale=60*60;
            else if(a==qsl("d") || a==qsl("dd") || a==qsl("day"))
                scale=60*60*24;
            else if(a==qsl("mo")|| a==qsl("mo") || a==qsl("month"))
                scale=(60*60*24*30);
            else if(a==qsl("y") || a==qsl("yy") || a==qsl("year"))
                scale=(60*60*12*365);
            else
                scale=1;//ms
            scale*=1000;
            auto iN=getNumber(v);
            auto i=iN.toDouble();
            i*=scale;
            if(i<=0)
                i=parseInterval(defaultV).toLongLong();
            return i;
        }
    }


};

DateUtil::DateUtil(const QVariant &v):QVariant(v)
{
    this->p = new DateUtilPvt(this);
}

DateUtil::~DateUtil()
{
    dPvt();
    this->p=nullptr;
    p.deleteLater();
}

DateUtil&DateUtil::operator=(const QVariant &v)
{
    this->setValue(v);
    return*this;
}

QDateTime DateUtil::firstMonthDate(const QVariant&v) const
{
    auto vv=v.isValid()?v:*this;
    vv=vv.canConvert(QVariant::Date)?vv.toDate():QDate::currentDate();
    auto d=(vv.isValid()?vv.toDateTime():vv.canConvert(QVariant::Date)?QDateTime(vv.toDate(), static_minTime):QDateTime()).date();
    return d.isValid()?QDateTime(QDate(d.year(), d.month(),1), static_minTime):QDateTime();
}

QDateTime DateUtil::lastMonthDate(const QVariant&v) const
{
    auto vv=(v.isValid()?v:*this);
    vv=vv.canConvert(QVariant::Date)?vv.toDate():QDate::currentDate();
    auto d=(vv.isValid()?vv.toDateTime():vv.canConvert(QVariant::Date)?QDateTime(vv.toDate(), static_maxTime):QDateTime()).date();
    return d.isValid()?QDateTime(d.addMonths(1).addDays(-1), static_maxTime):QDateTime();
}

QDateTime DateUtil::firstYearDate(const QVariant &v) const
{
    auto vv=v.isValid()?v:*this;
    vv=vv.canConvert(QVariant::Date)?vv.toDate():QDate::currentDate();
    auto d=(vv.isValid()?vv.toDateTime():vv.canConvert(QVariant::Date)?QDateTime(vv.toDate(), static_minTime):QDateTime()).date();
    return d.isValid()?QDateTime(QDate(d.year(),1,1), static_minTime):QDateTime();
}

QDateTime DateUtil::lastYearDate(const QVariant &v) const
{
    auto vv=(v.isValid()?v:*this);
    vv=vv.canConvert(QVariant::Date)?vv.toDate():QDate::currentDate();
    auto d=(vv.isValid()?vv.toDateTime():vv.canConvert(QVariant::Date)?QDateTime(vv.toDate(), static_maxTime):QDateTime()).date();
    return d.isValid()?QDateTime(d.addYears(1).addDays(-1), static_maxTime):QDateTime();
}

QVariantList DateUtil::listMonthDaysToDate(const QVariant &v) const
{
    QVariantList list;
    auto d=v.toDate();
    if(!d.isValid())
        d=QDate::currentDate();
    auto start=QDate(d.year(), d.month(), 1);
    auto finish=v.toDate();
    while(start<=finish){
        list<<start;
        start=start.addDays(1);
    }
    return list;
}

QVariantList DateUtil::listMonthDays(const QVariant &v)const
{
    QVariantList list;
    auto d=v.toDate();
    if(!d.isValid())
        d=QDate::currentDate();
    auto start=QDate(d.year(), d.month(), 1);
    auto finish=start.addMonths(1).addDays(-1);
    while(start<=finish){
        list<<start;
        start=start.addDays(1);
    }
    return list;
}

QVariantList DateUtil::listYearDaysToDate(const QVariant &v) const
{
    QVariantList list;
    auto d=v.toDate();
    if(!d.isValid())
        d=QDate::currentDate();
    auto start=QDate(d.year(), 1, 1);
    auto finish=v.toDate();
    while(start<=finish){
        list<<start;
        start=start.addDays(1);
    }
    return list;
}

QVariantList DateUtil::listYearDays(const QVariant &v) const
{
    QVariantList list;
    auto d=v.toDate();
    if(!d.isValid())
        d=QDate::currentDate();
    auto start=QDate(d.year(), 1, 1);
    auto finish=start.addYears(1).addDays(-1);
    while(start<=finish){
        list<<start;
        start=start.addDays(1);
    }
    return list;
}

const QTime&DateUtil::minTime()
{
    return static_minTime;
}

const QTime&DateUtil::maxTime()
{
    return static_maxTime;
}

QDateTime DateUtil::minDateTime()
{
    auto d=QDate::currentDate();
    return QDateTime(d, static_minTime);
}

QDateTime DateUtil::maxDateTime()
{
    auto d=QDate::currentDate();
    return QDateTime(d, static_maxTime);
}

const QDateTime DateUtil::toDateTime(const QVariant &v)
{
    if(v.isValid())
        QVariant::setValue(v);
    if(this->type()==this->Date){
        auto v=QDateTime(QVariant::toDate(), QTime());
        return v;
    }
    else if(this->type()==this->Time){
        auto v=QDateTime(QDate(), QVariant::toTime());
        return v;
    }
    else if(this->type()==this->String || this->type()==this->ByteArray){
        auto v=QDateTime::fromString(QVariant::toString(), Qt::ISODate);
        if(v.isNull()){
            v=QDateTime::fromString(QVariant::toString(), Qt::ISODateWithMs);
            if(v.isNull()){
                v=QDateTime::fromString(QVariant::toString(), Qt::TextDate);
            }
        }
        return v;
    }
    return QVariant::toDateTime();
}

const QDate DateUtil::toDate(const QVariant &v)
{
    if(v.isValid())
        QVariant::setValue(v);
    if(this->type()==this->DateTime){
        return QVariant::toDateTime().date();
    }
    else if(this->type()==this->String || this->type()==this->ByteArray){
        auto v=QDate::fromString(QVariant::toString(), Qt::ISODate);
        if(v.isNull()){
            v=QDate::fromString(QVariant::toString(), Qt::ISODateWithMs);
            if(v.isNull()){
                v=QDate::fromString(QVariant::toString(), Qt::TextDate);
            }
        }
        return v;
    }
    return QVariant::toDate();
}

const QTime DateUtil::toTime(const QVariant &v)
{
    if(v.isValid())
        QVariant::setValue(v);
    if(this->type()==this->DateTime){
        auto v=QVariant::toDateTime().time();
        return v;
    }
    else if(this->type()==this->String || this->type()==this->ByteArray){
        auto v=QTime::fromString(QVariant::toString(), Qt::ISODateWithMs);
        if(v.isNull()){
            v=QTime::fromString(QVariant::toString(), Qt::TextDate);
        }
        return v;
    }
    return QVariant::toTime();
}

bool DateUtil::setNow(QTime &v)
{
    v=QDateTime::currentDateTime().time();
    Q_ASSERT(v.isValid()); // Fails!
    return v.isValid();
}

bool DateUtil::setNow(QDate &v)
{
    v=QDateTime::currentDateTime().date();
    Q_ASSERT(v.isValid()); // Fails!
    return v.isValid();
}

bool DateUtil::setNow(QDateTime &v)
{
    v=QDateTime::currentDateTime();
    Q_ASSERT(v.isValid()); // Fails!
    return v.isValid();
}

bool DateUtil::setNow(QDateTime &dtA, QDateTime &dtB)
{
    dtA=QDateTime::currentDateTime();
    dtB=dtA;
    dtA.setTime(static_minTime);
    dtB.setTime(static_maxTime);
    Q_ASSERT(dtA.isValid()); // Fails!
    return dtA.isValid();
}

bool DateUtil::setMax(QTime &vA)
{
    vA=static_maxTime;
    Q_ASSERT(vA.isValid()); // Fails!
    return vA.isValid();
}

bool DateUtil::setMax(QDateTime &vA)
{
    if(!vA.isValid())
        vA=QDateTime::currentDateTime();

    vA=QDateTime(vA.date(), static_maxTime);
    Q_ASSERT(vA.isValid()); // Fails!
    return vA.isValid();
}

bool DateUtil::setMax(QTime &vA, QTime &vB)
{
    vA=static_minTime;
    vB=static_maxTime;
    return vA.isValid() && vB.isValid();
}

bool DateUtil::setMonthRange(QDate &vA, QDate &vB)
{
    const auto curDate=QDate::currentDate();
    const auto year=curDate.year();
    const auto month=curDate.month();
    vA=QDate(year, month, 01);
    vB=vA.addMonths(1).addDays(-1);
    return vA<vB;
}

bool DateUtil::setMonthRange(QDateTime &vA, QDateTime &vB)
{
    QDate a,b;
    vA=QDateTime();
    vB=QDateTime();
    if(setMonthRange(a,b)){
        vA=QDateTime(a,static_minTime);
        vB=QDateTime(a,static_maxTime);
    }
    return vA<vB;
}

bool DateUtil::setYearRange(QDate &vA, QDate &vB)
{
    const auto d=QDate::currentDate();
    const auto year=d.year();
    vA=QDate(year,1,01);
    vB=vA.addYears(1).addDays(-1);
    return vA<vB;
}

bool DateUtil::setYearRange(QDateTime &vA, QDateTime &vB)
{
    QDate a,b;
    vA=QDateTime();
    vB=QDateTime();
    if(setYearRange(a,b)){
        vA=QDateTime(a,static_minTime);
        vB=QDateTime(a,static_maxTime);
    }
    return vA<vB;
}

bool DateUtil::validBetween(const QDateTime&vVal, const QDateTime &vMin, const QDateTime &vMax)
{
    QDateTime vMax__(vMax);

    if(vMax__.time()==static_minTime)
        vMax__.setTime(static_maxTime);

    if(vVal.isNull() || vMin.isNull() || vMax__.isNull())
        return false;
    else if(vVal<vMin)
        return false;
    else if(vVal>vMax__)
        return false;
    else
        return true;
}

bool DateUtil::checkBetween(const QVariant &v, QDateTime &vMin, QDateTime &vMax)
{
    auto vv=v;
    if(vv.type()==vv.List || vv.type()==vv.StringList){
        auto l=vv.toList();
        if(l.isEmpty())
            vv=QVariant();
        else if(l.size()==1)
            vv=l.first();
        else
            vv=QVariantList()<<l[0]<<l[1];
    }
    else if(vv.type()==v.String || vv.type()==v.ByteArray){
        auto s=v.toString().trimmed();
        for(auto&c:static_paramDelimiter){
            if(s.contains(c)){
                vv=s.split(c);
                break;
            }
        }
    }

    if(vv.type()==vv.List || vv.type()==vv.StringList){
        auto l=vv.toList();
        for(auto&v:l){
            v=v.toString().replace(qsl("\""),qsl_null).replace(qsl("'"),qsl_null).replace(qsl(";"),qsl_null);
        }
        vMin=l.size()<=0?QDateTime():l[0].toDateTime();
        vMax=l.size()<=1?QDateTime():l[1].toDateTime();
    }
    else if(vv.type()==vv.Date || vv.type()==vv.DateTime){
        vMin=QDateTime(vv.toDateTime().date(), QTime());
        vMax=QDateTime(vv.toDateTime().date(), QTime());
    }


    if(!vMax.isValid()){
        if(vMin.isValid()){
            vMax=QDateTime(vMin.date(), QTime());
        }
    }

    if(vMin>vMax){
        auto aux=vMin;
        vMin=vMax;
        vMax=aux;
    }

    if(vMin.isValid())
        vMin.setTime(static_minTime);

    if(vMax.isValid())
        vMax.setTime(static_maxTime);

    return vMin.isValid() && vMax.isValid();
}

bool DateUtil::checkBetween(QDateTime &vMin, QDateTime &vMax)
{
    if(vMin>vMax){
        auto aux=vMin;
        vMin=vMax;
        vMax=aux;
    }

    vMin=QDateTime(vMin.date(), static_minTime);
    vMax=QDateTime(vMax.date(), static_maxTime);
    return vMin.isValid() && vMax.isValid();
}

bool DateUtil::checkBetween(QDate &vMin, QDate &vMax)
{
    if(vMin>vMax){
        auto aux=vMin;
        vMin=vMax;
        vMax=aux;
    }
    return vMin.isValid() && vMax.isValid();
}

FormattingUtil &DateUtil::formatting()
{
    dPvt();
    p.formatting.setValue(*this);
    return p.formatting;
}

FormattingUtil &DateUtil::formatting(const QVariant &v)
{
    dPvt();
    QVariant::setValue(v);
    p.formatting.setValue(v);
    return p.formatting;
}

QVariant DateUtil::parseInterval()
{
    dPvt();
    auto __return = p.parseInterval(*this);
    return __return;
}

QVariant DateUtil::parseInterval(const QVariant &v, const QVariant &defaultV)
{
    dPvt();
    if(v.isValid())
        QVariant::setValue(v);
    auto __return = p.parseInterval(*this, defaultV);
    return __return;
}

}
