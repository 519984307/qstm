#include "./qstm_util_variant.h"
#include "./qstm_util_date.h"
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtCborCommon>
#include <QCborStreamReader>
#include <QCborStreamWriter>
#include <QCborArray>
#include <QCborMap>
#include <QCborValue>
#include <QCborParserError>
#include <QFile>

namespace QStm {

#define dPvt()\
    auto&p = *reinterpret_cast<VariantUtilPvt*>(this->p)


#define set__value(v)\
if(v.isValid()) {p.vvm.clear();this->setValue(v);}

class VariantUtilPvt:public QObject{
public:
    VariantUtil*parent=nullptr;
    QVVM vvm;

    explicit VariantUtilPvt(VariantUtil*v):QObject(nullptr){
        this->parent=v;
    }
    virtual ~VariantUtilPvt(){
    }

    void clear(){
        vvm.clear();
        this->parent->setValue(QVariant());
    }

    QVariantHash toHash(const QVariant &v)const
    {
        QVariantHash map;
        if(v.type()==QVariant::Map || v.type()==QVariant::Hash)
            map=v.toHash();
        else if(v.isNull() || !v.isValid() || v.toString().trimmed().isEmpty())
            map.clear();
        else if(v.type()==QVariant::String || v.type()==QVariant::ByteArray || v.type()==QVariant::Char || v.type()==QVariant::BitArray){
            QJsonParseError*error=nullptr;
            auto doc=QJsonDocument::fromJson(v.toByteArray(),error);
            if(error!=nullptr){
#if Q_STM_LOG
                sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
            }
            else if(!doc.isEmpty() || !doc.isNull()){
                map=doc.object().toVariantHash();
            }
        }
        return map;
    }

    QVariantMap toMap(const QVariant &v)const
    {
        QVariantMap map;
        if(v.type()==QVariant::Map || v.type()==QVariant::Hash)
            map=v.toMap();
        else if(v.isNull() || !v.isValid() || v.toString().trimmed().isEmpty())
            map.clear();
        else if(v.type()==QVariant::String || v.type()==QVariant::ByteArray || v.type()==QVariant::Char || v.type()==QVariant::BitArray){
            QJsonParseError*error=nullptr;
            auto doc=QJsonDocument::fromJson(v.toByteArray(),error);
            if(error!=nullptr){
#if Q_STM_LOG
                sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
            }
            else if(!doc.isEmpty() || !doc.isNull()){
                map=doc.object().toVariantMap();
            }
        }
        return map;
    }

    static QByteArray toMd5(const QVariant &v)
    {
        //if(v.isValid()) vBase->setValue(v);
        auto vType=v.type();
        if(!v.isValid())
            return qbl_null;
        else if(vType==v.Uuid){
            auto uuid=v.toUuid();
            auto suuid=uuid.toByteArray();
            auto md5=suuid.replace(qbl("{"),qbl_null).replace(qbl("}"),qbl_null).replace(qbl("-"), qbl_null);
            if(md5.length()==32)
                return md5;
            else
                return QCryptographicHash::hash(suuid, QCryptographicHash::Md5).toHex();
        }
        else {
            auto bytes=v.toByteArray().trimmed();
            if(bytes.isEmpty())
                return qbl_null;
            //se ja for md5 ou uuid manteremos o uuid como md5 logo ja e um
            else if((vType==v.ByteArray || vType==v.String)){
                auto md5=bytes.replace(qbl("{"),qbl_null).replace(qbl("}"),qbl_null).replace(qbl("-"),qbl_null);
                if(md5.length()==32)
                    return md5;
            }
            return QCryptographicHash::hash(bytes, QCryptographicHash::Md5).toHex();
        }
    }

    static QByteArray toByteArray(const QVariant &v)
    {
        auto vType=v.type();
        if(vType==QVariant::List || vType==QVariant::StringList || vType==QVariant::Map || vType==QVariant::Hash)
            return QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
        else if(vType==QVariant::Uuid)
            return v.toUuid().toByteArray();
        else
            return v.toByteArray();
    }

