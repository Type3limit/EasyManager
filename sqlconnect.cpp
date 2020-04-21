
#include "sqlconnect.h"

SqlConnect::SqlConnect(QString type)
{

    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QMYSQL",type);
    db->setHostName("mylocal");
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
    case FE_Storage_old:
        IsSuccess = exec_Storage_old(paramter);
        break;
    case FE_Storage_new:
        IsSuccess = exec_Storage_new(paramter);
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
    case FE_SelcetSingle:
        IsSuccess =exec_SelectSingle(paramter);
        break;
    case FE_SelectAll:
        IsSuccess = exec_SelectAll(paramter);
        break;
    case FE_LoadCustomize:
        IsSuccess = exec_LoadCustomize(paramter);
        break;
    case FE_CustomerAdd:
        IsSuccess = exec_CustomerAdd(paramter);
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
    if(!query.next())
        ok=false;
    if(ok)
    {
        QString CorrectPasswd("\0");
        int IsLoggin = 0;
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
        itr++;
        Model[i] = CurrentChoose.toInt();
    }

    QString sentence1 =QString ("SELECT model_user_id FROM modelinfo WHERE model_user_id = '%1'").arg(Name);

    bool ok=query.exec(sentence1);
    if(ok)
    {
        sentence1 =  QString("UPDATE userinfo SET user_model_choose = 1 WHERE user_account = '%1'").arg(Name);

        query.clear();
        ok = query.exec(sentence1);
        QString sentence2;
        sentence2 = QString("INSERT INTO modelinfo"
                            "(model_user_id,model_customer_manage,model_product_manage,model_hold_queue,model_reserve,model_sell) "
                            "VALUES('%1','%2','%3','%4','%5','%6') ON DUPLICATE KEY UPDATE model_customer_manage = '%7',model_product_manage='%8',"
                            "model_hold_queue ='%9',model_reserve='%10',model_sell='%11' ").arg(Name)
                .arg(Model[Mo_customer]).arg(Model[Mo_product]).arg(Model[Mo_queue]).arg(Model[Mo_reserve]).arg(Model[Mo_sell])
                .arg(Model[Mo_customer]).arg(Model[Mo_product]).arg(Model[Mo_queue]).arg(Model[Mo_reserve]).arg(Model[Mo_sell]);

        ok= query.exec(sentence2);
    }


    if(!ok)
    {
        result = query.lastError().text();
        sentence1 =  QString("UPDATE userinfo SET user_model_choose = 0 WHERE user_account = '%1'").arg(Name);
        query.exec(sentence1);
    }
    else {
        result = "客制化已完成";
    }

    return ok;
}

bool SqlConnect::exec_SelectSingle(QString paramter)
{
    QString Type,Name,Selectpart;
    result.clear();
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
        sentence = QString("SELECT %1 FROM productsinfo WHERE product_name='%2'").arg(Selectpart).arg(Name);
    }
    else if (!Type.compare("Queue"))
    {
        sentence =QString ("SELECT %1 FROM queueinfo WHERE queue_costumer_id = '%2'").arg(Selectpart).arg(Name);
    }
    else if (!Type.compare("Reserve"))
    {
        sentence =QString ("SELECT %1 FROM reserveinfo WHERE reserve_customer_id = '%2'").arg(Selectpart).arg(Name);
    }
    else if (!Type.compare("CustomerAmount"))
    {
        sentence = QString("SELELCT customer_amount FROM customeramount WHERE customer_id  = '%1'").arg(Name);
    }
    else if (!Type.compare("ProductCount"))
    {
        sentence = QString ("SELECT product_count FROM productcountinfo WHERE product_id = '%1'").arg(Name);
    }
    else {
        ok = false;
        result = "查询的内容有误";
        return ok;
    }

    ok = query.exec(sentence);
    if(query.next())
        result = query.value(0).toString();
    if(!ok)
        result = "查询失败"+query.lastError().text();
    return ok;
}

