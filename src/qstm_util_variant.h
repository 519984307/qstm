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

//!
//! \brief The VariantUtil class
//!
class Q_STM_EXPORT VariantUtil:public QVariant{
public:
    explicit VariantUtil(Q_CONST_V);
    virtual ~VariantUtil();

    //!
    //! \brief typesListString
    //!
    const QStmVTypesList&typesListString     = QStmTypesListMetaString   ;

    //!
    //! \brief typesListNumeric
    //!
    const QStmVTypesList&typesListNumeric    = QStmTypesListNumeric  ;

    //!
    //! \brief typesListIntergers
    //!
    const QStmVTypesList&typesListIntergers  = QStmTypesListIntegers;

    //!
    //! \brief typesListClass
    //!
    const QStmVTypesList&typesListClass      = QStmTypesListClass    ;

    //!
    //! \brief typesListObjects
    //!
    const QStmVTypesList&typesListObjects    = QStmTypesListObjects  ;

    //!
    //! \brief typesListDates
    //!
    const QStmVTypesList&typesListDates      = QStmTypesListDates    ;

    //!
    //! \brief typesListBool
    //!
    const QStmVTypesList&typesListBool       = QStmTypesListBool     ;

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!
    VariantUtil&operator=(const QVariant&v);

    //!
    //! \brief isUuid
    //! \param v
    //! \return
    //!
    virtual bool isUuid(Q_CONST_V) const;

    //!
    //! \brief isUuid
    //! \param v
    //! \param uuidSet
    //! \return
    //!
    virtual bool isUuid(const QVariant&v, QUuid&uuidSet) const;

    //!
    //! \brief isHex
    //! \param v
    //! \return
    //!
    virtual bool isHex(Q_CONST_V) const;

    //!
    //! \brief isBase64
    //! \param v
    //! \return
    //!
    virtual bool isBase64(Q_CONST_V) const;

    //!
    //! \brief toStr
    //! \param v
    //! \return
    //!
    virtual const QString toStr(Q_CONST_V);

    //!
    //! \brief toAlphaNumber
    //! \param v
    //! \return
    //!
    virtual const QByteArray toAlphaNumber(Q_CONST_V);

    //!
    //! \brief toAlphaNumeric
    //! \param v
    //! \return
    //!
    virtual const QByteArray toAlphaNumeric(Q_CONST_V);


    //!
    //! \brief toAlphaNumeric
    //! \param v
    //! \return
    //!
    virtual const QString toAlphaText(Q_CONST_V);

    //!
    //! \brief toByteArray
    //! \param v
    //! \return
    //!
    virtual const QByteArray toByteArray(Q_CONST_V);

    //!
    //! \brief toChar
    //! \param v
    //! \return
    //!
    virtual const QChar toChar(Q_CONST_V);

    //!
    //! \brief toInt
    //! \param v
    //! \return
    //!
    virtual int toInt(Q_CONST_V);

    //!
    //! \brief toLongLong
    //! \param v
    //! \return
    //!
    virtual qlonglong toLongLong(Q_CONST_V);

    //!
    //! \brief toDate
    //! \param v
    //! \return
    //!
    virtual const QDate toDate(Q_CONST_V);

    //!
    //! \brief toTime
    //! \param v
    //! \return
    //!
    virtual const QTime toTime(Q_CONST_V);

    //!
    //! \brief toDateTime
    //! \param v
    //! \return
    //!
    virtual const QDateTime toDateTime(Q_CONST_V);

    //!
    //! \brief toDouble
    //! \param v
    //! \return
    //!
    virtual double toDouble(Q_CONST_V);

    //!
    //! \brief toBool
    //! \param v
    //! \return
    //!
    virtual bool toBool(Q_CONST_V);

    //!
    //! \brief canConvertJson
    //! \param v
    //! \return
    //!
    virtual bool canConvertJson(Q_CONST_V)const;

    //!
    //! \brief canConvertJson
    //! \param v
    //! \param vOut
    //! \return
    //!
    virtual bool canConvertJson(const QVariant &v, QVariant &vOut)const;

