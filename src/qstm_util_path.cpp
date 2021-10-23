#include "./qstm_util_path.h"
#include "./qstm_util_variant.h"
#include <QCryptographicHash>
#include <QDir>

namespace QStm {

#define dPvt()\
    auto&p = *reinterpret_cast<PathUtilPvt*>(this->p)

class PathUtilPvt:public QObject{
public:
    QString v;
    PathUtil*parent=nullptr;
    explicit PathUtilPvt(PathUtil*v):QObject(nullptr){
        this->parent=v;
    }
    virtual ~PathUtilPvt(){
    }

    void clear(){
        this->v.clear();
    }

    QString format(const QString&v)const{
        auto s=v;
        s=q_dir_separator+s.replace(qsl("\\"),q_dir_separator);
        s=s.replace(s,qsl_null);
        return s;
    }
};

PathUtil::PathUtil(const QVariant &v)
{
    this->p = new PathUtilPvt(this);
    dPvt();
    p.v=v.toString();
}

PathUtil::~PathUtil()
{
    dPvt();
    this->p=nullptr;
    delete&p;
}

PathUtil&PathUtil::operator=(const QVariant &v)
{
    this->setPath(v);
    return*this;
}

PathUtil &PathUtil::operator+=(const QVariant &v)
{
    return this->append(v);
}

PathUtil &PathUtil::operator-=(const QVariant &v)
{
    dPvt();
    return this->setPath(p.v.replace(v.toString(),qsl_null));
}

PathUtil &PathUtil::operator<<(const QVariant &v)
{
    dPvt();
    this->setPath(p.v+q_dir_separator+v.toString());
    return*this;
}

bool PathUtil::exists(const QVariant&v) const
{
    dPvt();
    if(v.isValid())
        return QDir(v.toString()).exists();
    else
        return QDir(p.v).exists();
}

bool PathUtil::isValid(const QVariant &v) const
{
    dPvt();
    if(v.isValid())
        return v.toString().trimmed().isEmpty();
    else
        return p.v.isEmpty();
}

PathUtil &PathUtil::clear()
{
    dPvt();
    p.clear();
    return*this;
}

PathUtil &PathUtil::setPath(const QVariant &v)
{
    dPvt();
    p.v=p.format(v.toString());
    return*this;
}

PathUtil &PathUtil::append(const QVariant &v)
{
    dPvt();
    p.v+=q_dir_separator+v.toString();
    return this->setPath(v);
}

PathUtil &PathUtil::remove(const QVariant &v)
{
    dPvt();
    auto s=v.toString().replace(qsl("\\"),q_dir_separator);
    s=p.v.replace(s,qsl_null);
    return this->setPath(s);
}

bool PathUtil::mkPath(const QVariant &v)
{
    dPvt();
    if(v.isValid())
        return QDir().mkpath(v.toString());
    else
        return QDir(p.v).mkpath(p.v);
}

QString PathUtil::toLower() const
{
    dPvt();
    return p.v.toLower();
}

QString PathUtil::toString() const
{
    dPvt();
    return p.v;
}

QByteArray PathUtil::toByteArray() const
{
    dPvt();
    return p.v.toUtf8();
}

QVariantList PathUtil::toList() const
{
    return QVariant(this->toStringList()).toList();
}

QStringList PathUtil::toStringList() const
{
    dPvt();
    return p.v.split(q_dir_separator);
}

QByteArray PathUtil::toMd5() const
{
    dPvt();
    VariantUtil vu;
    return vu.toMd5(p.v);
}

QUuid PathUtil::toUuid() const
{
    dPvt();
    VariantUtil vu;
    return vu.toMd5Uuid(p.v);
}

QString PathUtil::arg(const QVariant &v)
{
    dPvt();
    auto s=p.format(p.v+q_dir_separator+v.toString());
    return s;
}

}