bool SqlConnect::exec_SelectAll(QString paramter)
{
    QString Type,Part;
    auto itr = paramter.begin();
    while(*itr!=DepartSambol&&*itr!='\0')
    {
        Type+=*(itr++);
    }itr++;
    while(*itr!='\0')
    {
        Part+=*(itr++);
    }itr++;

    QString sentence;
    bool ok  =false;
    bool type = true;
    if(!Type.compare("Customer"))
    {
        sentence =QString("SELECT * FROM customerinfo");
        type=true;
    }
    else if (!Type.compare("Product"))
    {
        sentence = QString ("SELECT * FROM productsinfo");
        qDebug()<<"enter Product case";
        type= true;
    }

    else if (!Type.compare("Manual"))
    {

        sentence = QString("SELECT COUNT(*) FROM %1").arg(Part);
        qDebug()<<"enter manual case";
        type = false;
    }
    else {
        result = "查询内容有误";

        return ok;
    }
    query.clear();
    ok = query.exec(sentence);
    if(ok&&type)
    {
        QSqlRecord rec = query.record();
        int row = rec.count();
        qDebug()<<"Enter result case,current row:"<<row;
        while(query.next())
        {
            for(int i = 0 ;i<row;i++)
            {
                result+= QString(",%1").arg(query.value(i).toString());
            }
            result+='#';
        }
        qDebug()<<"on result case:"<<result;
    }
    else if (ok&& !type)
    {
        query.next();
        result  = query.value(0).toString();
        qDebug()<<"on count case:"<<result;
    }
    else
        result = query.lastError().text();
    return ok ;


}

bool SqlConnect::exec_LoadCustomize(QString paramter)
{
    QString Name;
    auto itr = paramter.begin();
    while(*itr!='\0')
    {
        Name+=*(itr++);
    }
    QString sentence =  QString("SELECT model_customer_manage,"
                                " model_product_manage,model_hold_queue,model_reserve,model_sell "
                                "FROM modelinfo WHERE model_user_id = '%1'").arg(Name);
    bool ok = query.exec(sentence);
    if(!query.next()||!ok)
    {
        result = "读取客制化信息失败！";
        return false;
    }
    result  = QString ("%1,%2,%3,%4,%5").arg(query.value(0).toString()).arg(query.value(1).toString())
            .arg(query.value(2).toString()).arg(query.value(3).toString()).arg(query.value(4).toString());
    return ok;
}

bool SqlConnect::exec_CustomerAdd(QString paramter)
{
    QString Name,Passwd,Contanct,CurTime;
    auto itr  =paramter.begin();
    while(*itr!=DepartSambol)
        Name+=*(itr++);
    itr++;
    while(*itr!=DepartSambol)
        Passwd+=*(itr++);
    itr++;
    while(*itr!='\0')
        Contanct+=*(itr++);
    CurTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:MM");
    QString Sentence =QString("INSERT INTO customerinfo"
                              "(customer_name,customer_password,customer_contanct,customer_regist_time"
                              ")"
                              "VALUES('%1','%2','%3','%4') "
                              ).arg(Name).arg(Passwd).arg(Contanct).arg(CurTime);
    query.clear();
    bool ok =query.exec(Sentence);
    qDebug()<<"on insert:"<<query.lastError().text();

    if(!ok )
    {
        result = query.lastError().text();
    }
    else {
        result = "新增成功";
    }
    return ok;
}

bool SqlConnect::exec_ReCharge(QString paramter)
{
    QString Name,Amount;
    QString CustomerID;
    QString Time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:MM");
    auto itr = paramter.begin();
    while(*itr!=DepartSambol)
        Name += *(itr++);
    itr++;
    while(*itr!='\0')
        Amount += *(itr++);

    QString sentence =QString ("SELECT customer_id FROM customerinfo WHERE customer_name = '%1'").arg(Name);

    bool ok=false;
    if(query.exec(sentence))
    {

        if(query.next())
        {
            double amount = Amount.toDouble();
            CustomerID = query.value(0).toString();
            sentence =QString ("INSERT INTO customeramount(customer_id,customer_amount) VALUES('%1','%2')"
                               "ON DUPLICATE KEY UPDATE customer_amount  = customer_amount + '%3' ").arg(CustomerID).arg(amount).arg(amount);
            query.clear();
            qDebug()<<"Current ID  is : "<<CustomerID;
            ok = query.exec(sentence);
            qDebug()<<"on insert"<<query.lastError().text();
            if(ok)
                result = QString("余额充值成功!本次充值:%1").arg(amount);


            sentence =QString ("INSERT INTO rechargeinfo(recharge_customer_id,"
                               "recharge_acount,recharge_action_time)"
                               " VALUES('%1','%2','%3')").arg(CustomerID).arg(amount)
                    .arg(Time);
            query.clear();
            ok = query.exec(sentence);
            qDebug()<<"on info insert"<<query.lastError().text();
        }
        else {
            ok = false;
            result = query.lastError().text();
        }
    }
    else
        result = query.lastError().text();
    return ok;
}

