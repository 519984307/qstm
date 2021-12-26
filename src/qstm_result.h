#pragma once

#include "./qstm_result_info.h"
#include "./qstm_global.h"
#include "./qstm_types.h"
#include <QSqlError>

//!
//! \brief The ResultValue class
//!class for carrying status and varying values
class Q_STM_EXPORT ResultValue : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantHash data READ data WRITE setData)
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

    //!
    //! \brief ResultValue
    //! \param parent
    //!
    //! constructor
    Q_INVOKABLE explicit ResultValue(QObject *parent = nullptr);

    //!
    //! \brief ~ResultValue
    //!
    Q_INVOKABLE virtual ~ResultValue();


    //!
    //! \brief operator bool
    //!
    operator bool() const;

    //!
    //! \brief operator =
    //! \param result
    //! \return
    //!
    ResultValue &operator=(const bool &result);

    //!
    //! \brief operator =
    //! \param error
    //! \return
    //!
    ResultValue &operator=(const QSqlError &error);

    //!
    //! \brief operator <<
    //! \param error
    //! \return
    //!
    ResultValue &operator<<(const QSqlError &error);

    //!
    //! \brief operator =
    //! \param value
    //! \return
    //!
    ResultValue &operator=(const QVariant &value);

    //!
    //! \brief operator <<
    //! \param value
    //! \return
    //!
    ResultValue &operator<<(const QVariant &value);

    //!
    //! \brief operator =
    //! \param value
    //! \return
    //!
    ResultValue &operator=(const QString &value);

    //!
    //! \brief operator =
    //! \param value
    //! \return
    //!
    ResultValue &operator=(void *value);

    //!
    //! \brief operator <<
    //! \param value
    //! \return
    //!
    ResultValue &operator<<(void *value);

    //!
    //! \brief operator =
    //! \param value
    //! \return
    //!
    ResultValue &operator=(const ResultValue &value);

    //!
    //! \brief operator <<
    //! \param value
    //! \return
    //!
    ResultValue &operator<<(const ResultValue &value);

    //!
    //! \brief operator ==
    //! \param value
    //! \return
    //!
    bool operator==(const ResultValue &value);

    //!
    //! \brief operator !=
    //! \param value
    //! \return
    //!
    bool operator!=(const ResultValue &value);

    //!
    //! \brief resultInfo
    //! \return
    //!
    virtual QStm::ResultInfo &resultInfo();

    //!
    //! \brief printInfo
    //! \param v
    //! \return
    //!
    virtual ResultValue &printInfo(const QVariant &v = QVariant());

    //!
    //! \brief printWarning
    //! \param v
    //! \return
    //!
    virtual ResultValue &printWarning(const QVariant &v = QVariant());

    //!
    //! \brief resultVariant
    //! \return
    //!
    virtual QVariant &resultVariant() const;

    //!
    //! \brief resultVariantInfo
    //! \return
    //!
    Q_INVOKABLE virtual QVariant resultVariantInfo() const;

    //!
    //! \brief resultMap
    //! \return
    //!
    virtual QVariantMap resultMap() const;

    //!
    //! \brief resultHash
    //! \return
    //!
    virtual QVariantHash resultHash() const;

    //!
    //! \brief resultList
    //! \return
    //!
    virtual QVariantList resultList() const;

    //!
    //! \brief resultToList
    //! \return
    //!
    virtual QVariantList resultToList() const;

    //!
    //! \brief resultString
    //! \return
    //!
    virtual QString resultString() const;

    //!
    //! \brief resultByteArray
    //! \return
    //!
    virtual QByteArray resultByteArray() const;

    //!
    //! \brief resultUuid
    //! \return
    //!
    virtual QUuid resultUuid() const;

    //!
    //! \brief resultInt
    //! \return
    //!
    virtual qlonglong resultInt() const;

    //!
    //! \brief resultDate
    //! \return
    //!
    virtual QDate resultDate() const;

    //!
    //! \brief resultDateTime
    //! \return
    //!
    virtual QDateTime resultDateTime() const;

    //!
    //! \brief resultTime
    //! \return
    //!
    virtual QTime resultTime() const;

    //!
    //! \brief resultUrl
    //! \return
    //!
    virtual QUrl resultUrl() const;

    //!
    //! \brief resultPointer
    //! \return
    //!
    virtual void *resultPointer() const;

    //!
    //! \brief resultObject
    //! \return
    //!
    template<class T>
    T resultObject()
    {
        auto p = reinterpret_cast<T>(this->resultPointer());
        return p;
    }

    //!
    //! \brief clear
    //! \return
    //!
    virtual ResultValue &clear();

    //!
    //! \brief toMap
    //! \return
    //!
    virtual const QVariantMap toMap();

    //!
    //! \brief toHash
    //! \return
    //!
    virtual const QVariantHash &toHash();

    //!
    //! \brief returnHash
    //! \return
    //!
    virtual QByteArray &returnHash() const;

    //!
    //! \brief returnType
    //! \return
    //!
    virtual MessageType returnType() const;

    //!
    //! \brief returnCode
    //! \return
    //!
    virtual QVariant &returnCode() const;

    //!
    //! \brief returnText
    //! \return
    //!
    virtual QString &returnText() const;

    //!
    //! \brief setResult
    //! \param result
    //! \return
    //!
    ResultValue &setResult(void *result);

    //!
    //! \brief setResult
    //! \param object
    //! \return
    //!
    ResultValue &setResult(QObject &object);

    //!
    //! \brief setResult
    //! \param result
    //! \return
    //!
    ResultValue &setResult(const QVariant &result);

    //!
    //! \brief setResult
    //! \param result
    //! \return
    //!
    ResultValue &setResult(const ResultValue &result);

    //!
    //! \brief setResult
    //! \param result
    //! \return
    //!
    ResultValue &setResult(const QSqlError &result);

    //!
    //! \brief setMsg
    //! \param value
    //! \return
    //!
    ResultValue &setMsg(const QVariant &value);

    //!
    //! \brief setInformation
    //! \param value
    //! \return
    //!
    ResultValue &setInformation(const QVariant &value);

    //!
    //! \brief setWarning
    //! \return
    //!
    ResultValue &setWarning();

    //!
    //! \brief setWarning
    //! \param value
    //! \return
    //!
    ResultValue &setWarning(const QVariant &value);

    //!
    //! \brief setValidation
    //! \return
    //!
    ResultValue &setValidation();

    //!
    //! \brief setValidation
    //! \param value
    //! \return
    //!
    ResultValue &setValidation(const QVariant &value);

    //!
    //! \brief setValidation
    //! \param lr
    //! \return
    //!
    ResultValue &setValidation(const ResultValue &lr);

    //!
    //! \brief setResponse
    //! \param value
    //! \return
    //!
    ResultValue &setResponse(const QVariant &value);

    //!
    //! \brief setUnauthorized
    //! \return
    //!
    ResultValue &setUnauthorized();

    //!
    //! \brief setUnauthorized
    //! \param value
    //! \return
    //!
    ResultValue &setUnauthorized(const QVariant &value);

    //!
    //! \brief setUnauthorized
    //! \param lr
    //! \return
    //!
    ResultValue &setUnauthorized(const ResultValue &lr);

    //!
    //! \brief setNotImplemented
    //! \return
    //!
    ResultValue &setNotImplemented();

    //!
    //! \brief setNotImplemented
    //! \param value
    //! \return
    //!
    ResultValue &setNotImplemented(const QVariant &value);

    //!
    //! \brief setNotImplemented
    //! \param lr
    //! \return
    //!
    ResultValue &setNotImplemented(const ResultValue &lr);

    //!
    //! \brief setBadRequest
    //! \return
    //!
    ResultValue &setBadRequest();

    //!
    //! \brief setBadRequest
    //! \param value
    //! \return
    //!
    ResultValue &setBadRequest(const QVariant &value);

    //!
    //! \brief setBadRequest
    //! \param lr
    //! \return
    //!
    ResultValue &setBadRequest(const ResultValue &lr);

    //!
    //! \brief setNotFound
    //! \return
    //!
    ResultValue &setNotFound();

    //!
    //! \brief setNotFound
    //! \param value
    //! \return
    //!
    ResultValue &setNotFound(const QVariant &value);

    //!
    //! \brief setNotFound
    //! \param lr
    //! \return
    //!
    ResultValue &setNotFound(const ResultValue &lr);

    //!
    //! \brief setUnsupportedMediaType
    //! \return
    //!
    ResultValue &setUnsupportedMediaType();

    //!
    //! \brief setUnsupportedMediaType
    //! \param value
    //! \return
    //!
    ResultValue &setUnsupportedMediaType(const QVariant &value);

    //!
    //! \brief setUnsupportedMediaType
    //! \param lr
    //! \return
    //!
    ResultValue &setUnsupportedMediaType(const ResultValue &lr);

    //!
    //! \brief setCritical
    //! \return
    //!
    ResultValue &setCritical();

    //!
    //! \brief setCritical
    //! \param value
    //! \return
    //!
    ResultValue &setCritical(const QString &value);

    //!
    //! \brief setCritical
    //! \param value
    //! \return
    //!
    ResultValue &setCritical(const QVariantHash &value);

    //!
    //! \brief setCritical
    //! \param value
    //! \return
    //!
    ResultValue &setCritical(const QVariantList &value);

    //!
    //! \brief setCritical
    //! \param value
    //! \return
    //!
    ResultValue &setCritical(const QSqlError &value);

    //!
    //! \brief setCritical
    //! \param lr
    //! \return
    //!
    ResultValue &setCritical(const ResultValue &lr);

    //!
    //! \brief isOk
    //! \return
    //!
    virtual bool isOk() const;

    //!
    //! \brief isNotOk
    //! \return
    //!
    virtual bool isNotOk() const;

    //!
    //! \brief isInformation
    //! \return
    //!
    virtual bool isInformation() const;

    //!
    //! \brief isWarning
    //! \return
    //!
    virtual bool isWarning() const;

    //!
    //! \brief isValidation
    //! \return
    //!
    virtual bool isValidation() const;

    //!
    //! \brief isCritical
    //! \return
    //!
    virtual bool isCritical() const;

    //!
    //! \brief isUnauthorized
    //! \return
    //!
    virtual bool isUnauthorized() const;

    //!
    //! \brief isNotfound
    //! \return
    //!
    virtual bool isNotfound() const;

    //!
    //! \brief isBadRequest
    //! \return
    //!
    virtual bool isBadRequest() const;

    //!
    //! \brief data
    //! \return
    //!
    virtual QVariantHash data() const;

    //!
    //! \brief setData
    //! \param data
    //!
    virtual void setData(const QVariantHash &data);

    //!
    //! \brief stateCode
    //! \return
    //!
    Q_INVOKABLE virtual QVariant stateCode() const;

    //!
    //! \brief sc
    //! \return
    //!
    Q_INVOKABLE virtual QVariant sc() const;

    //!
    //! \brief setCode
    //! \param statusCode
    //! \param reasonPhrase
    //! \return
    //!
    virtual ResultValue &setCode(const QVariant &statusCode, const QVariant &reasonPhrase);

    //!
    //! \brief toString
    //! \return
    //!
    Q_INVOKABLE virtual QString toString() const;
public:
    void *p = nullptr;
};
