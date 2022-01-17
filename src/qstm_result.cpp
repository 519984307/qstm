#include "./qstm_result.h"
#include "./qstm_macro.h"
#include "./qstm_object.h"
#include "./qstm_util_variant.h"
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QMutex>
#include <QThread>

typedef QHash<ResultValue::MessageType, int> MakeArStats;


static const MakeArStats &__makeArStats()
{
    static const MakeArStats __makeArStats({{ResultValue::None, 0},
                                            {ResultValue::Information, 0},
                                            {ResultValue::Warning, 406},
                                            {ResultValue::Validation, 406},
                                            {ResultValue::Notfound, 404},
                                            {ResultValue::UnsupportedMediaType, 415},
                                            {ResultValue::Critical, 500},
                                            {ResultValue::Unauthorized, 401},
                                            {ResultValue::BadRequest, 400}});
    return __makeArStats;
}

static const auto&__makeStatusCodeSuccessList()
{
    static auto vList=QVector<int>{0, 200, 201, 202};
    return vList;
}

static const auto&makeArStats = __makeArStats();
static const auto&statusCodeSuccessList = __makeStatusCodeSuccessList();

struct QStmConstsResult
{
public:
    QHash<QThread *, QByteArray> staticThreadError;
    QMutex staticThreadLocker;
};

Q_GLOBAL_STATIC(QStmConstsResult, ___consts)
auto &qapp = *QCoreApplication::instance();

static auto &consts = *___consts;

#define dPvt() auto &p = *reinterpret_cast<ResultValuePvt *>(this->p)

class ResultValuePvt
{
public:
    QUuid uuid = QUuid::createUuid();
    bool resultBool = true;
    QStm::ResultInfo resultInfo;
    ResultValue *parent = nullptr;
    QVariantHash data;
    QVariant returnCode;
    QByteArray returnHash;
    ResultValue::MessageType returnType = ResultValue::None;
    QString returnText;
    QVariant resultVariant;
    void *resultVoid = nullptr;

    explicit ResultValuePvt(ResultValue *parent)
    {
        this->parent = parent;
    }
    virtual ~ResultValuePvt()
    {

    }

    ResultValue &setCritical(const QVariant &code, const QVariant &value)
    {
        auto v = value.toString().trimmed().isEmpty() ? QVariant() : value.toString();
        this->clear();
        if (code.isValid() || v.isValid()) {
            this->returnType = ResultValue::Critical;
            this->returnCode = this->variantConvertToCode(code);
            this->returnText = this->variantConvertToText(v);
            if (!this->returnCode.isValid())
                this->returnCode = this->toMd5(this->returnText);
            this->makeResult();
        }
        return *this->parent;
    }

    void makeResult()
    {
        if (this->isOk()) {
            this->resultInfo.clearErrors();
            resultInfo.setSuccess(true);
            auto&msgs=resultInfo.messages();
            msgs.clear();
            msgs.append(this->parent->returnText());
            return;
        }
        this->data = this->toHash();
        this->returnHash = this->toMd5(this->variantConvertToCode(data));
        this->data = this->toHash();
        {
            if (this->returnCode.isValid())
                sWarning() << this->toString();

            consts.staticThreadLocker.lock();
            consts.staticThreadError[QThread::currentThread()]=this->returnHash;
            consts.staticThreadLocker.unlock();
        }
        if(!this->parent->returnText().isEmpty()){
            resultInfo.setSuccess(false);
            auto&msgs=resultInfo.errors();
            msgs.clear();
            msgs.append(this->parent->returnText());
        }
        QList<ResultValue *> listParentResultValue;
        auto pp = dynamic_cast<QStm::Object *>(this->parent->parent());
        while (pp != nullptr) {
            listParentResultValue.insert(0, &pp->lastResult());
            pp = dynamic_cast<QStm::Object *>(pp->parent());
        }
        for (auto &result : listParentResultValue) {
            auto pvt = static_cast<ResultValuePvt *>(result->p);
            if (pvt == nullptr)
                continue;
            pvt->read(this);
        }

    }
    bool isOk()
    {
        if (QThread::currentThread()->isInterruptionRequested())
            return false;

        if(this->returnType==ResultValue::Information || this->returnType==ResultValue::None)
            return true;

        if (this->returnCode.isValid())
            return false;

        if (this->returnCode.isValid())
            return false;

        return this->returnHash.trimmed().isEmpty();
    }