bool SqlConnect::exec_Storage_new(QString paramter)
{

    QString Name,Cost,ImagePath,Numbers,Info;
    QString CurId;
    auto itr = paramter.begin();
    while(*itr!=DepartSambol)
    {
        Name+=*(itr++);
    }itr++;
    while(*itr!=DepartSambol)
    {
        Cost+=*(itr++);
    }itr++;
    while(*itr!=DepartSambol)
    {
        ImagePath+=*(itr++);
    }itr++;
    while(*itr!=DepartSambol)
    {
        Numbers+=*(itr++);
    }itr++;
    while(*itr!='\0')
    {
        Info+=*(itr++);
    }
    int number = Numbers.toInt();

    int useable = 0 ;
    if(number>0)
        useable = 1;

    QString sentence = QString("INSERT INTO productsinfo (product_name,product_cost,product_info,product_image,product_useable)"
                               "VALUES('%1','%2','%3','%4','%5')").arg(Name).arg(Cost).arg(Info).arg(ImagePath).arg(useable);


    bool ok =query.exec(sentence);
    QSqlDatabase::database().commit();


    if(ok)
    {

        CurId = query.lastInsertId().toString();

        qDebug()<<"on select :"<<query.lastError().text();



        sentence = QString("INSERT INTO productcountinfo (product_id,product_count) VALUES('%1','%2')")
                .arg(CurId).arg(number);
        ok = query.exec(sentence);

        if(!ok)
            result = query.lastError().text();
    }

    sentence = QString("INSERT INTO productininfo(productin_product_id,productin_product_name,productin_product_type,"
                       "productin_product_number,productin_product_cost)"
                       "VALUES('%1','%2','%3','%4','%5') ").arg(CurId)
            .arg(Name).arg(0).arg(number).arg(Cost);

    ok = query.exec(sentence);

    if(ok) result = "商品入库完成！";
    else result = query.lastError().text();
    return ok;

}

bool SqlConnect::exec_Storage_old(QString paramter)
{
    QString Name,Numbers,InPrice,OutPrice;
    auto itr = paramter.begin();
    while(*itr!=DepartSambol)
    {
        Name+=*(itr++);
    }itr++;
    while(*itr!=DepartSambol)
    {
        Numbers+=*(itr++);
    }itr++;
    while(*itr!=DepartSambol)
    {
        InPrice+=*(itr++);
    }itr++;
    while(*itr!='\0')
    {
        OutPrice+=*(itr++);
    }itr++;
    QString sentence = QString ("SELECT product_id FROM productsinfo WHERE product_name = '%1'").arg(Name);
    bool ok = query.exec(sentence);
    if(ok&&query.next())
    {
        int number = Numbers.toInt();
        QString CurID = query.value(0).toString();
        sentence = QString("UPDATE productcountinfo SET product_count = product_count+ %1 WHERE product_id = '%2'")
                .arg(number).arg(CurID);
        ok = query.exec(sentence);
        if(number>=1)
        {
            sentence  = QString("UPDATE productsinfo SET product_cost= %1 ,product_useable= %2 WHERE product_id ='%3'")
                    .arg(InPrice).arg("1").arg(CurID);
            ok = query.exec(sentence);
        }
        sentence = QString ("INSERT INTO productininfo(productin_product_id,productin_product_name,productin_product_type,"
                            "productin_product_number,productin_product_cost) VALUES"
                            "('%1','%2',1,%3,'%4')").arg(CurID).arg(Name).arg(number).arg(OutPrice);
        ok = query.exec(sentence);

    }
    if(!ok)
        result = query.lastError().text();
    else {
        result = "进货信息录入成功！";
    }
    return ok;

}

