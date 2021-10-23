#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QVariantHash>
#include "./qstm_global.h"

namespace QStm {

    class Q_STM_EXPORT PathUtil{
    public:
        explicit PathUtil(Q_CONST_V);
        virtual ~PathUtil();

        PathUtil&operator=(const QVariant&v);
        PathUtil&operator+=(const QVariant&v);
        PathUtil&operator-=(const QVariant&v);
        PathUtil&operator<<(const QVariant&v);

        bool exists()const;
        bool exists(Q_CONST_V)const;
        bool isValid(Q_CONST_V)const;
        PathUtil&clear();
        PathUtil&setPath(Q_CONST_V);
        PathUtil&append(Q_CONST_V);
        PathUtil&remove(Q_CONST_V);
        bool mkPath(Q_CONST_V);

        QString toLower()const;
        QString toString()const;
        QByteArray toByteArray()const;
        QVariantList toList()const;
        QStringList toStringList()const;
        QByteArray toMd5()const;
        QUuid toUuid()const;
        QUrl toUrl();

        QString arg(const QVariant&v);

    private:
        void*p=nullptr;
    };

}

typedef QStm::PathUtil PathUtil;