    static bool canConvertJson(const QVariant &v, QVariant &vOut)
    {
        vOut=QVariant();
        if(v.isNull() || !v.isValid()){
            return false;
        }
        else if(v.type()==QVariant::Map || v.type()==QVariant::Hash || v.type()==QVariant::List || v.type()==QVariant::StringList){
            vOut=v;
            return true;
        }
        else if(!(v.type()==QVariant::String || v.type()==QVariant::ByteArray || v.type()==QVariant::Char || v.type()==QVariant::BitArray)){
            return false;
        }
        else{
            QJsonParseError*error=nullptr;
            auto doc=QJsonDocument::fromJson(v.toByteArray(),error);
            if(error!=nullptr)
                if(doc.isArray() || doc.isObject()){
                    vOut=doc.toVariant();
                    return true;
                }
        }
        return false;
    }

    bool md5ParserUuid(const QString& vtext, QString&outText)const{
        QByteArray suuid;
        auto text=vtext;
        text.replace(qsl("-"),qsl_null).replace(qsl("{"),qsl_null).replace(qsl("}"),qsl_null);
        if(text.length()==32){
            int i=0;
            for(auto&c:text){
                ++i;
                suuid.append(c.toLatin1());
                if(i==8 || i==12 || i==16 || i==20){
                    suuid.append(qbl("-"));
                }
            }
            outText=suuid;
            return true;
        }
        outText=qbl_null;
        return false;
    }

    QUuid md5toUuid(const QString&md5)const{
        auto smd5=md5;
        if(md5ParserUuid(smd5, smd5))
            return QUuid::fromString(qsl("{")+smd5+qsl("}"));
        else
            return QUuid();
    }

    QVariant vUnion(const QVariant &v){
        auto t=v.type();
        if(!v.isValid())
            return QVariant();
        else if(t==QVariant::List || t==QVariant::StringList){
            auto vList=v.toList();
            QVariant vA;
            while(!vList.isEmpty()){
                auto vB=vList.takeFirst();
                if(vB.type()==vA.type()){
                    vA=vUnion(vA,vB);
                }
            }
            return vA;
        }
        return QVariant();
    }

    QVariant vUnion(const QVariant &vDestine, const QVariant &vSource)
    {
        auto t=vDestine.type();
        if(vDestine.type()!=vSource.type())
            return QVariant();
        else if(t==QVariant::List || t==QVariant::StringList)
            return (vDestine.toList()+vSource.toList());
        else if(t==QVariant::Map || t==QVariant::Hash){
            auto aMap=vDestine.toHash();
            auto bMap=vSource.toHash();
            QHashIterator<QString, QVariant> i(bMap);
            while (i.hasNext()) {
                i.next();
                const auto&k=i.key();
                if(!aMap.contains(k)){
                    aMap[k]=i.value();
                }
            }
            return aMap;
        }
        else{
            QByteArray rByte;
            auto ls=QVariantList()<<vDestine<<vSource;
            for(auto&v:ls){
                rByte.append(v.toByteArray());
            }
            return rByte;
        }
        return QVariant();
    }

    QVariant vMerge(const QVariant &v){
        QVariant vOut;
        if(this->canConvertJson(v,vOut)){
            auto t=vOut.type();
            if(!vOut.isValid())
                return QVariant();
            else if(t==QVariant::List || t==QVariant::StringList){
                auto vList=vOut.toList();
                if(!vList.isEmpty()){
                    auto vA=QVariant(vList.first().type());
                    while(!vList.isEmpty()){
                        auto vB=vList.takeFirst();
                        if(vB.type()==vA.type()){
                            vA=vMerge(vA,vB);
                        }
                    }
                    return vA;
                }
            }
        }
        return QVariant();
    }

