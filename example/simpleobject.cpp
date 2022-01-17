#include "simpleobject.h"

SimpleObject::SimpleObject(QObject *parent):QStm::Object(parent)
{
}

ResultValue &SimpleObject::hashMd5(const QVariant &bytes)
{
    if(bytes.isNull())
        return this->lr()=false;//return false and without error

    if(bytes.toString().trimmed().isEmpty())
        return this->lr().setBadRequest("Invalid data");//return false and with error

    QStm::VariantUtil vu;
    QVariant md5=vu.toByteArray(bytes);
    return this->lr(md5);//return success and return value
}
