#pragma once

#include <QObject>
#include <QVariant>
#include <QDateTime>
#include <QVariantList>
#include <QVariantHash>
#include "./qstm_global.h"

namespace QStm {
//!
//! \brief The QCurrency class
//!
class Q_STM_EXPORT QCurrency:public QVariant{
public:
    explicit QCurrency(const QVariant&v=QVariant(), const QVariant&precision=QVariant());
    virtual ~QCurrency();

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //! operator to calc
    QCurrency&operator = (const QVariant&v);

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!operator to calc
    QCurrency&operator = (const qlonglong&v);

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!operator to calc
    QCurrency&operator = (const int&v);

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!operator to calc
    QCurrency&operator = (const double&v);

    //!
    //! \brief operator +
    //! \param o
    //! \return
    //!operator to calc
    QCurrency&operator + (const QCurrency&o);

    //!
    //! \brief operator -
    //! \param o
    //! \return
    //!operator to calc
    QCurrency&operator - (const QCurrency&o);

    //!
    //! \brief operator *
    //! \param o
    //! \return
    //!
    QCurrency&operator * (const QCurrency&o);

    //!
    //! \brief operator /
    //! \param o
    //! \return
    //!operator to calc
    QCurrency&operator / (const QCurrency&o);

    //!
    //! \brief operator %
    //! \param o
    //! \return
    //!operator to calc
    QCurrency&operator % (const QCurrency&o);

    //!
    //! \brief operator ^
    //! \param o
    //! \return
    //!operator to calc
    QCurrency&operator ^ (const QCurrency&o);

    //!
    //! \brief operator +=
    //! \param o
    //!operator to calc
    void operator += (const QVariant&o);

    //!
    //! \brief operator -=
    //! \param o
    //!operator to calc
    void operator -= (const QVariant&o);

    //!
    //! \brief operator *=
    //! \param o
    //!operator to calc
    void operator *= (const QVariant&o);

    //!
    //! \brief operator /=
    //! \param o
    //!operator to calc
    void operator /= (const QVariant&o);

    //!
    //! \brief operator ^=
    //! \param o
    //!operator to calc
    void operator ^= (const QVariant&o);

    //!
    //! \brief operator >
    //! \param o
    //! \return
    //!operator to calc
    bool operator > (const QCurrency&o);

    //!
    //! \brief operator >=
    //! \param o
    //! \return
    //!operator to calc
    bool operator >= (const QCurrency&o);

    //!
    //! \brief operator ==
    //! \param o
    //! \return
    //!
    bool operator == (const QCurrency&o);

    //!
    //! \brief operator <
    //! \param o
    //! \return
    //!operator to calc
    bool operator < (const QCurrency&o);

    //!
    //! \brief operator <=
    //! \param o
    //! \return
    //!operator to calc
    bool operator <= (const QCurrency&o);

    //!
    //! \brief setValue
    //! \param value
    //! \return
    //!operator to calc
    virtual QCurrency &setValue(const QVariant&value);

    //!
    //! \brief toDouble
    //! \return
    //! conversao para do double
    double toDouble()const;
private:
    void*p=nullptr;
};

}

typedef double qcurrency;
typedef QStm::QCurrency QCurrency;

Q_DECLARE_METATYPE(qcurrency)
Q_DECLARE_METATYPE(QCurrency)
Q_DECLARE_METATYPE(QCurrency*)
