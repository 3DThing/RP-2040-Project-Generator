#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPixmap"
#include "QDir"
#include "QMessageBox"
#include "QFileDialog"
#include <QFile>
#include "QStyle"
#include "QScreen"
#include "QProcess"
#include "compiller.h"
#include "QDesktopServices"

QFile file;
QDir dir;
QSettings settings(dir.currentPath()+"/config.ini" ,QSettings::IniFormat);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cmd = new QProcess(this);

    fStart = new FirstStart;

    gccarm = new Compiller;

    setting = new Setting;

    connect(this, &MainWindow::compillersignal, gccarm, &Compiller::compillerslots);

    ui->CreateVSCBtn->setEnabled(false);
    ui->BuildBtn->setEnabled(false);
    ui->SerialBtn->setEnabled(false);


    if(!file.exists(dir.currentPath()+"/config.ini")){
        fStart->show();
        this->setEnabled(false);
    }else{
        this->setEnabled(true);
        workspaceDir = settings.value("Directory/WorkSpace").toString();
        picoDir = settings.value("Directory/PicoSDK").toString();
        ui->PrjDirTxt->setText(workspaceDir);
        ui->PicoSDKTxT->setText(picoDir);
        if(!dir.exists(workspaceDir)){
            dir.mkdir(workspaceDir);
            msg.setText("Workspace folder has been created!\nIn local url: "+workspaceDir);
            msg.show();
        }
    }
    move(screen()->geometry().center() - frameGeometry().center());
    QPixmap logo(":/img/Raspberry_Pi_Logo.png");
    homeDir = dir.homePath();
    appDir = dir.currentPath();

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_DirBtn_clicked()
{
    workspaceDir = QFileDialog::getExistingDirectory(0, "Root Folder Projects", workspaceDir);
    ui->PrjDirTxt->setText(workspaceDir);
}

void MainWindow::on_CreateBtn_clicked()
{
    if(ui->PrjNameTxT->text().isEmpty()){
        msg.setText("Please enter name");
        msg.show();
    } else if (ui->PrjDirTxt->text().isEmpty()){
        msg.setText("Please select project");
        msg.show();
    } else if (ui->PicoSDKTxT->text().isEmpty()){
        msg.setText("Please select PicoSDK C/C++");
        msg.show();
    } else {
        if(!file.exists(picoDir+"/pico_sdk_init.cmake")){
            msg.setText("PicoSDK C/C++ is not found!");
            msg.show();
        } else {
            if (file.exists(projectDir + "/CMakeLists.txt")){
                msg.setText("Project allready created!");
                msg.show();
            } else {
                if(!dir.exists(projectDir)){
                    dir.mkdir(projectDir);
                    CreateNewProject(projectName, projectDir);
                    msg.setText("The project was successfully created.\nAvailable by url: " + projectDir);
                    msg.show();
                    if(ui->simplebox->checkState()==2){
                        QString fromlibPath = dir.currentPath() + "/lib";
                        QString tolibPath = projectDir + "/lib";
                        dir.mkdir(tolibPath);
                        copyPath(fromlibPath, tolibPath);
                    }
                } else {
                    CreateNewProject(projectName, projectDir);
                    msg.setText("The project was successfully created.\nAvailable by url: " + projectDir);
                    msg.show();
                    if(ui->simplebox->checkState()==2){
                        QString fromlibPath = dir.currentPath() + "/lib";
                        QString tolibPath = projectDir + "/lib";
                        dir.mkdir(tolibPath);
                        copyPath(fromlibPath + "/lib", tolibPath);

                    }
                }
            }

        }
    }

    if(file.exists(projectDir + "/CMakeLists.txt")){
        ui->CreateVSCBtn->setEnabled(true);
        ui->BuildBtn->setEnabled(true);
        ui->CreateBtn->setEnabled(false);
    } else {
        ui->CreateBtn->setEnabled(true);
        ui->BuildBtn->setEnabled(false);
        ui->CreateVSCBtn->setEnabled(false);
    }
}

void MainWindow::CreateNewProject(QString sprjname, QString sprjdir){
    QString maincppname = "/main.cpp";
    QFile maincpp(sprjdir + "/" + maincppname);
    if (maincpp.open(QIODevice::ReadWrite)) {
        QTextStream stream(&maincpp);
        stream <<"""#include <stdio.h>\n"
              <<SimpleLib()<<
                 "\n"
                 "int main(){\n"
                 "    //You program\n"
                 "    for(;;){\n"
                 "    //loop program\n"
                 "    }\n"
                 "}";
        maincpp.close();
    }

    QString cmaketxtname = "/CMakeLists.txt";
    QFile cmaketxt(sprjdir + "/" + cmaketxtname);
    if (cmaketxt.open(QIODevice::ReadWrite)) {
        QTextStream stream(&cmaketxt);
        stream <<"""cmake_minimum_required(VERSION 3.13)\n"
                              "include(~/pico/pico-sdk/pico_sdk_init.cmake)\n"
                              "project("<<sprjname<<"_prj)\n"
                              "pico_sdk_init()\n"
                              "add_executable("<<sprjname<<"\n"
                              "    main.cpp\n"
                              ")\n"
                              "target_link_libraries("<<sprjname<<""
                              " pico_stdlib"
                              ""<<SPI()<<""
                              ""<<i2c()<<""
                              ""<<DMA()<<""
                              ""<<PIO()<<""
                              ""<<interpolation()<<""
                              ""<<timer()<<""
                              ""<<WatchDog()<<""
                              ""<<Clock()<<""
                              " hardware_adc hardware_pwm )\n"
                              ""<<UARTSerial()<<"\n"
                              ""<<USBSerial()<<"\n"
                              "pico_add_extra_outputs("<<sprjname<<")\n"
                              "";
        cmaketxt.close();
    }
}


