#include "./qstm_setting_manager.h"
#include "./private/p_qstm_setting_manager.h"
#include "./qstm_setting_base.h"
#include <QCoreApplication>

namespace QStm {


SettingManager::SettingManager(QObject *parent) : QObject(nullptr)
{
    this->p = new SettingManagerPrv(this);
    if(parent && parent->thread()==this->thread())
        this->setParent(parent);
    dPvt();
    p.parentParent = parent;
    p.load(p.parentParent);
}

SettingManager::SettingManager(const QStringList &settingFileName, QObject *parent)
{
    this->p = new SettingManagerPrv(this);
    if(parent!=nullptr){
        if(parent->thread()==this->thread())
            this->setParent(parent);
    }
    dPvt();
    p.load(settingFileName);
}

SettingManager::SettingManager(const QString &settingFileName, QObject *parent):QObject(parent)
{
    this->p = new SettingManagerPrv(this);
    if(parent!=nullptr){
        if(parent->thread()==this->thread())
            this->setParent(parent);
    }
    dPvt();
    p.load(settingFileName);
}

SettingManager::~SettingManager()
{
    dPvt();delete&p;
}

SettingManager &SettingManager::clear()
{
    dPvt();
    p.clear();
    return*this;
}

SettingManager &SettingManager::insert(SettingBase &value)
{
    dPvt();
    return p.insert(value.toHash());
}

SettingManager &SettingManager::insert(const QVariantHash &value)
{
    dPvt();
    return p.insert(value);
}

SettingBase&SettingManager::setting()
{
    return this->setting(qsl_null);
}

SettingBase&SettingManager::setting(const QString&value)
{
    dPvt();
    const auto name=value.toUtf8();
    return p.settingGetCheck(name);
}

SettingBase *SettingManager::settingClone(const QString &value)
{
    dPvt();
    const auto name=value.toUtf8();
    auto&setting=p.settingGetCheck(name);
    if(setting.isValid()){
        auto _parent=(QThread::currentThread()==this->thread())?this:nullptr;
        auto newSetting=p.settingCreate(_parent);
        newSetting->fromHash(setting.toHash());
        return newSetting;
    }
    return nullptr;
}

QObject *SettingManager::settingCreate(QObject *parent)
{
    Q_UNUSED(parent)
    qFatal("not implemented");
    return nullptr;
}


bool SettingManager::load(const QVariant &settings)
{
    dPvt();
    return p.v_load(settings);
}

bool SettingManager::load(const SettingManager&manager)
{
    dPvt();
    return p.load(manager.toHash());
}

bool SettingManager::load(QObject *settingsObject)
{
    dPvt();
    return p.load(settingsObject);
}

QVariant SettingManager::settingsFileName()const
{
    dPvt();
    return p.settingsFileName;
}

SettingManager &SettingManager::operator<<(SettingBase &value)
{
    return this->insert(value);
}

QVariantHash SettingManager::settingBody() const
{
    dPvt();
    return p.settingBody;
}

const QVariantHash SettingManager::settingBody(const QString &value)
{
    auto&setting=this->setting(value);
    auto vHash=setting.toHash();
    return vHash;
}

QVariantHash SettingManager::arguments() const
{
    dPvt();
    return p.variables.value(qsl("arguments")).toHash();
}

void SettingManager::setArguments(const QVariantHash &value)
{
    dPvt();
    auto arguments=p.variables.value(qsl("arguments")).toHash();
    QHashIterator<QString, QVariant> i(value);
    while (i.hasNext()) {
        i.next();
        auto v=SettingBase::staticParseVariables(i.value());
        arguments.insert(i.key(), v);
    }
    p.variables.insert(qsl("arguments"),arguments);
}

QVariantHash SettingManager::variables() const
{
    dPvt();
    return p.variables;
}

void SettingManager::setVariables(const QVariantHash &value)
{
    dPvt();
    p.variables = value;
}

QVariantHash SettingManager::toHash() const
{
    dPvt();
    return p.toHash();
}

QString SettingManager::rootDir() const
{
    dPvt();
    auto v=p.variables.value(qsl("rootdir")).toString();
    return v;
}

SettingManager &SettingManager::setRootDir(const QString &value)
{
    dPvt();
    p.variables.insert(qsl("rootdir"),value);
    return*this;
}

QVariantHash SettingManager::toMap() const
{
    return this->toHash();
}

}
