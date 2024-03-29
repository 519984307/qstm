#include "./qstm_message.h"
#include "./qstm_util_variant.h"
#include <QJsonDocument>
#include <QJsonObject>

namespace QStm {

class MessagePvt{
public:
    static QByteArray base(){
        auto v=QUuid::createUuid().toString() + QDateTime::currentDateTime().toString();
        return v.toUtf8();
    }
public:
    Message*parent=nullptr;
    QVariant body;
public:
    QVariantHash variables;
    QUuid uuid;
    QString name;
    QString attachmentName;
    QString type;
    QString from;
    QString to;
    QString subject;
    QString bodyText;
    QString bodyHtml;
    QVariantList attachment;
    explicit MessagePvt(Message*parent)
    {
        this->parent=parent;
    }

    virtual ~MessagePvt()
    {
    }

    static QVariant staticReplaceVar(const QVariantHash&static_variables, const QVariant &v)
    {
        Q_DECLARE_VU;
        QString value;
        auto typeId=qTypeId(v);
        switch (typeId) {
        case QMetaType_QVariantList:
            value=QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
            break;
        case QMetaType_QStringList:
            value=QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
            break;
        case QMetaType_QVariantHash:
            value=QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
            break;
        case QMetaType_QVariantMap:
            value=QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
            break;
        case QMetaType_QUuid:
            value=v.toUuid().toString();
            break;
        case QMetaType_QUrl:
            value=v.toUrl().toString();
            break;
        default:
            value=v.toByteArray();
            break;
        }


        if(!value.contains(qsl("$")))
            return v;

        QHashIterator<QString, QVariant> i(static_variables);
        while (i.hasNext()) {
            i.next();
            auto key=i.key();
            key=key.replace(qsl("$"),qsl_null).replace(qsl("{"),qsl_null).replace(qsl("]"),qsl_null);
            const auto k1=QString(qsl("$")+key).replace(qsl("$$"),qsl("$"));
            const auto k2=qsl("${%1}").arg(key);

            auto v0=i.value();
            QString vv;
            if(vu.vIsList(i.value()))
                vv=v0.toStringList().join(qsl_key_return);
            else
                vv=v0.toString().trimmed();
            value=value.replace(k1,vv).replace(k2,vv);
        }

        switch (typeId) {
        case QMetaType_QVariantList:
        case QMetaType_QStringList:
        case QMetaType_QVariantHash:
        case QMetaType_QVariantMap:
            return QJsonDocument::fromJson(value.toUtf8()).toVariant();
        default:
            return value;
        }
    }


    QVariant parserVariable(const QVariant &v)
    {
        auto __return=staticReplaceVar(this->variables, v).toString();
        return __return;
    }

    QString parserText(const QVariant &v)
    {
        Q_DECLARE_VU;
        return vu.toStr(v);
    }

    QString parserTextHtml(const QVariant &v)
    {
        Q_DECLARE_VU;
        return vu.toStr(v);
    }

    QString parserTextLine(const QVariant &v)
    {
        Q_DECLARE_VU;
        QVariantList vl;
        if(vu.vIsObject(v))
            vl=v.toList();
        else if(vu.vIsString(v))
            vl=QVariant(v.toString().split(qsl("\n"))).toList();
        else
            vl<<v.toString();

        QStringList vsl;
        for(auto &v:vl)
            vsl<<vu.toStr(v);
        auto s=vsl.join(qsl_key_return);
        return s;
    }


    Message&setMap()
    {
        if(this->uuid.isNull())
            this->uuid=QUuid::createUuidV3(QUuid::createUuid(), base());
        QVariantHash vBody;
        vBody[qsl_fy(uuid)              ]=this->uuid            ;
        vBody[qsl_fy(name)              ]=this->name            ;
        vBody[qsl_fy(attachmentName)    ]=this->attachmentName  ;
        vBody[qsl_fy(type)              ]=this->type            ;
        vBody[qsl_fy(from)              ]=this->from            ;
        vBody[qsl_fy(to)                ]=this->to              ;
        vBody[qsl_fy(subject)           ]=this->subject         ;
        vBody[qsl_fy(bodyText)          ]=this->bodyText        ;
        vBody[qsl_fy(bodyHtml)          ]=this->bodyHtml        ;
        vBody[qsl_fy(attachment)        ]=this->attachment      ;
        this->body=vBody;
        this->parent->setValue(vBody);
        return*this->parent;
    }

    QString getStr(const QStringList &keys, const QVariantHash&vBody)
    {
        for(auto &v:keys){
            auto s=vBody.value(v).toString().trimmed();
            if(s.isEmpty())
                continue;
            return s;
        }
        return {};
    }



