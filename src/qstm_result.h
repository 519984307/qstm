#pragma once

#include "./qstm_global.h"
#include "./qstm_types.h"
#include <QSqlError>

/**
 * @brief The ResultValue class
 *
 * class for carrying status and varying values
 */
class Q_STM_EXPORT ResultValue : public QObject
{
    Q_OBJECT
    friend class ResultValuePvt;

public:
    enum MessageType {
        None = 1,
        Information = 2,
        Warning = 4,
        Validation = 8,
        Critical = 16,
        Unauthorized = 32,
        Notfound = 64,
        BadRequest = 128,
        UnsupportedMediaType = 256,
        NotImplemented = 512
    };

    Q_INVOKABLE explicit ResultValue(QObject *parent = nullptr);
    Q_INVOKABLE virtual ~ResultValue();

    Q_PROPERTY(QVariantHash data READ data WRITE setData)

    /**
     * @brief operator bool
     */
    operator bool() const;
    ResultValue &operator=(const bool &result);

    /**
     * @brief operator =
     */
    ResultValue &operator=(const QSqlError &error);

    ResultValue &operator<<(const QSqlError &error);

    /**
     * @brief operator =
     * @param value
     */
    ResultValue &operator=(const QVariant &value);
    ResultValue &operator<<(const QVariant &value);
    ResultValue &operator=(const QString &value);

    /**
     * @brief operator =
     * @param value
     */
    ResultValue &operator=(void *value);
    ResultValue &operator<<(void *value);

    /**
     * @brief operator =
     * @param value
     * @return
     */
    ResultValue &operator=(const ResultValue &value);
    ResultValue &operator<<(const ResultValue &value);
    bool operator==(const ResultValue &value);
    bool operator!=(const ResultValue &value);

    /**
     * @brief printInfo
     * @param v
     * @return
     */
    virtual ResultValue &printInfo(const QVariant &v = QVariant());

    /**
     * @brief printWarning
     * @param v
     * @return
     */
    virtual ResultValue &printWarning(const QVariant &v = QVariant());

    /**
     * @brief resultVariant
     * @return
     */
    virtual QVariant &resultVariant() const;

    /**
     * @brief resultMap
     * @return
     */
    virtual QVariantHash resultMap() const;

    /**
     * @brief resultHash
     * @return
     */
    virtual QVariantHash resultHash() const;

    /**
     * @brief resultList
     * @return
     */
    virtual QVariantList resultList() const;

    /**
     * @brief resultToList
     * @return
     *
     * converto return to QVariantList
     */
    virtual QVariantList resultToList() const;

    /**
     * @brief resultString
     * @return
     */
    virtual QString resultString() const;

    /**
     * @brief resultByteArray
     * @return
     */
    virtual QByteArray resultByteArray() const;

    /**
     * @brief resultUuid
     * @return
     */
    virtual QUuid resultUuid() const;

    /**
     * @brief resultLongLong
     * @return
     */
    virtual qlonglong resultInt() const;

    /**
     * @brief resultDate
     * @return
     */
    virtual QDate resultDate() const;

    /**
     * @brief resultDateTime
     * @return
     */
    virtual QDateTime resultDateTime() const;

    /**
     * @brief resultTime
     * @return
     */
    virtual QTime resultTime() const;

    /**
     * @brief resultUrl
     * @return
     */
    virtual QUrl resultUrl() const;

    /**
     * @brief resultPointer
     * @return
     */
    virtual void *resultPointer() const;

    /**
     * @brief resultObject
     * @return
     */
    template<class T>
    T resultObject()
    {
        auto p = reinterpret_cast<T>(this->resultPointer());
        return p;
    }

    /**
     * @brief clear
     */
    virtual ResultValue &clear();

    /**
     * @brief toMap
     * @return
     */
    virtual const QVariantMap toMap();

    /**
     * @brief toHash
     * @return
     */
    virtual const QVariantHash &toHash();

    /**
     * @brief returnHash
     * @return
     */
    virtual QByteArray &returnHash() const;

    /**
     * @brief returnCode
     * @return
     */
    virtual MessageType returnType() const;
    virtual QVariant &returnCode() const;
    virtual QString &returnText() const;

