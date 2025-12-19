#include "patientview.h"
#include "ui_patientview.h"
#include "idatabase.h"

PatientView::PatientView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientView)
{
    ui->setupUi(this);

    // TableView属性设置
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setAlternatingRowColors(true);

    // 初始化患者模型
    IDatabase &iDatabase = IDatabase::getInstance();
    if (iDatabase.initPatientModel()) {
        ui->tableView->setModel(iDatabase.patientTabModel);
        ui->tableView->setSelectionModel(iDatabase.thePatientSelection);
    } else {
        qDebug() << "患者模型初始化失败";
    }
}

PatientView::~PatientView()
{
    delete ui;
}

// 添加患者按钮槽函数
void PatientView::slot_btAdd_clicked()
{
    // 1. 调用数据库的“添加新患者”方法，获取新行索引
    int newRow = IDatabase::getInstance().addNewPatient();
    if (newRow == -1) {
        QMessageBox::warning(this, "失败", "添加新患者失败");
        return;
    }

    // 2. 通知MasterView打开患者编辑界面（传递新行索引）
    emit goPatientEditView(newRow); // 需在PatientView.h中声明带参数的信号
}


// 查询按钮槽函数
void PatientView::on_btSearch_clicked()
{
    // 注意：lineEdit_Search 替换为你UI中搜索输入框的真实objectName
    QString keyword = ui->lineEdit_Search->text().trimmed();
    if (keyword.isEmpty()) {
        IDatabase::getInstance().searchPatient("1=1");
        return;
    }
    // 注意：name 替换为你数据库中“姓名”字段的真实名称（比如 fullname）
    QString filter = QString("name like '%%1%'").arg(keyword);
    IDatabase::getInstance().searchPatient(filter);
}

// 删除按钮槽函数（可选，若有）
void PatientView::on_btDelete_clicked()
{
    QMessageBox::StandardButton ret = QMessageBox::question(
        this, "确认删除", "是否删除选中的患者？",
        QMessageBox::Yes | QMessageBox::No
    );
    if (ret != QMessageBox::Yes) return;

    bool success = IDatabase::getInstance().deleteCurrentPatient();
    if (!success) {
        QMessageBox::warning(this, "失败", "删除失败，请先选择患者");
    }
}

// patientview.cpp 编辑按钮槽函数
void PatientView::slot_btEdit_clicked()
{
    // 获取选中行索引
    IDatabase &db = IDatabase::getInstance();
    QModelIndex curIndex = db.thePatientSelection->currentIndex();
    if (!curIndex.isValid()) {
        QMessageBox::warning(this, "提示", "请先选择要编辑的患者");
        return;
    }

    // 打开编辑界面（传递选中行索引）
    emit goPatientEditView(curIndex.row());
}
