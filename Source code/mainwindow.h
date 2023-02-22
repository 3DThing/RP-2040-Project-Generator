#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QMessageBox"
#include "QSettings"
#include "firststart.h"
#include "QProcess"
#include "compiller.h"
#include "setting.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    void copyPath(QString src, QString dst);
    void SettingInicializations();
    void LoadSetting();
    void CreateNewProject(QString sprjname, QString sprjdir);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString projectName;
    QString homeDir;
    QString appDir;
    QString picoDir;
    QString workspaceDir;
    QString projectDir;
    QString SPI();
    QString i2c();
    QString DMA();
    QString PIO();
    QString interpolation();
    QString timer();
    QString WatchDog();
    QString Clock();
    QString SimpleLib();
    QString USBSerial();
    QString UARTSerial();

    QMessageBox msg;

private slots:
    void on_DirBtn_clicked();

    void on_CreateBtn_clicked();

    void on_PrjNameTxT_textChanged(const QString &arg1);

    void on_SDKBtn_clicked();

    void on_CreateVSCBtn_clicked();

    void on_PrjNameTxT_editingFinished();

    void on_PrjNameTxT_textEdited(const QString &arg1);

    void on_BuildBtn_clicked();

    void on_help_clicked();

    void on_QuitBtn_clicked();

    void on_SettingBtn_clicked();

private:
    Ui::MainWindow *ui;
    FirstStart *fStart;
    Compiller *gccarm;
    QProcess *cmd;
    Setting *setting;


signals:
    void compillersignal(QString projectname, QString projectdir);

};
#endif // MAINWINDOW_H
