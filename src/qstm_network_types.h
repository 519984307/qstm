#pragma once

#include "./qstm_global.h"

namespace QStm {
class Q_STM_EXPORT Network:public QObject
{
    Q_OBJECT

    Q_PROPERTY(QByteArray HEADER_CONTENT_TYPE MEMBER HEADER_CONTENT_TYPE CONSTANT)
    Q_PROPERTY(QByteArray HEADER_AUTHORIZATION MEMBER HEADER_AUTHORIZATION CONSTANT)
    Q_PROPERTY(QByteArray AUTHORIZATION_BASIC MEMBER AUTHORIZATION_BASIC CONSTANT)
    Q_PROPERTY(QByteArray AUTHORIZATION_BEARER MEMBER AUTHORIZATION_BEARER CONSTANT)

    Q_PROPERTY(QByteArray APPLICATION_JSON MEMBER APPLICATION_JSON CONSTANT)
    Q_PROPERTY(QByteArray APPLICATION_XML MEMBER APPLICATION_XML CONSTANT)
    Q_PROPERTY(QByteArray APPLICATION_TEXT_XML MEMBER APPLICATION_TEXT_XML CONSTANT)
    Q_PROPERTY(QByteArray APPLICATION_X_WWW_FORT_URLENCODED MEMBER APPLICATION_X_WWW_FORT_URLENCODED CONSTANT)
public:

    explicit Network(QObject*parent=nullptr):QObject{parent}
    {

    }

    const QByteArray HEADER_CONTENT_TYPE="Content-Type";
    const QByteArray HEADER_AUTHORIZATION="Authorization";
    const QByteArray AUTHORIZATION_BASIC="Basic";
    const QByteArray AUTHORIZATION_BEARER="Bearer";

    const QByteArray APPLICATION_JSON="application/json";
    const QByteArray APPLICATION_XML="application/xml";
    const QByteArray APPLICATION_TEXT_XML="text/xml";
    const QByteArray APPLICATION_X_WWW_FORT_URLENCODED="application/x-www-form-urlencoded";


    enum SyncMode{
        Sync, aSync
    };

    Q_ENUM(SyncMode)


    enum ContentType{
        ctJson=0,
        ctCBor=1,
        ctXml=2,
        ctBinary=3
    };

    Q_ENUM(ContentType)

    enum Method{
        GET=0,
        POST=1,
        PUT=2,
        DELETE=3,
        HEAD=4,
        OPTIONS=5
    };

    Q_ENUM(Method)

    enum Mode{
        mdSync=0, mdASync=1
    };
    Q_ENUM(Mode)

    static const QHash<int,QString> &methodName(){
        static const QHash<int,QString> __return{
            {HEAD,"Head"},
            {HEAD,"head"},
            {GET,"Get"},
            {GET,"get"},
            {POST,"Post"},
            {POST,"post"},
            {PUT,"Put"},
            {PUT,"put"},
            {DELETE,"Delete"},
            {DELETE,"delete"}
        };
        return __return;
    }

};
}

