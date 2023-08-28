#ifndef FTPDOWNLOADER_H
#define FTPDOWNLOADER_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QDir>
#include <curl.h>
#include "ftpinfo.h"
#include "localfile.h"

extern FtpFileList ftp_file_list;
extern ModFile mod_file;
extern QDir minecraft_folder;

class FtpDownloader : public QWidget
{
    Q_OBJECT
public:
    explicit FtpDownloader(QWidget *parent = nullptr);
    void ShowDownloadPage();
    void GetFtpFileList();
    static size_t GetFtpFileListCallback(char *ptr, size_t size, size_t nmemb, void *user_data);
    void DownloadFile();
    static size_t DownloadFileCallback(void *ptr, size_t size, size_t nmemb, void *user_data);

signals:
    void StartDownload();

private:
    // curl指针
    CURL* curl_;
    // curl状态码
    CURLcode res_;
    // ftp服务器信息
    FtpInfo ftp_info_;
};

#endif // FTPDOWNLOADER_H
