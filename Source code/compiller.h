#ifndef COMPILLER_H
#define COMPILLER_H

#include <QWidget>
#include "QProcess"
#include "QFile"



namespace Ui {
class Compiller;
}

class Compiller : public QWidget
{
    Q_OBJECT

public:
    explicit Compiller(QWidget *parent = nullptr);
    ~Compiller();
    QString dirbuild;
    QString prjname;

public slots:
    void compillerslots(QString projectname, QString projectdir);

private slots:
    void on_Complete_clicked();

private:
    Ui::Compiller *ui;
    QProcess comm;
    QFile file;

};

#endif // COMPILLER_H
