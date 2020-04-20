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