    //!
    //! \brief toMd5
    //! \param v
    //! \return
    //! se for um QVariantHash ou QVariantList convertera para json para entao tirar o md5
    //! se nao for md5 sera tirado o md5 dos bytes
    //! se nao for uuid um md5 sera convertido em string para md5
    //! se a string enviada for um md ou md5uui entao nada ocorrera retornando o md5 ja existe nao gerando outro
    virtual const QByteArray toMd5(Q_CONST_V);

    //!
    //! \brief toHex
    //! \param v
    //! \return
    //!
    virtual const QByteArray toHex(Q_CONST_V);

    //!
    //! \brief toUuid
    //! \param v
    //! \return
    //! se for md5 sera convertido para uuidMd5
    //! se for uuid nada ocorrera retornando o uuid
    virtual const QUuid toUuid(Q_CONST_V);

    //!
    //! \brief toUuidSimple
    //! \param v
    //! \return
    //! remove {} do uuid gerado pelo qt
    virtual const QString toUuidSimple(Q_CONST_V);

    //!
    //! \brief toMd5Uuid
    //! \param v
    //! \return
    //!se a string enviada for um md ou mduui entao nada ocorrera retornando o md5 ja existe nao gerando outro
    virtual const QUuid toMd5Uuid(Q_CONST_V);

    //!
    //! \brief toVVM
    //! \return
    //!
    virtual QVVM toVVM()const;

    //!
    //! \brief toVVM
    //! \param v
    //! \return
    //!
    virtual const QVVM toVVM(const QVariant&v);

    //!
    //! \brief toVVM
    //! \param key
    //! \param value
    //! \return
    //!
    virtual const QVVM toVVM(const QVariant&key, const QVariant &value);

    //!
    //! \brief takeList
    //! \param keyName
    //! \return
    //!
    virtual const QVariantList takeList(const QByteArray &keyName);

    //!
    //! \brief type
    //! \return
    //!
    virtual int typeId() const;

    //!
    //! \brief toStringList
    //! \return
    //!
    virtual const QStringList toStringList();

    //!
    //! \brief toStringList
    //! \param v
    //! \return
    //!
    virtual const QStringList toStringList(const QVariant&v);

    //!
    //! \brief toList
    //! \param v
    //! \return
    //!
    virtual const QVariantList toList(const QVariant&v=QVariant());

    //!
    //! \brief toMap
    //! \return
    //!
    virtual QVariantMap toMap()const;

    //!
    //! \brief toMap
    //! \param v
    //! \return
    //!
    virtual const QVariantMap toMap(const QVariant&v);

    //!
    //! \brief toMap
    //! \param key
    //! \param value
    //! \return
    //!
    virtual const QVariantMap toMap(const QVariant&key, const QVariant&value);

    //!
    //! \brief toHash
    //! \return
    //!
    virtual QVariantHash toHash() const;

    //!
    //! \brief toHash
    //! \param v
    //! \return
    //!
    virtual const QVariantHash toHash(const QVariant&v);

    //!
    //! \brief toHash
    //! \param key
    //! \param value
    //! \return
    //!
    virtual const QVariantHash toHash(const QVariant&key, const QVariant&value);

    //!
    //! \brief toMultiHash
    //! \return
    //!
    virtual QMultiHash<QString, QVariant> toMultiHash() const;

    //!
    //! \brief toMultiHash
    //! \param v
    //! \return
    //!
    const virtual QMultiHash<QString, QVariant> toMultiHash(const QVariant &v);

    //!
    //! \brief toMultiHash
    //! \param key
    //! \param value
    //! \return
    //!
    const virtual QMultiHash<QString, QVariant> toMultiHash(const QVariant &key, const QVariant &value);

    //!
    //! \brief toType
    //! \param type
    //! \param v
    //! \return
    //!
    const QVariant toType(int typeId, const QVariant &v=QVariant());

    //!
    //! \brief toVariant
    //! \param v
    //! \return
    //!
    virtual const QVariant toVariant(const QVariant&v);

