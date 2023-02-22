#include "setting.h"
#include "ui_setting.h"
#include "QScreen"
#include "QFile"
#include "QDir"
#include "QFileDialog"
#include "QProcess"
#include "QMessageBox"
#include "QDesktopServices"

QFile setfile;
QDir setdir;
QSettings setsettings(setdir.currentPath()+"/config.ini" ,QSettings::IniFormat);

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    move(screen()->geometry().center() - frameGeometry().center());
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    setworkspaceDir = setsettings.value("Directory/WorkSpace").toString();
    setPicoSDKDir = setsettings.value("Directory/PicoSDK").toString();
    ui->workspaceurl->setText(setworkspaceDir);
    ui->PicoSDKurl->setText(setPicoSDKDir);
    ui->Restart->setEnabled(false);
}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_Apply_clicked()
{
    setsettings.setValue("Directory/WorkSpace", setworkspaceDir);
    setsettings.setValue("Directory/PicoSDK", setPicoSDKDir);
    setmsg.setText("Setting saved! Please tap on Restart for restart!");
    setmsg.show();
    ui->Restart->setEnabled(true);
}

void Setting::on_Restart_clicked()
{
    this->close();
    qApp->closeAllWindows();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}





void Setting::on_workspacebtn_clicked()
{
    setworkspaceDir = QFileDialog::getExistingDirectory(0, "Folder Project", setworkspaceDir);
    ui->workspaceurl->setText(setworkspaceDir);
}


void Setting::on_PicoSDKbtn_clicked()
{
    setPicoSDKDir = QFileDialog::getExistingDirectory(0, "PicoSDK", setPicoSDKDir);
    ui->PicoSDKurl->setText(setPicoSDKDir);
}


void Setting::on_workspaceurl_editingFinished()
{
    setworkspaceDir = ui->workspaceurl->text();
}


void Setting::on_PicoSDKurl_editingFinished()
{
    setworkspaceDir = ui->workspaceurl->text();
}


void Setting::on_GitHub_clicked()
{
        QDesktopServices::openUrl(QUrl("https://github.com/3DThing/RP-2040ProjectGenerator"));
}

