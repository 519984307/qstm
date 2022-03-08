#ifndef Q_STM_ResultValueTestUnit_H
#define Q_STM_ResultValueTestUnit_H

#include "./qstm_test_unit.h"
#include "../src/qstm_object.h"
#include "../src/qstm_currency.h"
#include "../src/qstm_util_variant.h"

namespace QStm {

class Q_STM_ResultValueTestUnit : public SDKGoogleTestUnit {
public:
};

TEST_F(Q_STM_ResultValueTestUnit, operatorBool)
{
    QStm::Object objectA;
    QStm::Object objectB;

    EXPECT_EQ(objectA.lr()==objectB.lr(),true)<<"fail: error on check operatorBool";
    EXPECT_EQ(objectA.lr().isOk(),true)<<"fail: error on check isOK";

    EXPECT_EQ(objectA.lr().setCritical("error"),false)<<"fail: error on set falt on operatorBool";
    EXPECT_EQ(objectA.lr()==objectB.lr(),false)<<"fail: service start";
    EXPECT_EQ(objectA.lr().toString()=="error",true)<<"fail: error on check message error";

    objectA.lr().clear();
    EXPECT_EQ(objectA.lr()==objectB.lr(),true)<<"fail: error on check operatorBool";
    EXPECT_EQ(objectA.lr().isOk(),true)<<"fail: error on check isOK";

    EXPECT_EQ(objectA.lr().setCritical("error"),false)<<"fail: error on set falt on operatorBool";
    EXPECT_EQ(objectA.lr()==objectB.lr(),false)<<"fail: service start";
    EXPECT_EQ(objectA.lr().toString()=="error",true)<<"fail: error on check message error";

    objectA.lr(objectB.lr());
    EXPECT_EQ(objectA.lr()==objectB.lr(),true)<<"fail: error on check operatorBool";
    EXPECT_EQ(objectA.lr().isOk(),true)<<"fail: error on check isOK";
}

TEST_F(Q_STM_ResultValueTestUnit, checkOperatorResultValue)
{
    QStm::Object objectA;
    QStm::Object objectB;

    EXPECT_EQ(objectA.lr()==objectB.lr(),true)<<"fail: error on check operatorBool";
    EXPECT_EQ(objectA.lr().setCritical("error"),false)<<"fail: error on set falt on operatorBool";
    objectA.lr()=objectB.lr();
    EXPECT_EQ(objectA.lr()==objectB.lr(),true)<<"fail: error on check operatorBool";
}

TEST_F(Q_STM_ResultValueTestUnit, checkToString)
{
    QStm::Object objectA;
    QStm::Object objectB;

    EXPECT_EQ(objectA.lr()==objectB.lr(),true)<<"fail: error on check operatorBool";
    EXPECT_EQ(objectA.lr().setCritical("error"),false)<<"fail: error on set falt on operatorBool";
    EXPECT_EQ(objectA.lr()==objectB.lr(),false)<<"fail: service start";
    EXPECT_EQ(objectA.lr().toString()=="error",true)<<"fail: error on check message error";
}




TEST_F(Q_STM_ResultValueTestUnit, checkResult)
{
    QStm::Object objectA;
    QStm::Object objectB;
    EXPECT_EQ(objectA.lr().resultVariant().isValid(),false)<<"fail: error on check operatorBool";

    QVariantList vListValues;

    vListValues<<'1';
    vListValues<<"2";
    vListValues<<int(1);
    vListValues<<qlonglong(1);
    vListValues<<qulonglong(1);
    vListValues<<uint(1);
    vListValues<<double(1);
    vListValues<<1.0;
    vListValues<<QCurrency(1.2);
    vListValues<<qbl("bytearray");
    vListValues<<qsl("string");
    vListValues<<QVariantList{1,2,3};
    vListValues<<QVariantHash{{qsl("A"),QDate::currentDate()}, {"B",QDateTime::currentDateTime()}};
    vListValues<<QDate::currentDate();

    Q_DECLARE_VU;

    for(auto&v:vListValues){
        objectA.lr().clear()=v;
        EXPECT_EQ(objectA.lr().resultVariant().isValid(),true)<<"fail: error on set ResultValue";
        auto vA=vu.toStr(v);
        auto vB=vu.toStr(objectA.lr().resultVariant());
        EXPECT_EQ(vA,vB)<<"fail: error on check operatorBool";
        objectA.lr().clear();
        EXPECT_EQ(objectA.lr().resultVariant().isValid(),false)<<"fail: error on clear ResultValue";
    }
}

}

#endif // ResultValueTestUnit_H
