#pragma once

#include "./qstm_test.h"

namespace QStm {

struct PublicRecord{
    public:
        int server_port_http=9999;
        QByteArray server_protocol="http";
        QByteArray server_hostname="localhost";
    };

    Q_GLOBAL_STATIC(PublicRecord, __public_record);
    static auto&public_record=*__public_record;

    class SDKGoogleTestFunctional : public SDKGoogleTest{
    public:

        PublicRecord&publicRecord=public_record;

        explicit SDKGoogleTestFunctional():SDKGoogleTest(){
        }

    public:
    };

}
