#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    ,ui(new Ui::MainWindow)
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(Qt::Key_Escape == event->key())
    {
        this->close();
    }
}

void MainWindow::on_loginwindows_close()
{

    QString Name = loginwindow.GetCurrentUser();
    customizeDialog.SetName(Name);
    QString WelcomeWords = QString("Welcome!        %1").arg(Name);
    ui->WelcomeLabel->setText(WelcomeWords);
    if(sql == nullptr)
        sql = new SqlConnect("select");
    QString param = QString("User,%1,%2").arg(Name).arg("user_model_choose");
    bool ok = sql->exec(FE_SelcetSingle,param);
    int result = 0;
    ok? result=sql->Result().toInt():QMessageBox::warning(this,"warning",sql->Result());

    if(result == 0)
    {
        customizeDialog.exec();
        QString param = QString("User,%1,%2").arg(Name).arg("user_model_choose");
        sql->exec(FE_SelcetSingle,param);
        result= sql->Result().toInt();
        if(result == 0)
        {
            QMessageBox::warning(this,"warning","客制化异常!请重新登录！");
            this->close();
            loginwindow.show();
            return ;
        }
    }
        LoadCustomize();
}

void MainWindow::LoadCustomize()
{

    this->show();
    if(sql==nullptr)
        sql=new SqlConnect("LoadCustomize");
    if(sql->exec(FE_LoadCustomize,loginwindow.GetCurrentUser()))
    {
        QString result = sql->Result();
        auto itr = result.begin();
        for(int i = 0; i< ModelNumber;i++,itr+=2)
        {
            QString  cur = *itr;
           ModelChoose[i] = cur.toInt();
        }


        if(ModelChoose[Mo_sell]==1)
        {
            ui->SellButton->show();
        }
        else
            ui->SellButton->hide();

        if(ModelChoose[Mo_queue]==1)
        {
            ui->QueueButton->show();
        }
        else {
            if(ModelChoose[Mo_reserve]==1)
                ui->QueueButton->show();
            else {
                ui->QueueButton->hide();
            }
        }

        if(ModelChoose[Mo_reserve]==1)
        {
            ui->QueueButton->show();
        }
        else {
            if(ModelChoose[Mo_queue]==1)
                ui->QueueButton->show();
            else {
                ui->QueueButton->hide();
            }
        }

        if(ModelChoose[Mo_product]==1)
        {
            ui->ProductinButton->show();
            ui->ProductoutButton->show();
            ui->ProductinfoButton->show();
        }
        else {
            ui->ProductinButton->hide();
            ui->ProductoutButton->hide();
            ui->ProductinfoButton->hide();
        }
        if(ModelChoose[Mo_customer]==1)
        {
            ui->CustomerinfoButton->show();
            ui->CutomeraddButton->show();
            ui->CustomerrechargeButton->show();
        }
        else {
            ui->CustomerinfoButton->hide();
            ui->CutomeraddButton->hide();
            ui->CustomerrechargeButton->hide();
        }

    }
    else {
        QMessageBox::warning(this,"warning",sql->Result());
        this->close();
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::No == QMessageBox::question(this,"warning","确认退出吗？",QMessageBox::Ok,QMessageBox::No)) event->ignore();
    else {
        sql->exec(FE_Logout,loginwindow.GetCurrentUser());
    }
}

void MainWindow::on_LoginoutButton_2_clicked()
{

    if(this->close())
      loginwindow.show();
}

void MainWindow::on_SellButton_clicked()
{
    sellDialog.exec();
}

void MainWindow::on_CutomeraddButton_clicked()
{
    customerAddDialog.exec();
}

void MainWindow::on_CustomerrechargeButton_clicked()
{
    CRechargeDialog.exec();
}

void MainWindow::on_ProductinButton_clicked()
{
    ModelDialog.exec();
}
