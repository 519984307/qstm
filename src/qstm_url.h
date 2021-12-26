#pragma once

#include "./qstm_global.h"
#include "./qstm_result.h"
#include <QVariantHash>
#include <QUrl>

namespace QStm {

//!
//! \brief The Url class
//! url util class
class Q_STM_EXPORT Url: public QVariant
{
public:

    //!
    //! \brief Url
    //! \param v
    //!
    Q_INVOKABLE explicit Url(const QVariant&v=QVariantHash());

    //!
    //! \brief Url
    //! \param v
    //!
    Q_INVOKABLE explicit Url(const ResultValue &v);

    //!
    //! \brief ~Url
    //!
    virtual ~Url();

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!
    Url&operator=(const QVariant&v);


    //!
    //! \brief from
    //! \param v
    //! \return
    //!
    static Url from(const QVariant&v);

    //!
    //! \brief read
    //! \param v
    //! \return
    //!
    Url&read(const QVariant&v);

    //!
    //! \brief headers
    //! \return
    //!
    virtual QVariantHash&headers() const;

    //!
    //! \brief header
    //! \param value
    //! \return
    //!
    virtual Url&header(const QVariant &value);

    //!
    //! \brief setHeader
    //! \param value
    //! \return
    //!
    virtual Url&setHeader(const QVariant &value);

    //!
    //! \brief name
    //! \return
    //!
    virtual QString&name() const;

    //!
    //! \brief name
    //! \param value
    //! \return
    //!
    virtual Url&name(const QVariant &value);

    //!
    //! \brief setName
    //! \param value
    //! \return
    //!
    virtual Url&setName(const QVariant &value);

    //!
    //! \brief outPutName
    //! \return
    //!
    virtual QString&outPutName() const;

    //!
    //! \brief outPutName
    //! \param value
    //! \return
    //!
    virtual Url&outPutName(const QVariant &value);

    //!
    //! \brief setOutPutName
    //! \param value
    //! \return
    //!
    virtual Url&setOutPutName(const QVariant &value);

    //!
    //! \brief url
    //! \return
    //!
    virtual QUrl&url() const;

    //!
    //! \brief url
    //! \param value
    //! \return
    //!
    virtual Url&url(const QVariant &value);

    //!
    //! \brief setUrl
    //! \param value
    //! \return
    //!
    virtual Url&setUrl(const QVariant &value);

    //!
    //! \brief isValid
    //! \return
    //!
    virtual bool isValid() const;

    //!
    //! \brief isNull
    //! \return
    //!
    virtual bool isNull() const;

    //!
    //! \brief isLocalFile
    //! \return
    //!
    bool isLocalFile() const;

    //!
    //! \brief toLocalFile
    //! \return
    //!
    QString toLocalFile() const;

    //!
    //! \brief fromLocalFile
    //! \param localfile
    //! \return
    //!
    static Url fromLocalFile(const QString &localfile);

    //!
    //! \brief toMap
    //! \return
    //!
    virtual QVariantMap toMap() const;

    //!
    //! \brief toHash
    //! \return
    //!
    virtual QVariantHash toHash() const;

    //!
    //! \brief readBody
    //! \return
    //!
    virtual QByteArray readBody() const;

    //!
    //! \brief toString
    //! \return
    //!
    QString toString() const;

private:
    void*p = nullptr;
};

}

typedef QStm::Url Url;

Q_DECLARE_METATYPE(Url)
Q_DECLARE_METATYPE(Url*)
