#ifndef Q_STM_DateUtilTestUnit_H
#define Q_STM_DateUtilTestUnit_H

#include "./qstm_test_unit.h"
#include "./qstm_util_date.h"

namespace QStm {

class Q_STM_DateUtilTestUnit : public SDKGoogleTestUnit {
public:
    DateUtil u;

    const QTime minTime=QTime(0,0,0,0);
    const QTime maxTime=QTime(23,59,59,999);
    const QDate minDate=QDate(1901,1,1);
    const QDate maxDate=QDate(2500,1,1);
};

TEST_F(Q_STM_DateUtilTestUnit, CheckLists)
{
    {
        const QDateTime v(minDate, QTime(11,22,33));
        u=v;
        EXPECT_TRUE(u.toDateTime()==v)<<"fail: invalid check";
    }


    EXPECT_TRUE(u.firstMonthDate(QDate(1901,1,10)).date()==minDate)<<"invalid days";
    EXPECT_TRUE(u.lastMonthDate(QDate(1901,1,10)).date()==QDate(1901,1,31))<<"invalid days";
    EXPECT_TRUE(u.firstYearDate(QDate(1901,1,10)).date()==minDate)<<"invalid days";
    EXPECT_TRUE(u.lastYearDate(QDate(1901,1,10)).date()==QDate(1901,12,31))<<"invalid days";
    EXPECT_TRUE(u.listMonthDaysToDate(minDate.addDays(9)).count()==10)<<"invalid days number";
    EXPECT_TRUE(u.listMonthDays(minDate).count()==31)<<"invalid days number";
    EXPECT_TRUE(u.listYearDaysToDate(minDate.addMonths(1)).count()==32)<<"invalid years number";

    EXPECT_TRUE(u.listYearDays(QDate(2023,1,1)).count()==365)<<"invalid year days number";
    EXPECT_TRUE(u.listYearDays(QDateTime(QDate(2023,1,1),QTime())).count()==365)<<"invalid year days number";

    EXPECT_TRUE(u.listYearDays("2023").count()==365)<<"invalid year days number";
    EXPECT_TRUE(u.listYearDays("2024").count()==366)<<"invalid year days number";
    EXPECT_TRUE(u.listYearDays("2023-01-01").count()==365)<<"invalid year days number";
    EXPECT_TRUE(u.listYearDays("2024-01-01").count()==366)<<"invalid year days number";
    EXPECT_TRUE(u.listYearDays(2023).count()==365)<<"invalid year days number";
    EXPECT_TRUE(u.listYearDays(2024).count()==366)<<"invalid year days number";


    EXPECT_TRUE(u.minTime()==minTime)<<"invalid year days number";
    EXPECT_TRUE(u.maxTime()==maxTime)<<"invalid year days number";

    EXPECT_TRUE(u.minDateTime()==QDateTime(QDate::currentDate(), minTime))<<"invalid return value";
    EXPECT_TRUE(u.maxDateTime()==QDateTime(QDate::currentDate(), maxTime))<<"invalid return value";

    EXPECT_TRUE(u.minDateTime(QDate::currentDate().addDays(1))==QDateTime(QDate::currentDate().addDays(1), minTime))<<"invalid return value";
    EXPECT_TRUE(u.maxDateTime(QDate::currentDate().addDays(1))==QDateTime(QDate::currentDate().addDays(1), maxTime))<<"invalid return value";

    EXPECT_TRUE(u.minMonthDateTime()==QDateTime(QDate::currentDate(), minTime))<<"invalid return value";
    EXPECT_TRUE(u.minMonthDateTime(minDate.addDays(1))==QDateTime(minDate, minTime))<<"invalid return value";

    EXPECT_TRUE(u.maxMonthDateTime()==QDateTime(QDate(QDate::currentDate().year(),QDate::currentDate().month(),1).addMonths(1).addDays(-1), maxTime))<<"invalid return value";
    EXPECT_TRUE(u.maxMonthDateTime(minDate.addDays(1))==QDateTime(minDate.addMonths(1).addDays(-1), maxTime))<<"invalid return value";
}

TEST_F(Q_STM_DateUtilTestUnit, CheckConversor)
{
    EXPECT_TRUE(u.toDateTime(QDate::currentDate().addDays(1))==QDateTime(QDate::currentDate().addDays(1), minTime))<<"invalid return value";
    EXPECT_TRUE(u.toDateTime(QDateTime(QDate(1901,2,2), QTime(12,12,13)))==QDateTime(QDate(1901,2,2), QTime(12,12,13)))<<"invalid return value";
    EXPECT_FALSE(u.toDateTime(QTime(12,12,13)).isValid())<<"invalid return value";
    EXPECT_TRUE(u.toDateTime("1901-03-04T12:12:13")==QDateTime(QDate(1901,03,04), QTime(12,12,13)))<<"invalid return value";
    EXPECT_TRUE(u.toDateTime("1901-03-04")==QDateTime(QDate(1901,03,04), minTime))<<"invalid return value";
    EXPECT_TRUE(u.toDateTime("12:12:13")==QDateTime(QDate(), QTime(12,12,13)))<<"invalid return value";


    EXPECT_TRUE(u.toDate(QDate::currentDate())==QDate::currentDate())<<"invalid return value";
    EXPECT_TRUE(u.toDate(QDateTime(QDate(1901,2,2), QTime(12,12,13)))==QDate(1901,2,2))<<"invalid return value";
    EXPECT_TRUE(u.toDate(QTime(12,12,13))==QDate())<<"invalid return value";
    EXPECT_TRUE(u.toDate("1901-03-04T12:12:13")==QDate(1901,03,04))<<"invalid return value";
    EXPECT_TRUE(u.toDate("1901-03-04")==QDate(1901,03,04))<<"invalid return value";
    EXPECT_TRUE(u.toDate("12:12:13")==QDate())<<"invalid return value";

    EXPECT_TRUE(u.toTime(QDate::currentDate())==minTime)<<"invalid return value";
    EXPECT_TRUE(u.toTime(QDateTime(QDate(1901,2,2), QTime(12,12,13)))==QTime(12,12,13))<<"invalid return value";
    EXPECT_TRUE(u.toTime(QTime(12,12,13))==QTime(12,12,13))<<"invalid return value";
    EXPECT_TRUE(u.toTime("1901-03-04T12:12:13")==QTime(12,12,13))<<"invalid return value";
    EXPECT_TRUE(u.toTime("1901-03-04")==minTime)<<"invalid return value";
    EXPECT_TRUE(u.toTime("12:12:13")==QTime(12,12,13))<<"invalid return value";

}

TEST_F(Q_STM_DateUtilTestUnit, CheckMax)
{
    {
        QDateTime vMin, vMax;
        vMin=QDateTime(maxDate, QTime());
        vMax=QDateTime(minDate, QTime());
        EXPECT_TRUE(u.setMax(vMin,vMax))<<"fail: invalid check invert";
        EXPECT_TRUE(vMin==QDateTime(minDate, minTime))<<"fail: invalid check check invert values";
        EXPECT_TRUE(vMax==QDateTime(maxDate, maxTime))<<"fail: invalid check check invert values";

        vMin=QDateTime(QDate(), QTime());
        vMax=QDateTime(QDate(), QTime());
        EXPECT_TRUE(u.setMax(vMin,vMax))<<"fail: invalid check invert";
        EXPECT_TRUE(vMin==QDateTime(QDate::currentDate(), minTime))<<"fail: invalid check check invert values";
        EXPECT_TRUE(vMax==QDateTime(QDate::currentDate(), maxTime))<<"fail: invalid check check invert values";
    }

    {
        QTime vMin, vMax;
        vMin=QTime();
        vMax=QTime();
        EXPECT_TRUE(u.setMax(vMin,vMax))<<"fail: invalid check invert";
        EXPECT_TRUE(vMin==minTime)<<"fail: invalid check check invert values";
        EXPECT_TRUE(vMax==maxTime)<<"fail: invalid check check invert values";

        vMin=QTime::currentTime();
        vMax=QTime::currentTime();
        EXPECT_TRUE(u.setMax(vMin,vMax))<<"fail: invalid check invert";
        EXPECT_TRUE(vMin==minTime)<<"fail: invalid check check invert values";
        EXPECT_TRUE(vMax==maxTime)<<"fail: invalid check check invert values";
    }
}

TEST_F(Q_STM_DateUtilTestUnit, CheckRange)
{
    {
        QDate vMin, vMax;
        vMin=QDate();
        vMax=QDate();
        u=QDate(1901,1,4);
        EXPECT_TRUE(u.setMonthRange(vMin,vMax))<<"fail: invalid check invert";
        EXPECT_TRUE(vMin==minDate)<<"fail: invalid check invert";
        EXPECT_TRUE(vMax==QDate(1901,1,31))<<"fail: invalid check invert";
    }

    {
        QDateTime vMin, vMax;
        vMin=QDateTime();
        vMax=QDateTime();
        u=QDate(1901,1,4);
        EXPECT_TRUE(u.setMonthRange(vMin,vMax))<<"fail: invalid check invert";
        EXPECT_TRUE(vMin==QDateTime(minDate, minTime))<<"fail: invalid check invert";
        EXPECT_TRUE(vMax==QDateTime(QDate(1901,1,31), maxTime))<<"fail: invalid check invert";
    }

    {
        QDate vMin, vMax;
        vMin=QDate();
        vMax=QDate();
        u=QDate(1901,1,4);
        EXPECT_TRUE(u.setYearRange(vMin,vMax))<<"fail: invalid check invert";
        EXPECT_TRUE(vMin==minDate)<<"fail: invalid check invert";
        EXPECT_TRUE(vMax==QDate(1901,12,31))<<"fail: invalid check invert";
    }

    {
        QDateTime vMin, vMax;
        vMin=QDateTime();
        vMax=QDateTime();
        u=QDate(1901,1,4);
        EXPECT_TRUE(u.setYearRange(vMin,vMax))<<"fail: invalid check invert";
        EXPECT_TRUE(vMin==QDateTime(minDate, minTime))<<"fail: invalid check invert";
        EXPECT_TRUE(vMax==QDateTime(QDate(1901,12,31), maxTime))<<"fail: invalid check invert";
    }
}

TEST_F(Q_STM_DateUtilTestUnit, CheckBetween)
{


    {
        QDateTime vVal, vMin, vMax;
        vVal=QDateTime();
        vMin=QDateTime();
        vMax=QDateTime();
        EXPECT_FALSE(u.validBetween(vVal, vMin,vMax))<<"fail: invalid check invert";

        vVal=QDateTime(maxDate, QTime(12,12,12));
        vMin=QDateTime(maxDate, QTime(13,12,12));
        vMax=QDateTime(maxDate, maxTime);
        EXPECT_FALSE(u.validBetween(vVal, vMin,vMax))<<"fail: invalid check invert";

        vVal=QDateTime(maxDate, QTime(12,12,12));
        vMin=QDateTime(maxDate, QTime(12,12,12));
        vMax=QDateTime(maxDate, QTime(12,12,12));
        EXPECT_TRUE(u.validBetween(vVal, vMin,vMax))<<"fail: invalid check invert";
    }


    {
        QDateTime v1=QDateTime(maxDate, QTime()), v2=QDateTime(minDate, QTime());
        EXPECT_TRUE(u.checkBetween(v1,v2))<<"fail: invalid check invert";
        EXPECT_TRUE(v1<v2)<<"fail: invalid check check invert values";

        EXPECT_TRUE(u.checkBetween(v1,v2))<<"fail: invalid check invert";
        EXPECT_TRUE(v1<v2)<<"fail: invalid check check invert values";
    }

    {
        QDate v1=maxDate, v2=minDate;
        EXPECT_TRUE(u.checkBetween(v1,v2))<<"fail: invalid check invert";
        EXPECT_TRUE(v1<v2)<<"fail: invalid check check invert values";

        EXPECT_TRUE(u.checkBetween(v1,v2))<<"fail: invalid check invert";
        EXPECT_TRUE(v1<v2)<<"fail: invalid check check invert values";
    }

    {
        QTime v1=QTime(23,59,59,999), v2=QTime(00,00,00);
        EXPECT_TRUE(u.checkBetween(v1,v2))<<"fail: invalid check invert";
        EXPECT_TRUE(v1<v2)<<"fail: invalid check check invert values";

        EXPECT_TRUE(u.checkBetween(v1,v2))<<"fail: invalid check invert";
        EXPECT_TRUE(v1<v2)<<"fail: invalid check check invert values";
    }
}

TEST_F(Q_STM_DateUtilTestUnit, CheckParseInterval)
{
    QHash<QStringList,qlonglong> vHashCheck=
        {
            {{"1s","1sc","1second"},1},
            {{"10s","10sc","10second"},10},
            {{"1m","1mn","1minute"},60},
            {{"10m","10mn","10minute"},60*10},
            {{"10h","10hr","10hour"},60*60*10},
            {{"1d","1dd","1day"},60*60*24},
            {{"10d","10dd","10day"},60*60*24*10},
            {{"10mo","10month"},60*60*24*30*10},
            {{"1y","1yy","1year"},60*60*24*30*12}
        };

    QHashIterator<QStringList, qlonglong> i(vHashCheck);
    while (i.hasNext()) {
        i.next();
        qlonglong v2=i.value()*1000;
        for(auto&v:i.key()){
            qlonglong v1=u.parseInterval(v).toLongLong();
            EXPECT_EQ(v1,v2)<<"fail: invalid check invert";
        }
    }

}


}

#endif // DateUtilTestUnit_H
