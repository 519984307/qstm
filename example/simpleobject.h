#ifndef SIMPLEOBJECT_H
#define SIMPLEOBJECT_H

#include <QStm>

class SimpleObject : public QStm::Object {
    Q_OBJECT
public:
    Q_INVOKABLE explicit SimpleObject(QObject*parent=nullptr);

    ResultValue&hashMd5(const QVariant&bytes);
};


#endif // SIMPLEOBJECT_H
