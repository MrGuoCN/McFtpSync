#ifndef FTPINFO_H
#define FTPINFO_H

#include <QObject>
#include <QDebug>
#include <string>

struct FtpFileList
{
    QString file_name;
};

struct ModFile
{
    FILE* stream;
    QString file_name;
};

class FtpInfo : public QObject
{
    Q_OBJECT
public:
    explicit FtpInfo(QObject *parent = nullptr);
    explicit FtpInfo(QString ftp_url, QString ftp_usr_pwd, QObject* parent = nullptr);
    void InitModsList();
public:
    QString ftp_url_;
    QString ftp_usr_pwd_;
    QStringList mod_list_;
};

#endif // FTPINFO_H
