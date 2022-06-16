#include "./qstm_fileinfo.h"
#include "./qstm_object.h"
#include <QMetaProperty>

namespace QStm {

FileInfo::FileInfo():QFileInfo()
{

}

FileInfo::FileInfo(const QString &fileName):QFileInfo(fileName)
{
}

FileInfo::~FileInfo()
{
}

QVariantHash FileInfo::toHash() const
{
    QVariantHash __return;
    static const auto &metaObject=FileInfo::staticMetaObject;
    for(int col = 0; col < metaObject.propertyCount(); ++col) {
        auto property = metaObject.property(col);
        __return[property.name()]=property.readOnGadget(this);
    }
    return __return;
}

}

