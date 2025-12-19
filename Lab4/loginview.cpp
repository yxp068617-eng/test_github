#include "loginview.h"
#include "ui_loginview.h"
#include <QDebug>
#include "idatabase.h"

LoginView::LoginView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginView)
{
    ui->setupUi(this);
    this->setWindowTitle("登录界面"); // 设置界面标题
}

LoginView::~LoginView()
{
    delete ui;
}

// 登录按钮点击事件（教程逻辑：数据库验证账号密码）
void LoginView::on_loginBtn_clicked()
{
    qDebug() << "登录按钮点击，开始验证账号密码";

    // 1. 获取界面输入的用户名和密码（关键：替换为你UI中实际的输入框objectName）
    // 示例：若你的用户名输入框objectName是lineEdit_User，密码框是lineEdit_Pwd，需对应修改
    QString userName = ui->lineEdit_User->text();   // 用户名输入框（改这里！）
    QString password = ui->lineEdit_Pwd->text();   // 密码输入框（改这里！）

    // 2. 调用数据库单例的登录验证函数（教程核心）
    QString loginStatus = IDatabase::getInstance().userLogin(userName, password);

    // 3. 根据验证结果处理：只有验证通过才发送登录成功信号
    if (loginStatus == "loginOk") {
        qDebug() << "账号密码验证通过，触发界面跳转";
        emit loginSuccess(); // 发送信号，跳转到欢迎界面
    } else if (loginStatus == "wrongPassword") {
        qDebug() << "密码错误！";
        // 可选：添加界面提示（比如弹窗/标签显示）
        // ui->label_Tip->setText("密码错误，请重新输入");
    } else if (loginStatus == "wrongUsername") {
        qDebug() << "用户名不存在！";
        // 可选：添加界面提示
        // ui->label_Tip->setText("用户名不存在，请注册");
    } else {
        qDebug() << "登录验证异常";
    }
}


