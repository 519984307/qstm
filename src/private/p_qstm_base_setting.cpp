#include "./p_qstm_base_setting.h"

namespace QStm {
namespace Private {

typedef QStandardPaths StdPaths;

Q_GLOBAL_STATIC(QVariantHash, __static_dirs)
Q_GLOBAL_STATIC(QVariantHash, __static_variables)

QVariantHash &static_dirs()
{
    return *__static_dirs;
}

QVariantHash &make_static_variables()
{
    auto &d = *__static_dirs;

#ifndef Q_OS_IOS
    QProcess process;
    auto lst = process.environment();
    for (auto &v : lst) {
        auto s = v.split(qsl("="));
        auto env = s.first().trimmed();
        auto value = s.last().trimmed();
        d[env] = value;
    }
#endif
    d[qsl("$DesktopLocation")] = StdPaths::writableLocation(StdPaths::DesktopLocation);
    d[qsl("$DocumentsLocation")] = StdPaths::writableLocation(StdPaths::DocumentsLocation);
    d[qsl("$FontsLocation")] = StdPaths::writableLocation(StdPaths::FontsLocation);
    d[qsl("$ApplicationsLocation")] = StdPaths::writableLocation(StdPaths::ApplicationsLocation);
    d[qsl("$MusicLocation")] = StdPaths::writableLocation(StdPaths::MusicLocation);
    d[qsl("$MoviesLocation")] = StdPaths::writableLocation(StdPaths::MoviesLocation);
    d[qsl("$PicturesLocation")] = StdPaths::writableLocation(StdPaths::PicturesLocation);
    d[qsl("$TempLocation")] = StdPaths::writableLocation(StdPaths::TempLocation);
    d[qsl("$HomeLocation")] = StdPaths::writableLocation(StdPaths::HomeLocation);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    d[qsl("$DataLocation")] = StdPaths::writableLocation(StdPaths::DataLocation);
#endif
    d[qsl("$CacheLocation")] = StdPaths::writableLocation(StdPaths::CacheLocation);
    d[qsl("$GenericDataLocation")] = StdPaths::writableLocation(StdPaths::GenericDataLocation);
    d[qsl("$RuntimeLocation")] = StdPaths::writableLocation(StdPaths::RuntimeLocation);
    d[qsl("$ConfigLocation")] = StdPaths::writableLocation(StdPaths::ConfigLocation);
    d[qsl("$DownloadLocation")] = StdPaths::writableLocation(StdPaths::DownloadLocation);
    d[qsl("$GenericCacheLocation")] = StdPaths::writableLocation(StdPaths::GenericCacheLocation);
    d[qsl("$GenericConfigLocation")] = StdPaths::writableLocation(StdPaths::GenericConfigLocation);
    d[qsl("$AppDataLocation")] = StdPaths::writableLocation(StdPaths::AppDataLocation);
    d[qsl("$AppConfigLocation")] = StdPaths::writableLocation(StdPaths::AppConfigLocation);
    d[qsl("$AppLocalDataLocation")] = StdPaths::writableLocation(StdPaths::AppLocalDataLocation);
    d[qsl("$HOME")] = StdPaths::writableLocation(StdPaths::HomeLocation);
    d[qsl("$TEMPDIR")] = StdPaths::writableLocation(StdPaths::TempLocation);
    d[qsl("$APPDIR")] = StdPaths::writableLocation(StdPaths::ApplicationsLocation);
    d[qsl("$APPNAME")] = qApp->applicationName();

    return d;
}

void set_static_variables(const QVariantHash &v)
{
    *__static_variables = v;
    QHashIterator<QString, QVariant> i(*__static_dirs);
    while (i.hasNext()) {
        i.next();
        auto s = i.value().toString().trimmed();
        if (s.isEmpty())
            continue;
        (*__static_variables)[i.key()]=s;
    }
}

void init()
{
    *__static_variables = QStm::Private::make_static_variables();
}

Q_COREAPP_STARTUP_FUNCTION(init)

QVariantHash &static_variables()
{
    return *__static_variables;
}

} // namespace Private

} // namespace QStm
