#pragma once

#include <QObject>
#include <QVariant>
#include <QDateTime>
#include <QVariantList>
#include <QVariantHash>
#include "./qstm_global.h"

namespace QStm {
    class Q_STM_EXPORT QCurrency:public QVariant{
    public:
        explicit QCurrency(const QVariant&v=QVariant(), const QVariant&precision=QVariant());
        virtual ~QCurrency();

        /**
         * @brief operator =
         * @param value
         */
        QCurrency&operator = (const QVariant&v);
        QCurrency&operator = (const qlonglong&v);
        QCurrency&operator = (const int&v);
        QCurrency&operator = (const double&v);

        QCurrency&operator + (const QCurrency&o);
        QCurrency&operator - (const QCurrency&o);
        QCurrency&operator * (const QCurrency&o);
        QCurrency&operator / (const QCurrency&o);
        QCurrency&operator % (const QCurrency&o);
        QCurrency&operator ^ (const QCurrency&o);

        void operator += (const QVariant&o);
        void operator -= (const QVariant&o);
        void operator *= (const QVariant&o);
        void operator /= (const QVariant&o);
        void operator ^= (const QVariant&o);

        bool operator > (const QCurrency&o);
        bool operator >= (const QCurrency&o);
        bool operator == (const QCurrency&o);
        bool operator < (const QCurrency&o);
        bool operator <= (const QCurrency&o);

        virtual QCurrency &setValue(const QVariant&value);

        double toDouble()const;
    private:
        void*p=nullptr;
    };

}

typedef double qcurrency;
typedef QStm::QCurrency QCurrency;

Q_DECLARE_METATYPE(qcurrency)
Q_DECLARE_METATYPE(QCurrency)
Q_DECLARE_METATYPE(QCurrency*)
