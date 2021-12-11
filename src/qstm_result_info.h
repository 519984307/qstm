#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QVariantHash>
#include "./qstm_global.h"

namespace QStm {

//!
//! \brief The ResultInfo class
//!
//! class page navigator
class Q_STM_EXPORT ResultInfo:public QObject{
    Q_OBJECT

    Q_PROPERTY(QVariantList errors      READ errors      WRITE setErrors      )
    Q_PROPERTY(QVariantList messages    READ messages    WRITE setMessages    )
    Q_PROPERTY(bool         success     READ success     WRITE setSuccess     )
    Q_PROPERTY(int          page        READ page        WRITE setPage        )
    Q_PROPERTY(int          per_page    READ per_page    WRITE setPer_page    )
    Q_PROPERTY(int          count       READ count       WRITE setCount       )
    Q_PROPERTY(int          total_count READ total_count WRITE setTotal_count )
    Q_PROPERTY(int          total_pages READ total_pages WRITE setTotal_pages )

public:
    //!
    //! \brief ResultInfo constructor
    //! \param parent
    //!
    Q_INVOKABLE explicit ResultInfo(QObject*parent=nullptr);

    //! \brief ResultInfo destructor
    //!
    ~ResultInfo();

    //!
    //! \brief clear
    //!
    //!
    //! clear all values
    virtual void clear();

    //!
    //! \brief clearErrors
    //!
    //!
    //! clear all errors info
    virtual void clearErrors();


    //!
    //! \brief errors
    //! \return
    //! activity resource
    virtual bool enabled();
    virtual void setEnabled(bool value);

    //!
    //! \brief errors
    //! \return
    //! return errors to server
    virtual QVariantList&errors();
    virtual void setErrors(const QVariantList&value);

    //!
    //! \brief messages
    //! \return
    //!
    //!
    //! return message to server
    virtual QVariantList&messages();
    void setMessages(const QVariantList&value);

    //!
    //! \brief success
    //! \return
    //!
    //! return success true ou false to request
    int success() const;
    void setSuccess(bool value);

    //!
    //! \brief page
    //! \return
    //!
    //! currenty page
    int page() const;
    void setPage(int value);

    //!
    //! \brief per_page
    //! \return
    //!
    //! rows per page
    int per_page() const;
    void setPer_page(int value);

    //!
    //! \brief count
    //! \return
    //!
    //! returneds row per page
    int count() const;
    void setCount(int value);

    //!
    //! \brief total_count
    //! \return
    //!
    //! total rows to all pages
    int total_count() const;
    void setTotal_count(int value);

    //!
    //! \brief total_pages
    //! \return
    //!
    //! total pages
    int total_pages() const;
    void setTotal_pages(int value);

    //!
    //! \brief toRequestHash
    //! \return
    //!
    virtual const QVariantHash toRequestHash() const;

    //!
    //! \brief toMap
    //! \return
    //!
    virtual QVariantMap toMap() const;

    //!
    //! \brief toHash
    //! \return
    //!
    virtual QVariantHash toHash() const;

    //!
    //! \brief toVar
    //! \return
    //!
    virtual QVariant toVar() const;

    //!
    //! \brief fromVar
    //! \param v
    //! \return
    //!
    virtual bool fromVar(const QVariant &v);

    //!
    //! \brief fromMap
    //! \param map
    //! \return
    //!
    virtual bool fromMap(const QVariantMap &map);

    //!
    //! \brief fromHash
    //! \param map
    //! \return
    //!
    virtual bool fromHash(const QVariantHash &map);

private:
    void*p=nullptr;
};

}
