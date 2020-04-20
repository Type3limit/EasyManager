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
    QString Name,Passwd,Contanct,Confirm;
    Name = ui->NameEdit->text();
    Passwd = ui->PasswdEdit->text();
    Confirm= ui->ConfirmEdit->text();


    if(Confirm.compare(Passwd)!=0)
    {
        QMessageBox::warning(this,"tips","两次输入的密码不一致");
        ui->PasswdEdit->clear();
        ui->ConfirmEdit->clear();
        return;
    }

    Contanct = ui->ContanctEdit->text();
    QString Paramter = QString ("%1,%2,%3").arg("Customer").arg(Name).arg("customer_name");
    sql->exec(FE_Selcet,Paramter);
    QString result = sql->Result();

    if(!result.compare(""))
    {
        Paramter = QString("%1,%2,%3").arg(Name).arg(Passwd).arg(Contanct);
        bool ok = sql->exec(FE_CustomerAdd,Paramter);
        if(ok)
        {
            QMessageBox::information(this,"tips","会员注册成功");
            this->close();
            ui->NameEdit->clear();
            ui->PasswdEdit->clear();
            ui->ContanctEdit->clear();
            return;

        }
        else {
            QMessageBox::warning(this,"warning",sql->Result());
            return;
        }
    }
    else {
        QMessageBox::warning(this,"warning","会员名称已存在");
        ui->NameEdit->clear();
        return;
    }

}