    //!
    //! \brief toVariantObject
    //! \param v
    //! \return
    //!
    virtual const QVariant toVariantObject(const QVariant&v);

    //!
    //! \brief toVariantJson
    //! \param v
    //! \return
    //!
    virtual const QVariant toVariantJson(const QVariant&v);

    //!
    //! \brief toVariantCBor
    //! \param v
    //! \return
    //!
    virtual const QVariant toVariantCBor(const QVariant&v);

    //!
    //! \brief toUrl
    //! \param v
    //! \return
    //!
    virtual const QUrl toUrl(Q_CONST_V);

    //!
    //! \brief makeVVM
    //! \param key
    //! \param value
    //! \return
    //!
    virtual VariantUtil &makeVVM(const QVariant&key, const QVariant &value);

    //!
    //! \brief mVVM
    //! \param key
    //! \param value
    //! \return
    //!
    virtual VariantUtil &mVVM(const QVariant&key, const QVariant&value);

    //!
    //! \brief makeMap
    //! \param key
    //! \param value
    //! \return
    //!
    virtual VariantUtil &makeMap(const QVariant&key, const QVariant&value);

    //!
    //! \brief mMap
    //! \param key
    //! \param value
    //! \return
    //!
    virtual VariantUtil &mMap(const QVariant&key, const QVariant&value);

    //!
    //! \brief makeHash
    //! \param key
    //! \param value
    //! \return
    //!
    virtual VariantUtil &makeHash(const QVariant&key, const QVariant&value);

    //!
    //! \brief mHash
    //! \param key
    //! \param value
    //! \return
    //!
    virtual VariantUtil &mHash(const QVariant&key, const QVariant&value);

    //!
    //! \brief makeList
    //! \param value
    //! \return
    //!
    virtual VariantUtil &makeList(const QVariant&value);

    //!
    //! \brief mList
    //! \param value
    //! \return
    //!
    virtual VariantUtil &mList(const QVariant&value);

    //!
    //! \brief toUuidCompuser
    //! \param value
    //! \return
    //!
    virtual const QUuid toUuidCompuser(const QVariant&value);

    //!
    //! \brief clear
    //! \return
    //!
    virtual VariantUtil &clear();

    //!
    //! \brief vUnion
    //! \param v
    //! \return
    //!
    virtual VariantUtil &vUnion(const QVariant&v);

    //!
    //! \brief vUnion
    //! \param vDestine
    //! \param vSource
    //! \return
    //!
    virtual VariantUtil &vUnion(const QVariant&vDestine, const QVariant&vSource);

    //!
    //! \brief vMerge
    //! \param v
    //! \return
    //!
    virtual VariantUtil &vMerge(const QVariant&v);

    //!
    //! \brief vMerge
    //! \param vDestine
    //! \param vSource
    //! \return
    //!
    virtual VariantUtil &vMerge(const QVariant &vDestine, const QVariant&vSource);

    //!
    //! \brief vDeduplicate
    //! \param v
    //! \return
    //!
    virtual VariantUtil &vDeduplicate(const QVariant&v);

    //!
    //! \brief vIsEmpty
    //! \param v
    //! \return
    //!
    virtual bool vIsEmpty(Q_CONST_V);

    //!
    //! \brief vIsObject
    //! \param v
    //! \return
    //!
    virtual bool vIsObject(Q_CONST_V);

    //!
    //! \brief vIsList
    //! \param v
    //! \return
    //!
    virtual bool vIsList(Q_CONST_V);

    //!
    //! \brief vIsMap
    //! \param v
    //! \return
    //!
    virtual bool vIsMap(Q_CONST_V);

    //!
    //! \brief vIsString
    //! \param v
    //! \return
    //!
    virtual bool vIsString(Q_CONST_V);

    //!
    //! \brief convertTo
    //! \param v
    //! \param typeId
    //! \return
    //!
    virtual QVariant convertTo(const QVariant&v, int typeId);

private:
    void*p=nullptr;
};

}

typedef QStm::VariantUtil VariantUtil;


Q_DECLARE_METATYPE(VariantUtil)
Q_DECLARE_METATYPE(VariantUtil*)

