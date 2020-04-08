
#include "sqlconnect.h"

SqlConnect::SqlConnect()
{

    database = QSqlDatabase::database("QMYSQL");
    database.setHostName("127.0.0.1");
    database.setPort(3306);
    database.setDatabaseName("EasyManager");
    database.setUserName("root");
    database.setPassword("3939520");


    if(database.isOpen())
    {
        QMessageBox::warning(nullptr,"提示","数据库已打开");
    }
    if(!database.open())
     {
         if(QMessageBox::Cancel==QMessageBox::warning(nullptr,"失败","数据库错误"+database.lastError().text(),QMessageBox::Cancel))
         {
             exit(-1);
         }
     }
    query.clear();
    result.clear();
}



bool SqlConnect::exec(FunctionEnum command,QString paramter)
{
    bool IsSuccess = false;
    switch (command)
    {
    case FE_Consume:
       IsSuccess =  exec_Consume(paramter);
        break;
    case FE_Login:
        IsSuccess = exec_Login(paramter);
        break;
    case FE_OnHold:
        IsSuccess = exec_OnHold(paramter);
        break;
    case FE_BeReady:
        IsSuccess = exec_BeReady(paramter);
        break;
    case FE_Release:
        IsSuccess =exec_Release(paramter);
        break;
    case FE_Reserve:
        IsSuccess = exec_Reserve(paramter);
        break;
    case FE_Storage:
        IsSuccess = exec_Storage(paramter);
        break;
    case FE_Recharge:
        IsSuccess = exec_ReCharge(paramter);
        break;
    case FE_Customization:
        IsSuccess = exec_Customization(paramter);
        break;
    case FE_Register:
        IsSuccess = exec_Register(paramter);
        break;
    }
    return IsSuccess;
}


QString SqlConnect::Result()
{
    return result;
}


bool SqlConnect::exec_Login(QString paramter)
{
    QString UserName,Password;
    QString::iterator itr = paramter.begin();
    while(*itr != ',')
    {
        UserName+=*(itr++);
    }itr++;
    while(*itr!='\0')
    {
        Password+=*(itr++);
    }

    bool ok = query.exec("select password,IsLogin from userinfo where Acount = '"+ UserName +"';");

    if(ok)
    {
        QString CorrectPasswd("\0");
        int IsLoggin = 0;
        query.next();
        CorrectPasswd = query.value(0).toString();
        IsLoggin = query.value(1).toInt();
        if(IsLoggin!= 0)
        {
            ok= false;
            result = "当前用户已登录";
        }
        else {
            if(CorrectPasswd==Password)
            {
                query.exec("insert into userinfo(IsLogin) values ('1') where Account = '"+UserName+"';");
                result = "用户登录完成";
            }
        }
    }
    return ok;
}

bool SqlConnect::exec_Register(QString paramter)
{
    QString UserName,Password,Question,Anwser,Time;
    Time = QTime::currentTime().toString();
    QString::iterator itr = paramter.begin();
    while(*itr!=',')
    {
        UserName+=*(itr++);
    }itr++;
    while(*itr!=',')
    {
        Password+=*(itr++);
    }itr++;
    while(*itr!=',')
    {
        Question+=*(itr++);
    }itr++;
    while(*itr!='\0')
    {
        Anwser+=*(itr++);
    }
    QString Sentence =QString("insert into userinfo"
                              "(Acount,Password,RegistTime,IsLogin,ModelChoose,PasswdQuestion,PasswdAnwser)"
                              "values('"+UserName+"','"+Password+"','"+Time+"',1,"+"0,'"+Question+"','"+Anwser+"');"
                              );
    bool ok =query.exec(Sentence);

    ok?result = "用户注册成功":result = "用户注册失败";

    return ok;
}

bool SqlConnect::exec_Customization(QString paramter)
{
    bool ok=false;
    return ok;
}


bool SqlConnect::exec_ReCharge(QString paramter)
{
    bool ok;
    return ok;
}

bool SqlConnect::exec_Storage(QString paramter)
{
    bool ok;
    return ok;
}

bool SqlConnect::exec_Release(QString paramter)
{
    bool ok;
    return ok;
}

bool SqlConnect::exec_Consume(QString paramter)
{
    bool ok;
    return ok;
}

bool SqlConnect::exec_Reserve(QString paramter)
{
    bool ok;
    return ok;
}

bool SqlConnect::exec_OnHold(QString paramter)
{
    bool ok;
    return ok;
}

bool SqlConnect::exec_BeReady(QString paramter)
{
    bool ok;
    return ok;
}
