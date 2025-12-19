#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>

namespace Ui {
class LoginView;
}

class LoginView : public QWidget
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

signals:
    void loginSuccess(); // 登录成功信号

private slots:
    void on_loginBtn_clicked(); // 登录按钮点击槽

private:
    Ui::LoginView *ui;
};

#endif // LOGINVIEW_H
