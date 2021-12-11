#pragma once

#include "./qstm_result.h"
#include "./qstm_cache_pool.h"
#include "./qstm_global.h"

namespace QStm {

//!
//! \brief The Object class
//!
//! basic object class
class Q_STM_EXPORT Object: public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit Object(QObject*parent=nullptr);
    Q_INVOKABLE ~Object();


    //!
    //! \brief operator =
    //! \param value
    //!
    void operator=( ResultValue&value);

    //!
    //! \brief operator =
    //! \param value
    //!
    void operator=( QSqlError&value);

    //!
    //! \brief operator =
    //! \param value
    //!
    void operator=( QVariant&value);

    //!
    //! \brief cachePool
    //! \return
    //!
    CachePool&cachePool();

    //!
    //! \brief lr
    //! \return
    //! result value class
    virtual ResultValue &lr();

    //!
    //! \brief lr
    //! \param value
    //! \return
    //!result value class
    virtual ResultValue &lr(const ResultValue&value);

    //!
    //! \brief lr
    //! \param value
    //! \return
    //!result value class
    virtual ResultValue &lr(const QSqlError&value);

    //!
    //! \brief lr
    //! \param value
    //! \return
    //!result value class
    virtual ResultValue &lr(const QVariant&value);

    //!
    //! \brief lr
    //! \param value
    //! \return
    //!result value class
    virtual ResultValue &lr(const QString&value);

    //!
    //! \brief lastResult
    //! \return
    //!result value class
    virtual ResultValue &lastResult();

    //!
    //! \brief lastResult
    //! \param value
    //! \return
    //!result value class
    virtual ResultValue &lastResult(const ResultValue&value);

    //!
    //! \brief lastResult
    //! \param value
    //! \return
    //!result value class
    virtual ResultValue &lastResult(const QSqlError&value);

    //!
    //! \brief lastResult
    //! \param value
    //! \return
    //!result value class
    virtual ResultValue &lastResult(const QVariant&value);

    //!
    //! \brief lastResult
    //! \param value
    //! \return
    //!result value class
    virtual ResultValue &lastResult(const QString&value);

    //!
    //! \brief setResult
    //! \param value
    //! \return
    //!result value class
    virtual ResultValue &setResult(const ResultValue&value);

    //!
    //! \brief setResult
    //! \param value
    //! \return
    //!result value class
    virtual ResultValue &setResult(const QSqlError&value);

    //!
    //! \brief setResult
    //! \param value
    //! \return
    //!result value class
    virtual ResultValue &setResult(const QVariant&value);

    //!
    //! \brief setResult
    //! \param value
    //! \return
    //!result value class
    virtual ResultValue &setResult(const QString&value);

    //!
    //! \brief now
    //! \return
    //!
    static const QDateTime now();

    //!
    //! \brief toMd5
    //! \param value
    //! \return
    //!
    static const QByteArray toMd5(const QByteArray&value);

    //!
    //! \brief toMd5
    //! \param value
    //! \return
    //!
    static const QByteArray toMd5(const QString&value);

    //!
    //! \brief toMd5
    //! \param value
    //! \return
    //!
    static const QByteArray toMd5(const QVariant&value);

    //!
    //! \brief uuidGenerator
    //! \return
    //!
    static const QUuid uuidGenerator();

    //!
    //! \brief uuidGenerator
    //! \param uuidBase
    //! \return
    //!
    static const QUuid uuidGenerator(const QString&uuidBase);

    //!
    //! \brief uuidGenCheck
    //! \param uuid
    //! \return
    //!
    static const QUuid uuidGenCheck(const QUuid&uuid);

    //!
    //! \brief uuidGenCheck
    //! \param uuid
    //! \param uuidDefault
    //! \return
    //!
    static const QUuid uuidGenCheck(const QUuid&uuid, const QUuid&uuidDefault);

    //!
    //! \brief hashGenerator
    //! \return
    //!
    static const QByteArray hashGenerator();

    //!
    //! \brief randomGenerator
    //! \return
    //!
    static const QByteArray randomGenerator();

    //!
    //! \brief makeObjectName
    //! \param v
    //! \return
    //!
    static const QString makeObjectName(const QVariant &v);

    //!
    //! \brief toMap
    //! \return
    //!
    Q_INVOKABLE virtual QVariantMap toMap() const;

    //!
    //! \brief toHash
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash toHash() const;

    //!
    //! \brief toVar
    //! \return
    //!
    Q_INVOKABLE virtual QVariant toVar() const;

    //!
    //! \brief fromVar
    //! \param map
    //! \return
    //!
    Q_INVOKABLE virtual bool fromVar(const QVariant &v);

    //!
    //! \brief fromMap
    //! \param map
    //! \return
    //!
    Q_INVOKABLE virtual bool fromMap(const QVariantMap &map);

    //!
    //! \brief fromMap
    //! \param map
    //! \return
    //!
    Q_INVOKABLE virtual bool fromHash(const QVariantHash &map);

    //!
    //! \brief storedProperty
    //! \return
    //!
    virtual ResultValue &storedProperty();

    //!
    //! \brief storedIsChanged
    //! \return
    //!
    Q_INVOKABLE virtual bool storedIsChanged() const;

    //!
    //! \brief storedMd5
    //! \return
    //!
    Q_INVOKABLE virtual QByteArray &storedMd5() const;

    //!
    //! \brief storedMd5Make
    //! \return
    //!
    Q_INVOKABLE virtual QByteArray storedMd5Make() const;


private:
    void*p=nullptr;
};

}

