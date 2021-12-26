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

static const MakeArStats &makeArStats = __makeArStats();

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

    explicit ResultValuePvt(ResultValue *parent){
        this->parent = parent;
    }
    virtual ~ResultValuePvt() {}

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
        const auto isOk=this->isOk();
        if (!isOk) {
            this->data = this->toHash();
            this->returnHash = this->toMd5(this->variantConvertToCode(data));
            this->data = this->toHash();
            {
                if (this->returnCode.isValid())
                    sWarning() << this->toString();
                else if (this->returnCode.isValid())
                    sWarning() << this->toString();

                consts.staticThreadLocker.lock();
                consts.staticThreadError[QThread::currentThread()]=this->returnHash;
                consts.staticThreadLocker.unlock();
            }
            QList<ResultValue *> listParentResultValue;
            auto pp = dynamic_cast<QStm::Object *>(this->parent->parent());
            while (pp != nullptr) {
                listParentResultValue.insert(0, &pp->lastResult());
                pp = dynamic_cast<QStm::Object *>(pp->parent());
            }
            for (auto &result : listParentResultValue) {
                auto pvt = static_cast<ResultValuePvt *>(result->p);
                if (pvt != nullptr) {
                    pvt->read(this);
                }
            }

        }
        this->resultInfo.clearErrors();
        resultInfo.setSuccess(isOk);
        auto&msgs=resultInfo.errors();
        msgs.clear();
        msgs.append(this->parent->returnText());
        if(!isOk){
            auto&msgs=resultInfo.messages();
            msgs.clear();
            msgs.append(this->parent->returnText());
        }
    }
    bool isOk()
    {
        if (this->returnCode.isValid())
            return false;

        if (this->returnCode.isValid())
            return false;

        if (QThread::currentThread()->isInterruptionRequested())
            return false;

        return this->returnHash.trimmed().isEmpty();
    }

    const QString toString()
    {
        if (this->isOk())
            return qsl_null;

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
        if (qTypeId(value) == QMetaType_Double || qTypeId(value) == QMetaType_Int
            || qTypeId(value) == QMetaType_UInt || qTypeId(value) == QMetaType_LongLong
            || qTypeId(value) == QMetaType_ULongLong)
            return value.toByteArray();

        if (qTypeId(value) == QMetaType_QString || qTypeId(value) == QMetaType_QByteArray
            || qTypeId(value) == QMetaType_QChar) {
            auto code = value.toByteArray().trimmed();
            if ((code.isEmpty()))
                return {};

            return code; //QCryptographicHash::hash(code, QCryptographicHash::Md5).toHex();
        }

        {
            QStringList list;
            if (qTypeId(value) == QMetaType_QStringList) {
                list = value.toStringList();
            }
            else if (qTypeId(value) == QMetaType_QVariantList) {
                for (auto &v : value.toList())
                    list << v.toByteArray();
            }
            else if (qTypeId(value) == QMetaType_QVariantHash || qTypeId(value) == QMetaType_QVariantMap) {
                VariantUtil u;
                auto map = u.toHash(value);
                QStringList list;
                Q_V_HASH_ITERATOR(map){
                    i.next();
                    list << i.key() << qbl(".") << i.value().toByteArray();
                }
            }
            return QCryptographicHash::hash(list.join('.').toUtf8(), QCryptographicHash::Md5)
                .toHex();
        }
        return {};
    }


    static QString variantConvertToText(const QVariant &value)
    {
        if (value.isValid()) {
            QStringList list;
            if ((qTypeId(value) == QMetaType_Double || qTypeId(value) == QMetaType_Int
                 || qTypeId(value) == QMetaType_UInt || qTypeId(value) == QMetaType_LongLong
                 || qTypeId(value) == QMetaType_ULongLong))
                return qsl("%1: %2").arg(qapp.tr("Error value"), value.toString());
            else if (qTypeId(value) == QMetaType_QStringList) {
                list = value.toStringList();
            }
            else if (qTypeId(value) == QMetaType_QVariantList) {
                for (auto &v : value.toList())
                    list << v.toByteArray();
            }
            else if (qTypeId(value) == QMetaType_QVariantMap) {
                QStringList list;
                Q_V_HASH_ITERATOR(value.toHash()){
                    i.next();
                    list << i.key() << qbl("==") << i.value().toByteArray();
                }
            }
            else if (qTypeId(value) == QMetaType_QVariantHash) {
                QStringList list;
                Q_V_HASH_ITERATOR(value.toHash()){
                    i.next();
                    list << i.key() << qbl("==") << i.value().toByteArray();
                }
            }
            else {
                list << value.toString().trimmed();
            }
            return list.join(qbl("\n")).toUtf8();
        }
        return {};
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

QVariantHash ResultValue::resultMap() const
{
    dPvt();
    return p.resultVariant.toHash();
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
    if(qTypeId(v)==QMetaType_QVariantMap || qTypeId(v)==QMetaType_QVariantHash)
        return qvl_null<<v;

    return p.resultVariant.toList();
}

QVariantList ResultValue::resultToList() const
{
    dPvt();
    auto &v = p.resultVariant;
    if (qTypeId(v) == QMetaType_QVariantList || qTypeId(v) == QMetaType_QStringList)
        return v.toList();

    if (v.isValid())
        return qvl_null << v;

    return qvl_null;
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
    if (!lr)
        (*this) << lr;
    else
        return this->setValidation();
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
    if (!lr)
        (*this) << lr;
    else
        return this->setUnauthorized();
    return *this;
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
    if (!lr)
        (*this) << lr;
    else
        return this->setNotImplemented();
    return *this;
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
    if (!lr)
        (*this) << lr;
    else
        return this->setBadRequest();
    return *this;
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
    if (!lr)
        (*this) << lr;
    else
        return this->setNotFound();
    return *this;
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
    if (!lr)
        (*this) << lr;
    else
        return this->setUnsupportedMediaType();
    return *this;
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
    if (!lr)
        (*this) << lr;
    else
        return this->setCritical();
    return *this;
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
    static auto statusCodeList = QVector<int>() << 200 << 201 << 202;
    if (statusCodeList.contains(statusCode.toInt()))
        this->setInformation(QVariant());
    else {
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
    }
    return *this;
}

QString ResultValue::toString() const
{
    return this->returnText();
}
