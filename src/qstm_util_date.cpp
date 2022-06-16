#include "./qstm_util_date.h"
#include "./qstm_types.h"
#include <QCoreApplication>
#include <QStringList>
#include <QVariantList>
#include "./qstm_meta_types.h"

namespace QStm {

#define dPvt()\
auto &p = *reinterpret_cast<DateUtilPvt*>(this->p)

namespace QStmPvt
{
    Q_GLOBAL_STATIC_WITH_ARGS(QTime         , static_minTime        , (QTime(00,00,00,000))                 )//
    Q_GLOBAL_STATIC_WITH_ARGS(QTime         , static_maxTime        , (QTime(23,59,59,999))                 )//
    Q_GLOBAL_STATIC_WITH_ARGS(QStringList   , static_paramDelimiter , (qvsl_null<<","<<"|")                 )//
}

static const auto &static_minTime=*QStmPvt::static_minTime;
static const auto &static_maxTime=*QStmPvt::static_maxTime;
static const auto &static_paramDelimiter=*QStmPvt::static_paramDelimiter;

//static void initConsts(){
//}
//Q_COREAPP_STARTUP_FUNCTION(initConsts)


class DateUtilPvt:public QObject{
public:
    DateUtil*parent=nullptr;
    explicit DateUtilPvt(DateUtil*v):QObject(nullptr)
    {
        this->parent=v;
    }
    virtual ~DateUtilPvt()
    {
    }

    void clear()
    {
        this->parent->setValue(QVariant());
    }

    static const QVariant getAlpha(const QVariant &v)
    {
        auto num=qsl("0123456789,.");
        QString r,ss;
        switch (qTypeId(v)) {
        case QMetaType_Double:
            ss=QString::number(v.toDouble(),'f',6);
            break;
        case QMetaType_ULongLong:
        case QMetaType_LongLong:
        case QMetaType_Int:
        case QMetaType_UInt:
            ss=QString::number(v.toLongLong(),'f',0);
            break;
        default:
            ss=v.toString();
            break;
        }
        for(auto &c:ss){
            if(!num.contains(c))
                r+=c;
        }
        return r;
    }

    static const QVariant getNumber(const QVariant &v)
    {
        auto num=qsl("0123456789,.");
        QString r,ss;

        switch (qTypeId(v)) {
        case QMetaType_Double:
            ss=QString::number(v.toDouble(),'f',6);
            break;
        case QMetaType_ULongLong:
        case QMetaType_LongLong:
        case QMetaType_Int:
        case QMetaType_UInt:
            ss=QString::number(v.toLongLong(),'f',0);
            break;
        default:
            ss=v.toString();
            break;
        }

        for(auto &c:ss){
            if(num.contains(c))
                r+=c;
        }
        return r;
    }

