#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include "QSettings"
#include "QMessageBox"

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();


private slots:
    void on_Apply_clicked();

    void on_Restart_clicked();

    void on_workspacebtn_clicked();

    void on_PicoSDKbtn_clicked();

    void on_workspaceurl_editingFinished();

    void on_PicoSDKurl_editingFinished();

    void on_GitHub_clicked();

private:
    Ui::Setting *ui;
    QString setworkspaceDir;
    QString setPicoSDKDir;
    QMessageBox setmsg;

};

#endif // SETTING_H
