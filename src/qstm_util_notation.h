#pragma once

#include <QObject>
#include <QMetaMethod>
#include <QHash>
#include "./qstm_global.h"

namespace QStm {

//!
//! \brief The NotationUtil class
//!
//! Notation Util
class Q_STM_EXPORT NotationUtil:public QObject
{
    Q_OBJECT
public:

    //!
    //! \brief The Type enum
    //!
    enum Type{
        Class, Method
    };

    //!
    //! \brief NotationUtil
    //! \param parent
    //!
    Q_INVOKABLE explicit NotationUtil(QObject *parent = nullptr);
    virtual ~NotationUtil();

    //!
    //! \brief notationsClass
    //! \param parent
    //! \return
    //!
    virtual QHash<Type, QVariant> &notations()const;

    //!
    //! \brief notation
    //!
    virtual const QVariantHash notation() const;

    //!
    //! \brief notationMethod
    //! \param method
    //! \return
    //!
    virtual QVariantHash notationMethod(const QMetaMethod &method)const;

    //!
    //! \brief notationMethods
    //! \return
    //!
    virtual QVariantHash notationMethods()const;
private:
    void*p=nullptr;
};

} // namespace QStm
