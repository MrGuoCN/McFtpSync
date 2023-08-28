#include "ftpinfo.h"

FtpFileList ftp_file_list;
ModFile mod_file;

FtpInfo::FtpInfo(QObject *parent)
    : QObject{parent}
{
}

FtpInfo::FtpInfo(QString ftp_url, QString ftp_usr_pwd, QObject *parent)
{
    this->ftp_url_ = ftp_url;
    this->ftp_usr_pwd_ = ftp_usr_pwd;
}

void FtpInfo::InitModsList()
{
    this->mod_list_ = ftp_file_list.file_name.split("\r\n");
    this->mod_list_.erase(this->mod_list_.constEnd() - 1);
    qDebug() << this->mod_list_;
}
