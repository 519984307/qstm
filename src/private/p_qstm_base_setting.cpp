#include "./p_qstm_base_setting.h"

namespace QStm {
namespace Private{

Q_GLOBAL_STATIC(QVariantHash, __static_dirs)
Q_GLOBAL_STATIC(QVariantHash, __static_variables)


QVariantHash &static_dirs()
{
    return *__static_dirs;
}

QVariantHash &make_static_variables()
{
    auto &dir=*__static_dirs;

#ifndef Q_OS_IOS
    QProcess process;
    auto lst = process.environment();
    for(auto&v:lst){
        auto s=v.split(qsl("="));
        auto env=s.first().trimmed();
        auto value=s.last().trimmed();
        dir.insert(env, value);
    }
#endif
    dir.insert(qsl("$DesktopLocation"      ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation      ) );
    dir.insert(qsl("$DocumentsLocation"    ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation    ) );
    dir.insert(qsl("$FontsLocation"        ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::FontsLocation        ) );
    dir.insert(qsl("$ApplicationsLocation" ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation ) );
    dir.insert(qsl("$MusicLocation"        ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::MusicLocation        ) );
    dir.insert(qsl("$MoviesLocation"       ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::MoviesLocation       ) );
    dir.insert(qsl("$PicturesLocation"     ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::PicturesLocation     ) );
    dir.insert(qsl("$TempLocation"         ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::TempLocation         ) );
    dir.insert(qsl("$HomeLocation"         ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::HomeLocation         ) );
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    dir.insert(qsl("$DataLocation"         ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::DataLocation         ) );
#endif
    dir.insert(qsl("$CacheLocation"        ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::CacheLocation        ) );
    dir.insert(qsl("$GenericDataLocation"  ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation  ) );
    dir.insert(qsl("$RuntimeLocation"      ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::RuntimeLocation      ) );
    dir.insert(qsl("$ConfigLocation"       ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::ConfigLocation       ) );
    dir.insert(qsl("$DownloadLocation"     ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::DownloadLocation     ) );
    dir.insert(qsl("$GenericCacheLocation" ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation ) );
    dir.insert(qsl("$GenericConfigLocation").trimmed(), QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) );
    dir.insert(qsl("$AppDataLocation"      ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::AppDataLocation      ) );
    dir.insert(qsl("$AppConfigLocation"    ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation    ) );
    dir.insert(qsl("$AppLocalDataLocation" ).trimmed(), QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation ) );

    dir.insert(qsl("$HOME"),QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    dir.insert(qsl("$TEMPDIR"),QStandardPaths::writableLocation(QStandardPaths::TempLocation));
    dir.insert(qsl("$APPDIR"),QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation));
    dir.insert(qsl("$APPNAME"),qApp->applicationName());

    return dir;
}

void set_static_variables(const QVariantHash &v)
{
    *__static_variables=v;
    QHashIterator<QString, QVariant> i(*__static_dirs);
    while (i.hasNext()){
        i.next();
        __static_variables->insert(i.key(), i.value());
    }
}

void init()
{
    *__static_variables=QStm::Private::make_static_variables();
}

Q_COREAPP_STARTUP_FUNCTION(init)

QVariantHash &static_variables()
{
    return*__static_variables;
}

}


}

