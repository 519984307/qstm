#pragma once

#include <QObject>
#include <QFileInfo>
#include <QDateTime>
#include "./qstm_global.h"

namespace QStm {

//!
//! \brief The FileInfo class
//!
class Q_STM_EXPORT FileInfo :public QFileInfo
{
    Q_GADGET
public:
    //Q_PROPERTY(QString filePath READ filePath CONSTANT )
    //Q_PROPERTY(QString absoluteFilePath READ absoluteFilePath CONSTANT )
    Q_PROPERTY(QString canonicalFilePath READ canonicalFilePath CONSTANT )
    //Q_PROPERTY(QString fileName READ fileName CONSTANT )
    //Q_PROPERTY(QString baseName READ baseName CONSTANT )
    Q_PROPERTY(QString completeBaseName READ completeBaseName CONSTANT )
    Q_PROPERTY(QString suffix READ suffix CONSTANT )
    Q_PROPERTY(QString bundleName READ bundleName CONSTANT )
    Q_PROPERTY(QString completeSuffix READ completeSuffix CONSTANT )
    //Q_PROPERTY(QString path READ path CONSTANT )
    Q_PROPERTY(QString absolutePath READ absolutePath CONSTANT )
    //Q_PROPERTY(QString canonicalPath READ canonicalPath CONSTANT )
    Q_PROPERTY(bool isReadable READ isReadable CONSTANT )
    //Q_PROPERTY(bool isWritable READ isWritable CONSTANT )
    Q_PROPERTY(bool isExecutable READ isExecutable CONSTANT )
    Q_PROPERTY(bool isHidden READ isHidden CONSTANT )
    Q_PROPERTY(bool isNativePath READ isNativePath CONSTANT )
    Q_PROPERTY(bool isRelative READ isRelative CONSTANT )
    Q_PROPERTY(bool isAbsolute READ isAbsolute CONSTANT )
    //Q_PROPERTY(bool makeAbsolute READ makeAbsolute CONSTANT )
    Q_PROPERTY(bool isFile READ isFile CONSTANT )
    //Q_PROPERTY(bool isDir READ isDir CONSTANT )
    Q_PROPERTY(bool isSymLink READ isSymLink CONSTANT )
    Q_PROPERTY(bool isSymbolicLink READ isSymbolicLink CONSTANT )
    Q_PROPERTY(bool isShortcut READ isShortcut CONSTANT )
    Q_PROPERTY(bool isJunction READ isJunction CONSTANT )
    //Q_PROPERTY(bool isRoot READ isRoot CONSTANT )
    Q_PROPERTY(bool isBundle READ isBundle CONSTANT )
    Q_PROPERTY(QString symLinkTarget READ symLinkTarget CONSTANT )
    //Q_PROPERTY(QString owner READ owner CONSTANT )
    //Q_PROPERTY(uint ownerId READ ownerId CONSTANT )
    //Q_PROPERTY(QString group READ group CONSTANT )
    //Q_PROPERTY(uint groupId READ groupId CONSTANT )
    Q_PROPERTY(qint64 size READ size CONSTANT )
    Q_PROPERTY(QDateTime birthTime READ birthTime CONSTANT )
    Q_PROPERTY(QDateTime metadataChangeTime READ metadataChangeTime CONSTANT )
    Q_PROPERTY(QDateTime lastModified READ lastModified CONSTANT )
    Q_PROPERTY(QDateTime lastRead READ lastRead CONSTANT )
    //Q_PROPERTY(bool caching READ caching CONSTANT )
public:
    explicit FileInfo();
    explicit FileInfo(const QString &fileName);
    virtual ~FileInfo();

    //!
    //! \brief toHash
    //! \return
    //!
    QVariantHash toHash()const;
};

}
