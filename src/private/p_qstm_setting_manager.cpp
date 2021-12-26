#include "./p_qstm_setting_manager.h"

namespace QStm {

SettingManagerPrv::SettingManagerPrv(SettingManager *parent):settingsDefault(parent)
{
    this->parent=parent;
}

SettingManagerPrv::~SettingManagerPrv()
{
    this->clear();
}

bool SettingManagerPrv::isLoaded()
{
    QHashIterator<QString, SettingBase*> i(this->settings);
    while (i.hasNext()) {
        i.next();
        if(i.key().trimmed().isEmpty())
            continue;
        auto&v=i.value();
        if(!v->isValid())
            continue;
        return true;
    }
    return false;
}

bool SettingManagerPrv::isEmpty()
{
    QHashIterator<QString, SettingBase*> i(this->settings);
    while (i.hasNext()) {
        i.next();
        auto&v=i.value();
        if(v->isValid())
            return false;
    }
    return true;
}

void SettingManagerPrv::clear()
{
    auto _detail=this->settings.values();
    this->settings.clear();
    qDeleteAll(_detail);
}

QVariantHash SettingManagerPrv::toHash()
{
    QVariantHash map, vServices;
    auto vList=QList<SettingBase*>()<<&this->settingsDefault;
    vList=vList+this->settings.values();
    for(auto&v:vList)
        vServices[v->name()]=v->toHash();
    map[qsl("variables")]=this->variables;
    map[qsl("services")]=vServices;
    return map;
}

QByteArray SettingManagerPrv::settingNameAdjust(const QString &settingName)
{
    auto setting=settingName.trimmed();
    return setting.toUtf8();
}

QStm::SettingBase &SettingManagerPrv::settingGetCheck(const QByteArray &settingName)
{
    auto name=this->settingNameAdjust(settingName);
    auto ___return=settings.value(name);
    if(___return==nullptr){
        ___return=this->settingCreate(this->parent);
        settings.insert(name, ___return);
    }
    return*___return;
}

QStm::SettingBase *SettingManagerPrv::settingCreate(QObject *parent)
{
    auto object=this->parent->settingCreate(parent);
    if(object!=nullptr){
        auto setting=dynamic_cast<SettingBase*>(object);
        if(setting==nullptr)
            delete object;
        return setting;
    }
    return nullptr;
}

QStm::SettingManager &SettingManagerPrv::insert(const QVariantHash &value)
{
    auto&p=*this;
    QVariantHash vValue=value;
    if(vValue.isEmpty())
        return*this->parent;

    auto name=vValue.value(qsl("name")).toByteArray().trimmed();
    if(name.isEmpty())
        return*this->parent;

    auto setting=p.settings.value(name);
    if(setting!=nullptr)
        setting->deleteLater();

    static auto l=QStringList{qsl_fy(activityLimit), qsl_fy(activityInterval)};
    for(auto&property:l){
        auto v=vValue.value(property);
        if(v.isValid() && v.toLongLong()<=0){
            v=SettingBase::parseInterval(v);
            vValue[property]=v;
        }
    }
    setting=this->settingCreate(this->parent);
    setting->fromHash(vValue);
    setting->setName(name);
    p.settings.insert(setting->name(), setting);
    return*this->parent;
}

bool SettingManagerPrv::v_load(const QVariant &v)
{
    switch (qTypeId(v)) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return this->load(v.toStringList());
    case QMetaType_QVariantMap:
    case QMetaType_QVariantHash:
        return this->load(v.toHash());
    default:
        return this->load(v.toString());
    }
}

bool SettingManagerPrv::load(QObject *settingsObject)
{
    auto&p=*this;
    if(settingsObject==nullptr)
        return false;

    auto metaObject=settingsObject->metaObject();
    for(int methodIndex = 0; methodIndex < metaObject->methodCount(); ++methodIndex) {
        auto metaMethod = metaObject->method(methodIndex);
        if(metaMethod.parameterCount()>0)
            continue;

        auto methodName=QString(metaMethod.name()).toLower().trimmed();
        static auto staticNames=QStringList{qsl_fy(settingsfilename),qsl_fy(settings_server),qsl_fy(settingsserver)};
        if(!staticNames.contains(methodName))
            continue;
        QVariant invokeReturn;
        auto argReturn=Q_RETURN_ARG(QVariant, invokeReturn);
        if(!metaMethod.invoke(settingsObject, argReturn))
            continue;
        return p.v_load(invokeReturn);
    }
    return false;
}

bool SettingManagerPrv::load(const QStringList &settingsFileName)
{
    QVariantList vList;
    auto&p=*this;
    for(auto&fileName:settingsFileName){
        QFile file(fileName);
        if(fileName.isEmpty()){
            continue;
        }

        if(!file.exists()){
#if Q_RPC_LOG
            sWarning()<<qsl("file not exists %1").arg(file.fileName());
#endif
            continue;
        }

        if(!file.open(QFile::ReadOnly)){
#if Q_RPC_LOG
            sWarning()<<qsl("%1, %2").arg(file.fileName(), file.errorString());
#endif
            continue;
        }

        auto bytes=file.readAll();
        file.close();
        QJsonParseError*error=nullptr;
        auto doc=QJsonDocument::fromJson(bytes, error);
        if(error!=nullptr){
#if Q_RPC_LOG
            sWarning()<<qsl("%1, %2").arg(file.fileName(), error->errorString());
#endif
            continue;
        }

        if(doc.object().isEmpty()){
#if Q_RPC_LOG
            sWarning()<<qsl("object is empty, %1").arg(file.fileName());
#endif
            continue;
        }

        auto map=doc.object().toVariantHash();
        if(map.isEmpty())
            continue;
        vList<<map;
    }
    Q_DECLARE_VU;
    auto vMap=vu.vMerge(vList).toHash();
    if(p.load(vMap))
        this->settingsFileName=settingsFileName;
    else
        this->settingsFileName.clear();
    return p.isLoaded();
}