    const QString toString()
    {
        if (this->isOk())
            return {};

        if (this->returnCode.isValid()) {
            if (this->returnCode.toString() == this->returnText)
                return this->returnText;
            return this->returnCode.toString() + qsl(":") + this->returnText;
        }

        return this->returnText;
    }

    const QVariantHash &toHash()
    {
        this->data.clear();
        this->data.insert(qbl("resultBool"), this->resultBool);
        data.insert(qbl("returnType"), this->returnType);
        if (this->returnCode.isValid())
            data.insert(qbl("returnCode"), this->returnCode);
        if (!this->returnHash.isEmpty())
            data.insert(qbl("returnHash"), this->returnHash);
        if (!this->returnText.isEmpty())
            data.insert(qbl("returnText"), this->returnText);
        if (this->resultVariant.isValid())
            data.insert(qbl("resultVariant"), this->resultVariant);
        if (this->resultVariant.isValid())
            data.insert(qbl("resultInfo"), this->resultInfo.toHash());
        return data;
    }

    void clear()
    {
        this->data.clear();
        this->resultBool = true;
        this->returnType = ResultValue::None;
        this->returnHash = QByteArray();
        this->returnCode = QVariant();
        this->returnText.clear();
        this->resultVariant = QVariant();
        this->resultVoid = nullptr;
        this->resultInfo.clear();
    }

    void clearReturn()
    {
        this->data.clear();
        this->resultInfo.clearErrors();
        this->resultBool = true;
    }

    void read(ResultValuePvt *pvt)
    {
        if (pvt == nullptr) {
            this->clear();
            return;
        }

        this->data = this->toHash();
        this->resultBool = pvt->resultBool;
        this->returnHash = pvt->returnHash;
        this->returnCode = pvt->returnCode;
        this->returnText = pvt->returnText;
        this->returnType = pvt->returnType;
        this->resultInfo.fromHash(pvt->resultInfo.toHash());
    }

    void readFull(ResultValuePvt *pvt)
    {
        if (pvt == nullptr) {
            this->clear();
            return;
        }

        auto aux = (!this->isOk()) ? false : this->resultBool;
        this->data = pvt->data;
        this->returnType = pvt->returnType;
        this->resultBool = pvt->resultBool;
        this->returnHash = pvt->returnHash;
        this->returnCode = pvt->returnCode;
        this->returnText = pvt->returnText;
        this->resultVariant = pvt->resultVariant;
        this->resultVoid = pvt->resultVoid;
        this->resultBool = (aux && this->resultBool) ? aux : false;
        this->resultInfo.fromHash(pvt->resultInfo.toHash());
    }

    static QByteArray toMd5(const QVariant &v)
    {
        return QCryptographicHash::hash(v.toByteArray(), QCryptographicHash::Md5).toHex();
    }

    static QVariant variantConvertToCode(const QVariant &value)
    {
        if (!value.isValid())
            return {};

        auto typeId=qTypeId(value);
        switch (typeId) {
        case QMetaType_Double:
        case QMetaType_Int:
        case QMetaType_UInt:
        case QMetaType_LongLong:
        case QMetaType_ULongLong:
            return value.toByteArray();
        case QMetaType_QString:
        case QMetaType_QByteArray:
        case QMetaType_QChar:
        case QMetaType_QBitArray:
        {
            auto code = value.toByteArray().trimmed();
            if ((code.isEmpty()))
                return {};
            return code; //QCryptographicHash::hash(code, QCryptographicHash::Md5).toHex();
        }
        default:
            break;
        }

        QStringList list;
        switch (typeId) {
        case QMetaType_QStringList:
            list = value.toStringList();
            break;
        case QMetaType_QVariantList:
        {
            for (auto &v : value.toList())
                list << v.toByteArray();
            break;
        }
        case QMetaType_QVariantMap:
        case QMetaType_QVariantHash:
        {
            Q_DECLARE_VU;
            auto vHash = vu.toHash(value);
            QStringList list;
            Q_V_HASH_ITERATOR(vHash){
                i.next();
                list << i.key() << qbl(".") << i.value().toByteArray();
            }
            break;
        }
        default:
            break;
        }
        return QCryptographicHash::hash(list.join('.').toUtf8(), QCryptographicHash::Md5).toHex();
    }

