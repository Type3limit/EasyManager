#include "registdialog.h"
#include "ui_registdialog.h"

RegistDialog::RegistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistDialog)
{
    ui->setupUi(this);
    sql = nullptr;
}

RegistDialog::~RegistDialog()
{
    delete ui;
}

void RegistDialog::on_RegistButton_clicked()
{
    QString Name = ui->NameEdit->text();
    QString Password = ui->PasswordEdit->text();
    QString Passwdconfirm =ui->PasswordConfirm->text();
    QString Quetion =ui->QuestionEdit->text();
    QString Answer = ui->AnswerEdit->text();

    if(sql==nullptr)
        sql = new SqlConnect("regist");


    if(Password!=Passwdconfirm)
    {
        QMessageBox::warning(this,"tips","两次密码输入不一致");
        ui->PasswordEdit->clear();
        ui->PasswordConfirm->clear();
        return;
    }
    QString Param = Name + DepartSambol+Password +DepartSambol+Quetion+DepartSambol+Answer + "\0";



    bool ok = sql->exec(FE_Register,Param);
    QString result = sql->Result();
    ok? QMessageBox::warning(this,"成功",result):QMessageBox::warning(this,"失败",result);
    if(ok)
        this->close();
}