    static QVariant vMerge(const QVariant&vDestineIn, const QVariant&vSourceIn){
        QVariant vDestine;
        QVariant vSource;
        if(!canConvertJson(vDestineIn, vDestine))
            vDestine=vDestineIn;

        if(!canConvertJson(vSourceIn, vSource))
            vSource=vSourceIn;

        auto t=vDestine.type();
        if(vDestine.type()!=vSource.type()){
            return QVariant();
        }
        else if(t==QVariant::List || t==QVariant::StringList){
            auto dst=vDestine.toList();
            auto src=vSource.toList();
            QStringList keyList;
            QVariantList lst;
            for(const auto&v:dst){//cache de chaves existentes
                if(v.isValid()){
                    if( v.type()==v.List || v.type()==v.StringList || v.type()==v.Map || v.type()==v.Hash )
                        keyList<<toMd5(v);
                    else
                        keyList<<toByteArray(v);
                }
            }
            for(auto&v:src){
                if(v.isValid()){
                    QByteArray key;
                    if( v.type()==v.List || v.type()==v.StringList || v.type()==v.Map || v.type()==v.Hash )
                        key=toMd5(v);
                    else
                        key=toByteArray(v);

                    if(!lst.contains(key)){
                        lst<<v;
                    }
                }
            }
            return lst;
        }
        else if(t==QVariant::Map || t==QVariant::Hash){
            auto aMap=vDestine.toHash();
            auto bMap=vSource.toHash();
            QHashIterator<QString, QVariant> i(bMap);
            while (i.hasNext()) {
                i.next();
                const auto&k=i.key();
                const auto&vb=i.value();
                auto&va=aMap[k];
                if(!va.isValid() || va.isNull()){
                    va=vb;
                }
                else{
                    const auto v=vMerge(va,vb);
                    aMap[k]=v;
                }
            }
            return aMap;
        }
        else{
            QByteArray rByte;
            auto ls=QVariantList()<<vDestine<<vSource;
            for(auto&v:ls){
                rByte.append(v.toByteArray());
            }
            return rByte;
        }
        return QVariant();
    }

