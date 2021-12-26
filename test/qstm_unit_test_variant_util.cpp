#ifndef Q_STM_VariantUtilUnit_H
#define Q_STM_VariantUtilUnit_H

#include "./qstm_test_unit.h"
#include "./qstm_util_variant.h"
#include <QCryptographicHash>

namespace QStm {
class Q_STM_VariantUtilUnit : public SDKGoogleTestUnit {
public:
    VariantUtil vu;
};

TEST_F(Q_STM_VariantUtilUnit, serviceStart)
{
    EXPECT_EQ(this->serviceStart(),true)<<"fail: service start";
}


TEST_F(Q_STM_VariantUtilUnit, testeToUuid){

    auto md5_A=QCryptographicHash::hash("1", QCryptographicHash::Md5).toHex().replace("-","").replace("{","").replace("}","");
    auto md5_B = QByteArray(vu.toMd5("1")).replace("-","").replace("{","").replace("}","");
    auto uid_A = vu.toMd5Uuid("1").toString().replace("-","").replace("{","").replace("}","");
    EXPECT_EQ(md5_A,md5_B)<<"fail: Invalid MD5/UUID";
    EXPECT_EQ(uid_A,md5_B)<<"fail: Invalid MD5/UUID";
}


TEST_F(Q_STM_VariantUtilUnit, serviceStop)
{
    EXPECT_EQ(this->serviceStop(),true)<<"fail: service stop";
}

}


#endif