    static QString variantConvertToText(const QVariant &value)
    {
        if (!value.isValid())
            return {};

        auto typeId=qTypeId(value);

        QStringList list;
        switch (typeId) {
        case QMetaType_Double:
        case QMetaType_Int:
        case QMetaType_UInt:
        case QMetaType_LongLong:
        case QMetaType_ULongLong:
            return qsl("%1: %2").arg(qapp.tr("Error value"), value.toString());
        case QMetaType_QStringList:
            list = value.toStringList();
            break;
        case QMetaType_QVariantList:
        {
            for (auto &v : value.toList())
                list << v.toByteArray();
            break;
        }
        case QMetaType_QVariantMap:
        case QMetaType_QVariantHash:
            {
                Q_V_HASH_ITERATOR(value.toHash()){
                    i.next();
                    list << i.key() << qbl("==") << i.value().toByteArray();
                }
                break;
            }
        default:
            list << value.toString().trimmed();
            break;
        }
        return list.join(qbl("\n")).toUtf8();
    }
};

ResultValue::ResultValue(QObject *parent) : QObject(parent)
{
    this->p = new ResultValuePvt(this);
}

ResultValue::~ResultValue()
{
    dPvt();
    delete &p;
}

ResultValue &ResultValue::operator=(const bool &result)
{
    dPvt();
    p.resultBool = result;
    return *this;
}

ResultValue::operator bool() const
{
    dPvt();
    auto __isOK = p.isOk();
    bool __return = (p.resultBool & p.isOk());
    p.resultBool = __isOK;
    return __return;
}

ResultValue &ResultValue::operator=(const QSqlError &error)
{
    this->setCritical(error);
    return *this;
}

ResultValue &ResultValue::operator<<(const QSqlError &error)
{
    this->setCritical(error);
    return *this;
}

ResultValue &ResultValue::operator=(const QVariant &value)
{
    return this->setResult(value);
}

ResultValue &ResultValue::operator<<(const QVariant &value)
{
    return this->setResult(value);
}

ResultValue &ResultValue::operator=(const QString &value)
{
    return this->setResult(QVariant(value));
}

ResultValue &ResultValue::operator=(void *value)
{
    return this->setResult(value);
}

ResultValue &ResultValue::operator<<(void *value)
{
    return this->setResult(value);
}

ResultValue &ResultValue::operator=(const ResultValue &value)
{
    dPvt();
    p.readFull(static_cast<ResultValuePvt *>(value.p));
    return *this;
}

ResultValue &ResultValue::operator<<(const ResultValue &value)
{
    dPvt();
    p.readFull(static_cast<ResultValuePvt *>(value.p));
    return *this;
}

bool ResultValue::operator==(const ResultValue &value)
{
    auto uuidA = this->returnHash();
    auto uuidB = value.returnHash();
    return (uuidA == uuidB);
}

bool ResultValue::operator!=(const ResultValue &value)
{
    auto uuidA = this->returnHash();
    auto uuidB = value.returnHash();
    return (uuidA != uuidB);
}

QStm::ResultInfo &ResultValue::resultInfo()
{
    dPvt();
    return p.resultInfo;
}

ResultValue &ResultValue::printInfo(const QVariant &v)
{
    VariantUtil vu(v);
    sInfo() << vu.toStr();
    return *this;
}

