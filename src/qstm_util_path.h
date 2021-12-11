#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QVariantHash>
#include "./qstm_global.h"

namespace QStm {

class Q_STM_EXPORT PathUtil{
public:
    explicit PathUtil(Q_CONST_V);
    virtual ~PathUtil();

    PathUtil&operator=(const QVariant&v);
    PathUtil&operator+=(const QVariant&v);
    PathUtil&operator-=(const QVariant&v);
    PathUtil&operator<<(const QVariant&v);

    //!
    //! \brief exists
    //! \return
    //!
    bool exists()const;

    //!
    //! \brief exists
    //! \param v
    //! \return
    //!
    bool exists(Q_CONST_V)const;

    //!
    //! \brief isValid
    //! \param v
    //! \return
    //!
    bool isValid(Q_CONST_V)const;

    //!
    //! \brief clear
    //! \return
    //!
    PathUtil&clear();

    //!
    //! \brief setPath
    //! \param v
    //! \return
    //!
    PathUtil&setPath(Q_CONST_V);

    //!
    //! \brief append
    //! \param v
    //! \return
    //!
    PathUtil&append(Q_CONST_V);

    //!
    //! \brief remove
    //! \param v
    //! \return
    //!
    PathUtil&remove(Q_CONST_V);

    //!
    //! \brief mkPath
    //! \param v
    //! \return
    //!
    bool mkPath(Q_CONST_V);

    //!
    //! \brief toLower
    //! \return
    //!
    QString toLower()const;

    //!
    //! \brief toString
    //! \return
    //!
    QString toString()const;

    //!
    //! \brief toByteArray
    //! \return
    //!
    QByteArray toByteArray()const;

    //!
    //! \brief toList
    //! \return
    //!
    QVariantList toList()const;

    //!
    //! \brief toStringList
    //! \return
    //!
    QStringList toStringList()const;

    //!
    //! \brief toMd5
    //! \return
    //!
    QByteArray toMd5()const;

    //!
    //! \brief toUuid
    //! \return
    //!
    QUuid toUuid()const;

    //!
    //! \brief toUrl
    //! \return
    //!
    QUrl toUrl();

    //!
    //! \brief arg
    //! \param v
    //! \return
    //!
    QString arg(const QVariant&v);

private:
    void*p=nullptr;
};

}

typedef QStm::PathUtil PathUtil;
