#ifndef UTIL_H
#define UTIL_H

#include <QStm>

class Util : public QStm::Object
{
    Q_OBJECT
public:
    explicit Util(QObject *parent = nullptr);


    void usingQCurrency();
    void usingVariantUtil();
    void usingFormattingUtil();
    void usingDateUtil();
    void usingDoubleUtil();

signals:

};

#endif // UTIL_H
