#pragma once

#include "./private/p_qstm_base_setting.h"
#include "./qstm_global.h"

namespace QStm {

//!
//! \brief The SettingBase class
//!
//! basic class to configuration
class Q_STM_EXPORT SettingBase:public QStm::BaseSetting{
    Q_OBJECT
    SETTING_OBJECT(SettingBase)
public:
    //!
    //! \brief SettingBase
    //! \param parent
    //!
    Q_INVOKABLE explicit SettingBase(QObject*parent=nullptr);

    //!
    //! \brief ~SettingBase
    //!
    ~SettingBase();
public:

    //!
    //! \brief url
    //! \return
    //!
    virtual QVariant url() const;

    //!
    //! \brief service
    //! \return
    //!
    virtual QString service() const;

    //!
    //! \brief setService
    //! \param value
    //!
    virtual void setService(const QString &value);


    //!
    //! \brief headers
    //! \return
    //!
    virtual QVariantHash headers() const;

    //!
    //! \brief setHeaders
    //! \param value
    //!
    virtual void setHeaders(const QVariantHash &value);

    //!
    //! \brief protocol
    //! \return
    //!
    virtual QVariant protocol() const;

    //!
    //! \brief setProtocol
    //! \param value
    //!
    virtual void setProtocol(const QVariant &value);

    //!
    //! \brief method
    //! \return
    //!
    virtual QString method() const;

    //!
    //! \brief setMethod
    //! \param value
    //!
    virtual void setMethod(const QString &value);

    //!
    //! \brief driverName
    //! \return
    //!
    virtual QString driverName() const;

    //!
    //! \brief setDriverName
    //! \param value
    //!
    virtual void setDriverName(const QString &value);

    //!
    //! \brief hostName
    //! \return
    //!
    virtual QString hostName() const;

    //!
    //! \brief setHostName
    //! \param value
    //!
    virtual void setHostName(const QString &value);

    //!
    //! \brief userName
    //! \return
    //!
    virtual QString userName() const;

    //!
    //! \brief setUserName
    //! \param value
    //!
    virtual void setUserName(const QString &value);

    //!
    //! \brief password
    //! \return
    //!
    virtual QString password() const;

    //!
    //! \brief setPassword
    //! \param value
    //!
    virtual void setPassword(const QString &value);

    //!
    //! \brief port
    //! \return
    //!
    virtual int port() const;

    //!
    //! \brief setPort
    //! \param value
    //!
    virtual void setPort(int value);

    //!
    //! \brief route
    //! \return
    //!
    virtual QVariant route() const;

    //!
    //! \brief setRoute
    //! \param value
    //!
    virtual void setRoute(const QVariant &value);

    //!
    //! \brief routeList
    //! \return
    //!
    virtual QVariantList routeList() const;

    //!
    //! \brief path
    //! \return
    //!
    virtual QString path() const;

    //!
    //! \brief setPath
    //! \param value
    //!
    virtual void setPath(const QString &value);

    //!
    //! \brief parameters
    //! \return
    //!
    virtual QVariantHash parameters() const;

    //!
    //! \brief setParameters
    //! \param value
    //!
    virtual void setParameters(const QVariantHash &value);

    //!
    //! \brief body
    //! \return
    //!
    virtual QVariant body() const;

    //!
    //! \brief setBody
    //! \param value
    //!
    virtual void setBody(const QVariant &value);

    //!
    //! \brief cacheInterval
    //! \return
    //!
    virtual int cacheInterval() const;

    //!
    //! \brief setCacheInterval
    //! \param value
    //!
    virtual void setCacheInterval(const QVariant &value);

    //!
    //! \brief cacheCleanup
    //! \return
    //!
    virtual bool cacheCleanup() const;

    //!
    //! \brief setCacheCleanup
    //! \param value
    //!
    virtual void setCacheCleanup(const QVariant &value);

    //!
    //! \brief cacheCleanupInterval
    //! \return
    //!
    virtual int cacheCleanupInterval() const;

    //!
    //! \brief setCacheCleanupInterval
    //! \param value
    //!
    virtual void setCacheCleanupInterval(const QVariant &value);

public:
    void*p=nullptr;
};


}
