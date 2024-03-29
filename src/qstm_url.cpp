#include "./qstm_url.h"
#include "./qstm_util_variant.h"
#include <QFile>

namespace QStm {

class UrlPvt{
public:
    Url*parent=nullptr;
    Q_DECLARE_VU;
    QString name;
    QString outPutName;
    QVariant body;
    QVariantHash headers;
    QUrl url;
    explicit UrlPvt(Url*parent)
    {
        this->parent=parent;
    }

    virtual ~UrlPvt()
    {
    }

    Url&setData(){
        this->body.clear();
        QVariantHash vBody;
        if(!this->name.isEmpty())
            vBody[qsl("name")]=this->name;
        if(!this->outPutName.isEmpty())
            vBody[qsl("outPutName")]=this->name;
        if(this->url.isValid() && !this->url.isEmpty()){
            vBody[qsl_fy(url)]=this->url;
            if(!this->headers.isEmpty())
                vBody[qsl_fy(headers)]=this->headers;
        }
        this->body=vBody;
        this->parent->setValue(vBody);
        return*this->parent;
    }

    void setVar(const QVariant &v){
        if(!v.isValid() || v.isNull()){
            this->url.clear();
            this->headers.clear();
            this->setData();
            return;
        }
        if(qTypeId(v)==QMetaType_QUrl){
            this->url=v.toUrl();
            this->setData();
            return;
        }

        auto vMap=this->vu.toHash(v);
        this->name=vMap[qsl("name")].toString().trimmed();
        this->outPutName=vMap[qsl("outPutName")].toString().trimmed();
        if(this->outPutName.isEmpty())
            this->outPutName=vMap[qsl("outputname")].toString().trimmed();
        if(vMap.contains(qsl_fy(url))){
            this->url=this->vu.toUrl(vMap[qsl_fy(url)]);
            if(vMap.contains(qsl_fy(headers)))
                this->headers=this->vu.toHash(vMap[qsl_fy(headers)]);
        }
        else if(v.toString().toLower().startsWith(qsl("http")))
            this->url=this->vu.toUrl(v);
        else if(v.toString().toLower().startsWith(qsl("http")))
            this->url=this->vu.toUrl(v);
        this->setData();
    }

};

Url::Url(const QVariant &v):QVariant{}
{
    this->p = new UrlPvt{this};
    p->setVar(v);
}

Url::Url(const ResultValue &v):QVariant{}
{
    this->p = new UrlPvt{this};
    p->setVar(v.resultHash());
}

Url::~Url()
{
    delete p;
}

Url &Url::operator=(const QVariant &v)
{

    p->setVar(v);
    return*this;
}

Url Url::from(const QVariant &v)
{
    Url url(v);
    return url;
}

Url &Url::read(const QVariant &v)
{

    p->setVar(v);
    return*this;
}

QVariantHash &Url::headers() const
{

    return p->headers;
}

Url &Url::header(const QVariant &value)
{

    p->headers=p->vu.toHash(value);
    return p->setData();
}

Url &Url::setHeader(const QVariant &value)
{

    p->headers=p->vu.toHash(value);
    return p->setData();
}

QString &Url::name() const
{

    return p->name;
}

Url &Url::name(const QVariant &value)
{

    p->name=value.toString();
    return p->setData();
}

Url &Url::setName(const QVariant &value)
{

    p->name=value.toString();
    return p->setData();
}

QString &Url::outPutName() const
{

    return p->outPutName;
}

Url &Url::outPutName(const QVariant &value)
{

    p->outPutName=value.toString();
    return p->setData();
}

Url &Url::setOutPutName(const QVariant &value)
{

    p->outPutName=value.toString();
    return p->setData();
}

QUrl &Url::url() const
{

    return p->url;
}

Url &Url::url(const QVariant &value)
{

    p->url=p->vu.toUrl(value);
    return p->setData();
}

Url&Url::setUrl(const QVariant &value)
{

    p->url=p->vu.toUrl(value);
    return p->setData();
}

bool Url::isValid() const
{

    return p->url.isValid();
}

bool Url::isNull() const
{

    return p->url.isEmpty();
}

bool Url::isLocalFile() const
{

    return p->url.isLocalFile();
}

QString Url::toLocalFile() const
{

    return p->url.toLocalFile();
}

Url Url::fromLocalFile(const QString &localfile)
{
    return Url::from(QUrl::fromLocalFile(localfile));
}

QVariantMap Url::toMap() const
{

    return p->body.toMap();
}

QVariantHash Url::toHash() const
{

    return p->body.toHash();
}

QByteArray Url::readBody() const
{
    if(!this->isLocalFile())
        return {};
    QByteArray __return;
    QFile file(this->url().toLocalFile());
    if(!file.open(file.ReadOnly))
        return {};
    __return=file.readAll();
    file.close();
    return __return;
}

QString Url::toString() const
{

    return p->url.toString();
}

}
