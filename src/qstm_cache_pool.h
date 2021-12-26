#pragma once

#include <QObject>
#include <QThread>
#include <QVariant>
#include "./qstm_global.h"

namespace QStm {

//!
//! \brief The CachePool class
//! pool cache class
class Q_STM_EXPORT CachePool : public QObject
{
    Q_OBJECT
public:

    //!
    //! \brief CachePool
    //! \param parent
    //!
    Q_INVOKABLE explicit CachePool(QObject *parent = nullptr);

    //!
    //! \brief ~CachePool
    //!
    Q_INVOKABLE ~CachePool();

    //!
    //! \brief i
    //! \return
    //!
    static CachePool&i();

    //!
    //! \brief instance
    //! \return
    //!
    static CachePool&instance();

    //!
    //! \brief instance
    //! \param currentThread
    //! \return
    //!
    static CachePool&instance(QThread *currentThread);

    //!
    //! \brief clear
    //! \return
    //!
    virtual CachePool &clear();

    //!
    //! \brief get
    //! \param key
    //! \param value
    //! \return
    //!
    virtual bool get(const QVariant &key, QVariant &value)const;

    //!
    //! \brief get
    //! \param key
    //! \return
    //!
    virtual QVariant get(const QVariant &key)const;

    //!
    //! \brief set
    //! \param value
    //! \return
    //!
    virtual QByteArray set(QVariant&value)const;

    //!
    //! \brief set
    //! \param key
    //! \param value
    //! \return
    //!
    virtual bool set(const QVariant &key, const QVariant&value)const;

    //!
    //! \brief take
    //! \param key
    //! \return
    //!
    virtual QVariant take(const QVariant &key)const;

    //!
    //! \brief remove
    //! \param key
    //! \return
    //!
    virtual QVariant remove(const QVariant &key)const;

private:
    void*p=nullptr;
};

}
