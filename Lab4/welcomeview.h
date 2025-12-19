#ifndef WELCOMEVIEW_H
#define WELCOMEVIEW_H

#include <QWidget>

namespace Ui {
class WelcomeView;
}

class WelcomeView : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeView(QWidget *parent = nullptr);
    ~WelcomeView();

signals:
    // 声明三个跳转信号（对应医生/患者/科室管理）
    void goDoctorView();    // 跳转到医生管理界面
    void goPatientView();   // 跳转到患者管理界面
    void goDepartmentView();// 跳转到科室管理界面

private slots:
    // 三个按钮的点击槽函数（需和UI中按钮objectName匹配）
    void on_btDoctor_clicked();    // 医生管理按钮
    void on_btPatient_clicked();   // 患者管理按钮
    void on_btDepartment_clicked();// 科室管理按钮

private:
    Ui::WelcomeView *ui;
};

#endif // WELCOMEVIEW_H
