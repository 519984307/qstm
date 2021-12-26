#ifndef Q_STM_DoubleUtilTestUnit_H
#define Q_STM_DoubleUtilTestUnit_H

#include "./qstm_test_unit.h"
#include "./qstm_util_double.h"

namespace QStm {

    class Q_STM_DoubleUtilTestUnit : public SDKGoogleTestUnit {
    public:
    };

    TEST_F(Q_STM_DoubleUtilTestUnit, serviceStart)
    {
        EXPECT_EQ(this->serviceStart(),true)<<"fail: service start";
    }

    TEST_F(Q_STM_DoubleUtilTestUnit, serviceStop)
    {
        EXPECT_EQ(this->serviceStop(),true)<<"fail: service stop";
    }

}


#endif // DoubleUtilTestUnit_H
