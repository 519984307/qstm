#ifndef SIMPLEOBJECT_H
#define SIMPLEOBJECT_H

#include <QStm>
#include <QDebug>

class SimpleObject : public QStm::Object {
    Q_OBJECT
public:
    Q_INVOKABLE explicit SimpleObject(QObject*parent=nullptr);

    ResultValue&hashMd5(const QVariant&bytes);
};

class MyFirstObject : public QStm::Object {
    Q_OBJECT

    Q_PROPERTY(QUuid uuid MEMBER _uuid NOTIFY uuidChanged)
    Q_PROPERTY(QString name MEMBER _name NOTIFY nameChanged)

public:
    Q_INVOKABLE explicit MyFirstObject(QObject*parent=nullptr):QStm::Object(parent)
    {
    }

signals:
    void uuidChanged();
    void nameChanged();

private:
    QUuid _uuid;
    QString _name;
};

void run()
{
    MyFirstObject myFirstObject;

    QVariantHash vHash=myFirstObject.toHash();//include QMetaProperty in QVariantHash
    qWarning()<<vHash;
    //ouput is QVariantHash{ {"uuid", QUuid(...)}, {"name", QString(...)} }
}


#endif // SIMPLEOBJECT_H
