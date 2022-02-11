#pragma once

#include "../qstm_setting_manager.h"
#include "../qstm_util_variant.h"
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QStringList>
#include <QMetaMethod>
#include <QMetaProperty>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

namespace QStm {

#define dPvt()\
    auto&p = *reinterpret_cast<SettingManagerPrv*>(this->p)

class SettingManagerPrv{
public:
    QVariant settingsFileName;
    SettingBase settingsDefault;
    QVariantHash settingBody;
    QVariantHash variables;
    QHash<QString, SettingBase*> settings;
    SettingManager*parent=nullptr;
    QObject*parentParent=nullptr;

    explicit SettingManagerPrv(SettingManager*parent);

    virtual ~SettingManagerPrv();

    bool isLoaded();

    bool isEmpty();

    void clear();

    QVariantHash toHash();

    QByteArray settingNameAdjust(const QString&settingName);

    SettingBase&settingGetCheck(const QByteArray&settingName);

    SettingBase*settingCreate(QObject*parent);

    SettingManager &insert(const QVariantHash &value);

    bool v_load(const QVariant &v);

    bool load(QObject *settingsObject);

    bool load(const QStringList &settingsFileName);

    bool load(const QString &fileName);

    bool load(const QVariantHash &settingsBody);

};

}
