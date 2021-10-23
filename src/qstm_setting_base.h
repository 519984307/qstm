#pragma once

#include "./private/p_qstm_base_setting.h"
#include "./qstm_global.h"

namespace QStm {

/**
 * @brief The SettingBase struct
 */
class Q_STM_EXPORT SettingBase:public QStm::BaseSetting{
    Q_OBJECT
    SETTING_OBJECT(SettingBase)
public:
    Q_INVOKABLE explicit SettingBase(QObject*parent=nullptr);
    Q_INVOKABLE ~SettingBase();
public:

    /**
     * @brief url
     * @return
     */
    virtual QVariant url() const;

    /**
     * @brief service
     * @return
     */
    virtual QString service() const;
    virtual void setService(const QString &value);


    /**
     * @brief headers
     * @return
     */
    virtual QVariantHash headers() const;
    virtual void setHeaders(const QVariantHash &value);

    /**
     * @brief protocol
     * @return
     */
    virtual QVariant protocol() const;
    virtual void setProtocol(const QVariant &value);

    /**
     * @brief method
     * @return
     */
    virtual QString method() const;
    virtual void setMethod(const QString &value);

    /**
     * @brief driverName
     * @return
     */
    virtual QString driverName() const;
    virtual void setDriverName(const QString &value);

    /**
     * @brief hostName
     * @return
     */
    virtual QString hostName() const;
    virtual void setHostName(const QString &value);

    /**
     * @brief userName
     * @return
     */
    virtual QString userName() const;
    virtual void setUserName(const QString &value);

    /**
     * @brief password
     * @return
     */
    virtual QString password() const;
    virtual void setPassword(const QString &value);

    /**
     * @brief port
     * @return
     */
    virtual int port() const;
    virtual void setPort(int value);

    /**
     * @brief route
     * @return
     */
    virtual QVariant route() const;
    virtual void setRoute(const QVariant &value);
    virtual QVariantList routeList() const;

    /**
     * @brief path
     * @return
     */
    virtual QString path() const;
    virtual void setPath(const QString &value);

    /**
     * @brief parameters
     * @return
     */
    virtual QVariantHash parameters() const;
    virtual void setParameters(const QVariantHash &value);

    /**
     * @brief body
     * @return
     */
    virtual QVariant body() const;
    virtual void setBody(const QVariant &value);

    /**
     * @brief cacheInterval
     * @return
     */
    virtual int cacheInterval() const;
    virtual void setCacheInterval(const QVariant &value);

    /**
     * @brief cacheCleanup
     * @return
     */
    virtual bool cacheCleanup() const;
    virtual void setCacheCleanup(const QVariant &value);

    /**
     * @brief cacheCleanupInterval
     * @return
     */
    virtual int cacheCleanupInterval() const;
    virtual void setCacheCleanupInterval(const QVariant &value);

public:
    void*p=nullptr;
};


}
