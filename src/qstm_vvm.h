#pragma once

#include <QVariant>
#include <QVariantHash>
#include <QVariantHash>

#include "./qstm_global.h"

//!
//! \brief The QVVM class
//!
class Q_STM_EXPORT QVVM:public QVariantHash
{
public:
    //!
    //! \brief QVVM
    //!
    explicit QVVM();

    //!
    //! \brief QVVM
    //! \param other
    //!
    explicit QVVM(const QVariant &other);

    //!
    //! \brief QVVM
    //! \param key
    //! \param value
    //!
    explicit QVVM(const QVariant &key, const QVariant &value);

    //!
    //! \brief ~QVVM
    //!
    virtual ~QVVM();

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!
    QVVM&operator=(const QVariant &v);

    //!
    //! \brief operator +=
    //! \param v
    //! \return
    //!
    QVVM&operator+=(const QVariantHash &v);

    //!
    //! \brief operator +=
    //! \param v
    //! \return
    //!
    QVVM&operator+=(const QVariantMap &v);

    //!
    //! \brief from
    //! \param v
    //! \return
    //!
    static QVVM from(const QVariantHash &v);

    //!
    //! \brief from
    //! \param v
    //! \return
    //!
    static QVVM from(const QVariantMap &v);

    //!
    //! \brief insert
    //! \param key
    //! \param value
    //!
    virtual void insert(const QVariant&key, const QVariant&value);

    //!
    //! \brief remove
    //! \param key
    //!
    virtual void remove(const QVariant&key);

    //!
    //! \brief value
    //! \param key
    //! \return
    //!
    virtual QVariant value(const QVariant&key)const;
};

Q_DECLARE_METATYPE(QVVM)
Q_DECLARE_METATYPE(QVVM*)