    /**
     * @brief setResult
     * @param result
     * @return
     */
    ResultValue &setResult(void *result);
    ResultValue &setResult(QObject &object);
    ResultValue &setResult(const QVariant &result);
    ResultValue &setResult(const ResultValue &result);
    ResultValue &setResult(const QSqlError &result);

    /**
     * @brief setMsg
     * @param value
     * @return
     */
    ResultValue &setMsg(const QVariant &value);

    /**
     * @brief setInformation
     * @param value
     */
    ResultValue &setInformation(const QVariant &value);

    /**
     * @brief setWarning
     * @return
     */
    ResultValue &setWarning();

    /**
     * @brief setWarning
     * @param value
     */
    ResultValue &setWarning(const QVariant &value);

    /**
     * @brief setValidation
     * @return
     */
    ResultValue &setValidation();
    ResultValue &setValidation(const QVariant &value);
    ResultValue &setValidation(const ResultValue &lr);

    /**
     * @brief setUnauthorized
     * @param value
     * @return
     */
    ResultValue &setUnauthorized();
    ResultValue &setUnauthorized(const QVariant &value);
    ResultValue &setUnauthorized(const ResultValue &lr);

    /**
     * @brief setNotImplemented
     * @return
     */
    ResultValue &setNotImplemented();
    ResultValue &setNotImplemented(const QVariant &value);
    ResultValue &setNotImplemented(const ResultValue &lr);

    /**
     * @brief setBadRequest
     * @param value
     * @return
     */
    ResultValue &setBadRequest();
    ResultValue &setBadRequest(const QVariant &value);
    ResultValue &setBadRequest(const ResultValue &lr);

    /**
     * @brief setUnauthorized
     * @param value
     * @return
     */
    ResultValue &setNotFound();
    ResultValue &setNotFound(const QVariant &value);
    ResultValue &setNotFound(const ResultValue &lr);

    /**
     * @brief setUnsupportedMediaType
     * @return
     */
    ResultValue &setUnsupportedMediaType();
    ResultValue &setUnsupportedMediaType(const QVariant &value);
    ResultValue &setUnsupportedMediaType(const ResultValue &lr);

    /**
     * @brief setCritical
     * @param value
     */
    ResultValue &setCritical();
    ResultValue &setCritical(const QString &value);
    ResultValue &setCritical(const QVariantHash &value);
    ResultValue &setCritical(const QVariantList &value);
    ResultValue &setCritical(const QSqlError &value);
    ResultValue &setCritical(const ResultValue &lr);

    /**
     * @brief isOk
     * @return
     */
    virtual bool isOk() const;

    /**
     * @brief isNotOk
     * @return
     */
    virtual bool isNotOk() const;

    /**
     * @brief isInformation
     * @return
     */
    virtual bool isInformation() const;

    /**
     * @brief isWarning
     * @return
     */
    virtual bool isWarning() const;

    /**
     * @brief isValidation
     * @return
     */
    virtual bool isValidation() const;

    /**
     * @brief isCritical
     * @return
     */
    virtual bool isCritical() const;

    /**
     * @brief isUnauthorized
     * @return
     */
    virtual bool isUnauthorized() const;

    /**
     * @brief isNotfound
     * @return
     */
    virtual bool isNotfound() const;

    /**
     * @brief isBadRequest
     * @return
     */
    virtual bool isBadRequest() const;

    /**
     * @brief data
     * @return
     */
    virtual QVariantHash data() const;
    virtual void setData(const QVariantHash &data);

    /**
     * @brief stateCode
     * @return
     */
    Q_INVOKABLE virtual QVariant stateCode() const;
    Q_INVOKABLE virtual QVariant sc() const;

    /**
     * @brief setCode
     * @param statusCode
     * @param reasonPhrase
     * @return
     */
    virtual ResultValue &setCode(const QVariant &statusCode, const QVariant &reasonPhrase);

    /**
     * @brief toString
     * @return
     */
    Q_INVOKABLE virtual QString toString() const;

private:
    void *p = nullptr;
};
