#include "localfile.h"

// TODO
QDir minecraft_folder;

LocalFile::LocalFile(QWidget *parent)
    : QWidget{parent}
{

}

void LocalFile::GetMinecraftFolder()
{
    this->minecraft_folder_ = QFileDialog::getExistingDirectory(this, "请选择\".minecraft\"文件夹", "//", QFileDialog::ShowDirsOnly);
    while (this->minecraft_folder_.path().toStdString().substr(this->minecraft_folder_.path().toStdString().rfind('/') + 1) != ".minecraft")
    {
        short ret = QMessageBox::critical(this, "文件夹打开失败", "请选择正确的.minecraft的文件夹!", QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        if (!ret)
        {
            return;
        }
        this->minecraft_folder_ = QFileDialog::getExistingDirectory(this, "请选择\".minecraft\"文件夹", "//", QFileDialog::ShowDirsOnly);
    }
    qDebug() << minecraft_folder_;

    //TODO
    minecraft_folder = this->minecraft_folder_;

    emit GetMcFolderSuccess();
}