    QVariant vDeduplicate(const QVariant&v){
        QVariant vRet;
        if(v.type()==QVariant::Map || v.type()==QVariant::Hash){
            auto vMap=v.toHash();
            auto vAdd=QVariantHash();
            QHashIterator<QString, QVariant> i(vMap);
            while (i.hasNext()) {
                i.next();
                const auto&key=i.key();//no modifique a chave
                auto value=vDeduplicate(i.value());
                if(vAdd.contains(key))
                    vAdd.insert(key, value);
            }
            vRet=vAdd;
        }
        else if(v.type()==QVariant::List){
            auto vMap=v.toList();
            auto vAdd=QVariantHash();
            for(auto&v:vMap){
                const auto value=vDeduplicate(v);
                const auto key=toMd5(value);
                if(!vAdd.contains(key))
                    vAdd.insert(key,value);
            }
            vRet=vAdd.values();
        }
        return v;
    }

};

VariantUtil::VariantUtil(const QVariant &v):QVariant(v)
{
    this->p = new VariantUtilPvt(this);
}

VariantUtil::~VariantUtil()
{
    dPvt();
    this->p=nullptr;
    p.deleteLater();
}

VariantUtil&VariantUtil::operator=(const QVariant &v)
{
    this->setValue(v);
    return*this;
}

bool VariantUtil::isHex(const QVariant &v)const
{
    bool __isHex=false;
    for(auto&c:v.toString()){
        if (!isxdigit(c.toLatin1()))
            return false;
        else
            __isHex=true;
    }
    return __isHex;
}

bool VariantUtil::isBase64(const QVariant &v) const
{
    auto bytes=QByteArray::fromBase64(v.toByteArray());
    return !bytes.isEmpty();
}

const QString VariantUtil::toStr(const QVariant &v)
{
    dPvt();
    set__value(v);
    auto vType=QVariant::type();
    if(vType==QVariant::List || vType==QVariant::StringList || vType==QVariant::Map || vType==QVariant::Hash)
        return QJsonDocument::fromVariant(*this).toJson(QJsonDocument::Compact);
    else if(vType==QVariant::Uuid)
        return QVariant::toUuid().toString();
    else
        return QVariant::toString();
}

const QByteArray VariantUtil::toByteArray(const QVariant &v)
{
    dPvt();
    set__value(v);
    auto vType=this->type();
    if(vType==QVariant::List || vType==QVariant::StringList || vType==QVariant::Map || vType==QVariant::Hash)
        return QJsonDocument::fromVariant(*this).toJson(QJsonDocument::Compact);
    else if(vType==QVariant::Uuid)
        return QVariant::toUuid().toByteArray();
    else
        return QVariant::toByteArray();
}

const QChar VariantUtil::toChar(const QVariant &v)
{
    dPvt();
    set__value(v);
    return QVariant::toChar();
}

int VariantUtil::toInt(const QVariant &v)
{
    dPvt();
    set__value(v);
    return QVariant::toUInt();
}

qlonglong VariantUtil::toLongLong(const QVariant &v)
{
    if(v.isValid()) QVariant::setValue(v);
    return QVariant::toLongLong();
}

const QDate VariantUtil::toDate(const QVariant &v)
{
    dPvt();
    set__value(v);
    DateUtil du(*this);
    return du.toDate();
}

const QTime VariantUtil::toTime(const QVariant &v)
{
    dPvt();
    set__value(v);
    DateUtil du(*this);
    return du.toTime();
}

const QDateTime VariantUtil::toDateTime(const QVariant &v)
{
    dPvt();
    set__value(v);
    DateUtil du(*this);
    return du.toDateTime();
}

double VariantUtil::toDouble(const QVariant &v)
{
    dPvt();
    set__value(v);
    return QVariant::toDouble();
}

bool VariantUtil::toBool(const QVariant &v)
{
    const static auto listBool=QVector<QByteArray>()<<qbl("1")<<qbl("true")<<qbl("yes")<<qbl("sim")<<qbl("verdadeiro")<<qbl("t")<<qbl("s")<<qbl("v")<<qbl("y");
    dPvt();
    set__value(v);
    if(QVariant::type()==QVariant::Bool)
        return QVariant::toBool();
    else if(listBool.contains(QVariant::toByteArray().toLower().trimmed()))
        return true;
    else
        return false;
}

bool VariantUtil::canConvertJson(const QVariant &v) const
{
    QVariant vOut;
    dPvt();
    return p.canConvertJson(v, vOut);
}

bool VariantUtil::canConvertJson(const QVariant &v, QVariant &vOut) const
{
    dPvt();
    return p.canConvertJson(v, vOut);
}

const QByteArray VariantUtil::toMd5(const QVariant &v)
{
    dPvt();
    set__value(v);
    if(!this->isValid())
        return qbl_null;
    else if(this->type()==v.Uuid){
        auto uuid=QVariant::toUuid();
        auto suuid=uuid.toByteArray();
        auto md5=suuid.replace(qbl("{"), qbl_null).replace(qbl("}"), qbl_null).replace(qbl("-"), qbl_null);
        if(md5.length()==32)
            return md5;
        else
            return QCryptographicHash::hash(suuid, QCryptographicHash::Md5).toHex();
    }
    else {
        auto bytes=this->toByteArray().trimmed();
        if(bytes.isEmpty())
            return qbl_null;
        //se ja for md5 ou uuid manteremos o uuid como md5 logo ja e um
        else if((this->type()==v.ByteArray || this->type()==v.String)){
            auto md5=bytes.replace(qbl("{"), qbl_null).replace(qbl("}"), qbl_null).replace(qbl("-"), qbl_null);
            if(md5.length()==32)
                return md5;
        }
        return QCryptographicHash::hash(bytes, QCryptographicHash::Md5).toHex();
    }
}

const QByteArray VariantUtil::toHex(const QVariant &v)
{
    dPvt();
    set__value(v);
    return this->toByteArray().toHex();
}

const QUuid VariantUtil::toUuid(const QVariant &v)
{
    dPvt();
    set__value(v);
    if(QVariant::type()==v.Uuid)
        return QVariant::toUuid();
    else if(this->canConvert(v.String))
        return p.md5toUuid(this->toStr(v));
    else
        return QUuid();
}

const QUuid VariantUtil::toMd5Uuid(const QVariant &v)
{
    auto md5=this->toMd5(v);
    return this->toUuid(md5);
}

QVVM VariantUtil::toVVM() const
{
    dPvt();
    return p.vvm;
}

const QVVM VariantUtil::toVVM(const QVariant &v)
{
    dPvt();
    if(v.isValid())
        p.clear();
    auto map=VariantUtil::toHash();
    QHashIterator<QString, QVariant> i(map);
    while (i.hasNext()) {
        i.next();
        p.vvm.insert(i.key(), i.value());
    }
    return QVVM(p.vvm);
}

const QVVM VariantUtil::toVVM(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.vvm.clear();
    p.vvm.insert(key, value);
    this->setValue(QVariant());
    return QVVM(p.vvm);
}

const QVariantList VariantUtil::takeList(const QByteArray &keyName)
{
    QVariantList la;
    QVariantList lb;
    if(this->type()==QVariant::List)
        la=this->toList();
    else
        la<<this->toHash();
    for(auto&v:la){
        if((v.type()==QVariant::Map) || (v.type()==QVariant::Hash)){
            auto vm=v.toHash();
            auto vv=vm.value(keyName);
            if(vv.isValid()){
                lb<<vv;
            }
        }
    }
    return lb;
}

QVariant::Type VariantUtil::type() const
{
    dPvt();
    if(!p.vvm.isEmpty())
        return QVariant::Map;
    else
        return QVariant::type();
}

const QStringList VariantUtil::toStringList()
{
    return this->toStringList(*this);
}

const QStringList VariantUtil::toStringList(const QVariant &v)
{
    QStringList map;
    if(v.type()==QVariant::List || v.type()==QVariant::StringList)
        map=v.toStringList();
    else if(v.isNull() || !v.isValid() || v.toString().trimmed().isEmpty())
        map.clear();
    else if(v.type()==QVariant::String || v.type()==QVariant::ByteArray || v.type()==QVariant::Char || v.type()==QVariant::BitArray){
        QJsonParseError*error=nullptr;
        auto doc=QJsonDocument::fromJson(v.toByteArray(), error);
        if(error!=nullptr){
#if Q_STM_LOG
            sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
        }
        else if(!doc.isEmpty() || !doc.isNull()){
            map=doc.toVariant().toStringList();
        }
    }
    return map;
}

const QVariantList VariantUtil::toList(const QVariant &v)
{
    dPvt();
    set__value(v);
    return this->toVariantObject(v).toList();
}

QVariantMap VariantUtil::toMap() const
{
    dPvt();
    if(!p.vvm.isEmpty()){
        QVariantMap map;
        QHashIterator<QString, QVariant> i(p.vvm);
        while (i.hasNext()) {
            i.next();
            map.insert(i.key(), i.value());
        }
        return map;
    }
    else{
        auto v=p.toMap(*this);
        return v;
    }
}

QVariantMap VariantUtil::toMap(const QVariant &v)const
{
    QVariantMap map;
    if(v.type()==QVariant::Map || v.type()==QVariant::Hash)
        map=v.toMap();
    else if(v.isNull() || !v.isValid() || v.toString().trimmed().isEmpty())
        map.clear();
    else if(v.type()==QVariant::String || v.type()==QVariant::ByteArray || v.type()==QVariant::Char || v.type()==QVariant::BitArray){
        QJsonParseError*error=nullptr;
        auto doc=QJsonDocument::fromJson(v.toByteArray(),error);
        if(error!=nullptr){
#if Q_STM_LOG
            sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
        }
        else if(!doc.isEmpty() || !doc.isNull()){
            map=doc.object().toVariantMap();
        }
    }
    return map;
}

const QVariantMap VariantUtil::toMap(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.clear();
    this->makeMap(key,value);
    return this->toMap();
}

QVariantHash VariantUtil::toHash()const
{
    dPvt();
    if(!p.vvm.isEmpty()){
        QVariantHash map;
        QHashIterator<QString, QVariant> i(p.vvm);
        while (i.hasNext()) {
            i.next();
            map.insert(i.key(), i.value());
        }
        return map;
    }
    else{
        auto v=p.toHash(*this);
        return v;
    }
}

const QVariantHash VariantUtil::toHash(const QVariant &v)
{
    QVariantHash map;
    QVariant::Type vtype=v.type();
    if(vtype==QVariant::Map || vtype==QVariant::Hash)
        map=v.toHash();
    else if(v.isNull() || !v.isValid() || v.toString().trimmed().isEmpty())
        map.clear();
    else if(vtype==QVariant::String || vtype==QVariant::ByteArray || vtype==QVariant::Char || vtype==QVariant::BitArray){
        QJsonParseError*error=nullptr;
        auto doc=QJsonDocument::fromJson(v.toByteArray(),error);
        if(error!=nullptr){
#if Q_STM_LOG
            sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
        }
        else if(!doc.isEmpty() || !doc.isNull()){
            map=doc.object().toVariantHash();
        }
    }
    return map;
}

const QVariantHash VariantUtil::toHash(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.clear();
    this->makeHash(key,value);
    return this->toHash();
}

const QVariant VariantUtil::toType(const Type &type, const QVariant &v)
{
    dPvt();
    set__value(v);
    if(type==QVariant::Uuid)
        return this->toUuid(v);
    else if(type==QVariant::Url)
        return this->toUrl(v);
    else if(type==QVariant::String || type==QVariant::ByteArray  || type==QVariant::BitArray || type==QVariant::Char)
        return this->toStr(v);
    else if(type==QVariant::Map || type==QVariant::Hash)
        return this->toMap(v);
    else if(type==QVariant::StringList)
        return this->toStringList(v);
    else if(type==QVariant::List)
        return this->toList(v);
    else if(type==QVariant::Int || type==QVariant::UInt || type==QVariant::LongLong || type==QVariant::ULongLong || type==QVariant::Double)
        return this->toLongLong(v);
    else if(type==QVariant::Date)
        return this->toDate(v);
    else if(type==QVariant::Time)
        return this->toTime(v);
    else if(type==QVariant::DateTime)
        return this->toDateTime(v);
    else if(type==QVariant::Bool)
        return this->toBool(v);
    else
        return QVariant();
}

const QVariant VariantUtil::toVariant(const QVariant &v)
{
    if(v.type()==QVariant::Map || v.type()==QVariant::Hash || v.type()==QVariant::List || v.type()==QVariant::StringList){
        return v;
    }
    else if(v.type()==QVariant::String || v.type()==QVariant::ByteArray || v.type()==QVariant::Char || v.type()==QVariant::BitArray){
        auto vv=this->toVariantJson(v);
        if(vv.isNull() || !vv.isValid())
            vv=this->toVariantCBor(v);
        return vv.isValid()?vv:vv;
    }
    else{
        return v;
    }
}

const QVariant VariantUtil::toVariantObject(const QVariant &v)
{
    if(v.type()==QVariant::Map || v.type()==QVariant::Hash || v.type()==QVariant::List || v.type()==QVariant::StringList){
        return v;
    }
    else if(v.type()==QVariant::String || v.type()==QVariant::ByteArray || v.type()==QVariant::Char || v.type()==QVariant::BitArray){
        auto vv=this->toVariantJson(v);
        if(!(vv.type()==QVariant::Map || vv.type()==QVariant::Hash || vv.type()==QVariant::List || vv.type()==QVariant::StringList)){
            vv=this->toVariantCBor(v);
            if(!(vv.type()==QVariant::Map || vv.type()==QVariant::Hash || vv.type()==QVariant::List || vv.type()==QVariant::StringList)){
                vv=QVariant();
            }
        }
        return vv;
    }
    else{
        return QVariant();
    }
}

const QVariant VariantUtil::toVariantJson(const QVariant &v)
{
    if(v.type()==QVariant::Map || v.type()==QVariant::Hash || v.type()==QVariant::List || v.type()==QVariant::StringList){
        return v;
    }
    else if(v.type()==QVariant::String || v.type()==QVariant::ByteArray || v.type()==QVariant::Char || v.type()==QVariant::BitArray){
        auto vv=QJsonDocument::fromJson(v.toByteArray()).toVariant();
        if(vv.isNull() || !vv.isValid())
            vv=this->toVariantCBor(v);
        return vv.isValid()?vv:v;
    }
    else{
        return v;
    }
}

const QVariant VariantUtil::toVariantCBor(const QVariant &v)
{
    if(v.type()==QVariant::Map || v.type()==QVariant::Hash || v.type()==QVariant::List || v.type()==QVariant::StringList){
        return v;
    }
    else if(v.type()==QVariant::String || v.type()==QVariant::ByteArray || v.type()==QVariant::Char || v.type()==QVariant::BitArray){
        auto vv=QCborValue::fromVariant(v).toVariant();
        if(vv.isNull() || !vv.isValid())
            vv=this->toVariantJson(v);
        return vv.isValid()?vv:v;
    }
    else{
        return v;
    }
}

const QUrl VariantUtil::toUrl(const QVariant &v)
{
    if(v.isValid()) QVariant::setValue(v);
    if(v.type()==v.Url)
        return v.toUrl();
    else{
        QUrl url;
        auto surl=v.toString();
        if(QFile::exists(surl))
            url=QUrl::fromLocalFile(surl);
        else
            url=QUrl(surl);
        QVariant::setValue(url);
        return url;
    }
}

VariantUtil &VariantUtil::makeVVM(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.vvm.insert(key, value);
    this->setValue(QVariant());
    return*this;
}

VariantUtil &VariantUtil::mVVM(const QVariant &key, const QVariant &value)
{
    return this->makeVVM(key, value);
}

VariantUtil &VariantUtil::makeMap(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.vvm.clear();
    auto map=QVariant::toMap();
    map.insert(key.toString(),value);
    this->setValue(map);
    return*this;
}

VariantUtil &VariantUtil::mMap(const QVariant &key, const QVariant &value)
{
    return this->makeMap(key,value);
}

VariantUtil &VariantUtil::makeHash(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.vvm.clear();
    auto map=QVariant::toHash();
    map.insert(key.toString(),value);
    this->setValue(map);
    return*this;
}

VariantUtil &VariantUtil::mHash(const QVariant &key, const QVariant &value)
{
    return this->makeHash(key,value);
}

VariantUtil &VariantUtil::makeList(const QVariant &value)
{
    dPvt();
    p.vvm.clear();
    auto list=QVariant::toList();
    list<<value;
    this->setValue(list);
    return*this;
}

VariantUtil &VariantUtil::mList(const QVariant&value)
{
    return this->makeList(value);
}

VariantUtil &VariantUtil::clear()
{
    dPvt();
    p.clear();
    return*this;
}

VariantUtil &VariantUtil::vUnion(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(p.vUnion(v));
    return*this;
}

VariantUtil &VariantUtil::vUnion(const QVariant &vDestine, const QVariant &vSource)
{
    dPvt();
    p.clear();
    this->setValue(p.vUnion(vDestine,vSource));
    return*this;
}

VariantUtil &VariantUtil::vMerge(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(p.vMerge(v));
    return*this;
}

VariantUtil &VariantUtil::vMerge(const QVariant &vDestine, const QVariant &vSource)
{
    dPvt();
    p.clear();
    this->setValue(p.vMerge(vDestine,vSource));
    return*this;
}

VariantUtil &VariantUtil::vDeduplicate(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(p.vDeduplicate(v));
    return*this;
}

bool VariantUtil::vIsEmpty(const QVariant &v)
{
    auto vv=QVariant(v.isValid()?v:*this);
    bool invalid=vv.isValid() && !v.isNull();
    if(invalid){
        if(vv.type()==QVariant::Uuid)
            invalid=vv.toUuid().isNull();
        else if(vv.type()==QVariant::Url)
            invalid=vv.toUrl().isEmpty();
        else if(vv.type()==QVariant::String || vv.type()==QVariant::ByteArray  || vv.type()==QVariant::BitArray || vv.type()==QVariant::Char)
            invalid=vv.toByteArray().trimmed().isEmpty();
        else if(vv.type()==QVariant::Map || vv.type()==QVariant::Hash)
            invalid=vv.toHash().isEmpty();
        else if(vv.type()==QVariant::List || vv.type()==QVariant::StringList)
            invalid=vv.toList().isEmpty();
        else if(QByteArray(vv.typeName())==QT_STRINGIFY2(QVVM))
            invalid=vv.toHash().isEmpty();
        else if(vv.type()==QVariant::Int || vv.type()==QVariant::UInt || vv.type()==QVariant::LongLong || vv.type()==QVariant::ULongLong || vv.type()==QVariant::Double)
            invalid=vv.toDouble()==0;
        else if(vv.type()==QVariant::Date || vv.type()==QVariant::Time || vv.type()==QVariant::DateTime)
            invalid=vv.toDateTime().isNull();
        else
            invalid=vv.isNull();
    }
    return invalid;
}

bool VariantUtil::vIsObject(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(v);
    if(v.type()==v.List || v.type()==v.StringList)
        return true;
    else if(v.type()==v.Map || v.type()==v.Hash)
        return true;
    else
        return false;
}

bool VariantUtil::vIsList(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(v);
    return (v.type()==v.List || v.type()==v.StringList);
}

bool VariantUtil::vIsMap(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(v);
    return (v.type()==v.Hash || v.type()==v.Map || QByteArray(v.typeName())==QT_STRINGIFY2(QVVM));
}

bool VariantUtil::vIsString(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(v);
    return (v.type()==v.String || v.type()==v.ByteArray || v.type()==v.Char);
}

}
