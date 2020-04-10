#include "customizedialog.h"
#include "ui_customizedialog.h"

CustomizeDialog::CustomizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomizeDialog)
{
    ui->setupUi(this);
    sql = nullptr;
    initilize();
}


void CustomizeDialog::initilize()
{
    CurrentIndex = 0;
    ModelDescribe[Mo_customer] = "会员信息管理\n用于商户对会员信息的管理，加入此模块将会对会员的信息进行记录并管理，涉及到对会员关键信息的记录和处理等内容";
    ModelDescribe[Mo_product]="商品信息管理\n用于对商品信息的管理，加入此模块将会对各类商品的信息进行记录并管理，涉及到对商品条目、库存等内容的管理";
    ModelDescribe[Mo_queue]="等待队列\n用于会员的排队等待，加入此模块将提供一个为会员排队等待的队列，按照排队的先后顺序进行服务";
    ModelDescribe[Mo_reserve]="预约功能\n用于提供一个服务或商品预约的模块，加入此模块将会为会员提供一个预约的功能";
    ModelDescribe[Mo_sell]="直售功能\n用于提供将商品或服务直接向外部出售的模块，加入此模块将能完成在不需要会员的情况下出售商品的功能";

    ui->DescribeLabel->setText("欢迎进行客制化！接下来请根据本文字框内的具体描述来决定您是否需要加载具体的模块！");

    ui->CustomizeProcessBar->hide();
    ui->CompliteButton->hide();
    ui->backbutton ->hide();
    ui->SureButton->hide();
    ui->CancelButton->hide();
}




CustomizeDialog::~CustomizeDialog()
{
    delete ui;
}

bool CustomizeDialog::SetName(QString Name)
{
    if(!UserName.compare(""))
    {
            UserName = Name;
            return true;
    }

    else {
        return false;
    }
}

void CustomizeDialog::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::Cancel == QMessageBox::question(this,"tips","客制化尚未完成，确定要退出吗？"))
    {
        event->ignore();
    }
}

void CustomizeDialog::on_StartButton_clicked()
{
    ui->StartButton->hide();

    ui->CustomizeProcessBar->show();
    ui->CustomizeProcessBar->setValue(0);
    ui->SureButton->show();
    ui->CancelButton->show();

    ModelProcess();

}



void CustomizeDialog::ModelProcess()
{
    if(CurrentIndex<ModelNumber)
    {
        if(CurrentIndex>0)
            ui->backbutton->show();
        else {
            ui->backbutton->hide();
        }


        ui->DescribeLabel->setText(ModelDescribe[CurrentIndex]);
        ui->DescribeLabel->adjustSize();
        ui->DescribeLabel->setWordWrap(true);
        ui->DescribeLabel->setAlignment(Qt::AlignTop);

        ui->CustomizeProcessBar->setValue(ProcessStep*(CurrentIndex+1));
    }
    if(CurrentIndex>4)
        ui->CompliteButton->show();
    else {
        ui->CompliteButton->hide();
    }
}

void CustomizeDialog::on_SureButton_clicked()
{
    Model[CurrentIndex] = 1;
    CurrentIndex++;
    ModelProcess();
}

void CustomizeDialog::on_CancelButton_clicked()
{
      Model[CurrentIndex] = 0;
      CurrentIndex++;
      ModelProcess();
}

void CustomizeDialog::on_backbutton_clicked()
{
    Model[CurrentIndex-1]=0;
    CurrentIndex--;
    ModelProcess();
}



void CustomizeDialog::on_CompliteButton_clicked()
{
    if(sql==nullptr)
    {
        sql = new SqlConnect ("Customize");
    }

    QString sentence = UserName;
    for(int i =0;i<ModelNumber;i++)
    {
        sentence+=QString(",%1").arg(Model[i]);
    }
    bool ok = sql->exec(FE_Customization,sentence);

    if(!ok)
        QMessageBox::warning(this,"Failed",sql->Result());
    else {
        QMessageBox::information(this,"Success",sql->Result());
        this->close();
    }
}
