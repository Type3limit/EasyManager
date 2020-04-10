#include "findpasswddialog.h"
#include "ui_findpasswddialog.h"

FindPasswdDialog::FindPasswdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindPasswdDialog)
{
    ui->setupUi(this);
    sql = nullptr;
    Question.clear();
    Answer.clear();
}

FindPasswdDialog::~FindPasswdDialog()
{
    delete ui;
}


void FindPasswdDialog::on_pushButton_clicked()
{
    QString CurAnswer = ui->AnswerEdit->text();

    if(CurAnswer == Answer)
    {
        qDebug("验证通过");
        rsDialog = new ResetPasswdDialog(Name,this);
        rsDialog->exec();
        this->close();
    }
    else {
        QMessageBox::warning(this,"warning","问题验证失败");
        ui->AnswerEdit->clear();
    }
}



void FindPasswdDialog::on_NameEdit_editingFinished()
{
    QString CurName;

    CurName = ui->NameEdit->text();

    if(sql == nullptr)
        sql = new SqlConnect("findpasswd");

    bool ok = sql->exec(FE_FindPasswd,CurName);

     QString result = sql->Result();
    if(!ok)
    {
      QMessageBox::warning(this,"failed！",result);
      return ;
    }
    else {
        auto itr = result.begin();
        while(*itr!=DepartSambol)
            Question+=(*itr++);
        itr++;
        while(*itr!='\0')
            Answer += (*itr++);

        ui->QuestionLabel->setText(Question);
        Name= CurName;
    }
}