bool SqlConnect::exec_Release(QString paramter)
{

    QString Name,Number,Cost;
    QString CurID;
    auto itr = paramter.begin();
    while(*itr!= DepartSambol)
    {
        Name+=*(itr++);
    }itr++;
    while(*itr!=DepartSambol)
    {
        Number+=*(itr++);
    }itr++;
    while(*itr!='\0')
    {
        Cost+=*(itr++);
    }

    int CurNumber,StoragedNumber=0;
    CurNumber = Number.toInt();
    QString sentence = QString("SELECT product_id FROM productsinfo WHERE productname = '%1'").arg(Name);
    bool ok = query.exec(sentence);
    if(query.next())
    {
        CurID = query.value(0).toString();
        sentence = QString("SELECT product_count FROM productcountinfo WHERE product_id = '%1'").arg(CurID);
        ok = query.exec(sentence);
        if(query.next())
            StoragedNumber = query.value(0).toInt();
    }

    if(ok)
    {
        if(CurNumber>StoragedNumber)
            ok= false;
        else {
            int Diff = StoragedNumber -CurNumber;
            sentence =QString("INSERT INTO productoutinfo(productout_product_id,productout_number,"
                              "productout_cost) VALUES('%1','%2','%3')")
                    .arg(CurID).arg(CurNumber).arg(Cost);
            ok = query.exec(sentence);
            sentence = QString("UPDATE productcountinfo SET product_count = '%1'").arg(Diff);
            ok = query.exec(sentence);
            if(Diff == 0)
            {
                sentence = QString("UPDATE productsinfo SET product_useable = 0");
                ok = query.exec(sentence);
            }
        }
    }
    else {
        result = query.lastError().text();
    }
    return ok;
}

bool SqlConnect::exec_Consume(QString paramter)
{
    QString CustomerName,ProductName,Amount,Count,Time;
    Time = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:MM");
    QString CustomerID,ProductID;
    auto itr = paramter.begin();
    while(*itr!=DepartSambol)
    {
        CustomerName+=*(itr++);
    }itr++;
    while(*itr!=DepartSambol)
    {
        ProductName += *(itr++);
    }itr++;
    while(*itr!=DepartSambol)
    {
        Amount +=*(itr++);
    }itr++;
    while(*itr!='\0')
    {
        Count+=*(itr++);
    }itr++;

    QString sentence =QString ("SELECT customer_id FROM customerinfo WHERE customer_name = '%1'").arg(CustomerName);
    bool ok  = query.exec(sentence);
    if(query.next())
    {
        CustomerID = query.value(0).toString();
    }
    sentence =QString("SELECT product_id FROM productsinfo WHERE product_name = '%1'").arg(ProductName);
    query.clear();
    ok = query.exec(sentence);
    if(query.next())
    {
        ProductID =query.value(0).toString();
    }

    if(ok)
    {
        sentence=QString ("INSERT INTO customationinfo(consume_custom_id,consume_product_id,"
                          "consume_custom_amount,consume_count)").arg(CustomerID).arg(ProductID)
                .arg(Amount).arg(Count);
        query.clear();
        ok=query.exec(sentence);
        int Single = (Amount.toInt())/(Count.toInt());
        sentence=QString ("%1,%2,%3").arg(ProductName).arg(Count).arg(Single);
        ok = exec_Release(sentence);
        sentence =QString("SELECT custom_amount FROM customeramount WHERE custom_id = '%1' ").arg(CustomerID);
        query.clear();
        ok = query.exec(sentence);
        double CurAmount= 0;
        if(query.next())
        {
            CurAmount = query.value(0).toDouble();
            double Diff =CurAmount - Amount.toDouble();
            sentence = QString ("UPDATE customeramount SET custom_amount= '%1' WHERE custom_id = '%2'")
                    .arg(Diff).arg(CustomerID);
            query.clear();
            ok = query.exec(sentence);
        }
        else {
            ok = false;
        }

    }
    if(!ok)
        result = "消费信息记录失败";

    return ok;
}

