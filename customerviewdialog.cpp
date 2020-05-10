#include "customerviewdialog.h"
#include "ui_customerviewdialog.h"

CustomerViewDialog::CustomerViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomerViewDialog)
{
    ui->setupUi(this);
    sql = nullptr;
    Initilaize();
}

CustomerViewDialog::~CustomerViewDialog()
{
    delete ui;
}


void CustomerViewDialog::Initilaize()
{
    ui->CustomerBox->clear();

    if(sql == nullptr)
        sql = new SqlConnect("CustomerView");
    else {
        delete [] Names;
        delete [] IDs;
        delete [] Contancts;
        delete [] Amounts;
        delete [] RegistTimes;
    }
    QString paramter = QString("Manual,customerinfo");
    bool ok=sql->exec(FE_SelectAll,paramter);
    if(ok)
    {
        int CustomerCount = sql->Result().toInt();

        Names = new QString[CustomerCount];
        IDs = new QString[CustomerCount];
        Contancts = new QString[CustomerCount];
        Amounts = new QString[CustomerCount];
        RegistTimes = new QString[CustomerCount];
        ok = sql->exec(FE_SelectAll,"Customer");
        if(ok)
        {
            QString result  = sql->Result();
            auto itr = result.begin();
            for(int i  = 0 ; i<CustomerCount;i++)
            {
                while(*itr!=DepartSambol)
                    IDs[i]+= *(itr++);
                itr++;
                while(*itr!=DepartSambol)
                    Names[i]+=*(itr++);
                itr++;
                while(*itr!=DepartSambol)
                    Contancts[i]+=*(itr++);
                itr++;
                while(*itr!=DepartSambol)
                    itr++;
                itr++;
                while(*itr!=SentenceEnded&&*itr!='\0')
                    RegistTimes[i]+=*(itr++);
                itr++;
                ui->CustomerBox->addItem(Names[i]);
            }
        }
    }
    else {
        QMessageBox::warning(this,"warning",sql->Result());
    }
}


void CustomerViewDialog::on_CustomerBox_activated(int index)
{
    ui->ContanctLabel->setText(Contancts[index]);

    ui->RegiteTimeLabel->setText(RegistTimes[index]);

    if(sql == nullptr)
        sql = new SqlConnect("CustomerView");
    bool ok = sql->exec(FE_SelcetSingle,QString("CustomerAmount,%1").arg(IDs[index]));
    if(ok)
    {
        ui->AccountLabel->setText(sql->Result());
    }
    else
        QMessageBox::warning(this,"warning",sql->Result());
}
