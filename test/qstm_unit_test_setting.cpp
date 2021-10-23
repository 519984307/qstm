#ifndef Q_STM_ServiceSettingFunctional_H
#define Q_STM_ServiceSettingFunctional_H

#include "./qstm_test_unit.h"

namespace QStm {
class Q_STM_ServiceSettingFunctional : public SDKGoogleTestUnit {
public:
};

TEST_F(Q_STM_ServiceSettingFunctional, serviceStart)
{
    EXPECT_EQ(this->serviceStart(),true)<<"fail: service start";
}

TEST_F(Q_STM_ServiceSettingFunctional, serviceStop)
{
    EXPECT_EQ(this->serviceStop(),true)<<"fail: service stop";
}

}


#endif
