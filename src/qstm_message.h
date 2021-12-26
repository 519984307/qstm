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
    Q_INVOKABLE explicit Message(const QVariant&v=QVariantHash(), const QString&settingName=QString());
    Q_INVOKABLE explicit Message(const ResultValue &v);
    Q_INVOKABLE virtual ~Message();

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
    Message&name(const QVariant &value);
    Message&setName(const QVariant &value);

    //!
    //! \brief attachmentName
    //! \return
    //! attachment of message
    QString attachmentName() const;
    Message&attachmentName(const QVariant &value);
    Message&setAttachmentName(const QVariant &value);

    //!
    //! \brief type
    //! \return
    //! type of message
    QString typeId() const;
    Message&typeId(const QVariant &value);
    Message&setType(const QVariant &value);

    //!
    //! \brief uuid
    //! \return
    //! identification of message
    QUuid uuid() const;
    Message&uuid(const QVariant &value);
    Message&setUuid(const QVariant &value);

    //!
    //! \brief from
    //! \return
    //!read sender from to message
    QString from() const;
    Message&from(const QVariant &value);
    Message&setFrom(const QVariant &value);

    //!
    //! \brief to
    //! \return
    //!read value destinatary to message
    QString to() const;
    Message &to(const QVariant &value) const;
    Message &setTo(const QVariant &value);

    //!
    //! \brief subject
    //! \return
    //!read value subject to message
    QString subject() const;
    Message&subject(const QVariant &value);
    Message&setSubject(const QVariant &value);

    //!
    //! \brief bodyText
    //! \return
    //!read value body to message
    QString bodyText() const;
    Message&bodyText(const QVariant &value);
    Message&setBodyText(const QVariant &value);

    //!
    //! \brief bodyHtml
    //! \return
    //!read value html body to message
    QByteArray bodyHtml() const;
    Message&bodyHtml(const QVariant &value);
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
