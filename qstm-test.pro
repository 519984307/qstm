QT += testlib

CONFIG += testcase
CONFIG += console
CONFIG += silent
CONFIG -= debug_and_release
QT -= gui

TEMPLATE = app
TARGET = QStmTest

INCLUDEPATH+=$$PWD/../src
#INCLUDEPATH+=$$PWD/../src/private

QSTM_TEST_MODE=true
QMAKE_CXXFLAGS += -DQSTM_TEST_MODE=\\\"$$QSTM_TEST_MODE\\\"

LIBS += -lgmock
LIBS += -lgtest

include($$PWD/qstm.pri)
include($$PWD/test/qstm-test.pri)

