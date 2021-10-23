#pragma once

#include <QHash>
#include <QList>
#include <QMetaProperty>
#include <QMetaMethod>
#include "./qstm_global.h"
#include <QMetaMethod>
#include <QMetaProperty>

namespace QStm {

     /**
     * @brief The MetaObjectUtil class
     *
     * util class to operation objects
     */
    class Q_STM_EXPORT MetaObjectUtil{
    public:
        explicit MetaObjectUtil();
        explicit MetaObjectUtil(const QMetaObject&metaObject);
        ~MetaObjectUtil();

        MetaObjectUtil&operator=(const QMetaObject&v);
        MetaObjectUtil&operator+=(const QMetaObject&v);
        MetaObjectUtil&operator-=(const QMetaObject&v);
        MetaObjectUtil&operator<<(const QMetaObject&v);

        /**
         * @brief newInstance
         * @param parent
         * @return
         *
         * create object using QMetaObject
         */
        virtual QObject*newInstance(QObject *parent=nullptr);

        /**
         * @brief newInstance
         * @param metaObject
         * @param parent
         * @return
         *
         * create object using QMetaObject
         */
        virtual QObject*newInstance(const QMetaObject&metaObject, QObject *parent);

        /**
         * @brief method
         * @param name
         * @return
         *
         * return QMetaMethod by name
         */
        virtual QMetaMethod method(const QString &name);

        /**
         * @brief property
         * @param name
         * @return
         *
         * return QMetaProperty by name
         */
        virtual QMetaProperty property(const QByteArray&name);

        /**
         * @brief toMap
         * @param object
         * @return
         *
         * extract propertys values with object and set in QVariantMap
         */
        virtual const QVariantMap toMap(const QObject*object)const;

        /**
         * @brief toHash
         * @param object
         * @return
         *
         * extract propertys values with object and set in QVariantHash
         */
        virtual const QVariantHash toHash(const QObject*object) const;

        /**
         * @brief writeMap
         * @param object
         * @param v
         * @return
         *
         * write values in property using QVariantMap
         */
        virtual bool writeMap(QObject*object, const QVariantMap&v);

        /**
         * @brief writeHash
         * @param object
         * @param v
         * @return
         *
         * write values in property using QVariantHash
         */
        virtual bool writeHash(QObject*object, const QVariantHash&v);

        /**
         * @brief toPropertyList
         * @param object
         * @return
         *
         * return list propertys of object
         */
        virtual const QList<QMetaProperty> toPropertyList(const QObject*object=nullptr) const;

        /**
         * @brief toPropertyMap
         * @param object
         * @return
         *
         * return QHash propertys of object
         */
        virtual const QHash<QByteArray,QMetaProperty> toPropertyMap(const QObject*object=nullptr) const;

        /**
         * @brief newInstance
         * @param parent
         * @return
         *
         * create newInstance the object and converty to type.
         *
         * note, object a will be deleted, when different type
         */
        template <class T>
        T*newInstance(QObject *parent){
            QMetaObject&__metaObject=T::staticMetaObject;
            if((__metaObject.inherits(parent->metaObject())) || (&__metaObject == parent->metaObject())){
                auto object=this->newInstance(parent);
                if(object!=nullptr){
                    auto __return=dynamic_cast<T>(object);
                    if(__return==nullptr)
                        delete object;
                    return __return;
                }
            }
            return nullptr;
        }

    private:
        void*p=nullptr;
    };

}
