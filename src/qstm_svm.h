#pragma once

#include <QVariant>
#include <QVariantHash>
#include <QPair>
#include "./qstm_global.h"

typedef QVariantList QVL;
typedef QVariantHash QVM;

Q_DECLARE_METATYPE(QVL)
Q_DECLARE_METATYPE(QVM)

Q_DECLARE_METATYPE(QVL*)
Q_DECLARE_METATYPE(QVM*)

//!
//! \brief The QSVM class
//!
class Q_STM_EXPORT QSVM:public QVariantHash
{
public:
    //!
    //! \brief QSVM
    //!
    explicit QSVM();

    //!
    //! \brief QSVM
    //! \param other
    //!
    explicit QSVM(const QVariant &other);

    //!
    //! \brief ~QSVM
    //!
    virtual ~QSVM();

    /**
     * @brief operator =
     * @param v
     * @return
     */
    QSVM&operator=(const QVariant&v);

    /**
     * @brief operator +=
     * @param v
     * @return
     *
     * replace map
     */
    QSVM&operator+=(const QVariant&v);

    /**
     * @brief operator +=
     * @param v
     * @return
     */
    QSVM&operator+=(const QPair<QString, QVariant> &v);

    /**
     * @brief operator -=
     * @param v
     * @return
     *
     * insert key if not contains
     */
    QSVM&operator-=(const QVariant&v);

    /**
     * @brief operator <<
     * @param v
     * @return
     *
     * replace key
     */
    QSVM&operator<<(const QVariant&v);


    /**
     * @brief operator <<
     * @param v
     * @return
     *
     * insert ou replace key
     */
    QSVM&operator<<(const QPair<QString,QVariant>&v);

    /**
     * @brief insert
     * @param key
     * @param value
     */
    virtual QSVM &insert(const QVariant&key, const QVariant&value);

    /**
     * @brief remove
     * @param key
     */
    virtual QVariant remove(const QVariant&key);

    /**
     * @brief remove
     * @param key
     */
    virtual QVariant take(const QVariant&key);

    /**
     * @brief value
     * @param key
     * @return
     */
    virtual QVariant value(const QVariant&key)const;
};

Q_DECLARE_METATYPE(QSVM)
Q_DECLARE_METATYPE(QSVM*)
