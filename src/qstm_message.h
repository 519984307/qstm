#pragma once

#include "./qstm_global.h"
#include "./qstm_result.h"
#include "./qstm_url.h"
#include <QVariantHash>

namespace QStm {

//!
//! \brief The Message class
//!
class Q_STM_EXPORT Message: public QVariant
{
public:

    //!
    //! \brief Message
    //! \param v
    //! \param settingName
    //!
    explicit Message(const QVariant&v=QVariantHash(), const QString&settingName=QString());
    explicit Message(const ResultValue &v);
    virtual ~Message();

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //! operator to assigned values
    Message&operator=(const QVariant&v);

    //!
    //! \brief operator <<
    //! \param v
    //! \return
    //!operator to assigned values
    Message&operator<<(const QStm::Url &v);

    //!
    //! \brief make
    //! \param v
    //! \return
    //! make message with value
    static Message make(const QVariant&v);

    //!
    //! \brief variables
    //! \return
    //! read variables
    QVariantHash variables() const;

    //!
    //! \brief variables
    //! \param v
    //! \return
    //! write variabled
    Message &variables(const QVariant&v);

    //!
    //! \brief setVariables
    //! \param v
    //! \return
    //!
    Message &setVariables(const QVariant&v);

    //!
    //! \brief read
    //! \param v
    //! \return
    //! assign values
    Message&read(const QVariant&v);

    //!
    //! \brief isValid
    //! \return
    //!valid message
    virtual bool isValid() const;

    //!
    //! \brief isNull
    //! \return
    //! check values
    virtual bool isNull() const;

    //!
    //! \brief toMap
    //! \return
    //! convert to map
    virtual QVariantMap toMap() const;

    //!
    //! \brief toHash
    //! \return
    //! convert do hash
    virtual QVariantHash toHash() const;

    //!
    //! \brief toString
    //! \return
    //!convert to string
    QString toString() const;

    //!
    //! \brief name
    //! \return
    //! name
    QString name() const;

    //!
    //! \brief name
    //! \param value
    //! \return
    //!
    Message&name(const QVariant &value);

    //!
    //! \brief setName
    //! \param value
    //! \return
    //!
    Message&setName(const QVariant &value);

    //!
    //! \brief attachmentName
    //! \return
    //! attachment of message
    QString attachmentName() const;

    //!
    //! \brief attachmentName
    //! \param value
    //! \return
    //!
    Message&attachmentName(const QVariant &value);

    //!
    //! \brief setAttachmentName
    //! \param value
    //! \return
    //!
    Message&setAttachmentName(const QVariant &value);

    //!
    //! \brief type
    //! \return
    //! type of message
    QString typeId() const;

    //!
    //! \brief typeId
    //! \param value
    //! \return
    //!
    Message&typeId(const QVariant &value);

    //!
    //! \brief setType
    //! \param value
    //! \return
    //!
    Message&setType(const QVariant &value);

    //!
    //! \brief uuid
    //! \return
    //! identification of message
    QUuid uuid() const;

    //!
    //! \brief uuid
    //! \param value
    //! \return
    //!
    Message&uuid(const QVariant &value);

    //!
    //! \brief setUuid
    //! \param value
    //! \return
    //!
    Message&setUuid(const QVariant &value);

    //!
    //! \brief from
    //! \return
    //!read sender from to message
    QString from() const;

    //!
    //! \brief from
    //! \param value
    //! \return
    //!
    Message&from(const QVariant &value);

    //!
    //! \brief setFrom
    //! \param value
    //! \return
    //!
    Message&setFrom(const QVariant &value);

    //!
    //! \brief to
    //! \return
    //!read value destinatary to message
    QString to() const;

    //!
    //! \brief to
    //! \param value
    //! \return
    //!
    Message &to(const QVariant &value) const;

    //!
    //! \brief setTo
    //! \param value
    //! \return
    //!
    Message &setTo(const QVariant &value);

    //!
    //! \brief subject
    //! \return
    //!read value subject to message
    QString subject() const;

    //!
    //! \brief subject
    //! \param value
    //! \return
    //!
    Message&subject(const QVariant &value);

    //!
    //! \brief setSubject
    //! \param value
    //! \return
    //!
    Message&setSubject(const QVariant &value);

    //!
    //! \brief bodyText
    //! \return
    //!read value body to message
    QString bodyText() const;

    //!
    //! \brief bodyText
    //! \param value
    //! \return
    //!
    Message&bodyText(const QVariant &value);

    //!
    //! \brief setBodyText
    //! \param value
    //! \return
    //!
    Message&setBodyText(const QVariant &value);

    //!
    //! \brief bodyHtml
    //! \return
    //!read value html body to message
    QByteArray bodyHtml() const;

    //!
    //! \brief bodyHtml
    //! \param value
    //! \return
    //!
    Message&bodyHtml(const QVariant &value);

    //!
    //! \brief setBodyHtml
    //! \param value
    //! \return
    //!
    Message&setBodyHtml(const QVariant &value);

    //!
    //! \brief attachment
    //! \return
    //! attachments for sending, being possible to send url and body, the objective is that the url is downloaded and attached to the dispatcher
    QVariantList attachment() const;

    //!
    //! \brief attachment
    //! \param value
    //! \return
    //!attachments for sending, being possible to send url and body, the objective is that the url is downloaded and attached to the dispatcher
    Message &attachment(const QStm::Url &value);

    //!
    //! \brief addAttachment
    //! \param value
    //! \return
    //!attachments for sending, being possible to send url and body, the objective is that the url is downloaded and attached to the dispatcher
    Message &addAttachment(const QStm::Url &value);

    //!
    //! \brief setAttachment
    //! \param value
    //! \return
    //!attachments for sending, being possible to send url and body, the objective is that the url is downloaded and attached to the dispatcher
    Message &setAttachment(const QStm::Url &value);

    //!
    //! \brief setAttachment
    //! \param value
    //! \return
    //!attachments for sending, being possible to send url and body, the objective is that the url is downloaded and attached to the dispatcher
    Message &setAttachment(const QVariantList &value);

private:
    void*p = nullptr;
};
}

typedef QStm::Message Message;
Q_DECLARE_METATYPE(Message)
Q_DECLARE_METATYPE(Message*)