ResultValue &ResultValue::printWarning(const QVariant &v)
{
    VariantUtil vu(v);
    sWarning() << vu.toStr();
    return *this;
}

QVariant &ResultValue::resultVariant() const
{
    dPvt();
    return p.resultVariant;
}

QVariant ResultValue::resultVariantInfo() const
{
    dPvt();

    if(p.resultVariant.isNull() || !p.resultVariant.isValid()){
        auto vHash=p.resultVariant.toHash();
        vHash[qsl("resultInfo")]=p.resultInfo.toHash();
        return vHash;
    }

    if (QStmTypesVariantDictionary.contains(qTypeId(p.resultVariant))){
        auto vHash=p.resultVariant.toHash();
        vHash[qsl("resultInfo")]=p.resultInfo.toHash();
        return vHash;
    }
    return p.resultVariant;
}

QVariantMap ResultValue::resultMap() const
{
    dPvt();
    return p.resultVariant.toMap();
}

QVariantHash ResultValue::resultHash() const
{
    dPvt();
    return p.resultVariant.toHash();
}

QVariantList ResultValue::resultList() const
{
    dPvt();
    auto&v=p.resultVariant;
    switch (qTypeId(v)) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        return qvl{v};
    default:
        return p.resultVariant.toList();
    }
}

QStringList ResultValue::resultStringList() const
{
    dPvt();
    auto&v=p.resultVariant;
    switch (qTypeId(v)) {
    case QMetaType_QStringList:
        return v.toStringList();
    case QMetaType_QVariantList:
    {
        Q_DECLARE_VU;
        QStringList __return;
        for(auto&row:v.toList()){
            switch (qTypeId(row)) {
            case QMetaType_QVariantHash:
            case QMetaType_QVariantMap:
            case QMetaType_QVariantList:
            case QMetaType_QStringList:
                __return<<vu.toStr(row);
                break;
            case QMetaType_QUrl:
                __return<<row.toUrl().toString();
                break;
            case QMetaType_QUuid:
                __return<<row.toUuid().toString();
                break;
            default:
                __return<<row.toString();
            }
        }
        return __return;
    }
    default:
        return {};
    }
}

QVariantList ResultValue::resultToList() const
{
    dPvt();
    auto&v=p.resultVariant;
    switch (qTypeId(v)) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return v.toList();
    default:
        if (v.isValid())
            return qvl{v};
        return {};
    }
}

QString ResultValue::resultString() const
{
    dPvt();
    return p.resultVariant.toString();
}

QByteArray ResultValue::resultByteArray() const
{
    dPvt();
    return p.resultVariant.toByteArray();
}

QUuid ResultValue::resultUuid() const
{
    dPvt();
    return p.resultVariant.toUuid();
}

qlonglong ResultValue::resultInt() const
{
    dPvt();
    auto r = p.resultVariant.toLongLong();
    return r;
}

qlonglong ResultValue::resultLongLong() const
{
    dPvt();
    auto r = p.resultVariant.toLongLong();
    return r;
}

double ResultValue::resultDouble() const
{
    dPvt();
    auto r = p.resultVariant.toDouble();
    return r;
}

QDate ResultValue::resultDate() const
{
    dPvt();
    return p.resultVariant.toDate();
}

QDateTime ResultValue::resultDateTime() const
{
    dPvt();
    return p.resultVariant.toDateTime();
}

QTime ResultValue::resultTime() const
{
    dPvt();
    return p.resultVariant.toTime();
}

QUrl ResultValue::resultUrl() const
{
    dPvt();
    return p.resultVariant.toUrl();
}

void *ResultValue::resultPointer() const
{
    return this->p;
}

ResultValue &ResultValue::clear()
{
    dPvt();
    p.clear();
    return *this;
}

const QVariantMap ResultValue::toMap()
{
    dPvt();
    return QVariant(p.toHash()).toMap();
}

const QVariantHash &ResultValue::toHash()
{
    dPvt();
    return p.toHash();
}

