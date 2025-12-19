#include "patienteditview.h"
#include "ui_patienteditview.h"
#include "idatabase.h"       // 修复：IDatabase未定义
#include <QDataWidgetMapper>  // 修复：QDataWidgetMapper未定义
#include <QMessageBox>       // 修复：QMessageBox未定义
#include <QDebug>            // 可选：调试用

// 构造函数：参数匹配头文件声明（parent + index）
PatientEditView::PatientEditView(QWidget *parent, int index)
    : QWidget(parent)
    , ui(new Ui::PatientEditView)
    , dataMapper(nullptr) // 修复：初始化成员变量，避免野指针
{
    ui->setupUi(this);

    // 1. 获取数据库的患者模型
    IDatabase &db = IDatabase::getInstance();
    QSqlTableModel *tabModel = db.patientTabModel;
    if (tabModel == nullptr) {
        qDebug() << "患者模型未初始化，无法编辑";
        return;
    }

    // 2. 初始化DataWidgetMapper（绑定控件与模型）
    dataMapper = new QDataWidgetMapper(this);
    dataMapper->setModel(tabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    // 3. 绑定控件与数据库字段（关键修复：替换为你实际的控件名/字段名）
    dataMapper->addMapping(ui->dbEditID, tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName, tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditIDCard, tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->dbSpinHeight, tabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->dbSpinWeight, tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->dbDateEditDOB, tabModel->fieldIndex("BIRTHDAY"));
    dataMapper->addMapping(ui->dbComboSex, tabModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dbCreatedTimeStamp, tabModel->fieldIndex("CREATEDTIMESTAMP"));

    // 4. 定位到目标行
    dataMapper->setCurrentIndex(index);
}

PatientEditView::~PatientEditView()
{
    delete dataMapper; // 修复：释放数据绑定对象，避免内存泄漏
    delete ui;
}

// 保存按钮槽函数
void PatientEditView::on_pushButton_2_clicked()
{
    if (dataMapper == nullptr) { // 修复：空指针检查
        QMessageBox::warning(this, "错误", "数据绑定未初始化！");
        return;
    }

    // 1. 提交当前编辑的内容到模型（AutoSubmit可省略，手动提交需保留）
    dataMapper->submit();

    // 2. 提交模型修改到数据库
    IDatabase &db = IDatabase::getInstance();
    if (!db.submitPatientEdit()) {
        // 修复：拼接错误信息（QString拼接，避免char*冲突）
        QString errMsg = QString("保存患者信息失败：%1").arg(db.patientTabModel->lastError().text());
        QMessageBox::warning(this, "失败", errMsg);
        db.revertPatientEdit(); // 回滚错误
        return;
    }

    // 3. 保存成功：发送返回信号（需在头文件声明goPreviousView信号）
    emit goPreviousView();
    // 可选：关闭编辑界面
    this->close();
}
