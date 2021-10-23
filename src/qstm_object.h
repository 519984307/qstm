#pragma once

#include "./qstm_result.h"
#include "./qstm_cache_pool.h"
#include "./qstm_global.h"

namespace QStm {

    class Q_STM_EXPORT Object: public QObject
    {
        Q_OBJECT
    public:
        Q_INVOKABLE explicit Object(QObject*parent=nullptr);
        Q_INVOKABLE ~Object();


        /**
         * @brief operator =
         * @param value
         */
        void operator=( ResultValue&value);

        /**
         * @brief operator =
         * @param value
         */
        void operator=( QSqlError&value);

        /**
         * @brief operator =
         * @param value
         */
        void operator=( QVariant&value);

        /**
         * @brief cachePool
         * @return
         */
        CachePool&cachePool();

        /**
         * @brief lastResult
         * @return
         */
        virtual ResultValue &lr();
        virtual ResultValue &lr(const ResultValue&value);
        virtual ResultValue &lr(const QSqlError&value);
        virtual ResultValue &lr(const QVariant&value);
        virtual ResultValue &lr(const QString&value);

        virtual ResultValue &lastResult();
        virtual ResultValue &lastResult(const ResultValue&value);
        virtual ResultValue &lastResult(const QSqlError&value);
        virtual ResultValue &lastResult(const QVariant&value);
        virtual ResultValue &lastResult(const QString&value);

        virtual ResultValue &setResult(const ResultValue&value);
        virtual ResultValue &setResult(const QSqlError&value);
        virtual ResultValue &setResult(const QVariant&value);
        virtual ResultValue &setResult(const QString&value);

        /**
         * @brief now
         * @return
         */
        static const QDateTime now();

        /**
         * @brief toMd5
         * @param value
         * @return
         */
        static const QByteArray toMd5(const QByteArray&value);
        static const QByteArray toMd5(const QString&value);
        static const QByteArray toMd5(const QVariant&value);

        /**
         * @brief uuidGenerator
         * @return
         */
        static const QUuid uuidGenerator();
        static const QUuid uuidGenerator(const QString&uuidBase);
        static const QUuid uuidGenCheck(const QUuid&uuid);
        static const QUuid uuidGenCheck(const QUuid&uuid, const QUuid&uuidDefault);

        /**
         * @brief hashGenerator
         * @return
         */
        static const QByteArray hashGenerator();

        /**
         * @brief randomGenerator
         * @return
         */
        static const QByteArray randomGenerator();

        /**
         * @brief makeObjectName
         * @param v
         * @return
         */
        static const QString makeObjectName(const QVariant &v);

        /**
         * @brief toMap
         * @return
         */
        Q_INVOKABLE virtual QVariantMap toMap() const;

        /**
         * @brief toHash
         * @return
         */
        Q_INVOKABLE virtual QVariantHash toHash() const;

        /**
         * @brief toVar
         * @return
         */
        Q_INVOKABLE virtual QVariant toVar() const;

        /**
         * @brief fromMap
         * @param map
         * @return
         */
        Q_INVOKABLE virtual bool fromMap(const QVariantMap &map);

        /**
         * @brief fromMap
         * @param hash
         * @return
         */
        Q_INVOKABLE virtual bool fromMap(const QVariantHash &map);

        /**
         * @brief storedProperty
         * @return
         */
        virtual ResultValue &storedProperty();

        /**
         * @brief storedIsChanged
         * @return
         */
        Q_INVOKABLE virtual bool storedIsChanged() const;

        /**
         * @brief storedMd5
         * @return
         */
        Q_INVOKABLE virtual QByteArray &storedMd5() const;

        /**
         * @brief storedMd5Make
         * @return
         */
        Q_INVOKABLE virtual QByteArray storedMd5Make() const;


    private:
        void*p=nullptr;
    };

}

