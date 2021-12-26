#pragma once

#include <QObject>
#include <QVariant>
#include <QDateTime>
#include <QVariantList>
#include <QVariantHash>
#include "./qstm_global.h"
#include "./qstm_util_formatting.h"

namespace QStm {

//!
//! \brief The DoubleUtil class
//!util class to operation numeric values
class Q_STM_EXPORT DoubleUtil:public QVariant{
public:
    //!
    //! \brief DoubleUtil
    //! \param v
    //!
    explicit DoubleUtil(Q_CONST_V);

    //!
    //! \brief ~DoubleUtil
    //!
    virtual ~DoubleUtil();

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!
    DoubleUtil&operator=(const QVariant&v);

    //!
    //! \brief checkBetween
    //! \param vMin
    //! \param vMax
    //! \return
    //!
    bool checkBetween(double &vMin, double &vMax);

    //!
    //! \brief checkBetween
    //! \param vMin
    //! \param vMax
    //! \return
    //!
    bool checkBetween(qlonglong &vMin, qlonglong &vMax);

    //!
    //! \brief checkBetween
    //! \param vMin
    //! \param vMax
    //! \return
    //!
    bool checkBetween(int &vMin, int &vMax);

    //!
    //! \brief formatting
    //! \return
    //!
    virtual FormattingUtil&formatting();

    //!
    //! \brief formatting
    //! \param v
    //! \return
    //!
    virtual FormattingUtil&formatting(Q_CONST_V);
private:
    void*p=nullptr;
};

}

typedef QStm::DoubleUtil DoubleUtil;

Q_DECLARE_METATYPE(DoubleUtil)
Q_DECLARE_METATYPE(DoubleUtil*)
