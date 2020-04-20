#include "customerrechargedialog.h"
#include "ui_customerrechargedialog.h"

CustomerRechargeDialog::CustomerRechargeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomerRechargeDialog)
{
    ui->setupUi(this);
    sql= nullptr;
}

CustomerRechargeDialog::~CustomerRechargeDialog()
{
    delete ui;
}

void CustomerRechargeDialog::on_pushButton_clicked()
{
    QString Name,Count,CountConfirm;
    Name = ui->NameEdit->text();
    Count = ui->CountEdit->text();
    CountConfirm = ui->CountConfirmEdit->text();

    bool flag= false;
    double Acount = Count.toDouble(&flag);
    if(Count.compare(CountConfirm))
    {
        QMessageBox::warning(this,"tips","两次输入的金额不一致");
        ui->CountEdit->clear();
        ui->CountConfirmEdit->clear();
        return ;
    }
    else if(!flag)
    {
        QMessageBox::warning(this,"tips","输入了非法的金额充值信息");
        ui->CountEdit->clear();
        ui->CountConfirmEdit->clear();
        return;
    }

    else {
       if(sql==nullptr)
           sql = new SqlConnect("ReCharge");
       bool ok = sql->exec(FE_Recharge,QString(Name+","+QString::number(Acount)));
       qDebug()<<ok;
       ok?(QMessageBox::information(this,"tips",sql->Result())):(QMessageBox::warning(this,"warning",sql->Result()));
    }
}