    Message&setVar(const QVariant &v)
    {
        Q_DECLARE_VU;
        QVariantHash vBody=v.toHash();

        static auto keys=qvsl{qsl_fy(attachmentName),qsl_fy(attachmentname),qsl_fy(outPutName),qsl_fy(outputname),qsl_fy(outPutFileName),qsl_fy(outputfilename)};

        this->uuid=vu.toUuid(vBody[qsl_fy(uuid)]);
        this->name=vBody[qsl_fy(name)].toString();
        this->attachmentName=getStr(keys, vBody);
        this->type=parserText(vBody[qsl_fy(type)]);
        this->from=parserText(vBody[qsl_fy(from)]);
        this->to=parserText(vBody[qsl_fy(to)]);
        this->subject=parserText(vBody[qsl_fy(subject)]);
        this->bodyText=parserTextLine(vBody[qsl_fy(bodyText)]);
        this->bodyHtml=parserTextHtml(vBody[qsl_fy(bodyHtml)]);
        this->attachment=vBody[qsl_fy(attachment)].toList();

        if(!this->variables.isEmpty()){
            this->attachmentName=this->parserVariable(this->attachmentName).toString();
            this->name=this->parserVariable(this->name).toString();
            this->type=this->parserVariable(this->type).toString();
            this->from=this->parserVariable(this->from).toString();
            this->to=this->parserVariable(this->to).toString();
            this->subject=this->parserVariable(this->subject).toString();
            this->bodyText=this->parserVariable(this->bodyText).toString();
            this->bodyHtml=this->parserVariable(this->bodyHtml).toString();
        }

        return this->setMap();
    }

};

Message::Message(const QVariant &v, const QString &settingName):QVariant{}
{
    this->p = new MessagePvt{this};


    QVariant vv;
    QVariantHash vHash=v.toHash();
    if(!settingName.trimmed().isEmpty()){
        p->variables=vHash.value(qsl("variables")).toHash();
        vv=vHash.value(settingName).toHash();
    }
    else{
        vv=vHash;
    }
    p->setVar(vv);
}

Message::Message(const ResultValue &v):QVariant{}
{
    this->p = new MessagePvt{this};
    p->setVar(v.resultHash());
}

Message::~Message()
{
    delete p;
}

Message &Message::operator=(const QVariant &v)
{

    p->setVar(v);
    return*this;
}

Message &Message::operator<<(const QStm::Url &v)
{
    return this->addAttachment(v);
}

Message Message::make(const QVariant &v)
{
    Message Message(v);
    return Message;
}

QVariantHash Message::variables()const
{

    return p->variables;
}

Message &Message::variables(const QVariant &v)
{
    return this->setVariables(v);
}

Message &Message::setVariables(const QVariant &v)
{

    p->variables=v.toHash();
    p->setVar(p->body);
    return*this;
}

Message &Message::read(const QVariant &v)
{

    p->setVar(v);
    return*this;
}

bool Message::isValid() const
{

    return p->body.isValid();
}

bool Message::isNull() const
{

    return p->body.isNull();
}

QVariantMap Message::toMap() const
{

    return p->body.toMap();
}

QVariantHash Message::toHash() const
{

    return p->body.toHash();
}

QString Message::toString() const
{

    Q_DECLARE_VU;
    return vu.toStr(p->body);
}

QString Message::name() const
{

    return p->parserVariable(p->name).toString();
}

Message &Message::name(const QVariant &value)
{

    p->name=value.toString();
    return*this;
}

Message &Message::setName(const QVariant &value)
{

    p->name=value.toString();
    return*this;
}

QString Message::attachmentName() const
{

    return p->attachmentName;
}

Message &Message::attachmentName(const QVariant &value)
{

    p->attachmentName=value.toString();
    return*this;
}

Message &Message::setAttachmentName(const QVariant &value)
{

    p->attachmentName=value.toString();
    return*this;
}

QString Message::typeId() const
{

    return p->parserVariable(p->type).toString();
}

Message &Message::typeId(const QVariant &value)
{

    p->type = value.toString();
    return p->setMap();
}

Message &Message::setType(const QVariant &value)
{

    p->type = value.toString();
    return p->setMap();
}

QUuid Message::uuid() const
{

    return p->uuid;
}

Message &Message::uuid(const QVariant &value)
{

    Q_DECLARE_VU;
    p->uuid = vu.toUuid(value);
    return p->setMap();
}

Message &Message::setUuid(const QVariant &value)
{

    Q_DECLARE_VU;
    p->uuid = vu.toUuid(value);
    return p->setMap();
}

QString Message::from() const
{

    return p->parserVariable(p->from).toString();
}

Message &Message::from(const QVariant &value)
{

    p->from = value.toString();
    return p->setMap();
}

Message &Message::setFrom(const QVariant &value)
{

    p->from = value.toString();
    return p->setMap();
}

QString Message::to() const
{

    return p->parserVariable(p->to).toString();
}

Message&Message::to(const QVariant &value) const
{

    p->to = value.toString();
    return p->setMap();
}

Message&Message::setTo(const QVariant &value)
{

    p->to = value.toString();
    return p->setMap();
}

QString Message::subject() const
{

    return p->parserVariable(p->subject).toString();
}

Message &Message::subject(const QVariant &value)
{

    p->subject = value.toString();
    return p->setMap();
}

Message &Message::setSubject(const QVariant &value)
{

    p->subject = value.toString();
    return p->setMap();
}

QString Message::bodyText() const
{

    return p->parserVariable(p->bodyText).toString();
}

Message &Message::bodyText(const QVariant &value)
{

    p->bodyText = p->parserTextLine(value);
    return p->setMap();
}

Message &Message::setBodyText(const QVariant &value)
{

    p->bodyText = p->parserTextLine(value);
    return p->setMap();
}

QByteArray Message::bodyHtml() const
{

    return p->parserVariable(p->bodyHtml).toByteArray();
}

Message &Message::bodyHtml(const QVariant &value)
{

    p->bodyHtml = p->parserTextHtml(value);
    return p->setMap();
}

Message &Message::setBodyHtml(const QVariant &value)
{

    p->bodyHtml = p->parserTextHtml(value);
    return p->setMap();
}

QVariantList Message::attachment()const
{

    return p->attachment;
}

Message &Message::attachment(const QStm::Url &value)
{

    p->attachment.clear();
    p->attachment.append(value);
    return p->setMap();
}

Message&Message::setAttachment(const QStm::Url &value)
{

    p->attachment.clear();
    p->attachment.append(value);
    return p->setMap();
}

Message&Message::setAttachment(const QVariantList &value)
{

    p->attachment = value;
    return p->setMap();
}

Message &Message::addAttachment(const QStm::Url &value)
{

    p->attachment.append(value);
    return p->setMap();
}

}
