#include "productadddialog.h"
#include "ui_productadddialog.h"

ProductAddDialog::ProductAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductAddDialog)
{
    ui->setupUi(this);
    sql = nullptr;
}

ProductAddDialog::~ProductAddDialog()
{
    delete ui;
}

void ProductAddDialog::on_FileChooseButton_clicked()
{

    QString FileName = QFileDialog::getOpenFileName(
                this,
                "选择文件",
                ".",
                "Images(*png *jpg *png *jpeg *bmp)");
    if(!FileName.isEmpty())
    {
        ui->FileUrlEdit->setText(FileName);
        QImage image (FileName);
        int width = ui->ImageLabel->width();
        int height = ui->ImageLabel->height();
        QPixmap pixmap = QPixmap::fromImage(image);
        pixmap = pixmap.scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->ImageLabel->setPixmap(pixmap);
    }

}

void ProductAddDialog::on_ConfirmButton_clicked()
{
    QString Name,InCost,OutCost,Numbers,Info,ImageUrl;
    Name = ui->NameEdit->text();
    InCost = ui->InPriceEdit->text();
    OutCost = ui->OutPriceEdit->text();
    Numbers=QString::number(ui->CountSpinBox->value());
    Info = ui->InfoEdit->text();
    ImageUrl= ui->FileUrlEdit->text();
    if(Name.isEmpty()||InCost.isEmpty()||OutCost.isEmpty()||Numbers.isEmpty())
    {
        QMessageBox::warning(this,"warning","必要信息未填写！");
        return ;
    }
    QString Parameter = QString("%1,%2,%3,%4,%5").arg(Name).arg(InCost).arg(ImageUrl).arg(Numbers).arg(Info);
    if(sql == nullptr)
        sql = new SqlConnect("productAdd");
    if(sql ->exec(FE_Storage_new,Parameter))
    {
        QMessageBox::information(this,"tips",sql->Result());
    }
    else {
        QMessageBox::warning(this,"warning ",sql->Result());
    }
}
