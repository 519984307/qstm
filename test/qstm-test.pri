include($$PWD/../qstm.pri)

INCLUDEPATH+=$$PWD

CONFIG += console
CONFIG -= debug_and_release
CONFIG += testcase
LIBS += -L/usr/local/lib -lgmock
LIBS += -L/usr/local/lib -lgtest

Q_STM_TEST=true
QMAKE_CXXFLAGS += -DQ_STM_TEST=\\\"$$Q_STM_TEST\\\"

HEADERS += \
    $$PWD/qstm_test.h \
    $$PWD/qstm_test_unit.h \
    $$PWD/qstm_test_functional.h

SOURCES += \
    $$PWD/qstm_unit_test_result_value.cpp \
    $$PWD/qstm_unit_test_object.cpp \
    $$PWD/qstm_unit_test_variant_util.cpp \
    $$PWD/qstm_unit_test_setting.cpp \
    $$PWD/qstm_unit_test_manager.cpp \
    $$PWD/qstm_unit_test_date_util.cpp \
    $$PWD/qstm_unit_test_double_util.cpp \
    $$PWD/qstm_functional_test_manager.cpp \
    $$PWD/qstm_unit_test_formatting_util.cpp
