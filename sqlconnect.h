#ifndef SQLCONNECT_H
#define SQLCONNECT_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QTime>
#include <QVariant>
#include <QSqlError>


enum FunctionEnum{
  FE_Customization = 0, //客制化
  FE_Register,//注册
  FE_Login,//登入
  FE_Consume,//消费
  FE_Recharge,//充值
  FE_Storage,//入库
  FE_Release,//出库
  FE_OnHold,//入等待队列
  FE_BeReady,//出等待队列
  FE_Reserve//预约
};


class SqlConnect
{
public:
    SqlConnect();

    bool exec(FunctionEnum command,QString paramter=nullptr);
    QString Result();

private:
    bool exec_Customization(QString paramter);
    bool exec_Register(QString paramter);
    bool exec_Login(QString paramter);
    bool exec_Consume(QString paramter);
    bool exec_ReCharge(QString paramter);
    bool exec_Storage(QString paramter);
    bool exec_Release(QString paramter);
    bool exec_OnHold(QString paramter);
    bool exec_BeReady(QString paramter);
    bool exec_Reserve(QString paramter);

private:
    QSqlDatabase database;
    QString result;
    QSqlQuery query;
};

#endif // SQLCONNECT_H
