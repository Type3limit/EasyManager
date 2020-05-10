#include "selldialog.h"
#include "ui_selldialog.h"

SellDialog::SellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SellDialog)
{
    ui->setupUi(this);
    sql = nullptr;
    useable = true;
    Initialize();
}

SellDialog::~SellDialog()
{
    delete ui;
}

void SellDialog::Initialize()
{
    ui->ProductChooseBox->clear();
    ui->UserChoosenBox->clear();
    ui->NumberSpinBox->setValue(1);
    if(sql==nullptr)
        sql = new SqlConnect("OnSell");
    else {
        delete [] CustomerName;
        delete [] CustomerAcount;
        delete [] CustomerPasswd;

        delete [] ProductID;
        delete [] ProductName;
        delete [] ProductImage;
        delete [] ProductPrice;
    }
    QString parameter= QString("Manual,productsinfo");
    if(sql->exec(FE_SelectAll,parameter))
    {
        ProductCount = sql->Result().toInt();
        if(ProductCount>0)
        {
            ProductName = new QString[ProductCount];
            ProductImage = new QString[ProductCount];
            ProductPrice = new QString[ProductCount];
            ProductID = new QString[ProductCount];

            parameter = QString("Manual,customerinfo");
            if(sql->exec(FE_SelectAll,parameter))
            {
                CustomerCount = sql->Result().toInt();
                if(CustomerCount>0)
                {
                    CustomerName = new QString[CustomerCount];
                    CustomerPasswd= new QString[CustomerCount];
                    CustomerAcount = new QString[CustomerCount];

                    parameter = QString ("Customer");
                    if(sql->exec(FE_SelectAll,parameter))
                    {
                        QString result = sql->Result();
                        auto itr = result.begin();
                        for(int i  = 0 ; i<CustomerCount;i++)
                        {
                            QString ID;
                            while(*itr!=DepartSambol)
                                ID += *(itr++);
                            itr++;
                            while(*itr!=DepartSambol)
                                CustomerName[i]+=*(itr++);
                            itr++;
                            while(*itr!=DepartSambol)
                                itr++;
                            itr++;
                            while(*itr!=DepartSambol)
                                CustomerPasswd[i]+=*(itr++);
                            itr++;
                            while(*itr!=SentenceEnded&&*itr!='\0')
                                (itr++);
                            itr++;
                            if(sql->exec(FE_SelcetSingle,QString("CustomerAmount,%1").arg(ID)))
                            {
                                CustomerAcount[i] = sql->Result();
                            }
                            else {
                                QMessageBox::warning(this,"warning",sql->Result());
                            }
                            ui->UserChoosenBox->addItem(CustomerName[i]);
                        }
                        if(sql ->exec(FE_SelectAll,"Product"))
                        {
                            result = sql->Result();
                            itr = result.begin();
                            for(int i =0;i<ProductCount;i++)
                            {
                                QString UseAble;
                                while(*itr!=DepartSambol)
                                {
                                    ProductID[i] += *(itr++);
                                }itr++;
                                while(*itr!=DepartSambol)
                                {
                                    ProductName[i]+=*(itr++);
                                }itr++;
                                while(*itr!=DepartSambol)
                                {
                                    ProductImage[i]+=*(itr++);
                                }itr++;
                                while(*itr!=DepartSambol)
                                {
                                    ProductPrice[i]+=*(itr++);
                                }itr++;
                                while(*itr!=DepartSambol)
                                    itr++;
                                itr++;
                                while(*itr!=SentenceEnded)
                                {
                                    UseAble+=*(itr++);
                                }itr++;
                                if(UseAble.toInt()==1)
                                    ui->ProductChooseBox->addItem(ProductName[i]);
                            }
                            useable=true;
                        }

                        else {
                            QMessageBox::warning(this,"warning",sql->Result());
                             useable = false;
                        }
                    }
                    else {
                        QMessageBox::warning(this,"warning",sql->Result());
                         useable = false;
                    }
                }
                else {
                    QMessageBox::warning(this,"warning","暂无任何会员信息");
                     useable = false;

                }
            }
            else {
                QMessageBox::warning(this,"warning",sql->Result());
                 useable = false;

            }
        }
        else {
            QMessageBox::information(this,"tips","暂无任何商品信息");
            useable = false;
        }

    }
}
void SellDialog::on_ConfrimButton_clicked()
{
    double CurrentPrice = ui->AcountLabel->text().toDouble();
    double CurrentMoney = ui->UserAcountLabel->text().toDouble();
    if(CurrentPrice>CurrentMoney)
    {
        ui->ConfirmLabel->setText("当前会员余额不足以购买！");
        return ;
    }
    else {
        ui->ConfirmLabel->clear();
        if(sql==nullptr)
            sql = new SqlConnect("Sell");

        QString paramter = QString("%1,%2,%3,%4").arg(ui->UserChoosenBox->currentText())
                .arg(ui->ProductChooseBox->currentText())
                .arg(CurrentPrice).arg(ui->NumberSpinBox->value());
        if(sql->exec(FE_Consume,paramter))
            QMessageBox::information(this,"tips",sql->Result());
        else {
            QMessageBox::warning(this,"warning",sql->Result());
        }
    }
}

void SellDialog::on_ProductChooseBox_activated(int index)
{
    current_product_index=index;
    if(!ProductImage[index].isNull())
    {
        QImage image(ProductImage[index]);
        QPixmap pixmap = QPixmap::fromImage(image);
        int width = ui->ImageLabel->width();
        int height = ui->ImageLabel->height();
        pixmap = pixmap.scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->ImageLabel->setPixmap(pixmap);

    }
    else {
        ui->ImageLabel->setText("该商品暂无预览图");
    }

    double CurrentAmount = (ui->NumberSpinBox->value()) *
            (ProductPrice[index].toDouble());
    ui->AcountLabel->setText(QString::number(CurrentAmount));

    if(sql ==nullptr)
        sql = new SqlConnect("Sell");
    QString pram = QString("ProductCount,%1").arg(ProductID[index]);
    if(sql->exec(FE_SelcetSingle,pram))
    {
        ui->NumberSpinBox->setMaximum(sql->Result().toInt());
    }
}

void SellDialog::on_UserChoosenBox_activated(int index)
{
    ui->UserAcountLabel->setText(CustomerAcount[index]);
}

void SellDialog::on_NumberSpinBox_valueChanged(int arg1)
{
    double CurrentAmount = (ui->NumberSpinBox->value()) *
            (ProductPrice[current_product_index].toDouble());
    ui->AcountLabel->setText(QString::number(CurrentAmount));
}
