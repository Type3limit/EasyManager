#include "loginwindows.h"
#include "ui_loginwindows.h"

LoginWindows::LoginWindows(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindows)
{
    ui->setupUi(this);
    sql = nullptr;
    setWindowOpacity(1);
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);
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


    if(!UserName.compare("")||UserName.contains(DepartSambol))
    {
        QMessageBox::warning(this,"warning","用户名称有误！");
        ui->NameEdit->clear();
        ui->PasswordEdit->clear();
        return ;
    }

    QString Prameter = UserName + DepartSambol+Password+"\0";

    if(sql == nullptr)
      sql = new SqlConnect("login");

    bool ok = sql->exec(FE_Login,Prameter);
    if(!ok)
    {
        QMessageBox::warning(this,"Tips","登录失败!"+sql->Result());
        return ;
    }
    else {
        qDebug()<<"登录成功";
        CurrentUser = UserName;
        this->hide();
        this->close();

        //emit close();
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


void LoginWindows::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Escape)
    {

        if(QMessageBox::Yes == QMessageBox::question(this,"即将退出","确认退出吗?"))
            qApp->exit();
    }
    else {
        return QMainWindow::keyPressEvent(event);
    }

}
