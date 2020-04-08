#include "loginwindows.h"
#include "ui_loginwindows.h"

LoginWindows::LoginWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindows)
{
    ui->setupUi(this);

}

LoginWindows::~LoginWindows()
{
    delete ui;
}

void LoginWindows::on_RegistButton_clicked()
{
    registDialog = new RegistDialog(this);
    registDialog->exec();
}

void LoginWindows::on_FindPasswdButton_clicked()
{
    findPasswordDialog  = new FindPasswdDialog(this);
    findPasswordDialog->exec();
}

void LoginWindows::on_Confirm_clicked()
{
    QString UserName = ui->NameEdit->text();
    QString Password = ui->PasswordEdit->text();
    QString Prameter = UserName + ","+Password+"\0";
    sql = new SqlConnect();

    bool ok = sql->exec(FE_Login,Prameter);
    if(!ok)
    {
        QMessageBox::warning(this,"Tips","登录失败，请检查密码账号正确性或数据库完整性");
    }

}
