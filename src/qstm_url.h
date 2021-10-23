#pragma once

#include "./qstm_global.h"
#include "./qstm_result.h"
#include <QVariantHash>
#include <QUrl>

namespace QStm {

class Q_STM_EXPORT Url: public QVariant
{
public:
    Q_INVOKABLE explicit Url(const QVariant&v=QVariantHash());
    Q_INVOKABLE explicit Url(const ResultValue &v);
    Q_INVOKABLE virtual ~Url();

    /**
     * @brief operator =
     * @param v
     * @return
     */
    Url&operator=(const QVariant&v);

    /**
     * @brief from
     * @param v
     * @return
     */
    static Url from(const QVariant&v);

    /**
     * @brief read
     * @param v
     * @return
     */
    Url&read(const QVariant&v);

    /**
     * @brief header
     * @return
     */
    virtual QVariantHash&headers() const;
    virtual Url&header(const QVariant &value);
    virtual Url&setHeader(const QVariant &value);

    /**
     * @brief name
     * @return
     */
    virtual QString&name() const;
    virtual Url&name(const QVariant &value);
    virtual Url&setName(const QVariant &value);


    /**
     * @brief url
     * @return
     */
    virtual QString&outPutName() const;
    virtual Url&outPutName(const QVariant &value);
    virtual Url&setOutPutName(const QVariant &value);

    /**
     * @brief url
     * @return
     */
    virtual QUrl&url() const;
    virtual Url&url(const QVariant &value);
    virtual Url&setUrl(const QVariant &value);

    /**
     * @brief isValid
     * @return
     */
    virtual bool isValid() const;
    virtual bool isNull() const;

    /**
     * @brief isLocalFile
     * @return
     */
    bool isLocalFile() const;
    QString toLocalFile() const;
    static Url fromLocalFile(const QString &localfile);

    /**
     * @brief toMap
     * @return
     */
    virtual QVariantMap toMap() const;

    /**
     * @brief toHash
     * @return
     */
    virtual QVariantHash toHash() const;

    /**
     * @brief readBody
     * @return
     */
    virtual QByteArray readBody() const;

    /**
     * @brief toString
     * @return
     */
    QString toString() const;

private:
    void*p = nullptr;
};

}

typedef QStm::Url Url;

Q_DECLARE_METATYPE(Url)
Q_DECLARE_METATYPE(Url*)
