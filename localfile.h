#ifndef LOCALFILE_H
#define LOCALFILE_H

#include <QWidget>
#include <QString>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

class LocalFile : public QWidget
{
    Q_OBJECT
public:
    explicit LocalFile(QWidget *parent = nullptr);
    // 将.minecraft文件夹的路径赋给成员变量minecraft_folder
    void GetMinecraftFolder();

signals:
    void GetMcFolderSuccess();

public:
    // .minecraft文件夹的路径
    QDir minecraft_folder_;
};

#endif // LOCALFILE_H
