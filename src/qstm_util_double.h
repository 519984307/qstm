#pragma once

#include <QObject>
#include <QVariant>
#include <QDateTime>
#include <QVariantList>
#include <QVariantHash>
#include "./qstm_global.h"

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
    DoubleUtil&operator=(const QVariant &v);

    //!
    //! \brief checkBetween
    //! \param vMin
    //! \param vMax
    //! \return
    //!
    static bool checkBetween(double &vMin, double &vMax);

    //!
    //! \brief checkBetween
    //! \param val
    //! \param vMin
    //! \param vMax
    //! \return
    //!
    static bool checkBetween(const double &value, double &vMin, double &vMax);

    //!
    //! \brief checkBetween
    //! \param vMin
    //! \param vMax
    //! \return
    //!
    static bool checkBetween(qlonglong &vMin, qlonglong &vMax);

    //!
    //! \brief checkBetween
    //! \param value
    //! \param vMin
    //! \param vMax
    //! \return
    //!
    static bool checkBetween(const qlonglong &value, qlonglong &vMin, qlonglong &vMax);

    //!
    //! \brief checkBetween
    //! \param vMin
    //! \param vMax
    //! \return
    //!
    static bool checkBetween(int &vMin, int &vMax);

    //!
    //! \brief checkBetween
    //! \param value
    //! \param vMin
    //! \param vMax
    //! \return
    //!
    static bool checkBetween(const int &value, int &vMin, int &vMax);
};

}

typedef QStm::DoubleUtil DoubleUtil;

Q_DECLARE_METATYPE(DoubleUtil)
Q_DECLARE_METATYPE(DoubleUtil*)