bool SqlConnect::exec_Reserve(QString paramter)
{
    QString Name,Info,CurID;
    auto itr = paramter.begin();
    while(*itr!=DepartSambol)
    {
        Name+= *(itr++);
    }itr++;
    while(*itr!='\0')
    {
        Info +=*(itr++);
    }
    QString sentence = QString("SELECT cutomer_id FROM customerinfo WHERE cutomer_name = '%1'").arg(Name);
    bool ok = query.exec(sentence);
    if(query.next())
    {
        CurID = query.value(0).toString();
        sentence = QString ("INSERT INTO reserveinfo(reserve_customer_id,reserve_contain)"
                            "VALUES('%1','%2')").arg(CurID).arg(Info);
        query.clear();
        ok = query.exec(sentence);
        result = "预约信息记录成功";
    }
    return ok;
}

bool SqlConnect::exec_OnHold(QString paramter)
{
    QString Name,CurID;
    QString CurNext,CurPrevious,CurLastID;
    auto itr = paramter.begin();
    while(*itr!='\0')
    {
        Name += *(itr++);
    }
    QString sentence =QString("SELECT customer_id FROM customerinfo WHERE customer_name = '%1'")
            .arg(Name);
    bool ok =query.exec(sentence);
    if(query.next())
    {
        CurID = query.value(0).toString();
        sentence = QString("SELECT queue_customer_id FROM queueinfo "
                           "WHERE queue_next_id = NULL");
        query.clear();
        ok=query.exec(sentence);
        if(query.next())
        {
            CurLastID = query.value(0).toString();
            sentence =QString("UPDATE queueinfo SET queue_next_id = '%1' WHERE queue_customer_id = '%2'")
                    .arg(CurID).arg(CurLastID);
            ok = query.exec(sentence);
            result = "信息添加成功";
        }
        else
            CurLastID="NULL";
        sentence =QString ("INSERT INTO queueinfo(queue_costumer_id"
                           ",queue_previous_id) VALUES ('%1','%2')").arg(CurID).arg(CurLastID);
        query.clear();
        ok = query.exec(sentence);
    }
    if(!ok)
        result =query.lastError().text();
    return ok;
}

bool SqlConnect::exec_BeReady(QString paramter)
{
    QString Name,CurID,NextID,PreviousID;
    auto itr = paramter.begin();
    while(*itr!='\0')
        Name+=*(itr++);
    QString sentence = QString ("SELECT costumer_id FROM costumerinfo WHERE costumer_name = '%1'").arg(Name);
    bool ok =query.exec(sentence);
    if(query.next())
    {
        CurID = query.value(0).toString();
        sentence = QString("SELECT queue_next_id,queue_previous_id FROM queueinfo WHERE queue_costumer_id = '%1'")
                .arg(CurID);
        ok = query.exec(sentence);
        if(query.next())
        {
            NextID = query.value(0).toString();
            PreviousID = query.value(1).toString();
            if(PreviousID.isEmpty())
            {
                sentence  = QString ("UPDATE queueinfo SET queue_previous_id = NULL WHERE queue_customer_id = '%1'")
                        .arg(NextID);
                ok = query.exec(sentence);
                sentence  = QString ("DELECT FROM queueinfo WHERE queue_customer_id = '%1'").arg(CurID);
                ok = query.exec(sentence);
            }
            else {
                sentence =QString ("UPDATE queueinfo SET queue_next_id = '%1' WHERE queue_customer_id='%2'")
                        .arg(NextID).arg(PreviousID);
                ok = query.exec(sentence);
                sentence  =QString("UPDATE queueinfo SET queue_previous_id = '%1' WHERE queue_customer_id = '%2'")
                        .arg(PreviousID).arg(NextID);
                ok = query.exec(sentence);
            }
        }


    }
    if(!ok)
        result = query.lastError().text();
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
