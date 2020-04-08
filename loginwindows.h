#ifndef LOGINWINDOWS_H
#define LOGINWINDOWS_H

#include <QMainWindow>
#include <registdialog.h>
#include <findpasswddialog.h>
#include <sqlconnect.h>
namespace Ui {
class LoginWindows;
}

class LoginWindows : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindows(QWidget *parent = nullptr);
    ~LoginWindows();

private slots:
    void on_RegistButton_clicked();

    void on_FindPasswdButton_clicked();

    void on_Confirm_clicked();

private:
    Ui::LoginWindows *ui;
    RegistDialog* registDialog;
    FindPasswdDialog* findPasswordDialog;
    SqlConnect* sql;
};

#endif // LOGINWINDOWS_H
