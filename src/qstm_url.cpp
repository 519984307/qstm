#include "./qstm_url.h"
#include "./qstm_util_variant.h"

namespace QStm {

#define dPvt()\
    auto&p =*reinterpret_cast<UrlPvt*>(this->p)

class UrlPvt{
public:
    Url*parent=nullptr;
    VariantUtil vu;
    QString name;
    QString outPutName;
    QVariant body;
    QVariantHash headers;
    QUrl url;
    explicit UrlPvt(Url*parent){
        this->parent=parent;
    }

    virtual ~UrlPvt(){
    }

    Url&setMap(){
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
        }
        else if(v.type()==v.Url)
            this->url=v.toUrl();
        else{
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
        }
        this->setMap();
    }

};

Url::Url(const QVariant &v):QVariant()
{
    this->p = new UrlPvt(this);
    dPvt();
    p.setVar(v);
}

Url::Url(const ResultValue &v):QVariant()
{
    this->p = new UrlPvt(this);
    dPvt();
    p.setVar(v.resultHash());
}

Url::~Url()
{
    dPvt();delete&p;
}

Url &Url::operator=(const QVariant &v)
{
    dPvt();
    p.setVar(v);
    return*this;
}

Url Url::from(const QVariant &v)
{
    Url url(v);
    return url;
}

Url &Url::read(const QVariant &v)
{
    dPvt();
    p.setVar(v);
    return*this;
}

QVariantHash &Url::headers() const
{
    dPvt();
    return p.headers;
}

Url &Url::header(const QVariant &value)
{
    dPvt();
    p.headers=p.vu.toHash(value);
    return p.setMap();
}

Url &Url::setHeader(const QVariant &value)
{
    dPvt();
    p.headers=p.vu.toHash(value);
    return p.setMap();
}

QString &Url::name() const
{
    dPvt();
    return p.name;
}

Url &Url::name(const QVariant &value)
{
    dPvt();
    p.name=value.toString();
    return p.setMap();
}

Url &Url::setName(const QVariant &value)
{
    dPvt();
    p.name=value.toString();
    return p.setMap();
}

QString &Url::outPutName() const
{
    dPvt();
    return p.outPutName;
}

Url &Url::outPutName(const QVariant &value)
{
    dPvt();
    p.outPutName=value.toString();
    return p.setMap();
}

Url &Url::setOutPutName(const QVariant &value)
{
    dPvt();
    p.outPutName=value.toString();
    return p.setMap();
}

QUrl &Url::url() const
{
    dPvt();
    return p.url;
}

Url &Url::url(const QVariant &value)
{
    dPvt();
    p.url=p.vu.toUrl(value);
    return p.setMap();
}

Url&Url::setUrl(const QVariant &value)
{
    dPvt();
    p.url=p.vu.toUrl(value);
    return p.setMap();
}

bool Url::isValid() const
{
    dPvt();
    return p.url.isValid();
}

bool Url::isNull() const
{
    dPvt();
    return p.url.isEmpty();
}

bool Url::isLocalFile() const
{
    dPvt();
    return p.url.isLocalFile();
}

QString Url::toLocalFile() const
{
    dPvt();
    return p.url.toLocalFile();
}

Url Url::fromLocalFile(const QString &localfile)
{
    return Url::from(QUrl::fromLocalFile(localfile));
}

QVariantMap Url::toMap() const
{
    dPvt();
    return p.body.toMap();
}

QVariantHash Url::toHash() const
{
    dPvt();
    return p.body.toHash();
}

QByteArray Url::readBody() const
{
    QByteArray __return;
    if(this->isLocalFile()){
        QFile file(this->url().toLocalFile());
        if(file.open(file.ReadOnly)){
            __return=file.readAll();
            file.close();
        }
    }
    return __return;
}

QString Url::toString() const
{
    dPvt();
    return p.url.toString();
}

}
