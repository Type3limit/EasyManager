
#include "sqlconnect.h"

SqlConnect::SqlConnect(QString type)
{

        db = new QSqlDatabase();
        *db = QSqlDatabase::addDatabase("QMYSQL",type);
        db->setHostName("localhost");
        db->setPort(3306);
        db->setDatabaseName("EasyManager");
        db->setUserName("root");
        db->setPassword("3939520");

        if(!db->open())
        {
         if(QMessageBox::Cancel==QMessageBox::warning(nullptr,"失败","数据库错误"+db->lastError().text(),QMessageBox::Cancel))
         {
             exit(-1);
         }
        }
       query = QSqlQuery(*db);
       result.clear();
}

SqlConnect::~SqlConnect()
{
    db->close();
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
    case FE_Logout:
        IsSuccess = exec_Logout(paramter);
        break;
    case FE_FindPasswd:
        IsSuccess = exec_FindPasswd(paramter);
        break;
    case FE_ResetPasswd:
        IsSuccess = exec_ResetPasswd(paramter);
        break;
    case FE_Selcet:
        IsSuccess =exec_Select(paramter);
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
    while(*itr != DepartSambol)
    {
        UserName+=*(itr++);
    }itr++;
    while(*itr!='\0')
    {
        Password+=*(itr++);
    }
    QString sentence = QString("SELECT user_password,user_login FROM userinfo WHERE user_account = '%1'").arg(UserName);
    bool ok = query.exec(sentence);
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
            if(!CorrectPasswd.compare(Password))
            {
                sentence = QString("UPDATE userinfo SET user_login = 1 WHERE user_account = '%1'").arg(UserName);
                query.exec(sentence);
                result = "用户登录完成";
            }
            else {
                ok=false;
                result = "请检查账号或密码是否正确";
            }
        }
    }
    result += query.lastError().text();
    return ok;
}

bool SqlConnect::exec_Register(QString paramter)
{
    QString UserName,Password,Question,Anwser,Time;
    Time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:MM");
    QString::iterator itr = paramter.begin();
    while(*itr!=DepartSambol)
    {
        UserName+=*(itr++);
    }itr++;
    while(*itr!=DepartSambol)
    {
        Password+=*(itr++);
    }itr++;
    while(*itr!=DepartSambol)
    {
        Question+=*(itr++);
    }itr++;
    while(*itr!='\0')
    {
        Anwser+=*(itr++);
    }
    QString select = QString("SELECT user_account FROM userinfo WHERE user_account = '%1'").arg(UserName);
    query.exec(select);
    if(query.next())
    {
        result="当前用户名已被使用";
        return false;
    }
    query.clear();

    QString Sentence =QString("INSERT INTO userinfo"
                              "(user_account,user_password,user_regist_time,user_login,"
                              "user_model_choose,user_question,user_answer)"
                              "VALUES('%1','%2','%3',0,0,'%4','%5')"
                              ).arg(UserName).arg(Password).arg(Time).arg(Question).arg(Anwser);
    bool ok =query.exec(Sentence);

    qDebug()<<query.lastError().text();

    ok?result = "用户注册成功":result = "用户注册失败"+query.lastError().text();

    return ok;
}

bool SqlConnect::exec_FindPasswd(QString paramter)
{
    QString Name,Question,Answer;
    QString::iterator itr = paramter.begin();

    while(*itr != '\0')
    {
        Name+=*(itr++);
    }
    QString sentence= QString("SELECT user_question,user_answer FROM userinfo WHERE user_account = '%1'").arg(Name);
    bool ok = query.exec(sentence);

    if(ok)
    {
        if(query.next()&&!query.isNull(0))
        {
        result = QString("%1%2%3").arg(query.value(0).toString()).arg(DepartSambol).arg(query.value(1).toString());
        }
        else {
            ok = false;
            result = "无此用户,请检查您是否输入无误";
        }
    }
    else {
        result = query.lastError().text();

       }
    return ok;
}

