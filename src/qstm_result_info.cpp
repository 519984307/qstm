#include "./qstm_result_info.h"
#include <QMetaProperty>
#include <QJsonDocument>

namespace QStm {

#define dPvt()\
    auto&p = *reinterpret_cast<ResultInfoPvt*>(this->p)\

class ResultInfoPvt{
public :
    ResultInfo *parent=nullptr;
    bool enabled=false;
    QVariantList errors;
    QVariantList messages;
    bool success=true;
    int page=0;
    int per_page=9999999;
    int count=0;
    int total_count=0;
    int total_pages=0;

    explicit ResultInfoPvt(ResultInfo *parent){
        this->parent=parent;
    }
    virtual ~ResultInfoPvt(){
    }

    void clear(){
        success=false;
        page=0;
        per_page=9999999;
        count=0;
        total_count=0;
        total_pages=0;
        this->messages.clear();
        this->clearErrors();
    }

    void clearErrors(){
        this->errors.clear();
        this->success=true;
    }
};

ResultInfo::ResultInfo(QObject *parent):QObject(parent)
{
    this->p=new ResultInfoPvt(this);
}

ResultInfo::~ResultInfo()
{
    dPvt();
    delete&p;
}

void ResultInfo::clear()
{
    dPvt();
    p.clear();
}

void ResultInfo::clearErrors()
{
    dPvt();
    p.clearErrors();
}

bool ResultInfo::enabled()
{
    dPvt();
    return p.enabled;
}

void ResultInfo::setEnabled(bool value)
{
    dPvt();
    p.enabled=value;
}

QVariantList &ResultInfo::errors()
{
    dPvt();
    return p.errors;
}

void ResultInfo::setErrors(const QVariantList &value)
{
    dPvt();
    p.errors=value;
}

QVariantList &ResultInfo::messages()
{
    dPvt();
    return p.messages;
}

void ResultInfo::setMessages(const QVariantList &value)
{
    dPvt();
    p.messages=value;
}

int ResultInfo::success() const
{
    dPvt();
    return p.success;
}

void ResultInfo::setSuccess(bool value)
{
    dPvt();
    p.success=value;
}

int ResultInfo::page() const
{
    dPvt();
    return p.page;
}

void ResultInfo::setPage(int value)
{
    dPvt();
    p.page = value;
}

int ResultInfo::per_page() const
{
    dPvt();
    return p.per_page;
}

void ResultInfo::setPer_page(int value)
{
    dPvt();
    p.per_page = value;
}

int ResultInfo::count() const
{
    dPvt();
    return p.count;
}

void ResultInfo::setCount(int value)
{
    dPvt();
    p.count = value;
}

int ResultInfo::total_count() const
{
    dPvt();
    return p.total_count;
}

void ResultInfo::setTotal_count(int value)
{
    dPvt();
    p.total_count = value;
}

int ResultInfo::total_pages() const
{
    dPvt();
    return p.total_pages;
}

void ResultInfo::setTotal_pages(int value)
{
    dPvt();
    p.total_pages = value;
}

const QVariantHash ResultInfo::toRequestHash() const
{
    QVariantHash v;
    v[QT_STRINGIFY2(page)]=this->page();
    v[QT_STRINGIFY2(per_page)]=this->per_page();
    return v;
}

QVariantMap ResultInfo::toMap()const
{
    QVariantMap __return;
    auto&metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        __return.insert(property.name(), property.read(this));
    }
    return __return;
}

QVariantHash ResultInfo::toHash() const
{
    QVariantHash __return;
    auto&metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        __return.insert(property.name(), property.read(this));
    }
    return __return;
}

QVariant ResultInfo::toVar()const
{
    return this->toHash();
}



bool ResultInfo::fromVar(const QVariant &v)
{
    QVariantHash vHash;
    if(qTypeId(v)==QMetaType_QString || qTypeId(v)==QMetaType_QByteArray || qTypeId(v)==QMetaType_QChar || qTypeId(v)==QMetaType_QBitArray)
        vHash=QJsonDocument::fromJson(v.toByteArray()).toVariant().toHash();
    else if(qTypeId(v)==v.Hash || qTypeId(v)==v.Map)
        vHash=v.toHash();
    return this->fromHash(vHash);
}

bool ResultInfo::fromMap(const QVariantMap&map)
{
    bool __return=false;
    auto&metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        if(property.write(this, map.value(property.name()))){
            __return=true;
        }
    }
    return __return;
}

bool ResultInfo::fromHash(const QVariantHash &map)
{
    bool __return=false;
    auto&metaObject = *this->metaObject();
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        if(property.write(this, map.value(property.name()))){
            __return=true;
        }
    }
    return __return;
}

}
