#include "./qstm_util_variant.h"
#include "./qstm_util_date.h"
#include "./qstm_types.h"
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
        auto makeFromJson=[&v](){
            auto bytes=v.toByteArray().trimmed();
            if(bytes.isEmpty())
                return QVariantHash{};

            QJsonParseError*error=nullptr;
            auto doc=QJsonDocument::fromJson(bytes,error);
            if(error!=nullptr){
#if Q_STM_LOG
                sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
            }
            return doc.object().toVariantHash();
        };

        if(v.isNull() || !v.isValid())
            return {};

        switch (qTypeId(v)) {
        case QMetaType_QVariantMap:
            return v.toHash();
        case QMetaType_QVariantHash:
            return v.toHash();
        case QMetaType_QString:
            return makeFromJson();
        case QMetaType_QByteArray:
            return makeFromJson();
        default:
            return {};
        }
    }

    QVariantMap toMap(const QVariant &v)const
    {
        auto makeFromJson=[&v](){
            auto bytes=v.toByteArray().trimmed();
            if(bytes.isEmpty())
                return QVariantMap{};

            QJsonParseError*error=nullptr;
            auto doc=QJsonDocument::fromJson(bytes,error);
            if(error!=nullptr){
#if Q_STM_LOG
                sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
            }
            return doc.object().toVariantMap();
        };

        if(v.isNull() || !v.isValid())
            return {};

        auto typeId=qTypeId(v);

        switch (typeId) {
        case QMetaType_QVariantMap:
            return v.toMap();
        case QMetaType_QVariantHash:
            return v.toMap();
        case QMetaType_QString:
            return makeFromJson();
        case QMetaType_QByteArray:
            return makeFromJson();
        default:
            return {};
        }
    }

    static QByteArray toMd5(const QVariant &v)
    {
        //if(v.isValid()) vBase->setValue(v);
        auto typeId=qTypeId(v);
        if(!v.isValid())
            return qbl_null;

        if(typeId==QMetaType_QUuid){
            auto uuid=v.toUuid();
            auto suuid=uuid.toByteArray();
            auto md5=suuid.replace(qbl("{"),qbl_null).replace(qbl("}"),qbl_null).replace(qbl("-"), qbl_null);
            if(md5.length()==32)
                return md5;

            return QCryptographicHash::hash(suuid, QCryptographicHash::Md5).toHex();
        }

        auto bytes=v.toByteArray().trimmed();
        if(bytes.isEmpty())
            return {};
        //se ja for md5 ou uuid manteremos o uuid como md5 logo ja e um
        if(QStmTypesListObjectsString.contains(typeId)){
            auto md5=bytes.replace(qbl("{"),qbl_null).replace(qbl("}"),qbl_null).replace(qbl("-"),qbl_null);
            if(md5.length()==32)
                return md5;
        }
        return QCryptographicHash::hash(bytes, QCryptographicHash::Md5).toHex();
    }

    static QByteArray toByteArray(const QVariant &v)
    {
        auto typeId=qTypeId(v);
        switch (typeId) {
        case QMetaType_QUuid:
            return v.toUuid().toByteArray();
        case QMetaType_QUrl:
            return v.toUrl().toString().toUtf8();
        case QMetaType_Int:
            return QString::number(v.toLongLong()).toUtf8();
        case QMetaType_UInt:
            return QString::number(v.toLongLong()).toUtf8();
        case QMetaType_LongLong:
            return QString::number(v.toLongLong()).toUtf8();
        case QMetaType_ULongLong:
            return QString::number(v.toLongLong()).toUtf8();
        case QMetaType_Double:
            return QString::number(v.toDouble(),'f').toUtf8();
        case QMetaType_QDate:
            return v.toDate().toString(Qt::ISODate).toUtf8();
        case QMetaType_QTime:
            return v.toTime().toString(Qt::ISODateWithMs).toUtf8();
        case QMetaType_QDateTime:
            return v.toDateTime().toString(Qt::ISODateWithMs).toUtf8();
        default:
            if(QStmTypesObjectMetaData.contains(typeId))
                return QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
            return v.toByteArray();
        }
    }

    static bool canConvertJson(const QVariant &v, QVariant &vOut)
    {
        vOut=QVariant();
        if(v.isNull() || !v.isValid())
            return false;

        auto typeId=qTypeId(v);

        if(QStmTypesListObjects.contains(typeId)){
            vOut=v;
            return true;
        }

        if(QStmTypesListObjectsString.contains(typeId)){
            QJsonParseError*error=nullptr;
            auto doc=QJsonDocument::fromJson(v.toByteArray(),error);
            if(error!=nullptr){
                if(doc.isArray() || doc.isObject()){
                    vOut=doc.toVariant();
                    return true;
                }
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
                if(i==8 || i==12 || i==16 || i==20)
                    suuid.append(qbl("-"));
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

        return QUuid();
    }

    QVariant vUnion(const QVariant &v){
        auto t=qTypeId(v);
        if(!v.isValid())
            return {};

        if(QStmTypesVariantList.contains(t)){
            auto vList=v.toList();
            QVariant vA;
            while(!vList.isEmpty()){
                auto vB=vList.takeFirst();
                if(qTypeId(vB)==qTypeId(vB))
                    vA=vUnion(vA,vB);
            }
            return vA;
        }
        return {};
    }

    QVariant vUnion(const QVariant &vDestine, const QVariant &vSource)
    {
        auto t=qTypeId(vDestine);
        if(t!=qTypeId(vSource))
            return {};

        if(QStmTypesVariantList.contains(t))
            return (vDestine.toList()+vSource.toList());

        if(QStmTypesVariantDictionary.contains(t)){
            auto aMap=vDestine.toHash();
            auto bMap=vSource.toHash();
            QHashIterator<QString, QVariant> i(bMap);
            while (i.hasNext()) {
                i.next();
                const auto&k=i.key();
                if(!aMap.contains(k))
                    aMap[k]=i.value();
            }
            return aMap;
        }

        QByteArray rByte;
        auto ls=QVariantList{vDestine, vSource};
        for(auto&v:ls){
            rByte.append(v.toByteArray());
        }
        return rByte;
    }

    QVariant vMerge(const QVariant &v)
    {
        QVariant vOut;
        if(this->canConvertJson(v,vOut)){
            auto t=qTypeId(vOut);
            if(!vOut.isValid())
                return {};

            if(QStmTypesVariantList.contains(t)){
                auto vList=vOut.toList();
                if(!vList.isEmpty()){
                    auto vA=QVariant(vList.takeFirst());
                    for(const auto&vB:vList){
                        if(qTypeId(vB)==qTypeId(vA)){
                            vA=vMerge(vA,vB);
                        }
                    }
                    return vA;
                }
            }
        }
        return {};
    }

    static QVariant vMerge(const QVariant&vDestineIn, const QVariant&vSourceIn)
    {
        QVariant vDestine;
        QVariant vSource;
        if(!canConvertJson(vDestineIn, vDestine))
            vDestine=vDestineIn;

        if(!canConvertJson(vSourceIn, vSource))
            vSource=vSourceIn;

        auto t=qTypeId(vDestine);
        if(qTypeId(vDestine)!=qTypeId(vSource))
            return {};

        if(QStmTypesVariantList.contains(t)){
            auto dst=vDestine.toList();
            auto src=vSource.toList();
            QStringList keyList;
            QVariantList lst;
            for(const auto&v:dst){//cache de chaves existentes
                if(v.isValid()){
                    auto typeId=qTypeId(v);
                    if(QStmTypesVariantDictionary.contains(typeId)){
                        keyList<<toMd5(v);
                        continue;
                    }
                    keyList<<toByteArray(v);
                }
            }
            for(auto&v:src){
                if(v.isValid()){
                    QByteArray key;
                    auto typeId=qTypeId(v);
                    if(QStmTypesVariantDictionary.contains(typeId))
                        key=toMd5(v);
                    else
                        key=toByteArray(v);

                    if(!lst.contains(key))
                        lst<<v;
                }
            }
            return lst;
        }

        if(QStmTypesVariantDictionary.contains(t)){
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

        QByteArray rByte;
        auto ls=QVariantList{vDestine, vSource};
        for(auto&v:ls){
            rByte.append(v.toByteArray());
        }
        return rByte;
    }

    QVariant vDeduplicate(const QVariant&v){
        QVariant vRet;
        auto typeId=qTypeId(v);
        if(QStmTypesVariantDictionary.contains(typeId)){
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

        if(QStmTypesVariantList.contains(typeId)){
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
        return vRet;
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

bool VariantUtil::isUuid(const QVariant &v) const
{
    VariantUtil vu(v);
    auto uuid=vu.toUuid();
    return !uuid.isNull();
}

bool VariantUtil::isUuid(const QVariant &v, QUuid &uuidSet) const
{
    dPvt();
    QString text=v.toString();
    QUuid uuid;
    if(p.md5ParserUuid(text,text))
        uuid=QUuid::fromString(text);

    if(uuid.isNull())
        return false;

    uuidSet=uuid;
    return true;
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
    return p.toByteArray(*this);
}

const QByteArray VariantUtil::toAlphaNumber(const QVariant &v)
{
    QString __return;
    static auto num=qsl("0123456789");
    auto text=v.toString();
    for(auto&c:text){
        if(num.contains(c))
            __return+=c;
    }
    return __return.toUtf8();
}

const QByteArray VariantUtil::toAlphaNumeric(const QVariant &v)
{
    QString __return;
    static auto num=qsl("0123456789.,-");
    auto text=v.toString();
    for(auto&c:text){
        if(num.contains(c))
            __return+=c;
    }
    return __return.toUtf8();
}

const QString VariantUtil::toAlphaText(const QVariant &v)
{
    QString __return;
    static auto num=qsl("0123456789");
    auto text=v.toString();
    for(auto&c:text){
        if(!num.contains(c))
            __return+=c;
    }
    return __return;
}

const QByteArray VariantUtil::toByteArray(const QVariant &v)
{
    dPvt();
    set__value(v);
    return p.toByteArray(*this);
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

    if(qTypeId(*this)==QMetaType_Bool)
        return QVariant::toBool();

    if(listBool.contains(QVariant::toByteArray().toLower().trimmed()))
        return true;

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
        return {};

    if(qTypeId(*this)==QMetaType_QUuid){
        auto uuid=QVariant::toUuid();
        auto suuid=uuid.toByteArray();
        auto md5=suuid.replace(qbl("{"), qbl_null).replace(qbl("}"), qbl_null).replace(qbl("-"), qbl_null);
        if(md5.length()==32)
            return md5;

        return QCryptographicHash::hash(suuid, QCryptographicHash::Md5).toHex();
    }

    auto bytes=this->toByteArray().trimmed();
    if(bytes.isEmpty())
        return {};
    //se ja for md5 ou uuid manteremos o uuid como md5 logo ja e um
    if(QStmTypesListObjectsString.contains(qTypeId(*this))){
        auto md5=bytes.replace(qbl("{"), qbl_null).replace(qbl("}"), qbl_null).replace(qbl("-"), qbl_null);
        if(md5.length()==32)
            return md5;
    }
    return QCryptographicHash::hash(bytes, QCryptographicHash::Md5).toHex();
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
    if(qTypeId(*this)==QMetaType_QUuid)
        return QVariant::toUuid();
    return p.md5toUuid(this->toStr(v));
}

const QString VariantUtil::toUuidSimple(const QVariant &v)
{
    dPvt();
    set__value(v);
    auto __return=this->toUuid().toString();
    return __return.toLower().replace(qsl("{"), QString()).replace(qsl("}"), QString());
}

const QUuid VariantUtil::toMd5Uuid(const QVariant &v)
{
    auto md5=this->toMd5(v);
    return this->toUuid(md5);
}

QVVM VariantUtil::toVVM() const
{
    dPvt();
    auto vvm=p.vvm;
    p.clear();
    return vvm;
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
        p.vvm[i.key()]=i.value();
    }
    return QVVM(p.vvm);
}

const QVVM VariantUtil::toVVM(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.vvm.clear();
    p.vvm.insert(key, value);
    this->setValue(QVariant());
    return p.vvm;
}

const QVariantList VariantUtil::takeList(const QByteArray &keyName)
{
    QVariantList la;
    QVariantList lb;
    if(QStmTypesVariantList.contains(qTypeId(*this)))
        la=this->toList();
    else
        la<<this->toHash();
    for(auto&v:la){
        if(QStmTypesVariantDictionary.contains(qTypeId(v))){
            auto vm=v.toHash();
            auto vv=vm.value(keyName);
            if(vv.isValid())
                lb<<vv;
        }
    }
    return lb;
}

int VariantUtil::typeId() const
{
    dPvt();
    if(!p.vvm.isEmpty())
        return QMetaType_QVariantMap;

    return qTypeId(*this);
}

const QStringList VariantUtil::toStringList()
{
    return this->toStringList(*this);
}

const QStringList VariantUtil::toStringList(const QVariant &v)
{
    auto typeId=qTypeId(v);
    if(QStmTypesVariantList.contains(typeId))
        return v.toStringList();

    if(v.isNull() || !v.isValid())
        return {};

    if(QStmTypesListObjectsString.contains(typeId)){
        if(v.toString().trimmed().isEmpty())
            return {};
        QJsonParseError*error=nullptr;
        auto doc=QJsonDocument::fromJson(v.toByteArray(), error);
        if(error!=nullptr){
#if Q_STM_LOG
            sWarning()<<qsl("Invalid parse: ")<<v.toString();
#endif
            return {};
        }

        if(!doc.isEmpty() || !doc.isNull()){
            return doc.toVariant().toStringList();
        }
    }
    return {};
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
            map[i.key()]=i.value();
        }
        return map;
    }

    auto v=p.toMap(*this);
    return v;
}

const QVariantMap VariantUtil::toMap(const QVariant &v)
{
    dPvt();
    set__value(v);
    return p.toMap(v);
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
            map[i.key()]=i.value();
        }
        return map;
    }

    auto v=p.toHash(*this);
    return v;
}

const QVariantHash VariantUtil::toHash(const QVariant &v)
{
    dPvt();
    set__value(v);
    return p.toHash(v);
}

const QVariantHash VariantUtil::toHash(const QVariant &key, const QVariant &value)
{
    dPvt();
    p.clear();
    this->makeHash(key,value);
    return this->toHash();
}

QMultiHash<QString, QVariant> VariantUtil::toMultiHash() const
{
    return QMultiHash<QString, QVariant>{this->toHash()};
}

const QMultiHash<QString, QVariant> VariantUtil::toMultiHash(const QVariant &v)
{
    return QMultiHash<QString, QVariant>{this->toHash(v)};
}

const QMultiHash<QString, QVariant> VariantUtil::toMultiHash(const QVariant &key, const QVariant &value)
{
    return QMultiHash<QString, QVariant>{this->toHash(key, value)};
}

const QVariant VariantUtil::toType(int typeId, const QVariant &v)
{
    dPvt();
    set__value(v);
    switch (typeId) {
    case QMetaType_QUuid:
        return this->toUuid(v);
    case QMetaType_QUrl:
        return this->toUrl(v);
    case QMetaType_QString:
        return this->toStr(v);
    case QMetaType_QByteArray:
        return this->toStr(v);
    case QMetaType_QBitArray:
        return this->toStr(v);
    case QMetaType_QChar:
        return this->toStr(v);
    case QMetaType_QVariantHash:
        return this->toMap(v);
    case QMetaType_QVariantMap:
        return this->toMap(v);
    case QMetaType_QStringList:
        return this->toStringList(v);
    case QMetaType_QVariantList:
        return this->toList(v);
    case QMetaType_Int:
        return this->toInt(v);
    case QMetaType_UInt:
        return this->toInt(v);
    case QMetaType_LongLong:
        return this->toLongLong(v);
    case QMetaType_ULongLong:
        return this->toLongLong(v);
    case QMetaType_Double:
        return this->toDouble(v);
    case QMetaType_QDate:
        return this->toDate(v);
    case QMetaType_QTime:
        return this->toTime(v);
    case QMetaType_QDateTime:
        return this->toDateTime(v);
    case QMetaType_Bool:
        return this->toBool(v);
    default:
        return {};
    }
}

const QVariant VariantUtil::toVariant(const QVariant &v)
{
    auto typeId=qTypeId(v);
    if(QStmTypesListObjects.contains(typeId))
        return v;

    if(QStmTypesListObjectsString.contains(typeId)){
        auto vv=this->toVariantJson(v);
        if(vv.isNull() || !vv.isValid())
            vv=this->toVariantCBor(v);
        return vv;
    }

    return v;
}

const QVariant VariantUtil::toVariantObject(const QVariant &v)
{
    auto typeId=qTypeId(v);
    if(QStmTypesListObjects.contains(typeId))
        return v;

    if(QStmTypesListObjectsString.contains(typeId)){
        auto vv=this->toVariantJson(v);
        typeId=qTypeId(vv);
        if(!QStmTypesListObjects.contains(typeId)){
            vv=this->toVariantCBor(v);
            typeId=qTypeId(vv);
            if(!QStmTypesListObjects.contains(typeId))
                vv=QVariant();
        }
        return vv;
    }
    return {};
}

const QVariant VariantUtil::toVariantJson(const QVariant &v)
{
    auto typeId=qTypeId(v);
    if(QStmTypesListObjects.contains(typeId))
        return v;

    if(QStmTypesListObjectsString.contains(typeId)){
        auto vv=QJsonDocument::fromJson(v.toByteArray()).toVariant();
        if(vv.isNull() || !vv.isValid())
            vv=this->toVariantCBor(v);
        return vv.isValid()?vv:v;
    }
    return v;
}

const QVariant VariantUtil::toVariantCBor(const QVariant &v)
{
    auto typeId=qTypeId(v);
    if(QStmTypesListObjects.contains(typeId))
        return v;

    if(QStmTypesListObjectsString.contains(typeId)){
        auto vv=QCborValue::fromVariant(v).toVariant();
        if(vv.isNull() || !vv.isValid())
            vv=this->toVariantJson(v);
        return vv.isValid()?vv:v;
    }

    return v;
}

const QUrl VariantUtil::toUrl(const QVariant &v)
{
    if(v.isValid()) QVariant::setValue(v);
    if(qTypeId(v)==QMetaType_QUrl)
        return v.toUrl();

    QUrl url;
    auto surl=v.toString();
    if(QFile::exists(surl))
        url=QUrl::fromLocalFile(surl);
    else
        url=QUrl(surl);
    QVariant::setValue(url);
    return url;
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
    map[key.toString()]=value;
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
    map[key.toString()]=value;
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

const QUuid VariantUtil::toUuidCompuser(const QVariant &value)
{
    QStringList compuserList;
    QVariantList compuserValues;
    Q_DECLARE_VU;

    auto typeId=qTypeId(value);

    if(QStmTypesVariantList.contains(typeId))
        compuserValues=value.toList();
    else
        compuserValues<<value;

    if(compuserValues.isEmpty())
        return {};

    for(auto&v:compuserValues){
        QString text;
        switch (qTypeId(v)) {
        case QMetaType_QUuid:
            text=v.toUuid().toString().toLower().replace(qsl("{"), qsl_null).replace(qsl("}"), qsl_null).replace(qsl("-"), qsl_null);
            break;
        case QMetaType_QUrl:
            text=v.toUrl().toString().toLower().toUtf8();
            break;
        case QMetaType_Int:
        case QMetaType_UInt:
        case QMetaType_LongLong:
        case QMetaType_ULongLong:
            text=QString::number(v.toLongLong(),0).toUtf8();
            break;
        case QMetaType_Double:
            text=QString::number(v.toDouble(),'f').toUtf8();
            break;
        case QMetaType_QDate:
            text=v.toDate().toString(Qt::ISODate).toUtf8();
            break;
        case QMetaType_QTime:
            text=v.toTime().toString(Qt::ISODateWithMs).toUtf8();
            break;
        case QMetaType_QDateTime:
            text=v.toDateTime().toString(Qt::ISODateWithMs).toUtf8();
            break;
        case QMetaType_QVariantHash:
        case QMetaType_QVariantMap:
        case QMetaType_QVariantList:
        case QMetaType_QStringList:
            text=QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
            break;
        default:
            text=v.toByteArray();
            break;
        }
        text=text.trimmed();
        if(text.isEmpty())
            continue;
        compuserList<<text;
    }
    if(compuserList.isEmpty())
        return {};
    auto join=compuserList.join(qsl("."));
    auto uuid=vu.toMd5Uuid(join);
    QVariant::setValue(uuid);
    return uuid;
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
    dPvt();
    p.clear();
    this->setValue(v);
    auto vv=QVariant(v.isValid()?v:*this);
    bool invalid=vv.isValid() && !v.isNull();
    if(!invalid)
        return false;

    switch (qTypeId(*this)) {
    case QMetaType_QUuid:
        return vv.toUuid().isNull();
    case QMetaType_QUrl:
        return vv.toUrl().isEmpty();
    case QMetaType_QString:
    case QMetaType_QByteArray:
    case QMetaType_QBitArray:
    case QMetaType_QChar:
        return vv.toByteArray().trimmed().isEmpty();
    case QMetaType_QVariantMap:
    case QMetaType_QVariantHash:
        return vv.toHash().isEmpty();
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return vv.toList().isEmpty();
    case QMetaType_Int:
    case QMetaType_UInt:
    case QMetaType_LongLong:
    case QMetaType_ULongLong:
    case QMetaType_Double:
        return vv.toDouble()==0;
    case QMetaType_QDate:
        return vv.toDate().isNull();
    case QMetaType_QTime:
        return vv.toTime().isNull();
    case QMetaType_QDateTime:
        return vv.toDateTime().isNull();
    default:
        if(QByteArray(vv.typeName())==QT_STRINGIFY2(QVVM))
            return vv.toHash().isEmpty();
        return vv.isNull();
    }
}

bool VariantUtil::vIsObject(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(v);
    if(QStmTypesListObjects.contains(qTypeId(*this)))
        return true;
    return false;
}

bool VariantUtil::vIsList(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(v);
    if(QStmTypesVariantList.contains(qTypeId(*this)))
        return true;
    return false;
}

bool VariantUtil::vIsMap(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(v);
    if(QStmTypesVariantDictionary.contains(qTypeId(*this)))
        return true;
    if(QByteArray(v.typeName())==QT_STRINGIFY2(QVVM))
        return true;
    return false;
}

bool VariantUtil::vIsString(const QVariant &v)
{
    dPvt();
    p.clear();
    this->setValue(v);
    if(QStmTypesListString.contains(qTypeId(v)))
        return true;
    return false;
}

QVariant VariantUtil::convertTo(const QVariant &v, int typeId)
{
    VariantUtil vu(v);
    switch (typeId) {
    case QMetaType_QUuid:
        return vu.toUuid();
    case QMetaType_Int:
    case QMetaType_UInt:
        return vu.toInt();
    case QMetaType_LongLong:
    case QMetaType_ULongLong:
        return vu.toLongLong();
    case QMetaType_QDateTime:
        return vu.toDateTime();
    case QMetaType_QDate:
        return vu.toDate();
    case QMetaType_QTime:
        return vu.toTime();
    case QMetaType_QUrl:
        return vu.toUrl();
    case QMetaType_Bool:
        return vu.toBool();
    default:
        return v;
    }
}

}
