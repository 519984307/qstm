INCLUDEPATH += $$PWD/includes

QTREFORCE_QSTM=true
DEFINES+=QTREFORCE_QSTM

include($$PWD/3rdparty/bcmath/bcmath.pri)
include($$PWD/src/qstm.pri)
