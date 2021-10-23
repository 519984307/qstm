#pragma once

#include "./qstm_global.h"
#include "./qstm_setting_base.h"
#include <QSettings>

namespace QStm {

#define Q_SETTING_MANAGER_REPLACE_METHODS(Manager,Setting)                                                                                          \
public:                                                                                                                                             \
    Q_INVOKABLE explicit Manager(QObject *parent = nullptr) : QStm::SettingManager(parent)                                                          \
    {                                                                                                                                               \
    }                                                                                                                                               \
    Q_INVOKABLE explicit Manager(const QStringList&settingFileName, QObject *parent = nullptr):QStm::SettingManager(settingFileName, parent)        \
    {                                                                                                                                               \
    }                                                                                                                                               \
    Q_INVOKABLE explicit Manager(const QString&settingFileName, QObject *parent = nullptr):QStm::SettingManager(settingFileName, parent)            \
    {                                                                                                                                               \
    }                                                                                                                                               \
    Q_INVOKABLE ~Manager()                                                                                                                          \
    {                                                                                                                                               \
    }                                                                                                                                               \
    Setting &setting(){                                                                                                                             \
        auto setting=&QStm::SettingManager::setting();                                                                                              \
        return*dynamic_cast<Setting*>(setting);                                                                                                     \
    }                                                                                                                                               \
    Setting &setting(const QString &value){                                                                                                         \
        auto setting=&QStm::SettingManager::setting(value);                                                                                         \
        return*dynamic_cast<Setting*>(setting);                                                                                                     \
    }                                                                                                                                               \
    Setting *settingClone(const QString &value){                                                                                                    \
        auto setting=QStm::SettingManager::settingClone(value);                                                                                     \
        return dynamic_cast<Setting*>(setting);                                                                                                     \
    }                                                                                                                                               \
    virtual QObject*settingCreate(QObject*parent){                                                                                                  \
        return new Setting(parent);                                                                                                                 \
    }

class Q_STM_EXPORT SettingManager : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit SettingManager(QObject *parent = nullptr);
    Q_INVOKABLE explicit SettingManager(const QStringList&settingFileName, QObject *parent = nullptr);
    Q_INVOKABLE explicit SettingManager(const QString&settingFileName, QObject *parent = nullptr);
    Q_INVOKABLE ~SettingManager();

    /**
     * @brief clear
     */
    virtual SettingManager&clear();

    /**
     * @brief insert
     * @param settingName
     */
    virtual SettingManager&insert(SettingBase &value);
    virtual SettingManager&insert(const QVariantHash &value);

    /**
     * @brief setting
     * @return
     */
    SettingBase &setting();
    SettingBase &setting(const QString &value);
    SettingBase *settingClone(const QString &value);

    /**
     * @brief settingCreate
     * @param parent
     * @return
     */
    virtual QObject *settingCreate(QObject*parent);

    /**
     * @brief load
     * @param settings
     * @return
     */
    virtual bool load(const QVariant&settings);
    virtual bool load(const SettingManager &manager);
    virtual bool load(QObject*settingsObject);

    /**
     * @brief settingsFileName
     * @return
     */
    virtual QVariant settingsFileName() const;

    /**
     * @brief operator <<
     * @param value
     * @return
     */
    SettingManager&operator<<(SettingBase&value);

    /**
     * @brief settingBody
     * @return
     *
     * full settings source
     */
    virtual QVariantHash settingBody() const;
    virtual const QVariantHash settingBody(const QString &value);

    /**
     * @brief arguments
     * @return
     *
     * arguments with settings
     */
    virtual QVariantHash arguments() const;
    virtual void setArguments(const QVariantHash &value);

    /**
     * @brief variables
     * @return
     */
    virtual QVariantHash variables() const;
    virtual void setVariables(const QVariantHash &value);

    /**
     * @brief rootDir
     * @return
     */
    virtual QString rootDir() const;
    virtual SettingManager&setRootDir(const QString &value);

    /**
     * @brief toMap
     * @return
     */
    virtual QVariantHash toMap() const;

    /**
     * @brief toHash
     * @return
     */
    virtual QVariantHash toHash() const;


private:
    void*p=nullptr;
};

}
