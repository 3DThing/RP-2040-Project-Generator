#include "firststart.h"
#include "ui_firststart.h"
#include <QApplication>
#include <QProcess>
#include "QScreen"
#include "QFile"
#include "QDir"
#include "QFileDialog"


QFile sfile;
QDir sdir;
QSettings ssettings(sdir.currentPath()+"/config.ini" ,QSettings::IniFormat);


FirstStart::FirstStart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstStart)
{
    ui->setupUi(this);
    move(screen()->geometry().center() - frameGeometry().center());
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    sworkspaceDir = sdir.homePath()+"/pico-workspace";
    sPicoSDKDir = sdir.homePath()+"/pico/pico-sdk";
    ui->WorkspaseTxt->setText(sworkspaceDir);
    ui->PicoSDKTxt->setText(sPicoSDKDir);

}


FirstStart::~FirstStart()
{
    delete ui;
}

void FirstStart::on_nextBtn_clicked()
{
    ssettings.setValue("Directory/WorkSpace", sworkspaceDir);
    ssettings.setValue("Directory/PicoSDK", sPicoSDKDir);
    this->close();
    qApp->closeAllWindows();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}



void FirstStart::on_workspaceSel_clicked()
{
    sworkspaceDir = QFileDialog::getExistingDirectory(0, "Folder Project", sworkspaceDir);
    ui->WorkspaseTxt->setText(sworkspaceDir);
}


void FirstStart::on_picoSDKCel_clicked()
{
    sPicoSDKDir = QFileDialog::getExistingDirectory(0, "Folder Project", sPicoSDKDir);
    ui->PicoSDKTxt->setText(sPicoSDKDir);
}


void FirstStart::on_FirstStart_destroyed()
{

}

