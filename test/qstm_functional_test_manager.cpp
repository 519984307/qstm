#ifndef Q_STM_ServiceManagerFunctional_H
#define Q_STM_ServiceManagerFunctional_H

#include "./qstm_test_functional.h"

namespace QStm {
class Q_STM_ServiceManagerFunctional : public SDKGoogleTestFunctional {
public:
};

TEST_F(Q_STM_ServiceManagerFunctional, serviceStart)
{
    EXPECT_EQ(this->serviceStart(),true)<<"fail: service start";
}

TEST_F(Q_STM_ServiceManagerFunctional, serviceStop)
{
    EXPECT_EQ(this->serviceStop(),true)<<"fail: service stop";
}

}


#endif
