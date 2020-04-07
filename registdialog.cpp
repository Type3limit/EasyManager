#include "registdialog.h"
#include "ui_registdialog.h"

RegistDialog::RegistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistDialog)
{
    ui->setupUi(this);
}

RegistDialog::~RegistDialog()
{
    delete ui;
}
