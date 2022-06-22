#include "./qstm_util_path.h"
#include "./qstm_util_variant.h"
#include <QCryptographicHash>
#include <QDir>

namespace QStm {

class PathUtilPvt:public QObject{
public:
    QString v;
    PathUtil*parent=nullptr;
    explicit PathUtilPvt(PathUtil*v):QObject(nullptr)
    {
        this->parent=v;
    }
    virtual ~PathUtilPvt()
    {
    }

    void clear()
    {
        this->v.clear();
    }

    QString format(const QString &v)const
    {
        auto s=v;
        s=q_dir_separator+s.replace(qsl("\\"),q_dir_separator);
        s=s.replace(s,qsl_null);
        return s;
    }
};

PathUtil::PathUtil(const QVariant &v)
{
    this->p = new PathUtilPvt{this};

    p->v=v.toString();
}

PathUtil::~PathUtil()
{
    delete p;
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

    return this->setPath(p->v.replace(v.toString(),qsl_null));
}

PathUtil &PathUtil::operator<<(const QVariant &v)
{

    this->setPath(p->v+q_dir_separator+v.toString());
    return*this;
}

bool PathUtil::exists(const QVariant &v) const
{

    if(v.isValid())
        return QDir(v.toString()).exists();
    return QDir(p->v).exists();
}

bool PathUtil::isValid(const QVariant &v) const
{

    if(v.isValid())
        return v.toString().trimmed().isEmpty();
    return p->v.isEmpty();
}

PathUtil &PathUtil::clear()
{

    p->clear();
    return*this;
}

PathUtil &PathUtil::setPath(const QVariant &v)
{

    p->v=p->format(v.toString());
    return*this;
}

PathUtil &PathUtil::append(const QVariant &v)
{

    p->v+=q_dir_separator+v.toString();
    return this->setPath(v);
}

PathUtil &PathUtil::remove(const QVariant &v)
{

    auto s=v.toString().replace(qsl("\\"),q_dir_separator);
    s=p->v.replace(s,qsl_null);
    return this->setPath(s);
}

bool PathUtil::mkPath(const QVariant &v)
{

    if(v.isValid())
        return QDir().mkpath(v.toString());
    return QDir(p->v).mkpath(p->v);
}

QString PathUtil::toLower() const
{

    return p->v.toLower();
}

QString PathUtil::toString() const
{

    return p->v;
}

QByteArray PathUtil::toByteArray() const
{

    return p->v.toUtf8();
}

QVariantList PathUtil::toList() const
{
    return QVariant(this->toStringList()).toList();
}

QStringList PathUtil::toStringList() const
{

    return p->v.split(q_dir_separator);
}

QByteArray PathUtil::toMd5() const
{

    Q_DECLARE_VU;
    return vu.toMd5(p->v);
}

QUuid PathUtil::toUuid() const
{

    Q_DECLARE_VU;
    return vu.toMd5Uuid(p->v);
}

QString PathUtil::arg(const QVariant &v)
{

    auto s=p->format(p->v+q_dir_separator+v.toString());
    return s;
}

}
