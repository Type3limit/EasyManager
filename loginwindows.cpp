#include "loginwindows.h"
#include "ui_loginwindows.h"

LoginWindows::LoginWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindows)
{
    ui->setupUi(this);
    sql = nullptr;
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

    if(sql == nullptr)
      sql = new SqlConnect("login");

    bool ok = sql->exec(FE_Login,Prameter);
    if(!ok)
    {
        QMessageBox::warning(this,"Tips","登录失败!"+sql->Result());
        qDebug()<<sql->Result();
    }
    else {
        qDebug()<<"登录成功";
        this->hide();
        CurrentUser = UserName;



        emit close();
    }

}


QString LoginWindows::GetCurrentUser()
{
    if(!CurrentUser.isNull())
    return CurrentUser;
    else {
        return "错误用户";
    }
}
