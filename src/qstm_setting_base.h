#pragma once

#include "./private/p_qstm_base_setting.h"
#include "./qstm_global.h"

namespace QStm {

//!
//! \brief The SettingBase class
//!
//! basic class to configuration
class Q_STM_EXPORT SettingBase:public QStm::SettingBaseTemplate<SettingBase>
{
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
    virtual SettingBase &setService(const QString &value);

    //!
    //! \brief headers
    //! \return
    //!
    virtual QVariantHash headers() const;

    //!
    //! \brief setHeaders
    //! \param value
    //!
    virtual SettingBase &setHeaders(const QVariantHash &value);

    //!
    //! \brief protocol
    //! \return
    //!
    virtual QVariant protocol() const;

    //!
    //! \brief setProtocol
    //! \param value
    //!
    virtual SettingBase &setProtocol(const QVariant &value);

    //!
    //! \brief method
    //! \return
    //!
    virtual QString method() const;

    //!
    //! \brief setMethod
    //! \param value
    //!
    virtual SettingBase &setMethod(const QString &value);

    //!
    //! \brief driverName
    //! \return
    //!
    virtual QString driverName() const;

    //!
    //! \brief setDriverName
    //! \param value
    //!
    virtual SettingBase &setDriverName(const QString &value);

    //!
    //! \brief hostName
    //! \return
    //!
    virtual QString hostName() const;

    //!
    //! \brief setHostName
    //! \param value
    //!
    virtual SettingBase &setHostName(const QString &value);

    //!
    //! \brief userName
    //! \return
    //!
    virtual QString userName() const;

    //!
    //! \brief setUserName
    //! \param value
    //!
    virtual SettingBase &setUserName(const QString &value);

    //!
    //! \brief password
    //! \return
    //!
    virtual QString password() const;

    //!
    //! \brief setPassword
    //! \param value
    //!
    virtual SettingBase &setPassword(const QString &value);

    //!
    //! \brief port
    //! \return
    //!
    virtual int port() const;

    //!
    //! \brief setPort
    //! \param value
    //!
    virtual SettingBase &setPort(int value);

    //!
    //! \brief route
    //! \return
    //!
    virtual QVariant route() const;

    //!
    //! \brief setRoute
    //! \param value
    //!
    virtual SettingBase &setRoute(const QVariant &value);

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
    virtual SettingBase &setPath(const QString &value);

    //!
    //! \brief parameters
    //! \return
    //!
    virtual QVariantHash parameters() const;

    //!
    //! \brief setParameters
    //! \param value
    //!
    virtual SettingBase &setParameters(const QVariantHash &value);

    //!
    //! \brief body
    //! \return
    //!
    virtual QVariant body() const;

    //!
    //! \brief setBody
    //! \param value
    //!
    virtual SettingBase &setBody(const QVariant &value);

    //!
    //! \brief cacheInterval
    //! \return
    //!
    virtual int cacheInterval() const;

    //!
    //! \brief setCacheInterval
    //! \param value
    //!
    virtual SettingBase &setCacheInterval(const QVariant &value);

    //!
    //! \brief cacheCleanup
    //! \return
    //!
    virtual bool cacheCleanup() const;

    //!
    //! \brief setCacheCleanup
    //! \param value
    //!
    virtual SettingBase &setCacheCleanup(const QVariant &value);

    //!
    //! \brief cacheCleanupInterval
    //! \return
    //!
    virtual int cacheCleanupInterval() const;

    //!
    //! \brief setCacheCleanupInterval
    //! \param value
    //!
    virtual SettingBase &setCacheCleanupInterval(const QVariant &value);

signals:
    void serviceChanged();
    void headersChanged();
    void protocolChanged();
    void methodChanged();
    void driverNameChanged();
    void hostNameChanged();
    void userNameChanged();
    void passwordChanged();
    void portChanged();
    void routeChanged();
    void pathChanged();
    void parametersChanged();
    void bodyChanged();
    void cacheIntervalChanged();
    void cacheCleanupChanged();
    void cacheCleanupIntervalChanged();
private:
    void*p=nullptr;
};


}
