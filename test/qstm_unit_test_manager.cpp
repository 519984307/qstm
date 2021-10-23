#ifndef Q_STM_ServiceManagerUnit_H
#define Q_STM_ServiceManagerUnit_H

#include "./qstm_test_unit.h"

namespace QStm {
class Q_STM_ServiceManagerUnit : public SDKGoogleTestUnit {
public:
};

TEST_F(Q_STM_ServiceManagerUnit, serviceStart)
{
    EXPECT_EQ(this->serviceStart(),true)<<"fail: service start";
}

TEST_F(Q_STM_ServiceManagerUnit, serviceStop)
{
    EXPECT_EQ(this->serviceStop(),true)<<"fail: service stop";
}

}


#endif