QByteArray &ResultValue::returnHash() const
{
    dPvt();
    return p.returnHash;
}

ResultValue::MessageType ResultValue::returnType() const
{
    dPvt();
    return p.returnType;
}

QVariant &ResultValue::returnCode() const
{
    dPvt();
    return p.returnCode;
}

QString &ResultValue::returnText() const
{
    dPvt();
    return p.returnText;
}

ResultValue &ResultValue::setResult(void *result)
{
    dPvt();
    p.clearReturn();
    p.resultVariant = QVariant::fromValue<void *>(result);
    p.resultVoid = result;
    return *this;
}

ResultValue &ResultValue::setResult(QObject &object)
{
    dPvt();
    p.clearReturn();
    p.resultVariant = QVariant::fromValue<QObject *>(&object);
    p.resultVoid = &object;
    return *this;
}

ResultValue &ResultValue::setResult(const QVariant &result)
{
    dPvt();
    p.clearReturn();
    p.resultVariant = result;
    p.resultVoid = &p.resultVariant;
    return *this;
}

ResultValue &ResultValue::setResult(const ResultValue &result)
{
    dPvt();
    auto pp = static_cast<ResultValuePvt *>(result.p);
    p.readFull(pp);
    return *this;
}

ResultValue &ResultValue::setResult(const QSqlError &result)
{
    dPvt();
    return p.setCritical(result.nativeErrorCode(), result.text());
}

ResultValue &ResultValue::setMsg(const QVariant &value)
{
    dPvt();
    p.clear();
    if (value.isValid()) {
        p.returnType = MessageType::None;
        p.returnCode = QVariant();
        p.returnText = p.variantConvertToText(value);
        p.makeResult();
    }
    return *this;
}

ResultValue &ResultValue::setInformation(const QVariant &value)
{
    dPvt();
    p.clear();
    if (value.isValid()) {
        p.returnType = Information;
        p.returnCode = p.variantConvertToCode(value);
        p.returnText = p.variantConvertToText(value);
        p.makeResult();
    }
    return *this;
}

ResultValue &ResultValue::setWarning()
{
    if (this->isOk())
        return this->setWarning(tr("Unknow error"));

    return *this;
}

ResultValue &ResultValue::setWarning(const QVariant &value)
{
    dPvt();
    p.clear();
    if (value.isValid()) {
        p.returnType = Warning;
        p.returnCode = p.variantConvertToCode(value);
        p.returnText = p.variantConvertToText(value);
        p.makeResult();
    }
    return *this;
}

ResultValue &ResultValue::setValidation()
{
    if (this->isOk())
        return this->setValidation(tr("Invalid information"));

    return *this;
}

ResultValue &ResultValue::setValidation(const QVariant &value)
{
    dPvt();
    p.clear();
    if (value.isValid()) {
        p.returnType = Validation;
        p.returnCode = p.variantConvertToCode(value);
        p.returnText = p.variantConvertToText(value);
        p.makeResult();
    }
    return *this;
}

ResultValue &ResultValue::setValidation(const ResultValue &lr)
{
    if(!lr){
        (*this) << lr;
        return *this;
    }
    return this->setValidation();
}

ResultValue &ResultValue::setResponse(const QVariant &value)
{
    dPvt();
    switch (qTypeId(value)) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    {
        auto vHash=value.toHash();
        //auto qt_status_code=vHash.value(qsl("qt_status_code")).toInt();
        auto status_code=vHash.value(qsl("status_code")).toInt();
        auto response_body=vHash.value(qsl("response_body"));
        auto reason_phrase=vHash.value(qsl("reason_phrase")).toString().trimmed();
        if(!statusCodeSuccessList.contains(status_code)){
            QStm::ResultInfo resultInfo;
            QVariant vResultInfo;
            switch (qTypeId(response_body)) {
            case QMetaType_QVariantHash:
            case QMetaType_QVariantMap:
            {
                auto vHash=response_body.toHash();
                vResultInfo=vHash.value(qsl("resultInfo"));
                break;
            }
            default:
                vResultInfo=vHash.value(qsl("resultInfo"));
                break;
            }

            resultInfo.fromVar(vResultInfo);
            if(resultInfo.errors().isEmpty()){
                if(reason_phrase.isEmpty())
                    resultInfo.errors()<<reason_phrase;
            }
            if(!resultInfo.errors().isEmpty())
                reason_phrase=resultInfo.errors().first().toString().trimmed();
            this->setCode(status_code, reason_phrase);
            p.resultVariant=response_body;
            p.resultInfo.fromResultInfo(resultInfo);
        }
        break;
    }
    default:
        break;
    }
    return *this;
}

