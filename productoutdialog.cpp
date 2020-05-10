#include "productoutdialog.h"
#include "ui_productoutdialog.h"

ProductOutDialog::ProductOutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProductOutDialog)
{
    ui->setupUi(this);
    sql = nullptr;
    Initialize();
}

ProductOutDialog::~ProductOutDialog()
{
    delete ui;
}


void ProductOutDialog::Initialize()
{
    ui->ProductView->clear();
    if(sql==nullptr)
       sql = new SqlConnect("ProductOut");
    else {
        delete [] IDs;
        delete [] Names;
        delete [] Images;
        delete [] Costs;
        delete [] Infoes;
    }
    QString paramter = QString("Manual,productsinfo");
    bool ok = sql->exec(FE_SelectAll,paramter);
    if(ok)
    {
        count = sql->Result().toInt();

        if(count)
        {
            IDs = new QString[count];
            Names =new QString[count];
            Images = new QString[count];
            Costs = new QString[count];
            Infoes = new QString[count];

            ok = sql ->exec(FE_SelectAll,"Product");
            if(ok)
            {
                QString result = sql->Result();
                qDebug()<<result;
                auto itr = result.begin();
                for(int i =0;i<count;i++)
                {
                    while(*itr!=DepartSambol)
                    {
                        IDs[i] += *(itr++);
                    }itr++;
                    while(*itr!=DepartSambol)
                    {
                        Names[i]+=*(itr++);
                    }itr++;
                    while(*itr!=DepartSambol)
                    {
                        Images[i]+=*(itr++);
                    }itr++;
                    while(*itr!=DepartSambol)
                    {
                        Costs[i]+=*(itr++);
                    }itr++;
                    while(*itr!=DepartSambol)
                    {
                        Infoes[i]+=*(itr++);
                    }itr++;
                    while(*itr!=SentenceEnded)
                    {
                        itr++;
                    }itr++;
                    ui->ProductView->addItem(Names[i]);

                }
            }
        }
    }
    else {
        QMessageBox::warning(this,"warning","读入商品信息失败");
    }
}



void ProductOutDialog::on_ComfirmButton_clicked()
{
    if(sql==nullptr)
        sql = new SqlConnect("ProductOut");
    CurrentCount = QString::number(ui->NumberBox->value());
    bool ok  = sql->exec(FE_Release,QString("%1,%2,%3").arg(CurrentName).arg(CurrentCount).arg(CurrentCost));
    ok?(QMessageBox::information(this,"成功","商品出库成功")):(QMessageBox::warning(this,"失败",sql->Result()));
}

void ProductOutDialog::on_ProductView_itemDoubleClicked(QListWidgetItem *item)
{
    QString Name = item->text();
    CurrentName = Name;
    if(sql == nullptr)
        sql = new SqlConnect("ProductOut");
    ui->ProductChooseEdit->setText(Name);
    int index=0;
    while(index<count)
    {
        if(!Names[index].compare(Name))
            break;
        index++;
    }
    bool ok = sql->exec(FE_SelcetSingle,QString("ProductCount,%1").arg(IDs[index]));
    qDebug()<<IDs[index];
    if(ok)
    {
        ui->NumberBox->setValue(1);
        ui->NumberBox->setMinimum(0);
        ui->NumberBox->setMaximum(sql->Result().toInt());
        ui->CountLabel->setText(sql->Result());
        CurrentCost = Costs[index];
        ui->CostEdit->setText(Costs[index]);
        if(!Images[index].isEmpty())
        {
            QImage image(Images[index]);
            QPixmap pixmap = QPixmap::fromImage(image);
            int width = ui->ProductViewLabel->width();
            int height = ui->ProductViewLabel->height();
            pixmap = pixmap.scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
            ui->ProductViewLabel->setPixmap(pixmap);
        }
        else {
            ui->ProductViewLabel->setText("该商品无预览图");
        }
    }
    else {
        QMessageBox::warning(this,"warning",sql->Result());
    }
}
