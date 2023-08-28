#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Minecraft服务器mod同步器V1.0\tby Mr.Guo");
    ui->statusbar->showMessage("欢迎!");

    // 选择".minecraft"文件夹
    LocalFile* local_file = new LocalFile(this);
    connect(ui->OpenMcFolderBtn, &QPushButton::clicked, local_file, &LocalFile::GetMinecraftFolder);

    // 生成下载页面
    FtpDownloader* ftp_downloader = new FtpDownloader(this);
    connect(local_file, &LocalFile::GetMcFolderSuccess, ftp_downloader, &FtpDownloader::ShowDownloadPage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