void MainWindow::on_PrjNameTxT_textChanged(const QString &arg1)
{

}


void MainWindow::on_SDKBtn_clicked()
{
    picoDir = QFileDialog::getExistingDirectory(0, "PicoSDK", picoDir);
    ui->PicoSDKTxT->setText(picoDir);
}


void MainWindow::on_CreateVSCBtn_clicked()
{

    cmd->startCommand("code -a " +  projectDir);
}


void MainWindow::on_PrjNameTxT_editingFinished()
{
    projectDir = workspaceDir + "/" + projectName;

}

//CheckBox
QString MainWindow::SPI(){
    if(ui->spibox->checkState()==2){
        return " hardware_spi \n spi_flash \n spi_slave \n spi_master ";
    } else {
        return 0;
    }
}

QString MainWindow::i2c(){
    if(ui->i2cbox->checkState()==2){
        return " hardware_i2c pico_i2c_slave ";
    } else {
        return 0;
    }
}

QString MainWindow::DMA(){
    if(ui->dmabox->checkState()==2){
        return " hardware_dma ";
    } else {
        return 0;
    }
}

QString MainWindow::PIO(){
    if(ui->piobox->checkState()==2){
        return " hello_gpio_irq ";
    } else {
        return 0;
    }
}

QString MainWindow::interpolation(){
    if(ui->intbox->checkState()==2){
        return " hardware_interp ";
    } else {
        return 0;
    }
}

QString MainWindow::timer(){
    if(ui->timerbox->checkState()==2){
        return "";
    } else {
        return 0;
    }
}

QString MainWindow::WatchDog(){
    if(ui->wdbox->checkState()==2){
        return "";
    } else {
        return 0;
    }
}

QString MainWindow::Clock(){
    if(ui->clockbox->checkState()==2){
        return "";
    } else {
        return 0;
    }
}

QString MainWindow::SimpleLib(){
    if(ui->simplebox->checkState()==2){
        return "#include \"lib/simpleIO/simpleIO.h\"\n#include \"lib/timer.h\"\n\n\nsimpleIO io;\n";
    } else {
        return 0;
    }
}

QString MainWindow::USBSerial(){
    if(ui->usbbox->checkState()==2){
        return "pico_enable_stdio_usb(" + projectName  + " 1)";
    } else {
        return "pico_enable_stdio_usb(" + projectName  + " 0)";
    }
}

QString MainWindow::UARTSerial(){
            if(ui->uartbox->checkState()==2){
                return "pico_enable_stdio_uart(" + projectName  + " 1)";
            } else {
                return "pico_enable_stdio_uart(" + projectName  + " 0)";
            }
}

void MainWindow::copyPath(QString src, QString dst)
{
    QDir dir(src);
    if (! dir.exists())
        return;

    foreach (QString d, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString dst_path = dst + QDir::separator() + d;
        dir.mkpath(dst_path);
        copyPath(src+ QDir::separator() + d, dst_path);
    }

    foreach (QString f, dir.entryList(QDir::Files)) {
        QFile::copy(src + QDir::separator() + f, dst + QDir::separator() + f);
    }
}

void MainWindow::on_PrjNameTxT_textEdited(const QString &arg1)
{
    projectName = ui->PrjNameTxT->text();
    if(dir.exists(workspaceDir + "/" + projectName)){
        ui->CreateVSCBtn->setEnabled(true);
        ui->CreateBtn->setEnabled(false);
        ui->BuildBtn->setEnabled(true);
    } else {
        ui->CreateVSCBtn->setEnabled(false);
        ui->CreateBtn->setEnabled(true);
        ui->BuildBtn->setEnabled(false);
    }
}


void MainWindow::on_BuildBtn_clicked()
{
    QString builddir = projectDir + "/build";
    emit compillersignal(projectName, builddir);
    gccarm->show();
    ui->BuildBtn->setEnabled(true);
}


void MainWindow::on_help_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/3DThing/RP-2040ProjectGenerator"));
}


void MainWindow::on_QuitBtn_clicked()
{
    qApp->exit(0);
}


void MainWindow::on_SettingBtn_clicked()
{
    setting->show();
}

