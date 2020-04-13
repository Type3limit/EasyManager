#include "customeradddialog.h"
#include "ui_customeradddialog.h"

CustomerAddDialog::CustomerAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomerAddDialog)
{
    ui->setupUi(this);
    sql = nullptr;
}

CustomerAddDialog::~CustomerAddDialog()
{
    delete ui;
}

void CustomerAddDialog::on_pushButton_clicked()
{
    if(sql==nullptr)
        sql = new SqlConnect("CustomerAdd");
    QString Name,Passwd,Contanct;
    Name = ui->NameEdit->text();
    Passwd = ui->PasswdEdit->text();
    Contanct = ui->ContanctEdit->text();
    QString Paramter = QString("%1,%2,%3").arg(Name).arg(Passwd).arg(Contanct);
    bool ok = sql->exec(FE_CustomerAdd,Paramter);
    if(ok)
        {
       QMessageBox::information(this,"tips","会员注册成功");
       this->close();
       return;
    }
    else {
        QMessageBox::warning(this,"warning",sql->Result());
        return;
    }
}
