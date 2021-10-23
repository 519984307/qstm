QT += core
QT += network
QT += websockets

INCLUDEPATH+=$$PWD

HEADERS += \
    $$PWD/private/p_qstm_base_setting.h \
    $$PWD/private/p_qstm_setting_manager.h \
    $$PWD/private/p_qstm_service_manager.h \
    $$PWD/qstm_const.h \
    $$PWD/qstm_global.h \
    $$PWD/qstm_macro.h \
    $$PWD/qstm_util_path.h \
    $$PWD/qstm_result.h \
    $$PWD/qstm_cache_pool.h \
    $$PWD/qstm_object.h \
    $$PWD/qstm_setting_manager.h \
    $$PWD/qstm_setting_base.h \
    $$PWD/qstm_svm.h \
    $$PWD/qstm_types.h \
    $$PWD/qstm_currency.h \
    $$PWD/qstm_vvm.h \
    $$PWD/qstm_url.h \
    $$PWD/qstm_message.h \
    $$PWD/qstm_util_formatting.h \
    $$PWD/qstm_util_variant.h \
    $$PWD/qstm_util_date.h \
    $$PWD/qstm_util_double.h \
    $$PWD/qstm_util_meta_object.h \

SOURCES += \
    $$PWD/private/p_qstm_base_setting.cpp \
    $$PWD/qstm_util_path.cpp \
    $$PWD/qstm_result.cpp \
    $$PWD/qstm_cache_pool.cpp \
    $$PWD/qstm_object.cpp \
    $$PWD/qstm_setting_manager.cpp \
    $$PWD/qstm_setting_base.cpp \
    $$PWD/qstm_svm.cpp \
    $$PWD/qstm_currency.cpp \
    $$PWD/qstm_vvm.cpp \
    $$PWD/qstm_url.cpp \
    $$PWD/qstm_message.cpp \
    $$PWD/qstm_util_formatting.cpp \
    $$PWD/qstm_util_variant.cpp \
    $$PWD/qstm_util_date.cpp \
    $$PWD/qstm_util_double.cpp \
    $$PWD/qstm_util_meta_object.cpp \

