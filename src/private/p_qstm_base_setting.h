#pragma once

#include "./qstm_object.h"
#include <QVariant>
#include <QVariantHash>

namespace QStm {

#define SETTING_OBJECT(BaseClass)\
public:\
BaseClass&operator=(const BaseClass&value)\
{\
    this->fromSetting(value);\
    return*this;\
}\
BaseClass&operator=(const QVariant&value)\
{\
    this->fromVariant(value);\
    return*this;\
}\
BaseClass&operator=(const QVariantMap&value)\
{\
    this->fromMap(value);\
    return*this;\
}\
BaseClass&operator=(const QVariantHash&value)\
{\
    this->fromHash(value);\
    return*this;\
}\
BaseClass&operator+=(const QVariant&value){\
    this->mergeVariant(value);\
    return*this;\
}\
BaseClass&operator+=(const QVariantMap&value)\
{\
    this->mergeVariant(value);\
    return*this;\
}\
BaseClass&operator+=(const QVariantHash&value)\
{\
    this->mergeVariant(value);\
    return*this;\
}\
BaseClass&operator<<(const QVariant&value){\
    this->mergeVariant(value);\
    return*this;\
}\
Q_PROPERTY(QString      identification          READ identification       WRITE setIdentification     )\
Q_PROPERTY(QVariantHash variables               READ variables            WRITE setVariables          )\
Q_PROPERTY(bool         enabled                 READ enabled              WRITE setEnabled            )\
Q_PROPERTY(QString      name                    READ name                 WRITE setName               )\
Q_PROPERTY(QString      memoryLimit             READ memoryLimit          WRITE setMemoryLimit        )\
Q_PROPERTY(QVariant     activityLimit           READ activityLimit        WRITE setActivityLimit      )\
Q_PROPERTY(QVariant     activityInterval        READ activityInterval     WRITE setActivityInterval   )\
Q_PROPERTY(QVariant     activityThread          READ activityThread       WRITE setActivityThread     )

/**
 * @brief The BaseSetting struct
 */
class Q_STM_EXPORT BaseSetting:public QStm::Object{
    Q_OBJECT
    SETTING_OBJECT(BaseSetting)
public:
    Q_INVOKABLE explicit BaseSetting(QObject*parent=nullptr);
    Q_INVOKABLE ~BaseSetting();

    /**
     * @brief print
     */
    virtual void print() const;

    /**
     * @brief parseVariables
     * @param v
     * @return
     */
    QVariant parseVariables(const QVariant &v) const;

    /**
     * @brief staticParseVariables
     * @param v
     * @return
     */
    static const QVariant staticParseVariables(const QVariant &v);

    /**
     * @brief variable
     * @param v
     * @return
     */
    QVariant variable(const QString&v) const;

    /**
     * @brief parseAlpha
     * @param v
     * @return
     */
    static const QVariant parseAlpha(const QVariant&v);

    /**
     * @brief parseNumber
     * @param v
     * @return
     */
    static const QVariant parseNumber(const QVariant&v);

    /**
     * @brief parseInterval
     * @param v
     * @return
     */
    static const QVariant parseInterval(const QVariant&v);

    /**
     * @brief parseInterval
     * @param v
     * @param interval
     * @return
     */
    static const QVariant parseInterval(const QVariant&v, const QVariant &interval);

    /**
     * @brief staticVariables
     * @return
     */
    const QVariantHash &staticVariables();

    /**
     * @brief setStaticVariables
     * @param v
     */
    void setStaticVariables(const QVariantHash&v);

    /**
     * @brief macth
     * @param name
     * @return
     */
    virtual bool macth(const QString&name);


    /**
     * @brief clear
     */
    virtual void clear();

    /**
     * @brief isValid
     * @return
     */
    virtual bool isValid() const;

    /**
     * @brief toMap
     * @return
     */
    virtual QVariantMap toMap() const;

    /**
     * @brief toHash
     * @return
     */
    virtual QVariantHash toHash() const;

    /**
     * @brief fromSetting
     * @param setting
     * @return
     */
    virtual bool fromSetting(const BaseSetting &v);

    /**
     * @brief fromHash
     * @param map
     * @return
     */
    virtual bool fromHash(const QVariantHash &v);

    /**
     * @brief fromMap
     * @param map
     * @return
     */
    virtual bool fromMap(const QVariantMap &v);

    /**
     * @brief fromVariant
     * @param map
     * @return
     */
    virtual bool fromVariant(const QVariant &v);

    /**
     * @brief mergeHash
     * @param map
     * @return
     */
    virtual bool mergeHash(const QVariantHash &v);

    /**
     * @brief mergeMap
     * @param v
     * @return
     */
    virtual bool mergeMap(const QVariantMap &v);

    /**
     * @brief mergeVariant
     * @param v
     * @return
     */
    virtual bool mergeVariant(const QVariant &v);

public:

    /**
     * @brief identification
     * @return
     */
    virtual QString identification() const;
    virtual void setIdentification(const QString &value);

    /**
     * @brief name
     * @return
     */
    virtual QString name() const;
    virtual void setName(const QString &value);

    /**
     * @brief variables
     * @return
     */
    virtual QVariantHash &variables() const;
    virtual void setVariables(const QVariantHash &value);

    /**
     * @brief enabled
     * @return
     */
    virtual bool enabled() const;
    virtual void setEnabled(const bool &value);

    /**
     * @brief activityLimit
     * @return
     */
    virtual qlonglong activityLimit() const;
    virtual void setActivityLimit(const QVariant &value);

    /**
     * @brief activityInterval
     * @return
     */
    virtual qlonglong activityInterval() const;
    virtual void setActivityInterval(const QVariant &value);

    /**
     * @brief activityInterval
     * @return
     */
    virtual int activityThread() const;
    virtual void setActivityThread(const QVariant &value);

    /**
     * @brief memoryLimit
     * @return
     */
    virtual qlonglong memoryLimit() const;
    virtual void setMemoryLimit(const QVariant &value);

private:
    void*p=nullptr;
};

static const auto defaultLimit="1y";//1 ano
static const auto defaultInterval="1m";//1minute
static const auto defaultThreadCount=QThread::idealThreadCount();

}
