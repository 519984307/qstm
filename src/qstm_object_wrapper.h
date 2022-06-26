#pragma once

#include "./qstm_global.h"
#include <QObject>
#include <QVariant>

namespace QStm {


#define QSTM_OBJECT_WRAPPER(CLASS)\
public:\
void operator=(const CLASS *object)\
{\
    ObjectWrapper::setValues(object);\
}\
Q_INVOKABLE void operator=(const QVariant &object)\
{\
    ObjectWrapper::setValues(object);\
}\
static CLASS *from(const QVariant &v, QObject *parent)\
{\
    auto item = new CLASS{parent};\
    (*item)=v;\
    if(!item->isValid()){\
        delete item;\
        return nullptr;\
    }\
    return item;\
}

class Q_STM_EXPORT ObjectWrapper : public QObject
{
    Q_OBJECT
    QSTM_OBJECT_WRAPPER(ObjectWrapper)
public:
    //!
    //! \brief ObjectWrapper
    //! \param parent
    //!
    explicit ObjectWrapper(QObject *parent = nullptr);

    //!
    //! \brief printProperties
    //!
    Q_INVOKABLE void printProperties();

    //!
    //! \brief isValid
    //! \return
    //!
    virtual bool isValid()const;

    //!
    //! \brief readFom
    //! \return
    //!
    Q_INVOKABLE virtual void readFrom(const QVariant &values);

    //!
    //! \brief readFom
    //! \return
    //!
    virtual void readFrom(const QObject *object);

    //!
    //! \brief mergeFrom
    //! \return
    //!
    Q_INVOKABLE virtual void mergeFrom(const QVariant &values);

    //!
    //! \brief mergeFrom
    //! \return
    //!
    virtual void mergeFrom(const QObject *object);

    //!
    //! \brief clear
    //!
    Q_INVOKABLE virtual void clear();

    //!
    //! \brief toJson
    //! \return
    //!
    Q_INVOKABLE virtual const QString toJson();

    //!
    //! \brief toHash
    //! \return
    //!
    Q_INVOKABLE const virtual QVariantHash toHash();

    //!
    //! \brief toPropList
    //! \return
    //!
    QVector<QMetaProperty> toPropList()const;

    //!
    //! \brief values
    //! \return
    //!
    QVariant values()const;
    virtual bool setValues(const QVariant &v);
    virtual bool setValues(const QObject *v);

    //!
    //! \brief baseValues
    //! \return
    //!
    QObject *baseValues() const;
    void setBaseValues(QObject *newBaseValues);
    void resetBaseValues();


    //!
    //! \brief parserVariant
    //! \param v
    //! \return
    //!
    static const QVariant parserVariant(const QVariant &v);

    //!
    //! \brief extractProperty
    //! \param object
    //! \return
    //!
    static const QVector<QMetaProperty> extractProperty(const QObject *object);

    //!
    //! \brief extractHash
    //! \param object
    //! \return
    //!
    static const QVariantHash extractHash(const QObject *object);

protected:

    //!
    //! \brief beforeSetProperty
    //! \param property
    //! \param value
    //! \return
    //!
    virtual bool beforeSetProperty(const QMetaProperty &property, QVariant &value);

    //!
    //! \brief afterSetProperty
    //! \param property
    //! \param value
    //! \return
    //!
    virtual bool afterSetProperty(const QMetaProperty &property, const QVariant &value);


private:
    bool _clearOnSetFail=true;
    QVariant _values={};

signals:
    void changed();
    void cleared();
    void asJsonChanged();
    void valuesChanged();
    void clearOnSetFailChanged();
    void baseValuesChanged();
};

} // namespace QMFE
