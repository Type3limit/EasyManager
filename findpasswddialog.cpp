#include "findpasswddialog.h"
#include "ui_findpasswddialog.h"

FindPasswdDialog::FindPasswdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPasswdDialog)
{
    ui->setupUi(this);
}

FindPasswdDialog::~FindPasswdDialog()
{
    delete ui;
}