    QVariant parseInterval(const QVariant &v, const QVariant&defaultV=QVariant())
    {
        if(v.isNull() || !v.isValid() || v.toLongLong()<0)
            return defaultV;

        if(QMetaTypeUtilNumeric.contains(qTypeId(v)))
            return v;

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
            scale=(60*60*24*30*12);
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


};

DateUtil::DateUtil(const QVariant &v):QVariant{v}
{
    this->p = new DateUtilPvt{this};
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

QDateTime DateUtil::firstMonthDate(const QVariant &v) const
{
    auto vv=v.isValid()?v:*this;
    QDate d;
    switch (qTypeId(vv)) {
    case QMetaType_QDate:
        d=vv.toDate();
        break;
    case QMetaType_QDateTime:
        d=vv.toDateTime().date();
        break;
    case QMetaType_QString:
    case QMetaType_QByteArray:
    {
        auto v=QDateTime::fromString(QVariant::toString(), Qt::ISODate);
        if(v.isNull()){
            v=QDateTime::fromString(QVariant::toString(), Qt::ISODateWithMs);
            if(v.isNull())
                v=QDateTime::fromString(QVariant::toString(), Qt::TextDate);
        }
        d=v.date();
        break;
    }
    default:
        d=QDate::currentDate();
    }
    return QDateTime(QDate(d.year(), d.month(), 1), static_minTime);
}

QDateTime DateUtil::lastMonthDate(const QVariant &v) const
{
    auto vv=v.isValid()?v:*this;
    QDate d;
    switch (qTypeId(vv)) {
    case QMetaType_QDate:
        d=vv.toDate();
        break;
    case QMetaType_QDateTime:
        d=vv.toDateTime().date();
        break;
    case QMetaType_QString:
    case QMetaType_QByteArray:
    {
        auto v=QDateTime::fromString(QVariant::toString(), Qt::ISODate);
        if(v.isNull()){
            v=QDateTime::fromString(QVariant::toString(), Qt::ISODateWithMs);
            if(v.isNull())
                v=QDateTime::fromString(QVariant::toString(), Qt::TextDate);
        }
        d=v.date();
        break;
    }
    default:
        d=QDate::currentDate();
    }
    d=QDate(d.year(), d.month(), 1).addMonths(1).addDays(-1);
    return QDateTime(d, static_maxTime);
}

QDateTime DateUtil::firstYearDate(const QVariant &v) const
{
    auto vv=v.isValid()?v:*this;
    QDate d;
    switch (qTypeId(vv)) {
    case QMetaType_QDate:
        d=vv.toDate();
        break;
    case QMetaType_QDateTime:
        d=vv.toDateTime().date();
        break;
    case QMetaType_QString:
    case QMetaType_QByteArray:
    {
        auto v=QDateTime::fromString(QVariant::toString(), Qt::ISODate);
        if(v.isNull()){
            v=QDateTime::fromString(QVariant::toString(), Qt::ISODateWithMs);
            if(v.isNull())
                v=QDateTime::fromString(QVariant::toString(), Qt::TextDate);
        }
        d=v.date();
        break;
    }
    default:
        d=QDate::currentDate();
    }
    return QDateTime(QDate(d.year(),1,1), static_minTime);
}

QDateTime DateUtil::lastYearDate(const QVariant &v) const
{
    auto vv=v.isValid()?v:*this;
    QDate d;
    switch (qTypeId(vv)) {
    case QMetaType_QDate:
        d=vv.toDate();
        break;
    case QMetaType_QDateTime:
        d=vv.toDateTime().date();
        break;
    case QMetaType_QString:
    case QMetaType_QByteArray:
    {
        auto v=QDateTime::fromString(QVariant::toString(), Qt::ISODate);
        if(v.isNull()){
            v=QDateTime::fromString(QVariant::toString(), Qt::ISODateWithMs);
            if(v.isNull())
                v=QDateTime::fromString(QVariant::toString(), Qt::TextDate);
        }
        d=v.date();
        break;
    }
    default:
        d=QDate::currentDate();
    }
    return QDateTime(QDate(d.year(),12,31), static_maxTime);
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
    int year=0;
    switch (qTypeId(v)) {
    case QMetaType_QDate:
        year=v.toDate().year();
        break;
    case QMetaType_QDateTime:
        year=v.toDateTime().date().year();
        break;
    case QMetaType_ULongLong:
    case QMetaType_LongLong:
    case QMetaType_UInt:
    case QMetaType_Int:
        year=v.toInt();
        break;
    default:
        auto d=QDateTime(QDate::fromString(v.toString(), Qt::ISODate),QTime());
        if(d.isValid()){
            year=d.date().year();
            break;
        }
        d=QDateTime::fromString(v.toString(), Qt::ISODateWithMs);
        if(d.isValid()){
            year=d.date().year();
            break;
        }

        year=v.toInt();
        if(year>0)
            break;

        year=QDate::currentDate().year();
        break;
    }

    auto start=QDate(year, 1, 1);
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

QDateTime DateUtil::minDateTime(const QVariant &dt)
{
    auto d=qTypeId(dt)==QMetaType_QDateTime?dt.toDateTime().date():dt.toDate();
    return QDateTime(d, static_minTime);
}

QDateTime DateUtil::maxDateTime()
{
    auto d=QDate::currentDate();
    return QDateTime(d, static_maxTime);
}

QDateTime DateUtil::maxDateTime(const QVariant &dt)
{
    auto d=qTypeId(dt)==QMetaType_QDateTime?dt.toDateTime().date():dt.toDate();
    return QDateTime(d, static_maxTime);
}

QDateTime DateUtil::minMonthDateTime()
{
    auto d=QDate::currentDate();
    return QDateTime(d, static_minTime);
}

QDateTime DateUtil::minMonthDateTime(const QDate &dt)
{
    QDate d(dt);
    d=QDate(d.year(), d.month(),1);
    return QDateTime(d, static_minTime);
}

QDateTime DateUtil::minMonthDateTime(int year, int month)
{
    auto d=QDate(year, month,1);
    return QDateTime(d, static_minTime);
}

QDateTime DateUtil::maxMonthDateTime()
{
    auto d=QDate::currentDate();
    d=QDate(d.year(), d.month(),1).addMonths(1).addDays(-1);
    return QDateTime(d, static_maxTime);
}

QDateTime DateUtil::maxMonthDateTime(const QDate &dt)
{
    QDate d(dt);
    d=QDate(d.year(), d.month(),1).addMonths(1).addDays(-1);
    return QDateTime(d, static_maxTime);
}

QDateTime DateUtil::maxMonthDateTime(int year, int month)
{
    auto d=QDate(year, month,1).addMonths(1).addDays(-1);
    return QDateTime(d, static_maxTime);
}

const QDateTime DateUtil::toDateTime(const QVariant &v)
{
    if(v.isValid())
        QVariant::setValue(v);

    QDateTime dt;
    switch (qTypeId(*this)) {
    case QMetaType_QDateTime:
        dt=QVariant::toDateTime();
        break;
    case QMetaType_QDate:
        dt=QDateTime(QVariant::toDate(), QTime());
        break;
    case QMetaType_QTime:
        dt=QDateTime(QDate(), QVariant::toTime());
        break;
    case QMetaType_QString:
    case QMetaType_QByteArray:
    {
        auto v=QDateTime::fromString(QVariant::toString(), Qt::ISODateWithMs).toUTC();
        if(v.isNull()){
            v=QDateTime::fromString(QVariant::toString(), Qt::ISODate);
            if(v.isNull())
                v=QDateTime::fromString(QVariant::toString(), Qt::TextDate);
        }
        dt=v;
        break;
    }
    default:
        dt=QVariant::toDateTime();
    }
    if(dt.time().isNull() || !dt.time().isValid())
        dt.setTime(static_minTime);
    return dt;
}

const QDate DateUtil::toDate(const QVariant &v)
{
    if(v.isValid())
        QVariant::setValue(v);

    switch (qTypeId(*this)) {
    case QMetaType_QDateTime:
        return QVariant::toDateTime().date();
    case QMetaType_QDate:
        return QVariant::toDate();
    case QMetaType_QTime:
        return {};
    case QMetaType_QString:
    case QMetaType_QByteArray:
    {
        auto v=QDate::fromString(QVariant::toString(), Qt::ISODate);
        if(v.isNull()){
            v=QDate::fromString(QVariant::toString(), Qt::ISODateWithMs);
            if(v.isNull())
                v=QDate::fromString(QVariant::toString(), Qt::TextDate);
        }
        return v;
    }
    default:
        return QVariant::toDate();
    }
}

const QTime DateUtil::toTime(const QVariant &v)
{
    if(v.isValid())
        QVariant::setValue(v);

    QTime __return;
    switch (qTypeId(*this)) {
    case QMetaType_QDateTime:
        __return=QVariant::toDateTime().time();
        break;
    case QMetaType_QDate:
        __return=static_minTime;
        break;
    case QMetaType_QTime:
    {
        __return=QVariant::toTime();
        break;
    }
    case QMetaType_QString:
    case QMetaType_QByteArray:
    {
        __return=QTime::fromString(QVariant::toString(), Qt::ISODateWithMs);
        if(__return.isNull() || !__return.isValid()){
            __return=QDateTime::fromString(QVariant::toString(), Qt::ISODateWithMs).time();
        }
        break;
    }
    default:
        __return=QVariant::toTime();
        break;
    }
    if(__return.isNull() || !__return.isValid())
        __return=static_minTime;
    return __return;
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
//    if(vA>vB){
//        auto v=vA;
//        vA=vB;
//        vB=v;
//    }
    vA=static_minTime;
    vB=static_maxTime;
    return vA.isValid() && vB.isValid();
}

bool DateUtil::setMax(QDateTime &vA, QDateTime &vB)
{
    if(!vA.isValid() || vA.isNull())
        vA=QDateTime::currentDateTime();
    if(!vB.isValid() || vB.isNull())
        vB=QDateTime::currentDateTime();
    if(vA>vB){
        auto v=vA;
        vA=vB;
        vB=v;
    }
    vA=QDateTime(vA.date(),static_minTime);
    vB=QDateTime(vB.date(),static_maxTime);
    return vA.isValid() && vB.isValid();
}

bool DateUtil::setMonthRange(QDate &vA, QDate &vB)
{
    if(vA>vB){
        auto v=vA;
        vA=vB;
        vB=v;
    }
    const auto curDate=QVariant::toDate();
    if(!curDate.isValid())
        QDate::currentDate();
    const auto year=curDate.year();
    const auto month=curDate.month();
    vA=QDate(year, month, 1);
    vB=vA.addMonths(1).addDays(-1);
    return vA<vB;
}

bool DateUtil::setMonthRange(QDateTime &vA, QDateTime &vB)
{
    if(vA>vB){
        auto v=vA;
        vA=vB;
        vB=v;
    }
    QDate a=vA.date(),b=vB.date();
    vA=QDateTime();
    vB=QDateTime();
    if(setMonthRange(a,b)){
        vA=QDateTime(a,static_minTime);
        vB=QDateTime(b,static_maxTime);
    }
    return vA<vB;
}

bool DateUtil::setYearRange(QDate &vA, QDate &vB)
{
    QDate d;
    if(vA.isValid())
        d=vA;

    if(vB.isValid())
        d=vB;

    if(!d.isValid())
        d=QVariant::toDate();

    if(!d.isValid())
        d=QDate::currentDate();

    const auto year=d.year();
    vA=QDate(year,1,1);
    vB=vA.addYears(1).addDays(-1);
    return vA<vB;
}

bool DateUtil::setYearRange(QDateTime &vA, QDateTime &vB)
{
    if(vA>vB){
        auto v=vA;
        vA=vB;
        vB=v;
    }
    QDate a=vA.date(),b=vB.date();
    vA=QDateTime();
    vB=QDateTime();
    if(setYearRange(a,b)){
        vA=QDateTime(a,static_minTime);
        vB=QDateTime(b,static_maxTime);
    }
    return vA<vB;
}

bool DateUtil::setDistantRange(QDate &vA, QDate &vB)
{
    vA=QDate(1901,1,1);
    vB=QDate(2500,1,1);
    return vA<vB;
}

bool DateUtil::setDistantRange(QDateTime &vA, QDateTime &vB)
{
    vA=QDateTime(QDate(1901,1,1), static_minTime);
    vB=QDateTime(QDate(2500,1,1), static_maxTime);
    return vA<vB;
}

bool DateUtil::validBetween(const QDateTime&vVal, const QDateTime &vMin, const QDateTime &vMax)
{
    QDateTime vMax__(vMax);

    if(vMax__.time().isNull() || !vMax__.time().isValid() || vMax__.time()==static_minTime)
        vMax__.setTime(static_maxTime);

    if(vVal.isNull() || vMin.isNull() || vMax__.isNull())
        return false;

    if(vVal<vMin)
        return false;

    if(vVal>vMax__)
        return false;

    return true;
}

bool DateUtil::checkBetween(const QVariant &v, QDateTime &vMin, QDateTime &vMax)
{
    if(!v.isValid() || v.isNull())
        return false;

    auto vv=v;
    switch (qTypeId(vv)) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    {
        auto l=vv.toList();
        if(l.isEmpty())
            vv=QVariant();
        else if(l.size()==1)
            vv=l.first();
        else
            vv=QVariantList{l[0], l[1]};
        break;
    }
    case QMetaType_QString:
    case QMetaType_QByteArray:
    {
        auto s=v.toString().trimmed();
        for(auto &c:static_paramDelimiter){
            if(s.contains(c)){
                vv=s.split(c);
                break;
            }
        }
        break;
    }
    default:
        break;
    }

    switch (qTypeId(vv)) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    {
        auto l=vv.toList();
        for(auto &v:l){
            v=v.toString().replace(qsl("\""),qsl_null).replace(qsl("'"),qsl_null).replace(qsl(";"),qsl_null);
        }
        vMin=l.size()<=0?QDateTime():l[0].toDateTime();
        vMax=l.size()<=1?QDateTime():l[1].toDateTime();
        break;
    }
    case QMetaType_QDate:
    case QMetaType_QDateTime:
    {
        vMin=QDateTime(vv.toDateTime().date(), QTime());
        vMax=QDateTime(vv.toDateTime().date(), QTime());
        break;
    }
    default:
        break;
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

bool DateUtil::checkBetween(QTime &vMin, QTime &vMax)
{
    if(vMin>vMax){
        auto aux=vMin;
        vMin=vMax;
        vMax=aux;
    }
    return vMin.isValid() && vMax.isValid();
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
