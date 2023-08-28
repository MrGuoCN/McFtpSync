#include "ftpdownloader.h"

FtpDownloader::FtpDownloader(QWidget *parent)
    : QWidget{parent}
{
    this->curl_ = nullptr;
    curl_global_init(CURL_GLOBAL_ALL);
    this->ftp_info_.ftp_url_ = "";
    this->ftp_info_.ftp_usr_pwd_ = "";
}

void FtpDownloader::ShowDownloadPage()
{
    QDialog* download_dlg = new QDialog(this);
    QLabel* download_hits = new QLabel(download_dlg);
    download_hits->setText("Mod同步中!");
    download_dlg->show();

    this->GetFtpFileList();
    this->DownloadFile();

    emit StartDownload();
}

void FtpDownloader::GetFtpFileList()
{
    this->curl_ = curl_easy_init();
    if (!this->curl_)
    {
        QMessageBox::critical(this, "网络错误", "curl初始化失败!", QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        return;
    }
    curl_easy_setopt(this->curl_, CURLOPT_URL, this->ftp_info_.ftp_url_.toStdString().c_str());
    curl_easy_setopt(this->curl_, CURLOPT_USERPWD, this->ftp_info_.ftp_usr_pwd_.toStdString().c_str());
    curl_easy_setopt(this->curl_, CURLOPT_DIRLISTONLY, 1L);
    curl_easy_setopt(this->curl_, CURLOPT_WRITEDATA, &ftp_file_list);
    curl_easy_setopt(this->curl_, CURLOPT_WRITEFUNCTION, GetFtpFileListCallback);

    this->res_ = curl_easy_perform(this->curl_);

    if (CURLE_OK != this->res_)
    {
        QMessageBox::critical(this, "网络错误", "curl连接有误!", QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        curl_easy_strerror(this->res_);
    }
    curl_easy_cleanup(this->curl_);
    qDebug() << ftp_file_list.file_name;
}

size_t FtpDownloader::GetFtpFileListCallback(char *ptr, size_t size, size_t nmemb, void *user_data)
{
    FtpFileList* stream = (FtpFileList*)user_data;
    stream->file_name.append(ptr);
    return nmemb;
}

void FtpDownloader::DownloadFile()
{
    ftp_info_.InitModsList();

    for (int i = 0; i < ftp_info_.mod_list_.size(); ++i)
    {
        this->curl_ = curl_easy_init();

        mod_file = {
            nullptr,
            minecraft_folder.path() + "/mods/" + this->ftp_info_.mod_list_[i]
        };

        curl_easy_setopt(this->curl_, CURLOPT_URL, (this->ftp_info_.ftp_url_ + this->ftp_info_.mod_list_[i]).toStdString().c_str());
        curl_easy_setopt(this->curl_, CURLOPT_USERPWD, this->ftp_info_.ftp_usr_pwd_.toStdString().c_str());
        curl_easy_setopt(this->curl_, CURLOPT_WRITEDATA, &mod_file);
        curl_easy_setopt(this->curl_, CURLOPT_WRITEFUNCTION, DownloadFileCallback);
        this->res_ = curl_easy_perform(this->curl_);
        qDebug() << mod_file.file_name << "\n" << mod_file.stream;
        if (this->res_ != CURLE_OK)
        {
            QMessageBox::critical(this, "网络错误", "curl下载失败!", QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
            curl_easy_strerror(this->res_);
            return;
        }
        curl_easy_cleanup(this->curl_);
    }
}

size_t FtpDownloader::DownloadFileCallback(void *ptr, size_t size, size_t nmemb, void *user_data)
{
    ModFile* write_here = (ModFile*)user_data;
    if (!write_here->stream && write_here)
    {
        fopen_s(&write_here->stream, write_here->file_name.toStdString().c_str(), "wb+");
        if (!write_here->stream)
        {
            return -1;
        }
    }
    return fwrite(ptr, size, nmemb, write_here->stream);
}