bool SettingManagerPrv::load(const QString &fileName)
{
    auto&p=*this;
    QFile file(fileName);
    if(fileName.trimmed().isEmpty()){
#if Q_RPC_LOG
        sWarning()<<qsl("not file settings");
#endif
        return false;
    }

    if(!file.exists()){
#if Q_RPC_LOG
        sWarning()<<qsl("file not exists %1").arg(file.fileName());
#endif
        return false;
    }

    if(!file.open(QFile::ReadOnly)){
#if Q_RPC_LOG
        sWarning()<<qsl("%1, %2").arg(file.fileName(), fileName);
#endif
        return false;
    }

    auto bytes=file.readAll();
    file.close();
    QJsonParseError*error=nullptr;
    auto doc=QJsonDocument::fromJson(bytes, error);
    if(error!=nullptr){
#if Q_RPC_LOG
        sWarning()<<qsl("%1, %2").arg(file.fileName(), error->errorString());
#endif
        return false;
    }

    if(doc.object().isEmpty()){
#if Q_RPC_LOG
        sWarning()<<qsl("object is empty, %1").arg(file.fileName());
#endif
        return false;
    }

    auto map=doc.object().toVariantHash();
    if(map.contains(qsl("services"))){
#if Q_RPC_LOG
        sWarning()<<qsl("tag services not exists, %1").arg(file.fileName());
#endif
        return false;
    }

    return p.load(map);
}

bool SettingManagerPrv::load(const QVariantHash &settingsBody)
{
    auto&p=*this;
    p.settingBody=settingsBody;

    const auto settings=settingsBody.contains(qsl("services"))?settingsBody.value(qsl("services")).toHash():p.settingBody;

    {//variables
        this->variables=settingsBody[qsl("variables")].toHash();

        auto rootDir=settingsBody[qsl("rootdir")].toString().trimmed();
        this->variables[qsl("rootdir")]=rootDir.isEmpty()?qsl("%HOME/$APPNAME"):rootDir;

        QVariantHash arguments;
        auto varguments=settingsBody[qsl("arguments")];
        if(varguments.isNull() || !varguments.isValid())
            varguments=this->variables[qsl("arguments")];
        else
            this->variables[qsl("arguments")]=varguments;

        switch (qTypeId(varguments)) {
        case QMetaType_QVariantHash:
        case QMetaType_QVariantMap:
        {
            QHashIterator<QString, QVariant> i(varguments.toHash());
            while (i.hasNext()) {
                i.next();
                arguments.insert(i.key().toLower(), i.value());
            }
            break;
        }
        case QMetaType_QVariantList:
        case QMetaType_QStringList:
        {
            for(auto&v:varguments.toList()){
                auto l=v.toString().split(qsl("="));
                if(l.isEmpty())
                    continue;

                if(l.size()==1){
                    auto key=l.first();
                    auto value=l.last();
                    arguments.insert(key,value);
                }
                else{
                    auto key=l.first().toLower();
                    auto value=l.last();
                    arguments.insert(key,value);
                }
            }
        }
        default:
            break;
        }
        this->parent->setArguments(arguments);
    }

    QVariantHash defaultVariables({{qsl_fy(hostName), qsl_fy(SERVICE_HOST)}});
    QVariantHash defaultValues;
    if(!defaultVariables.isEmpty()){
        QHashIterator<QString, QVariant> i(defaultVariables);
        while (i.hasNext()) {
            i.next();
            auto env = i.value().toByteArray();
            auto v = QByteArray(getenv(env)).trimmed();
            if(v.isEmpty())
                v = QByteArray(getenv(env.toLower())).trimmed();
            if(!v.isEmpty())
                defaultValues.insert(i.key(),v);
        }
    }

    auto defaultSetting=settings.value(qsl("default")).toHash();

    p.settingsDefault=defaultSetting;

    if(settings.contains(qsl("hostName")) && settings.contains(qsl("port"))){
        this->insert(settings);
        return this->isLoaded();
    }

    QHashIterator<QString, QVariant> i(settings);
    while (i.hasNext()) {
        i.next();
        auto value=i.value().toHash();
        value[qsl("name")]=i.key().trimmed();
        {
            QHashIterator<QString, QVariant> i(defaultValues);
            while (i.hasNext()) {
                i.next();
                if(!value.contains(i.key()))
                    value.insert(i.key(), i.value());
            }
        }

        {
            QHashIterator<QString, QVariant> i(defaultSetting);
            while (i.hasNext()) {
                i.next();
                if(!value.contains(i.key()))
                    value.insert(i.key(), i.value());
            }
        }

        this->insert(value);

    }
    return this->isLoaded();
}

}
