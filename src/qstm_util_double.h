#pragma once

#include <QObject>
#include <QVariant>
#include <QDateTime>
#include <QVariantList>
#include <QVariantHash>
#include "./qstm_global.h"
#include "./qstm_util_formatting.h"

namespace QStm {

     /**
     * @brief The DoubleUtil class
     *
     * util class to operation numeric values
     */
    class Q_STM_EXPORT DoubleUtil:public QVariant{
    public:
        explicit DoubleUtil(Q_CONST_V);
        virtual ~DoubleUtil();

        DoubleUtil&operator=(const QVariant&v);

        bool checkBetween(double &vMin, double &vMax);
        bool checkBetween(qlonglong &vMin, qlonglong &vMax);
        bool checkBetween(int &vMin, int &vMax);

        virtual FormattingUtil&formatting();
        virtual FormattingUtil&formatting(Q_CONST_V);
    private:
        void*p=nullptr;
    };

}

typedef QStm::DoubleUtil DoubleUtil;

Q_DECLARE_METATYPE(DoubleUtil)
Q_DECLARE_METATYPE(DoubleUtil*)
