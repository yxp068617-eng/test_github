#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "loginview.h"
#include "welcomeview.h"
#include "doctorview.h"
#include "patientview.h"
#include "departmentview.h"
#include "patienteditview.h"


class PatientEditView;
namespace Ui {
class MasterView;
}

class MasterView : public QWidget
{
    Q_OBJECT

public:
    explicit MasterView(QWidget *parent = nullptr);
    ~MasterView();
    void goPatientEditView(int rowNo = 0);
    void pushWidgetToStackView(QWidget *widget);

public slots:
    // 界面跳转槽函数
    void goLoginView();
    void goWelcomView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientView();
    void goPreviousView();

private slots:
    void on_btBack_clicked();
    void on_stackedWidget_currentChanged(int arg1);
    void on_btLogout_clicked();

private:
    Ui::MasterView *ui;
    // 各子界面对象指针
    WelcomeView *welcomeView;
    DoctorView *doctorView;
    PatientView *patientView;
    DepartmentView *departmentView;
    LoginView *loginView;
    PatientEditView *patientEditView;
    // 私有方法：将控件加入StackedWidget
};

#endif // MASTERVIEW_H
