#include "productindialog.h"
#include "ui_productindialog.h"

ProductInDialog::ProductInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductInDialog)
{
    ui->setupUi(this);
}

ProductInDialog::~ProductInDialog()
{
    delete ui;
}
