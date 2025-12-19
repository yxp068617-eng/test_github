#include "welcomeview.h"
#include "ui_welcomeview.h"
#include <QDebug>


WelcomeView::WelcomeView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeView)
{
    ui->setupUi(this);
    this->setWindowTitle("欢迎界面");
}

WelcomeView::~WelcomeView()
{
    delete ui;
}

// 医生管理按钮点击 - 发送跳转到医生界面的信号
void WelcomeView::on_btDoctor_clicked()
{
    qDebug() << "点击医生管理按钮";
    emit goDoctorView();
}

// 患者管理按钮点击 - 发送跳转到患者界面的信号
void WelcomeView::on_btPatient_clicked()
{
    qDebug() << "点击患者管理按钮";
    emit goPatientView();
}

// 科室管理按钮点击 - 发送跳转到科室界面的信号
void WelcomeView::on_btDepartment_clicked()
{
    qDebug() << "点击科室管理按钮";
    emit goDepartmentView();
}

