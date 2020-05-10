#include "productinmodeldialog.h"
#include "ui_productinmodeldialog.h"

ProductInModelDialog::ProductInModelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductInModelDialog)
{
    ui->setupUi(this);
}

ProductInModelDialog::~ProductInModelDialog()
{
    delete ui;
}

void ProductInModelDialog::on_pushButton_clicked()
{
    productAddDialog.exec();
}


void ProductInModelDialog::on_pushButton_2_clicked()
{
    productInDialog.Initlize();
    productInDialog.exec();
}
