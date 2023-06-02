#include "compiller.h"
#include "ui_compiller.h"
#include <QProcess>
#include <QProgressBar>
#include "QDir"
#include "QFile"
#include "QScreen"


static bool removePath(const QString &path)
{
    bool result = true;
    QFileInfo info(path);
    if (info.isDir()) {
        QDir dir(path);
        foreach (const QString &entry, dir.entryList(QDir::AllDirs | QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot)) {
            result &= removePath(dir.absoluteFilePath(entry));
        }
        if (!info.dir().rmdir(info.fileName()))
            return false;
    } else {
        result = QFile::remove(path);
    }
    return result;
}

Compiller::Compiller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Compiller)
{
    ui->setupUi(this);
    move(screen()->geometry().center() - frameGeometry().center());
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

}

Compiller::~Compiller()
{
    delete ui;
}

void Compiller::compillerslots(QString name, QString dirproject)
{
    ui->Complete->setEnabled(false);
    QDir dir;
    dirbuild = dirproject;
    prjname = name;
    ui->console->setText(dirbuild + "\n" + prjname);
    if(dir.exists(dirproject)){
        removePath(dirproject);
    }
    dir.mkdir(dirbuild);
    QStringList arr1,arr2;
    arr1<<"..";
    arr2<<prjname;
    comm.setWorkingDirectory(dirbuild);
    comm.start("cmake", arr1);
    while(comm.waitForFinished()){
    comm.waitForReadyRead();
    ui->console->append(comm.readAll());
    }
    
    comm.start("make", arr2);
    while(comm.waitForFinished()){
        comm.waitForReadyRead();
        ui->console->append(comm.readAll());
    }
    if(QFile::exists(dirproject + "/" + prjname + ".uf2")){
        ui->Complete->setEnabled(true);
        ui->Complete->setText("Complete");
    } else {
        ui->Complete->setEnabled(true);
        ui->Complete->setText("Error");
    }
}


void Compiller::on_Complete_clicked()
{
    this->close();
}

