#pragma once

#include <QObject>
#include <QLocale>
#include <QVariant>
#include <QDateTime>
#include <QVariantList>
#include <QVariantHash>
#include "./qstm_global.h"

namespace QStm {
     /**
     * @brief The FormattingUtil class
     *
     * util class to format string values
     */
    class Q_STM_EXPORT FormattingUtil:public QVariant{
    public:

        class Masks{
            friend class FormattingUtil;
        public:
            explicit Masks();
            virtual ~Masks();
            virtual QString&date() const;
            virtual QString&time() const;
            virtual QString&dateTime() const;
            virtual QString&currency() const;
            virtual QString&number() const;
            virtual QString&numeric() const;
            virtual QString&percent() const;
            virtual QString&boolean(const bool&v)const;
        private:
            void*p=nullptr;
        };

        explicit FormattingUtil(Q_CONST_V);
        virtual ~FormattingUtil();

        FormattingUtil&operator=(const QVariant&v);

        virtual const QString toDate(Q_CONST_V);
        virtual const QString toTime(Q_CONST_V);
        virtual const QString toDateTime(Q_CONST_V);
        virtual const QString toCurrency(Q_CONST_V, int prec=-1);
        virtual const QString toInt(Q_CONST_V);
        virtual const QString toDouble(Q_CONST_V, int prec=-1);
        virtual const QString toPercent(Q_CONST_V, int prec=-1);
        virtual const QString toBool(Q_CONST_V);
        virtual const QString toString();
        virtual const QString v(Q_CONST_V, int prec=-1);

        static const QString currencySymbol(Q_CONST_V);

        virtual Masks&masks() const;

    private:
        void*p=nullptr;
    };

}

typedef QStm::FormattingUtil FormattingUtil;

Q_DECLARE_METATYPE(FormattingUtil)
Q_DECLARE_METATYPE(FormattingUtil*)