ResultValue &ResultValue::setUnauthorized()
{
    return this->setUnauthorized(tr("Unauthorized"));
}

ResultValue &ResultValue::setUnauthorized(const QVariant &value)
{
    dPvt();
    p.clear();
    if (value.isValid()) {
        p.returnType = Unauthorized;
        p.returnCode = p.variantConvertToCode(value);
        p.returnText = p.variantConvertToText(value);
        p.makeResult();
    }
    return *this;
}

ResultValue &ResultValue::setUnauthorized(const ResultValue &lr)
{
    if (!lr){
        (*this) << lr;
        return *this;
    }
    return this->setUnauthorized();
}

ResultValue &ResultValue::setNotImplemented()
{
    return this->setBadRequest(tr("Not implemented"));
}

ResultValue &ResultValue::setNotImplemented(const QVariant &value)
{
    dPvt();
    p.clear();
    if (value.isValid()) {
        p.returnType = NotImplemented;
        p.returnCode = p.variantConvertToCode(value);
        p.returnText = p.variantConvertToText(value);
        p.makeResult();
    }
    return *this;
}

ResultValue &ResultValue::setNotImplemented(const ResultValue &lr)
{
    if (!lr){
        (*this) << lr;
        return *this;
    }
    return this->setNotImplemented();
}

ResultValue &ResultValue::setBadRequest()
{
    return this->setBadRequest(tr("Bad format"));
}

ResultValue &ResultValue::setBadRequest(const QVariant &value)
{
    dPvt();
    p.clear();
    if (value.isValid()) {
        p.returnType = BadRequest;
        p.returnCode = p.variantConvertToCode(value);
        p.returnText = p.variantConvertToText(value);
        p.makeResult();
    }
    return *this;
}

ResultValue &ResultValue::setBadRequest(const ResultValue &lr)
{
    if (!lr){
        (*this) << lr;
        return *this;
    }
    return this->setBadRequest();
}

ResultValue &ResultValue::setNotFound()
{
    return this->setNotFound(tr("Not found"));
}

ResultValue &ResultValue::setNotFound(const QVariant &value)
{
    dPvt();
    p.clear();
    if (value.isValid()) {
        p.returnType = Notfound;
        p.returnCode = p.variantConvertToCode(value);
        p.returnText = p.variantConvertToText(value);
        p.makeResult();
    }
    return *this;
}

ResultValue &ResultValue::setNotFound(const ResultValue &lr)
{
    if (!lr){
        (*this) << lr;
        return *this;
    }
    return this->setNotFound();
}

ResultValue &ResultValue::setUnsupportedMediaType()
{
    return this->setCritical(tr("Unsupported Media Type"));
}

ResultValue &ResultValue::setUnsupportedMediaType(const QVariant &value)
{
    dPvt();
    p.clear();
    if (value.isValid()) {
        p.returnType = UnsupportedMediaType;
        p.returnCode = p.variantConvertToCode(value);
        p.returnText = p.variantConvertToText(value);
        p.makeResult();
    }
    return *this;
}

ResultValue &ResultValue::setUnsupportedMediaType(const ResultValue &lr)
{
    if (!lr){
        (*this) << lr;
        return *this;
    }
    return this->setUnsupportedMediaType();
}

