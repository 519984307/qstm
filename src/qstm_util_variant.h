#pragma once

#include <QObject>
#include <QUuid>
#include <QVariant>
#include <QUrl>
#include <QDateTime>
#include <QVariantList>
#include <QVariantHash>
#include "./qstm_global.h"
#include "./qstm_types.h"
#include "./qstm_vvm.h"

namespace QStm {

    class Q_STM_EXPORT VariantUtil:public QVariant{
    public:
        explicit VariantUtil(Q_CONST_V);
        virtual ~VariantUtil();

        const QStmVTypesList&typesListString     = QStmTypesListString   ;
        const QStmVTypesList&typesListNumeric    = QStmTypesListNumeric  ;
        const QStmVTypesList&typesListIntergers  = QStmTypesListIntergers;
        const QStmVTypesList&typesListClass      = QStmTypesListClass    ;
        const QStmVTypesList&typesListObjects    = QStmTypesListObjects  ;
        const QStmVTypesList&typesListDates      = QStmTypesListDates    ;
        const QStmVTypesList&typesListBool       = QStmTypesListBool     ;

        VariantUtil&operator=(const QVariant&v);

        virtual bool isHex(Q_CONST_V) const;
        virtual bool isBase64(Q_CONST_V) const;

        virtual const QString toStr(Q_CONST_V);
        virtual const QByteArray toByteArray(Q_CONST_V);
        virtual const QChar toChar(Q_CONST_V);
        virtual int toInt(Q_CONST_V);
        virtual qlonglong toLongLong(Q_CONST_V);
        virtual const QDate toDate(Q_CONST_V);
        virtual const QTime toTime(Q_CONST_V);
        virtual const QDateTime toDateTime(Q_CONST_V);
        virtual double toDouble(Q_CONST_V);
        virtual bool toBool(Q_CONST_V);

        virtual bool canConvertJson(Q_CONST_V)const;
        virtual bool canConvertJson(const QVariant &v, QVariant &vOut)const;

        /**
         * @brief toMd5
         * @param v
         * @return
         *
         * se for um QVariantHash ou QVariantList convertera para json para entao tirar o md5
         * se nao for md5 sera tirado o md5 dos bytes
         * se nao for uuid um md5 sera convertido em string para md5
         * se a string enviada for um md ou md5uui entao nada ocorrera retornando o md5 ja existe nao gerando outro
         *
         */
        virtual const QByteArray toMd5(Q_CONST_V);
        virtual const QByteArray toHex(Q_CONST_V);

        /**
         * @brief toMd5
         * @param v
         * @return
         *
         * se for md5 sera convertido para uuidMd5
         * se for uuid nada ocorrera retornando o uuid
         */
        virtual const QUuid toUuid(Q_CONST_V);

        /**
         * @brief toMd5
         * @param v
         * @return
         *
         * se a string enviada for um md ou mduui entao nada ocorrera retornando o md5 ja existe nao gerando outro
         */
        virtual const QUuid toMd5Uuid(Q_CONST_V);

        /**
         * @brief toVVM
         * @param v
         * @return
         */
        virtual QVVM toVVM()const;
        virtual const QVVM toVVM(const QVariant&v);
        virtual const QVVM toVVM(const QVariant&key, const QVariant &value);

        /**
         * @brief takeList
         * @param keyName
         * @return
         */
        virtual const QVariantList takeList(const QByteArray &keyName);

        /**
         * @brief type
         * @return
         */
        virtual QVariant::Type type() const;
        virtual const QStringList toStringList();
        virtual const QStringList toStringList(const QVariant&v);

        /**
         * @brief toList
         * @param v
         * @return
         */
        virtual const QVariantList toList(const QVariant&v=QVariant());

        /**
         * @brief toMap
         * @return
         */
        virtual QVariantMap toMap()const;
        virtual QVariantMap toMap(const QVariant&v) const;
        virtual const QVariantMap toMap(const QVariant&key, const QVariant&value);

        /**
         * @brief toHash
         * @return
         */
        virtual QVariantHash toHash() const;
        virtual const QVariantHash toHash(const QVariant&v);
        virtual const QVariantHash toHash(const QVariant&key, const QVariant&value);

        /**
         * @brief toType
         * @param type
         * @param v
         * @return
         */
        virtual const QVariant toType(const QVariant::Type&type, const QVariant&v=QVariant());
        virtual const QVariant toVariant(const QVariant&v);
        virtual const QVariant toVariantObject(const QVariant&v);
        virtual const QVariant toVariantJson(const QVariant&v);
        virtual const QVariant toVariantCBor(const QVariant&v);

        /**
         * @brief toUrl
         * @param v
         * @return
         */
        virtual const QUrl toUrl(Q_CONST_V);

        /**
         * @brief makeVVM
         * @param key
         * @param value
         * @return
         */
        virtual VariantUtil &makeVVM(const QVariant&key, const QVariant &value);
        virtual VariantUtil &mVVM(const QVariant&key, const QVariant&value);
        virtual VariantUtil &makeMap(const QVariant&key, const QVariant&value);
        virtual VariantUtil &mMap(const QVariant&key, const QVariant&value);
        virtual VariantUtil &makeHash(const QVariant&key, const QVariant&value);
        virtual VariantUtil &mHash(const QVariant&key, const QVariant&value);
        virtual VariantUtil &makeList(const QVariant&value);
        virtual VariantUtil &mList(const QVariant&value);
        virtual VariantUtil &clear();
        virtual VariantUtil &vUnion(const QVariant&v);
        virtual VariantUtil &vUnion(const QVariant&vDestine, const QVariant&vSource);
        virtual VariantUtil &vMerge(const QVariant&v);
        virtual VariantUtil &vMerge(const QVariant &vDestine, const QVariant&vSource);
        virtual VariantUtil &vDeduplicate(const QVariant&v);


        /**
         * @brief vIsEmpty
         * @param v
         * @return
         */
        virtual bool vIsEmpty(Q_CONST_V);

        /**
         * @brief vIsObject
         * @param v
         * @return
         */
        virtual bool vIsObject(Q_CONST_V);

        /**
         * @brief vIsList
         * @param v
         * @return
         */
        virtual bool vIsList(Q_CONST_V);

        /**
         * @brief vIsMap
         * @param v
         * @return
         */
        virtual bool vIsMap(Q_CONST_V);

        /**
         * @brief vIsString
         * @param v
         * @return
         */
        virtual bool vIsString(Q_CONST_V);

    private:
        void*p=nullptr;
    };

}

typedef QStm::VariantUtil VariantUtil;


Q_DECLARE_METATYPE(VariantUtil)
Q_DECLARE_METATYPE(VariantUtil*)

