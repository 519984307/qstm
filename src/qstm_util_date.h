#pragma once

#include "./qstm_global.h"
#include "./qstm_util_formatting.h"

namespace QStm {

//!
//! \brief The DateUtil class
//!util class to operation datetimes
class Q_STM_EXPORT DateUtil:public QVariant{
public:
    //!
    //! \brief DateUtil
    //! \param v
    //!
    explicit DateUtil(Q_CONST_V);

    //!
    //! \brief ~DateUtil
    //!
    virtual ~DateUtil();

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //! set values
    DateUtil&operator=(const QVariant&v);

    //!
    //! \brief firstMonthDate
    //! \param v
    //! \return
    //! first day of month
    QDateTime firstMonthDate(Q_CONST_V)const;

    //!
    //! \brief lastMonthDate
    //! \param v
    //! \return
    //!
    QDateTime lastMonthDate(Q_CONST_V)const;

    //!
    //! \brief firstYearDate
    //! \param v
    //! \return
    //! returns first year day
    QDateTime firstYearDate(Q_CONST_V)const;

    //!
    //! \brief lastYearDate
    //! \param v
    //! \return
    //!returns last year day
    QDateTime lastYearDate(Q_CONST_V)const;

    //!
    //! \brief listMonthDaysToDate
    //! \param v
    //! \return
    //!list days in month to date
    QVariantList listMonthDaysToDate(Q_CONST_V)const;

    //!
    //! \brief listMonthDays
    //! \param v
    //! \return
    //!full list month days
    QVariantList listMonthDays(Q_CONST_V)const;

    //!
    //! \brief listYearDaysToDate
    //! \param v
    //! \return
    //!list days in year to date
    QVariantList listYearDaysToDate(Q_CONST_V)const;

    //!
    //! \brief listYearDays
    //! \param v
    //! \return
    //!full list year days
    QVariantList listYearDays(Q_CONST_V)const;

    //!
    //! \brief minTime
    //! \return
    //!minimal time dat
    static const QTime &minTime();

    //!
    //! \brief maxTime
    //! \return
    //!maximo time day
    static const QTime &maxTime();

    //!
    //! \brief minDateTime
    //! \return
    //!minimal datetime day
    static QDateTime minDateTime();

    //!
    //! \brief minDateTime
    //! \param dt
    //! \return
    //!minimal datetime day
    static QDateTime minDateTime(const QVariant&dt);

    //!
    //! \brief maxDateTime
    //! \return
    //!maximum datetime day
    static QDateTime maxDateTime();

    //!
    //! \brief maxDateTime
    //! \param dt
    //! \return
    //!maximum datetime day
    static QDateTime maxDateTime(const QVariant&dt);

    //!
    //! \brief minMonthDateTime
    //! \return
    //!maximum datetime day
    static QDateTime minMonthDateTime();
    static QDateTime minMonthDateTime(const QDate&dt);
    static QDateTime minMonthDateTime(int year, int month);

    //!
    //! \brief maxMonthDateTime
    //! \return
    //!maximum datetime month
    static QDateTime maxMonthDateTime();
    static QDateTime maxMonthDateTime(const QDate&dt);
    static QDateTime maxMonthDateTime(int year, int month);

    //!
    //! \brief toDateTime
    //! \param v
    //! \return
    //!convert to Datetime
    const QDateTime toDateTime(Q_CONST_V);

    //!
    //! \brief toDate
    //! \param v
    //! \return
    //!convert to date
    const QDate toDate(Q_CONST_V);

    //!
    //! \brief toTime
    //! \param v
    //! \return
    //!convert toDate
    const QTime toTime(Q_CONST_V);

    //!
    //! \brief setNow
    //! \param v
    //! \return
    //!set now in variable
    bool setNow(QTime &v);

    //!
    //! \brief setNow
    //! \param v
    //! \return
    //!set now in variable
    bool setNow(QDate &v);

    //!
    //! \brief setNow
    //! \param v
    //! \return
    //!set now in variable
    bool setNow(QDateTime &v);

    //!
    //! \brief setNow
    //! \param dtA
    //! \param dtB
    //! \return
    //!set now in variable
    bool setNow(QDateTime &dtA, QDateTime &dtB);

    //!
    //! \brief setMax
    //! \param vA
    //! \return
    //!set max time in variable
    bool setMax(QTime &vA);

    //!
    //! \brief setMax
    //! \param vA
    //! \return
    //!set max time in variable
    bool setMax(QDateTime &vA);

    //!
    //! \brief setMax
    //! \param vA
    //! \param vB
    //! \return
    //!set Max and Minimal datetime
    bool setMax(QTime &vA, QTime &vB);
    bool setMax(QDateTime &vA, QDateTime &vB);

    //!
    //! \brief setMonthRange
    //! \param vA
    //! \param vB
    //! \return
    //!set minimal/maximum month date
    bool setMonthRange(QDate &vA, QDate &vB);

    //!
    //! \brief setMonthRange
    //! \param vA
    //! \param vB
    //! \return
    //!set minimal/maximum month date/time
    bool setMonthRange(QDateTime &vA, QDateTime &vB);

    //!
    //! \brief setYearRange
    //! \param vA
    //! \param vB
    //! \return
    //!set minimal/maximum year date
    bool setYearRange(QDate &vA, QDate &vB);

    //!
    //! \brief setYearRange
    //! \param vA
    //! \param vB
    //! \return
    //!set minimal/maximum year date/time
    bool setYearRange(QDateTime &vA, QDateTime &vB);

    //!
    //! \brief validBetween
    //! \param vVal
    //! \param vMin
    //! \param vMax
    //! \return
    //! check bettween dates
    bool validBetween(const QDateTime &vVal, const QDateTime &vMin, const QDateTime &vMax);

    //!
    //! \brief checkBetween
    //! \param v
    //! \param vMin
    //! \param vMax
    //! \return
    //!
    //! check and arrange bettween dates
    bool checkBetween(const QVariant&v, QDateTime &vMin, QDateTime &vMax);

    //!
    //! \brief checkBetween
    //! \param vMin
    //! \param vMax
    //! \return
    //!check em fix minimal/maximum date
    bool checkBetween(QDateTime &vMin, QDateTime &vMax);

    //!
    //! \brief checkBetween
    //! \param vMin
    //! \param vMax
    //! \return
    //!check em fix minimal/maximum date/time
    bool checkBetween(QDate &vMin, QDate &vMax);

    //!
    //! \brief formatting
    //! \return
    //!cosnts to forma date/time
    virtual FormattingUtil&formatting();

    //!
    //! \brief formatting
    //! \param v
    //! \return
    //!cosnts to forma date/time
    virtual FormattingUtil&formatting(Q_CONST_V);

    //!
    //! \brief parseInterval
    //! \return
    //!parse text to interval ms
    QVariant parseInterval();

    //!
    //! \brief parseInterval
    //! \param v
    //! \param defaultV
    //! \return
    //!parse text to interval ms
    QVariant parseInterval(const QVariant&v, const QVariant&defaultV=QVariant());

private:
    void*p=nullptr;
};

}


typedef QStm::DateUtil DateUtil;

Q_DECLARE_METATYPE(DateUtil)
Q_DECLARE_METATYPE(DateUtil*)

