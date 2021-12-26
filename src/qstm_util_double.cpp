#include "./qstm_util_double.h"
#include "./qstm_vvm.h"

namespace QStm {

#define dPvt()\
    auto&p = *reinterpret_cast<DoubleUtilPvt*>(this->p)

class DoubleUtilPvt:public QObject{
public:
    QVVM vvm;
    FormattingUtil formatting;
    DoubleUtil*parent=nullptr;
    explicit DoubleUtilPvt(DoubleUtil*v):QObject(nullptr){
        this->parent=v;
    }
    virtual ~DoubleUtilPvt(){
    }

    void clear(){
        this->vvm=QVVM();
        this->parent->setValue(QVariant());
    }
};

DoubleUtil::DoubleUtil(const QVariant &v):QVariant(v)
{
    this->p = new DoubleUtilPvt(this);
}

DoubleUtil::~DoubleUtil()
{
    dPvt();
    this->p=nullptr;
    p.deleteLater();
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

bool DoubleUtil::checkBetween(qlonglong &vMin, qlonglong &vMax)
{
    if(vMin>vMax){
        auto aux=vMin;
        vMin=vMax;
        vMax=aux;
    }
    return vMin>0 || vMax>0;
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

FormattingUtil &DoubleUtil::formatting()
{
    dPvt();
    p.formatting.setValue(*this);
    return p.formatting;
}

FormattingUtil &DoubleUtil::formatting(const QVariant &v)
{
    dPvt();
    QVariant::setValue(v);
    p.formatting.setValue(v);
    return p.formatting;
}

}