ResultValue &ResultValue::setCritical()
{
    dPvt();
    if (!this->isCritical()) {
        auto msg = p.returnText.trimmed();
        msg = msg.isEmpty() ? tr("Critical error").toUtf8() : msg;
        this->setCritical(msg);
    }
    return *this;
}

ResultValue &ResultValue::setCritical(const QString &value)
{
    dPvt();
    return p.setCritical(QVariant(), value);
}

ResultValue &ResultValue::setCritical(const QVariantHash &value)
{
    dPvt();
    return p.setCritical(QVariant(), value);
}

ResultValue &ResultValue::setCritical(const QVariantList &value)
{
    dPvt();
    return p.setCritical(QVariant(), value);
}

ResultValue &ResultValue::setCritical(const QSqlError &value)
{
    dPvt();
    p.clear();
    if (value.isValid()) {
        auto nc = value.nativeErrorCode().toUtf8().trimmed();
        auto nt = value.text().toUtf8().trimmed();
        if (!(nc.isEmpty() && nt.isEmpty())) {
            p.returnType = ResultValue::Critical;
            p.returnCode = p.variantConvertToCode(value.nativeErrorCode());
            p.returnText = value.text().toUtf8().trimmed();
            if (!p.returnCode.isValid())
                p.returnCode = p.toMd5(p.returnText);
            p.makeResult();
        }
    }
    return *this;
}

ResultValue &ResultValue::setCritical(const ResultValue &lr)
{
    if (!lr){
        (*this) << lr;
        return *this;
    }
    return this->setCritical();
}

bool ResultValue::isOk() const
{
    dPvt();
    return p.isOk();
}

bool ResultValue::isNotOk() const
{
    return !this->isOk();
}

bool ResultValue::isInformation() const
{
    dPvt();
    return p.returnType == Information;
}

bool ResultValue::isUnauthorized() const
{
    dPvt();
    return p.returnType == Unauthorized;
}

bool ResultValue::isNotfound() const
{
    dPvt();
    return p.returnType == Notfound;
}

bool ResultValue::isBadRequest() const
{
    dPvt();
    return p.returnType;
}

bool ResultValue::isWarning() const
{
    dPvt();
    return p.returnCode.isValid();
}

bool ResultValue::isValidation() const
{
    dPvt();
    return p.returnCode.isValid();
}

bool ResultValue::isCritical() const
{
    dPvt();
    return p.returnType == Critical;
}

QVariantHash ResultValue::data() const
{
    dPvt();
    return p.data;
}

void ResultValue::setData(const QVariantHash &data)
{
    dPvt();
    p.data = data;
}

QVariant ResultValue::stateCode() const
{
    QVariantHash v;
    QVariant code;
    QVariant phrase;
    if (QThread::currentThread()->isInterruptionRequested())
        code = 500; //InternalServerError
    else if (makeArStats.contains(this->returnType()))
        code = makeArStats.value(this->returnType());
    else
        code = 500; //InternalServerError

    phrase = this->returnText().isEmpty() ? QVariant() : this->returnText();

    if (code.isValid())
        v.insert(qbl("code"), code);
    if (phrase.isValid())
        v.insert(qbl("phrase"), phrase);

    return v.isEmpty() ? QVariant() : v;
}

QVariant ResultValue::sc() const
{
    return this->stateCode();
}

ResultValue &ResultValue::setCode(const QVariant &statusCode, const QVariant &reasonPhrase)
{
    if (statusCodeSuccessList.contains(statusCode.toInt())){
        this->setInformation(QVariant());
        return*this;
    }

    const auto &returnType = makeArStats.key(statusCode.toInt());
    if (makeArStats.contains(returnType)) {
        dPvt();
        p.returnType = returnType;
        p.returnCode = p.variantConvertToCode(returnType);
        p.returnText = reasonPhrase.toByteArray();
        if (!p.returnCode.isValid())
            p.returnCode = p.toMd5(p.returnText);
        p.makeResult();
    }
    return *this;
}

QString ResultValue::toString() const
{
    return this->returnText();
}
