#pragma once

#include <QThread>
#include <QDebug>
#include <QByteArray>

#define Q_CONST_V\
    const QVariant&v=QVariant()

#define Q_CONST_D\
    const QDate&v=QDate()

#define Q_CONST_T\
    const QTime&v=QTime()

#define Q_CONST_DT\
    const QDateTime&v=QDateTime()

#define Q_DECLARE_OBJECT(name)

#define Q_DECLARE_VU \
    QStm::VariantUtil vu

#define Q_DECLARE_FU \
    QStm::FormattingUtil fu

#define Q_DECLARE_DU \
    QStm::DateUtil du

#define Q_DECLARE_DBU \
    QStm::DateUtil dbu

#define Q_DECLARE_INSTANCE(Controller)\
public:\
static Controller&instance(){\
    static Controller*static_##Controller=nullptr;\
    if(static_##Controller==nullptr)\
        static_##Controller=new Controller(nullptr);\
    return*static_##Controller;\
}\
static Controller&i(){\
    return instance();\
}

#define Q_LOOP_TIMEOUT(mSecs)\
auto&___##mSecs=mSecs;\
auto ___m_msecs_max_time##mSecs = QDateTime::currentDateTime().addMSecs(___##mSecs);\
while(QDateTime::currentDateTime()<___m_msecs_max_time##mSecs)

#define Q_LOOP_LIMIT(limit)\
for (int loop = 0; loop < limit; ++loop)

#define ___party_1\
    QString::number(qlonglong(QThread::currentThreadId()))+QStringLiteral(":")

#define ___party_2\
    QString(__PRETTY_FUNCTION__).replace(QStringLiteral("virtual"),QLatin1String("")).split(QStringLiteral("(")).first().trimmed()+QStringLiteral(":")

#define cDebug()\
    qDebug()<<___party_1

#define cCritical()\
    qCritical()<<___party_1

#define cInfo()\
    qInfo()<<___party_1

#define cWarning()\
    qWarning()<<___party_1

#define sDebug()\
    qDebug()<<___party_1<<___party_2

#define sCritical()\
    qCritical()<<___party_1<<___party_2

#define sInfo()\
    qInfo()<<___party_1<<___party_2

#define sWarning()\
    qWarning()<<___party_1<<___party_2

#define sDebugMethodStart()\
    qDebug()<<___party_1<<___party_2<<QStringLiteral(":start")

#define sDebugMethodFinish()\
    qDebug()<<___party_1<<___party_2<<QStringLiteral(":finish")

#define v_vl QVariantList()

#define v_sl QStringList()

#define qsl QStringLiteral

#define qbl QByteArrayLiteral

#define qv QVariant

#define qvm QVariantMap

#define qvh QVariantHash

#define qvl QVariantList

#define qvsl QStringList

#define qvm_null QVariantMap()

#define qvh_null QVariantHash()

#define qvl_null QVariantList()

#define qvsl_null QStringList()

#define qv_null QVariant()

#define qsl_null QLatin1String("")

#define qsl_space QStringLiteral(" ")

#define qsl_pipe QStringLiteral("|")

#define qsl_percent QByteArrayLiteral("%")

#define qsl_underline QStringLiteral("_")

#define qbl_null QByteArrayLiteral("")

#define qbl_space QByteArrayLiteral(" ")

#define qbl_percent QByteArrayLiteral("%")

#define qbl_underline QStringLiteral("_")

#define qsl_number(v) QString::number(v,'f',0)

#define qbl_number(v) QString::number(v,'f',0).toUtf8()

#define qsl_double(v) QString::number(v,'f',6)

#define qbl_double(v) QString::number(v,'f',6).toUtf8()

#define qsl_fy(v) QT_STRINGIFY(v)

#define qbl_fy(v) QString(QT_STRINGIFY(v)).toUtf8()

#define q_dir_separator QDir::separator()

#define q_dir_separatorX2 QByteArrayLiteral("//")

#define qsl_key_return \
    QByteArrayLiteral("\n")

#define qsl_key_enter \
    QByteArrayLiteral("\n")

#define Q_V_MAP_ITERATOR(v)\
QMapIterator<QString, QVariant> i(v);\
while (i.hasNext())

#define Q_V_HASH_ITERATOR(v)\
QHashIterator<QString, QVariant> i(v);\
    while (i.hasNext())

#define Q_V_MULTI_HASH_ITERATOR(v)\
QMultiHashIterator<QString, QVariant> i(v);\
    while (i.hasNext())

#define Q_V_PROPERTY_ITERATOR(v)\
QHashIterator<QString, QMetaProperty> i(v);\
while (i.hasNext())

#define Q_V_METHOD_ITERATOR(v)\
QHashIterator<QString, QMetaMethod> i(v);\
while (i.hasNext())

#define Q_V_METAOBJECT_ITERATOR(v)\
QHashIterator<QByteArray, QMetaObject> i(v);\
while (i.hasNext())

#define Q_V_HASH_ITERATOR_STR_DOUBLE(v)\
QHashIterator<QString, double> i(v);\
while (i.hasNext())

#define Q_V_HASH_ITERATOR_STRING(v)\
QHashIterator<QString, QString> i(v);\
while (i.hasNext())

#define Q_V_VVM_ITERATOR(v)\
QHashIterator<QString, QVariant> i(v);\
while (i.hasNext())

#define Q_V_DATABASE_ITERATOR(v)\
QHashIterator<QString, QSqlDatabase> i(v);\
while (i.hasNext())

#define qtr QObject::tr

#define __FUNCTION_UUID__\
    QCryptographicHash::hash(__PRETTY_FUNCTION__, QCryptographicHash::Md5).toHex()

#define Q_DECLARE_PVT \
    void*p=nullptr;

#define vpsFiltrableStrategyLikeLR \
QVariantHash{qsl("operator"),QOrm::koLike}, {qsl("format"),qsl("%%1cS%")}}

#define vpsFiltrableStrategyLikeL \
QVariantHash{{qsl("operator"),QOrm::koLike}, {qsl("format"),qsl("%%1")}}

#define vpsFiltrableStrategyLikeR \
QVariantHash{{qsl("operator"),QOrm::koLike}, {qsl("format"),qsl("%1%")}}
