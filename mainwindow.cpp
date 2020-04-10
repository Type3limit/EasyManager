#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sql = nullptr;
    connect(&loginwindow,(&LoginWindows::close),this,(&MainWindow::on_loginwindows_close));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SysStart()
{
    loginwindow.show();
}

void MainWindow::on_loginwindows_close()
{
    this->show();
    QString Name = loginwindow.GetCurrentUser();
    customizeDialog.SetName(Name);
    QString WelcomeWords = QString("Welcome! %1").arg(Name);
    ui->WelcomeLabel->setText(WelcomeWords);
    if(sql == nullptr)
        sql = new SqlConnect("select");
    QString param = QString("User,%1,%2").arg(Name).arg("user_model_choose");
    bool ok = sql->exec(FE_Selcet,param);
    int result = 0;
    ok? result=sql->Result().toInt():QMessageBox::warning(this,"warning",sql->Result());

    if(result == 0)
    {

        customizeDialog.exec();
        sql->exec(FE_Selcet,param);
        result= sql->Result().toInt();
        if(result == 0)
        {
            QMessageBox::warning(this,"warning","客制化异常!请重新登录！");
            this->close();
            loginwindow.show();
            return ;
        }
    }
    QMessageBox::information(this,"tips","该用户客制化已完成！");

}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::No == QMessageBox::question(this,"warning","确认退出吗？",QMessageBox::Ok,QMessageBox::No)) event->ignore();
    else {
        sql->exec(FE_Logout,loginwindow.GetCurrentUser());
        QMainWindow::closeEvent(event);
    }
}
