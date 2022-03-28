#pragma once

#include "./qstm_global.h"
#include <QObject>
#include <QVector>
#include <QVariant>
#include <QVariantHash>
#include <QString>
#include <QMetaProperty>

//!
//! \brief Consts to QMetaType
static const int QMetaType_UnknownType  = QMetaType::UnknownType   ;
static const int QMetaType_Void         = QMetaType::Void          ;
static const int QMetaType_Bool         = QMetaType::Bool          ;
static const int QMetaType_User         = QMetaType::User          ;
static const int QMetaType_Double       = QMetaType::Double        ;
static const int QMetaType_Int          = QMetaType::Int           ;
static const int QMetaType_UInt         = QMetaType::UInt          ;
static const int QMetaType_LongLong     = QMetaType::LongLong      ;
static const int QMetaType_ULongLong    = QMetaType::ULongLong     ;
static const int QMetaType_QBitArray    = QMetaType::QBitArray     ;
static const int QMetaType_QByteArray   = QMetaType::QByteArray    ;
static const int QMetaType_QChar        = QMetaType::QChar         ;
static const int QMetaType_QDate        = QMetaType::QDate         ;
static const int QMetaType_QDateTime    = QMetaType::QDateTime     ;
static const int QMetaType_QString      = QMetaType::QString       ;
static const int QMetaType_QStringList  = QMetaType::QStringList   ;
static const int QMetaType_QTime        = QMetaType::QTime         ;
static const int QMetaType_QUrl         = QMetaType::QUrl          ;
static const int QMetaType_QUuid        = QMetaType::QUuid         ;
static const int QMetaType_QVariantHash = QMetaType::QVariantHash  ;
static const int QMetaType_QVariantList = QMetaType::QVariantList  ;
static const int QMetaType_QVariantMap  = QMetaType::QVariantMap   ;
static const int QMetaType_QObjectStar  = QMetaType::QObjectStar   ;
static const int QMetaType_QColor       = QMetaType::QColor        ;
static const int QMetaType_QJsonObject  = QMetaType::QJsonValue    ;
static const int QMetaType_QJsonArray   = QMetaType::QJsonArray    ;
static const int QMetaType_QJsonValue   = QMetaType::QJsonObject   ;
static const int QMetaType_CustomType   = 65538                    ;

namespace QStm{

//!
//! \brief The QMetaTypeUtil class
//!
//! List for QMetaType
class Q_STM_EXPORT QMetaTypeUtil:public QVector<int>
{
public:
    //!
    //! \brief QMetaTypeUtil
    //!
    explicit QMetaTypeUtil();

    //!
    //! \brief QMetaTypeUtil
    //!
    explicit QMetaTypeUtil(const QVector<int>&list);

    //!
    //! \brief ~QMetaTypeUtil
    //!
    virtual ~QMetaTypeUtil();

    //!
    //! \brief qTypeId
    //! \param v
    //! \return
    //!
    static int qTypeId(const QVariant&v);

    //!
    //! \brief qTypeId
    //! \param p
    //! \return
    //!
    static int qTypeId(const QMetaProperty&p);

    //!
    //! \brief qIsNumeric
    //! \param v
    //! \return
    //!
    static bool qIsNumeric(const QVariant&v);

    //!
    //! \brief QMetaTypeUtilString
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilString();

    //!
    //! \brief QMetaTypeUtilMetaString
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilMetaString();

    //!
    //! \brief QMetaTypeUtilNumeric
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilNumeric();

    //!
    //! \brief QMetaTypeUtilDoubles
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilDoubles();

    //!
    //! \brief QMetaTypeUtilIntegers
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilIntegers();

    //!
    //! \brief QMetaTypeUtilClass
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilClass();

    //!
    //! \brief QMetaTypeUtilObjects
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilObjects();

    //!
    //! \brief QMetaTypeUtilObjectsString
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilObjectsString();

    //!
    //! \brief QMetaTypeUtilDates
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilDates();

    //!
    //! \brief QMetaTypeUtilBool
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilBool();

    //!
    //! \brief QMetaTypeUtilVariantDictionary
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilVariantDictionary();

    //!
    //! \brief QMetaTypeUtilVariantList
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilVariantList();

    //!
    //! \brief QMetaTypeUtilObjectMetaData
    //! \return
    //!
    static const QMetaTypeUtil &qMetaTypeUtilObjectMetaData();
};

}


//!
//! \brief qTypeId
//! \param v
//! \return
//!
int qTypeId(const QVariant&v);

//!
//! \brief qTypeId
//! \param p
//! \return
//!
int qTypeId(const QMetaProperty&p);

//!
//! \brief qIsNumeric
//! \param v
//! \return
//!
bool qIsNumeric(const QVariant&v);

//!
//! \brief QMetaTypeUtilString
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilString=QStm::QMetaTypeUtil::qMetaTypeUtilString();

//!
//! \brief QMetaTypeUtilMetaString
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilMetaString=QStm::QMetaTypeUtil::qMetaTypeUtilMetaString();

//!
//! \brief QMetaTypeUtilNumeric
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilNumeric=QStm::QMetaTypeUtil::qMetaTypeUtilNumeric();

//!
//! \brief QMetaTypeUtilDoubles
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilDoubles=QStm::QMetaTypeUtil::qMetaTypeUtilDoubles();

//!
//! \brief QMetaTypeUtilIntegers
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilIntegers=QStm::QMetaTypeUtil::qMetaTypeUtilIntegers();

//!
//! \brief QMetaTypeUtilClass
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilClass=QStm::QMetaTypeUtil::qMetaTypeUtilClass();

//!
//! \brief QMetaTypeUtilObjects
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilObjects=QStm::QMetaTypeUtil::qMetaTypeUtilObjects();

//!
//! \brief QMetaTypeUtilObjectsString
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilObjectsString=QStm::QMetaTypeUtil::qMetaTypeUtilObjectsString();

//!
//! \brief QMetaTypeUtilDates
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilDates=QStm::QMetaTypeUtil::qMetaTypeUtilDates();

//!
//! \brief QMetaTypeUtilBool
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilBool=QStm::QMetaTypeUtil::qMetaTypeUtilBool();

//!
//! \brief QMetaTypeUtilVariantDictionary
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilVariantDictionary=QStm::QMetaTypeUtil::qMetaTypeUtilVariantDictionary();

//!
//! \brief QMetaTypeUtilVariantList
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilVariantList=QStm::QMetaTypeUtil::qMetaTypeUtilVariantList();

//!
//! \brief QMetaTypeUtilObjectMetaData
//!
static const QStm::QMetaTypeUtil &QMetaTypeUtilObjectMetaData=QStm::QMetaTypeUtil::qMetaTypeUtilObjectMetaData();
