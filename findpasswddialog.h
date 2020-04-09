#ifndef FINDPASSWDDIALOG_H
#define FINDPASSWDDIALOG_H

#include <QDialog>
#include <sqlconnect.h>
#include <resetpasswddialog.h>
namespace Ui {
class FindPasswdDialog;
}

class FindPasswdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindPasswdDialog(QWidget *parent = nullptr);
    ~FindPasswdDialog();

private slots:
    void on_pushButton_clicked();

    void on_NameEdit_editingFinished();

private:
    Ui::FindPasswdDialog *ui;
    ResetPasswdDialog * rsDialog;
    SqlConnect * sql;
    QString Question,Answer,Name;
};

#endif // FINDPASSWDDIALOG_H
