#pragma once

#include "./qstm_global.h"
#include "./qstm_util_formatting.h"

namespace QStm {

      /**
     * @brief The DateUtil class
     *
     * util class to operation datetimes
     */
    class Q_STM_EXPORT DateUtil:public QVariant{
    public:
        explicit DateUtil(Q_CONST_V);
        virtual ~DateUtil();

        /**
         * @brief operator =
         * @param v
         * @return
         *
         * set values
         */
        DateUtil&operator=(const QVariant&v);

        /**
         * @brief firstMonthDate
         * @param v
         * @return
         */
        QDateTime firstMonthDate(Q_CONST_V)const;

        /**
         * @brief lastMonthDate
         * @param v
         * @return
         */
        QDateTime lastMonthDate(Q_CONST_V)const;

        /**
         * @brief firstMonthDate
         * @param v
         * @return
         *
         * returns first year day
         */
        QDateTime firstYearDate(Q_CONST_V)const;

        /**
         * @brief lastMonthDate
         * @param v
         * @return
         *
         * returns last year day
         */
        QDateTime lastYearDate(Q_CONST_V)const;

        /**
         * @brief listMonthDaysToDate
         * @return
         *
         * list days in month to date
         */
        QVariantList listMonthDaysToDate(Q_CONST_V)const;

        /**
         * @brief listMonthDays
         * @return
         *
         * full list month days
         */
        QVariantList listMonthDays(Q_CONST_V)const;

        /**
         * @brief listYearDaysToDate
         * @return
         *
         * list days in year to date
         */
        QVariantList listYearDaysToDate(Q_CONST_V)const;

        /**
         * @brief listMonthDays
         * @return
         *
         * full list year days
         */
        QVariantList listYearDays(Q_CONST_V)const;

        /**
         * @brief minTime
         * @return
         *
         * minimal time dat
         */
        static const QTime &minTime();

        /**
         * @brief maxTime
         * @return
         *
         * maximo time day
         */
        static const QTime &maxTime();

        /**
         * @brief minDateTime
         * @return
         *
         * minimal datetime day
         */
        static QDateTime minDateTime();

        /**
         * @brief maxDateTime
         * @return
         *
         * maximum datetime day
         */
        static QDateTime maxDateTime();

        /**
         * @brief toDateTime
         * @param v
         * @return
         *
         * convert to Datetime
         */
        const QDateTime toDateTime(Q_CONST_V);

        /**
         * @brief toDate
         * @param v
         * @return
         *
         * convert to date
         */
        const QDate toDate(Q_CONST_V);

        /**
         * @brief toTime
         * @param v
         * @return
         *
         * convert toDate
         */
        const QTime toTime(Q_CONST_V);

        /**
         * @brief setNow
         * @param v
         * @return
         *
         * set now in variable
         */
        bool setNow(QTime &v);

        /**
         * @brief setNow
         * @param v
         * @return
         *
         * set now in variable
         */
        bool setNow(QDate &v);

        /**
         * @brief setNow
         * @param v
         * @return
         *
         * set now in variable
         */
        bool setNow(QDateTime &v);

        /**
         * @brief setNow
         * @param dtA
         * @param dtB
         * @return
         *
         * set now in variable
         */
        bool setNow(QDateTime &dtA, QDateTime &dtB);

        /**
         * @brief setMax
         * @param vA
         * @return
         *
         * set max time in variable
         */
        bool setMax(QTime &vA);

        /**
         * @brief setMax
         * @param vA
         * @return
         *
         * set max time in variable
         */
        bool setMax(QDateTime &vA);

        /**
         * @brief setMax
         * @param vA
         * @param vB
         * @return
         *
         * set Max and Minimal datetime
         */
        bool setMax(QTime &vA, QTime &vB);
        bool setMax(QDateTime &vA, QDateTime &vB);

        /**
         * @brief setMonthRange
         * @param vA
         * @param vB
         * @return
         *
         * set minimal/maximum month date
         */
        bool setMonthRange(QDate &vA, QDate &vB);

        /**
         * @brief setMonthRange
         * @param vA
         * @param vB
         * @return
         *
         * set minimal/maximum month date/time
         */
        bool setMonthRange(QDateTime &vA, QDateTime &vB);

        /**
         * @brief setYearRange
         * @param vA
         * @param vB
         * @return
         *
         * set minimal/maximum year date
         */
        bool setYearRange(QDate &vA, QDate &vB);

        /**
         * @brief setYearRange
         * @param vA
         * @param vB
         * @return
         *
         * set minimal/maximum year date/time
         */
        bool setYearRange(QDateTime &vA, QDateTime &vB);

        /**
         * @brief validBetween
         * @param vValue
         * @param vMin
         * @param vMax
         * @return
         */
        bool validBetween(const QDateTime &vVal, const QDateTime &vMin, const QDateTime &vMax);

        /**
         * @brief checkBetween
         * @param v
         * @param vMin
         * @param vMax
         * @return
         *
         * check variable in range
         */
        bool checkBetween(const QVariant&v, QDateTime &vMin, QDateTime &vMax);

        /**
         * @brief checkBetween
         * @param vMin
         * @param vMax
         * @return
         *
         * check em fix minimal/maximum date
         */
        bool checkBetween(QDateTime &vMin, QDateTime &vMax);

        /**
         * @brief checkBetween
         * @param vMin
         * @param vMax
         * @return
         *
         * check em fix minimal/maximum date/time
         */
        bool checkBetween(QDate &vMin, QDate &vMax);

        /**
         * @brief formatting
         * @return
         *
         * cosnts to forma date/time
         */
        virtual FormattingUtil&formatting();
        virtual FormattingUtil&formatting(Q_CONST_V);

        /**
         * @brief parseInterval
         * @param v
         * @param defaultV
         * @return
         *
         * parse text to interval ms
         */
        QVariant parseInterval();
        QVariant parseInterval(const QVariant&v, const QVariant&defaultV=QVariant());

    private:
        void*p=nullptr;
    };

}


typedef QStm::DateUtil DateUtil;

Q_DECLARE_METATYPE(DateUtil)
Q_DECLARE_METATYPE(DateUtil*)

