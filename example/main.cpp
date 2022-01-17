#include <QCoreApplication>

class SimpleObject : public QStm::Object {
    Q_OBJECT
public:
    ResultValue&hashMd5(const QVariant&bytes)
    {
        if(bytes.isNull())
            return this->lr()=false;//return false and without error

        if(bytes.toString().trimmed().isEmpty())
            return this->lr().setBadRequest("Invalid data");//return false and with error

        QStm::VariantUtil vu;
        QVariant md5=vu.toByteArray(bytes);
        return this->lr(md5);//return success and return value
    }
};


void check()
{
    SimpleObject simpleObject;

    QByteArray bytes("1234567890");

    if(!simpleObject.hashMd5(bytes)){
        qWarning()<<simpleObject.lr().returnCode();//error code
        qWarning()<<simpleObject.lr().returnText();//error text
        return;
    }

    //to bytes
    qWarning()<<simpleObject.lr().resultByteArray();

    //to int
    qWarning()<<simpleObject.lr().resultInt();

    //to Double
    qWarning()<<simpleObject.lr().resultDouble();

    //to QString
    qWarning()<<simpleObject.lr().resultString();

    //to QDate
    qWarning()<<simpleObject.lr().resultDate();

    //to QTime
    qWarning()<<simpleObject.lr().resultTime();

    //to QDateTime
    qWarning()<<simpleObject.lr().resultDateTime();

    //to QUrl
    qWarning()<<simpleObject.lr().resultUrl();

    //to QUuid
    qWarning()<<simpleObject.lr().resultUuid();

    //to QVariantList
    qWarning()<<simpleObject.lr().resultList();

    //to QStringList
    qWarning()<<simpleObject.lr().resultStringList();

    //to QVariantHash
    qWarning()<<simpleObject.lr().resultHash();

    //to QVariantMap
    qWarning()<<simpleObject.lr().resultMap();

    //to void*
    qWarning()<<simpleObject.lr().resultObject();

    //to QObject
    qWarning()<<simpleObject.lr().resultObject<QObject*>();
}




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
