#ifndef FIRSTSTART_H
#define FIRSTSTART_H

#include <QWidget>
#include "QMessageBox"
#include "QSettings"


namespace Ui {
class FirstStart;
}

class FirstStart : public QWidget
{
    Q_OBJECT

public:
    explicit FirstStart(QWidget *parent = nullptr);
    ~FirstStart();


private slots:
    void on_nextBtn_clicked();

    void on_FirstStart_destroyed();

    void on_workspaceSel_clicked();

    void on_picoSDKCel_clicked();

private:
    QString sworkspaceDir;
    QString sPicoSDKDir;
    Ui::FirstStart *ui;

};

#endif // FIRSTSTART_H
