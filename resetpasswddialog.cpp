#include "resetpasswddialog.h"
#include "ui_resetpasswddialog.h"

ResetPasswdDialog::ResetPasswdDialog(QString CurrentName,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResetPasswdDialog)
{
    ui->setupUi(this);
    sql=nullptr;
    CurrentUser = CurrentName;
}

ResetPasswdDialog::~ResetPasswdDialog()
{
    delete ui;
}

void ResetPasswdDialog::on_Comfirm_clicked()
{
    QString NewPasswd;
    if(sql==nullptr)
        sql = new SqlConnect("ResetPasswd");

    NewPasswd = ui->PasswdEdit->text();

    QString param  = QString("%1,%2").arg(CurrentUser).arg(NewPasswd);
    bool ok = sql->exec(FE_ResetPasswd,param);
    if(ok)
    {
        QMessageBox::critical(this,"tips","修改完成");
        this->close();
    }
    else {
        QMessageBox::warning(this,"warning","失败，"+sql->Result());
    }
}
