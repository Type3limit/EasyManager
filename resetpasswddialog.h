#ifndef RESETPASSWDDIALOG_H
#define RESETPASSWDDIALOG_H

#include <QDialog>
#include <sqlconnect.h>
namespace Ui {
class ResetPasswdDialog;
}

class ResetPasswdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResetPasswdDialog(QString CurrentName,QWidget *parent = nullptr);
    ~ResetPasswdDialog();

private slots:
    void on_Comfirm_clicked();

private:
    Ui::ResetPasswdDialog *ui;
    SqlConnect* sql;
    QString CurrentUser;
};

#endif // RESETPASSWDDIALOG_H
