#include "./qstm_types.h"

int qTypeId(const QVariant &v)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    return v.typeId();
#else
    return v.type();
#endif
}

int qTypeId(const QMetaProperty &v)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    return v.typeId();
#else
    return v.type();
#endif
}
