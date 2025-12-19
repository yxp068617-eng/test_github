#include "masterview.h"
#include "ui_masterview.h"
#include <QDebug>
#include "idatabase.h"
#include "patienteditview.h"

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);
    goLoginView(); // 启动时默认进入登录界面
    IDatabase::getInstance();
}

MasterView::~MasterView()
{
    delete ui;
}

// 跳转到登录界面
void MasterView::goLoginView()
{
    qDebug() << "goLoginView";
    loginView = new LoginView(this);

    ui->stackedWidget->addWidget(loginView);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1); // 总是显示最新加入的View
    ui->labelTitle->setText(loginView->windowTitle());

    // 连接“登录成功”信号到“跳转到欢迎界面”槽
    connect(loginView, SIGNAL(loginSuccess()), this, SLOT(goWelcomView()));
}


void MasterView::pushWidgetToStackView(QWidget *widget)
{
    // 假设你的MasterView中有一个QStackedWidget，objectName是stackedWidget
    // 替换为你UI中实际的栈控件名！
    QStackedWidget *stackWidget = ui->stackedWidget;
    if (!stackWidget || !widget) {
        qDebug() << "栈控件或目标界面为空！";
        return;
    }
    // 移除旧界面（可选，根据需求）
    // stackWidget->removeWidget(stackWidget->currentWidget());
    // 添加新界面到栈控件
    stackWidget->addWidget(widget);
    // 切换到新界面
    stackWidget->setCurrentWidget(widget);
}


// 跳转到欢迎界面
void MasterView::goWelcomView()
{
    qDebug() << "goWelcomView";
    welcomeView = new WelcomeView(this);

    // 直接写界面添加逻辑（匹配你截图的格式）
    ui->stackedWidget->addWidget(welcomeView);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1);
    ui->labelTitle->setText(welcomeView->windowTitle());

    // 连接欢迎界面的三个按钮信号到对应跳转函数
    // 医生管理按钮 → 跳转到医生界面
    connect(welcomeView, SIGNAL(goDoctorView()), this, SLOT(goDoctorView()));
    // 患者管理按钮 → 跳转到患者界面
    connect(welcomeView, SIGNAL(goPatientView()), this, SLOT(goPatientView()));
    // 科室管理按钮 → 跳转到科室界面
    connect(welcomeView, SIGNAL(goDepartmentView()), this, SLOT(goDepartmentView()));
}

// 跳转到医生界面
void MasterView::goDoctorView()
{
    qDebug() << "goDoctorView";
    doctorView = new DoctorView(this);

    ui->stackedWidget->addWidget(doctorView);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1); // 总是显示最新加入的View
    ui->labelTitle->setText(doctorView->windowTitle());
}

// 跳转到科室界面
void MasterView::goDepartmentView()
{
    qDebug() << "goDepartmentView";
    departmentView = new DepartmentView(this);

    ui->stackedWidget->addWidget(departmentView);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1); // 总是显示最新加入的View
    ui->labelTitle->setText(departmentView->windowTitle());
}

// 跳转到患者编辑界面
void MasterView::goPatientEditView(int rowNo)
{
    qDebug() << "打开患者编辑界面，行索引：" << rowNo;
    patientEditView = new PatientEditView(this, rowNo);
    pushWidgetToStackView(patientEditView);
    connect(patientEditView, SIGNAL(goPreviousView()), this, SLOT(goPreviousView()));
}

// 跳转到患者界面
void MasterView::goPatientView()
{
    qDebug() << "goPatientView";
    patientView = new PatientView(this);

    // 直接写界面添加逻辑（匹配你截图的格式）
    ui->stackedWidget->addWidget(patientView);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1);
    ui->labelTitle->setText(patientView->windowTitle());

    // 连接患者界面的添加按钮信号 → 跳转到患者编辑界面
    connect(patientView, SIGNAL(goPatientEditView()), this, SLOT(goPatientEditView()));
}


// 返回上一界面（从StackedWidget中移除当前界面）
void MasterView::goPreviousView()
{
    int count = ui->stackedWidget->count();
    if (count > 1) {
        // 切换到上一个界面
        ui->stackedWidget->setCurrentIndex(count - 2);
        // 更新标题
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());
        // 移除并删除当前界面
        QWidget *widget = ui->stackedWidget->widget(count - 1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}

// 返回按钮点击槽函数
void MasterView::on_btBack_clicked()
{
    goPreviousView();
}

void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count = ui->stackedWidget->count();
    if (count > 1)
        ui->btBack->setEnabled(true);
    else
        ui->btBack->setEnabled(false);

    QString title = ui->stackedWidget->currentWidget()->windowTitle();
    if (title == "欢迎") {
        ui->btLogout->setEnabled(true);
        ui->btBack->setEnabled(false);
    } else {
        ui->btLogout->setEnabled(false);
    }
}

void MasterView::on_btLogout_clicked()
{
    goPreviousView();
}

