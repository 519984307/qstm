#include "qstm_util_notation.h"

namespace QStm {

#define dPvt()\
auto&p = *reinterpret_cast<NotationUtilPvt*>(this->p)

class NotationUtilPvt:public QObject{
public:
    NotationUtil*parent=nullptr;
    QHash<NotationUtil::Type, QVariant> notations;

    //!
    //! \brief NotationUtilPvt
    //! \param parent
    //!
    explicit NotationUtilPvt(NotationUtil*parent):QObject(nullptr)
    {
        this->parent=parent;
        this->notations=this->buildNotations();
    }
    virtual ~NotationUtilPvt()
    {
    }

    //!
    //! \brief reMakeNotation
    //! \param notations
    //! \return
    //!
    QVariantHash reMakeNotation(const QVariant &notations)const
    {
        QVariantHash __return;
        auto vList=notations.toList();
        for(auto&v:vList){
            auto vHash=v.toHash();

            if(vHash.isEmpty())
                continue;

            QHashIterator<QString, QVariant> i(vHash);
            while(i.hasNext()){
                i.next();
                __return.insert(i.key(), i.value());
            }
        }
        return __return;
    }

    //!
    //! \brief buildNotations
    //! \return
    //!
    QHash<NotationUtil::Type, QVariant> buildNotations()const
    {
        auto makeObject=this->parent->parent();
        if(makeObject==nullptr)
            return {};

        auto metaObject=makeObject->metaObject();
        static const auto _notations_method=QByteArrayLiteral("_notations_method");
        static const auto _notations_class=QByteArrayLiteral("_notations_class");

        QVariantList vNotationsClass;
        QVariantHash vNotationsMethod;

        for (auto i = 0; i < metaObject->methodCount(); ++i) {
            auto method = metaObject->method(i);

            if(method.methodType()!=method.Method)
                continue;

            if(method.parameterCount()>0)
                continue;

            const auto methodName = method.name().toLower();

            if(!methodName.startsWith(qbl("_notations_")))//ignore methods with [_] in start name
                continue;

            if(method.name().startsWith(_notations_class)){
                QVariantList returnVariant;
                if(method.invoke(makeObject, Qt::DirectConnection, Q_ARG(QVariantList, returnVariant)))
                    vNotationsClass<<reMakeNotation(returnVariant);
            }

            if(method.name().startsWith(_notations_method)){
                QVariantList returnVariant;
                if(method.invoke(makeObject, Qt::DirectConnection, Q_ARG(QVariantList, returnVariant)))
                    vNotationsMethod.insert(method.name(), reMakeNotation(returnVariant));
            }
        }
        return {{NotationUtil::Class, vNotationsClass}, {NotationUtil::Method, vNotationsClass}};
    }


};


NotationUtil::NotationUtil(QObject *parent):QObject(parent)
{
    this->p=new NotationUtilPvt(this);
}

NotationUtil::~NotationUtil()
{
    dPvt();
    delete&p;
}

QHash<NotationUtil::Type, QVariant> &NotationUtil::notations()const
{
    dPvt();
    return p.notations;
}

const QVariantHash NotationUtil::notation()const
{
    dPvt();
    auto __return=p.notations.value(NotationUtil::Class).toHash();
    return __return;
}

QVariantHash NotationUtil::notationMethod(const QMetaMethod &method) const
{
    dPvt();
    auto vNotations=p.notations.value(NotationUtil::Method).toHash();
    return vNotations.value(method.name()).toHash();
}

QVariantHash NotationUtil::notationMethods() const
{
    dPvt();
    auto __return = p.notations.value(NotationUtil::Method).toHash();
    return __return;
}

} // namespace QStm
