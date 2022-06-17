#include "./qstm_util_double.h"

namespace QStm {

DoubleUtil::DoubleUtil(const QVariant &v):QVariant{v}
{
}

DoubleUtil::~DoubleUtil()
{
}

DoubleUtil&DoubleUtil::operator=(const QVariant &v)
{
    this->setValue(v);
    return*this;
}

bool DoubleUtil::checkBetween(double &vMin, double &vMax)
{
    if(vMin>vMax){
        auto aux=vMin;
        vMin=vMax;
        vMax=aux;
    }
    return vMin>0 || vMax>0;
}

bool DoubleUtil::checkBetween(const double &value, double &vMin, double &vMax)
{
    if(!checkBetween(vMin, vMax))
        return false;
    return (value>=vMin) && (value<=vMax);
}

bool DoubleUtil::checkBetween(qlonglong &vMin, qlonglong &vMax)
{
    if(vMin>vMax){
        auto aux=vMin;
        vMin=vMax;
        vMax=aux;
    }
    return vMin>0 || vMax>0;
}

bool DoubleUtil::checkBetween(const qlonglong &value, qlonglong &vMin, qlonglong &vMax)
{
    if(!checkBetween(vMin, vMax))
        return false;
    return (value>=vMin) && (value<=vMax);
}

bool DoubleUtil::checkBetween(int &vMin, int &vMax)
{
    if(vMin>vMax){
        auto aux=vMin;
        vMin=vMax;
        vMax=aux;
    }
    return vMin>0 || vMax>0;
}

bool DoubleUtil::checkBetween(const int &value, int &vMin, int &vMax)
{
    if(!checkBetween(vMin, vMax))
        return false;
    return (value>=vMin) && (value<=vMax);
}

}
