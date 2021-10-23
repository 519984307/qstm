#pragma once

#include "./qstm_global.h"
#include "./qstm_result.h"
#include "./qstm_url.h"
#include <QVariantHash>

namespace QStm {

class Q_STM_EXPORT Message: public QVariant
{
public:
    Q_INVOKABLE explicit Message(const QVariant&v=QVariantHash(), const QString&settingName=QString());
    Q_INVOKABLE explicit Message(const ResultValue &v);
    Q_INVOKABLE virtual ~Message();

    /**
     * @brief operator =
     * @param v
     * @return
     */
    Message&operator=(const QVariant&v);

    /**
     * @brief operator <<
     * @param v
     * @return
     */
    Message&operator<<(const QStm::Url &v);

    /**
     * @brief make
     * @param v
     * @return
     */
    static Message make(const QVariant&v);

    /**
     * @brief variables
     * @return
     */
    QVariantHash variables() const;
    Message &variables(const QVariant&v);
    Message &setVariables(const QVariant&v);

    /**
     * @brief read
     * @param v
     * @return
     */
    Message&read(const QVariant&v);

    /**
     * @brief isValid
     * @return
     */
    virtual bool isValid() const;

    /**
     * @brief isNull
     * @return
     */
    virtual bool isNull() const;

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
     * @brief toString
     * @return
     */
    QString toString() const;

    /**
     * @brief name
     * @return
     */
    QString name() const;
    Message&name(const QVariant &value);
    Message&setName(const QVariant &value);

    /**
     * @brief attachmentName
     * @return
     */
    QString attachmentName() const;
    Message&attachmentName(const QVariant &value);
    Message&setAttachmentName(const QVariant &value);

    /**
     * @brief type
     * @return
     */
    QString type() const;
    Message&type(const QVariant &value);
    Message&setType(const QVariant &value);

    /**
     * @brief uuid
     * @return
     */
    QUuid uuid() const;
    Message&uuid(const QVariant &value);
    Message&setUuid(const QVariant &value);

    /**
     * @brief from
     * @return
     *
     * remente
     */
    QString from() const;
    Message&from(const QVariant &value);
    Message&setFrom(const QVariant &value);

    /**
     * @brief to
     * @return
     *
     * destinatario da mensagem
     */
    QString to() const;
    Message &to(const QVariant &value) const;
    Message &setTo(const QVariant &value);

    /**
     * @brief subject
     * @return
     *
     * assunto da mensagem
     */
    QString subject() const;
    Message&subject(const QVariant &value);
    Message&setSubject(const QVariant &value);

    /**
     * @brief bodyText
     * @return
     *
     * corpo do mensagem se texto
     */
    QString bodyText() const;
    Message&bodyText(const QVariant &value);
    Message&setBodyText(const QVariant &value);

    /**
     * @brief bodyHtml
     * @return
     *
     * corpo da mensagem se html
     */
    QByteArray bodyHtml() const;
    Message&bodyHtml(const QVariant &value);
    Message&setBodyHtml(const QVariant &value);

    /**
     * @brief attachment
     * @return
     *
     * anexos para envio, sendo possivel enviar url e body,
     * objetivo é que a url seja baixada e anexadas no despachante
     */
    QVariantList attachment() const;
    Message &attachment(const QStm::Url &value);
    Message &addAttachment(const QStm::Url &value);
    Message &setAttachment(const QStm::Url &value);
    Message &setAttachment(const QVariantList &value);

private:
    void*p = nullptr;
};
}

typedef QStm::Message Message;
Q_DECLARE_METATYPE(Message)
Q_DECLARE_METATYPE(Message*)