bool SqlConnect::exec_ResetPasswd(QString paramter)
{
    QString UserName,NewPasswd;
    auto itr= paramter.begin();
    while(*itr!=DepartSambol)
    {
        UserName +=*(itr++);
    }itr++;
    while(*itr!='\0')
    {
        NewPasswd += *(itr++);
    }
    QString sentence = QString("UPDATE userinfo SET user_password = '%1',user_login = 0 WHERE user_account = '%2'").arg(NewPasswd).arg(UserName);
    bool ok = query.exec(sentence);
    ok? result = "修改密码成功":"修改失败"+query.lastError().text();
    return ok;
}


bool SqlConnect::exec_Customization(QString paramter)
{
    int Model[ModelNumber];
    QString Name;
    auto itr = paramter.begin();
    while(*itr!=DepartSambol)
        Name+=*(itr++);
    itr++;

    for(int i = 0 ; i<ModelNumber;i++)
    {
        QString CurrentChoose = *(itr++);
        Model[i] = CurrentChoose.toInt();
    }

    QString sentence1 = QString("UPDATE userinfo SET user_model_choose = 1 WHERE user_account = '%1'").arg(Name);

    bool ok=query.exec(sentence1);
    if(ok)
    {
        QString sentence2 = QString("INSERT INTO modelinfo"
                                    "(model_user_id,model_customer_manage,model_product_manage,model_hold_queue,model_reserve,model_sell)"
                                    "VALUES(%1,%2,%3,%4,%5,%6)").arg(Name)
                .arg(Model[Mo_customer]).arg(Model[Mo_product]).arg(Model[Mo_queue]).arg(Model[Mo_reserve]).arg(Model[Mo_sell]);
        ok= query.exec(sentence2);
    }


    if(!ok)
        result = query.lastError().text();
    else {
        result = "客制化已完成";
    }

    return ok;
}

bool SqlConnect::exec_Select(QString paramter)
{
    QString Type,Name,Selectpart;
    bool ok =false;
    auto itr = paramter.begin();

    while(*itr!=DepartSambol)
        Type+=*(itr++);
    itr++;
    while(*itr!=DepartSambol)
        Name+=*(itr++);
    itr++;
    while(*itr!='\0')
       Selectpart+= *(itr++);
    QString sentence;
    if(!Type.compare("User"))
    {
        sentence = QString("SELECT %1 FROM userinfo WHERE user_account='%2'").arg(Selectpart).arg(Name);
    }
    else if (!Type.compare("Customer"))
    {
         sentence = QString("SELECT %1 FROM customerinfo WHERE customer_name='%2'").arg(Selectpart).arg(Name);
    }
    else if (!Type.compare("Product"))
    {
         sentence = QString("SELECT %1 FROM productsinfo WHERE product_id='%2'").arg(Selectpart).arg(Name);
    }
    else if (!Type.compare("Queue"))
    {
         sentence =QString ("SELECT %1 FROM queueinfo WHERE queue_acount = '%2'").arg(Selectpart).arg(Name);
    }
    else if (!Type.compare("Reserve"))
    {
        sentence =QString ("SELECT %1 FROM reserveinfo WHERE reserve_customer_id = '%2'").arg(Selectpart).arg(Name);
    }
    else {
        ok = false;
        result = "查询的内容有误";
        return ok;
    }
    ok = query.exec(sentence);
    if(query.next()&&!query.value(0).isNull())
        result = query.value(0).toString();
    if(!ok)
        result = "查询失败"+query.lastError().text();
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

bool SqlConnect::exec_Logout(QString paramter)
{
    QString UserName;
    auto itr = paramter.begin();
    while(*itr!='\0')
    {
          UserName+=*(itr++);
    }
    QString sentence = QString("UPDATE userinfo SET user_login=0 WHERE user_account = '%1'").arg(UserName);

    bool ok = query.exec(sentence);
    ok?result = "用户已退出":result = query.lastError().text();
    return ok;
}
