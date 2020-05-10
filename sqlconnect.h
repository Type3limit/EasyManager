#ifndef SQLCONNECT_H
#define SQLCONNECT_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QTime>
#include <QVariant>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

enum Model//模块内容
{
    Mo_customer = 0,//客户信息管理
    Mo_product ,//商品信息管理
    Mo_queue,//等待队列
    Mo_reserve,//预约
    Mo_sell //商品贩售
};

enum FunctionEnum{//提供的功能选项
    FE_Customization = 0, //客制化
    FE_Register,//注册
    FE_Login,//登入
    FE_Logout,//登出
    FE_Consume,//消费
    FE_Recharge,//充值
    FE_Storage_new,//新品入库
    FE_Storage_old,//旧商品入库
    FE_Release,//出库
    FE_OnHold,//入等待队列
    FE_BeReady,//出等待队列
    FE_Reserve,//预约
    FE_FindPasswd,//找回密码
    FE_ResetPasswd,//重设密码
    FE_SelcetSingle,//查询（单条内容）debug
    FE_SelectAll,//查询所有 debug
    FE_LoadCustomize,//加载客制化
    FE_CustomerAdd//添加会员
};

const int ModelNumber = 5;//当前模块数

const char DepartSambol = ',';//数据分隔符
const char SentenceEnded = '#';//单条数据结束符


class SqlConnect
{
public:
    SqlConnect(QString type = "default");
    ~SqlConnect();

    bool exec(FunctionEnum command,QString paramter=nullptr);
    QString Result();

private:
    bool exec_Customization(QString paramter);
    bool exec_Register(QString paramter);
    bool exec_Login(QString paramter);
    bool exec_Logout(QString paramter);
    bool exec_Consume(QString paramter);
    bool exec_ReCharge(QString paramter);
    bool exec_Storage_new(QString paramter);
    bool exec_Storage_old(QString paramter);
    bool exec_Release(QString paramter);
    bool exec_OnHold(QString paramter);
    bool exec_BeReady(QString paramter);
    bool exec_Reserve(QString paramter);
    bool exec_FindPasswd(QString paramter);
    bool exec_ResetPasswd(QString paramter);
    bool exec_SelectSingle(QString paramter);
    bool exec_SelectAll(QString paramter);
    bool exec_LoadCustomize(QString paramter);
    bool exec_CustomerAdd(QString paramter);

private:
    QSqlDatabase* db;
    QString result;
    QSqlQuery query;
};

#endif // SQLCONNECT_H
