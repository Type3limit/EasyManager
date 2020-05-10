#include "productindialog.h"
#include "ui_productindialog.h"

ProductInDialog::ProductInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductInDialog)
{
    ui->setupUi(this);
    sql = nullptr;
    Initlize();
}

ProductInDialog::~ProductInDialog()
{
    delete ui;
}

void ProductInDialog::Initlize()
{
    ui->ProductChooseBox->clear();
    if(sql == nullptr)
        sql = new SqlConnect("ProductIn");
    else {
        delete [] Names;
        delete [] IDs;
        delete [] Images;
    }
    int Count=0;
    bool ok =sql->exec(FE_SelectAll,QString("Manual,productsinfo"));
    if(ok)
    {

        Count = sql->Result().toInt();

        IDs = new QString[Count];
        Names= new QString[Count];
        Images= new QString[Count];
    }
    else {
        QMessageBox::information(this,"tips",sql->Result());
    }
    ok = sql->exec(FE_SelectAll,"Product");
    qDebug()<<sql->Result();
    if(ok)
    {
        QString result  = sql->Result();

        auto itr = result.begin();
        for(int i  = 0 ; i<Count;i++)
        {
            while(*itr!= DepartSambol)
                IDs[i]+=*(itr++);
            itr++;
            while(*itr!=DepartSambol)
                Names[i]+= *(itr++);
            itr++;
            while(*itr!=DepartSambol)
                Images[i]+=*(itr++);
            itr++;
            while(*itr!=SentenceEnded)
                itr++;
            itr++;
            ui->ProductChooseBox->addItem(Names[i]);
        }
    }
    else {
        QMessageBox::warning(this,"warning",sql->Result());
    }
}




void ProductInDialog::on_ProductChooseBox_activated(int index)
{
    if(sql==nullptr)
        sql = new SqlConnect("ProductIn");
    QString pram = QString("ProductCount,%1").arg(IDs[index]);

    if(sql->exec(FE_SelcetSingle,pram))
    {
        QString currentNumber = sql->Result();
        qDebug()<<currentNumber;
        ui->CountHavenEdit->setText(currentNumber);
        if(!Images[index].isNull())
        {
            QImage image(Images[index]);
            QPixmap pixmap = QPixmap::fromImage(image);
            int width = ui->ImageLabel->width();
            int height = ui->ImageLabel->height();
            pixmap = pixmap.scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->ImageLabel->setPixmap(pixmap);
        }
        else {
            ui->ImageLabel->setText("该商品无预览图");
        }
    }
    else {
        QMessageBox::warning(this,"warning",sql->Result());
    }

}

void ProductInDialog::on_ConfirmButton_clicked()
{
    QString Name = ui->ProductChooseBox->currentText();
    QString Numbers = ui->CountEdit->text();
    QString InPrice = ui->InPriceEdit->text();
    QString OutPrice = ui->OutPriceEdit->text();

    if(Name.isEmpty()||Numbers.isEmpty()||InPrice.isEmpty()||OutPrice.isEmpty())
    {
        QMessageBox::warning(this,"warning","关键信息未输入");
        return ;
    }

    if(sql==nullptr)
        sql= new SqlConnect("ProductIn");

    bool ok  = sql->exec(FE_Storage_old,Name+','+Numbers+','+InPrice+','+OutPrice+'\0');

    if(!ok)
        QMessageBox::warning(this,"warning",sql->Result());
    else
        QMessageBox::information(this,"tips",sql->Result());
}
