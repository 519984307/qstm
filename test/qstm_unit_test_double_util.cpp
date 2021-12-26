#ifndef Q_STM_DoubleUtilTestUnit_H
#define Q_STM_DoubleUtilTestUnit_H

#include "./qstm_test_unit.h"
#include "../src/qstm_util_double.h"

namespace QStm {

class Q_STM_DoubleUtilTestUnit : public SDKGoogleTestUnit {
public:
    DoubleUtil u;
};

TEST_F(Q_STM_DoubleUtilTestUnit, CheckConversor)
{
    const double v=12.55;
    u=v;
    EXPECT_TRUE(u.toDouble()==v)<<"fail: invalid check";
}

TEST_F(Q_STM_DoubleUtilTestUnit, CheckBetween)
{

    {
        qlonglong v1=2,v2=1;
        EXPECT_TRUE(u.checkBetween(v1,v2))<<"fail: invalid check invert";
        EXPECT_TRUE(v1<v2)<<"fail: invalid check check invert values";

        EXPECT_TRUE(u.checkBetween(v1,v2))<<"fail: invalid check invert";
        EXPECT_TRUE(v1<v2)<<"fail: invalid check check invert values";
    }

    {
        int v1=2,v2=1;
        EXPECT_TRUE(u.checkBetween(v1,v2))<<"fail: invalid check invert";
        EXPECT_TRUE(v1<v2)<<"fail: invalid check check invert values";

        EXPECT_TRUE(u.checkBetween(v1,v2))<<"fail: invalid check invert";
        EXPECT_TRUE(v1<v2)<<"fail: invalid check check invert values";
    }

    {
        const double cV1=1.05, cV2=1.06;
        double v1=cV2,v2=cV1;

        EXPECT_TRUE(u.checkBetween(v1,v2))<<"fail: invalid check invert";
        EXPECT_TRUE(v1<v2)<<"fail: invalid check check invert values";
        EXPECT_TRUE(v1==cV1)<<"fail: invalid check values";
        EXPECT_TRUE(v2==cV2)<<"fail: invalid check values";

        EXPECT_TRUE(u.checkBetween(v1,v2))<<"fail: invalid check invert";
        EXPECT_TRUE(v1<v2)<<"fail: invalid check check invert values";
        EXPECT_TRUE(v1==cV1)<<"fail: invalid check values";
        EXPECT_TRUE(v2==cV2)<<"fail: invalid check values";
    }
}

}


#endif // DoubleUtilTestUnit_H
