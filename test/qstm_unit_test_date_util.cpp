#ifndef Q_STM_DateUtilTestUnit_H
#define Q_STM_DateUtilTestUnit_H

#include "./qstm_test_unit.h"
#include "./qstm_util_date.h"

namespace QStm {

    class Q_STM_DateUtilTestUnit : public SDKGoogleTestUnit {
    public:
    };

    TEST_F(Q_STM_DateUtilTestUnit, serviceStart)
    {
        EXPECT_EQ(this->serviceStart(),true)<<"fail: service start";
    }

    TEST_F(Q_STM_DateUtilTestUnit, serviceStop)
    {
        EXPECT_EQ(this->serviceStop(),true)<<"fail: service stop";
    }

}

#endif // DateUtilTestUnit_H
