#pragma once

#include <QObject>
#include "./qstm_macro.h"
#include "./qstm_const.h"
#include "./qstm_types.h"

#ifndef QT_STATIC
#  if defined(QT_BUILD_SQL_LIB)
#    define Q_STM_EXPORT Q_DECL_EXPORT
#  else
#    define Q_STM_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_STM_EXPORT
#endif
