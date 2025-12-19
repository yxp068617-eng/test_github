#include "idatabase.h"
#include <QSqlError>       // 新增：必须包含QSqlError头文件
#include <QSqlTableModel>  // 患者模型依赖
#include <QItemSelectionModel>
#include <QUuid>
#include <QDateTime>
#include <QSqlRecord>


IDatabase& IDatabase::getInstance()
{
    static IDatabase instance;
    return instance;
}

IDatabase::IDatabase(QObject *parent) : QObject(parent)
{
    initDatabase();
}

void IDatabase::initDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    // 【关键】替换为你的数据库绝对路径（教程里是D:/QtCode/libda.db，你要改成D:/Qt/Document/libda.db）
    QString aFile = "D:/Qt/Document/libda.db";
    database.setDatabaseName(aFile);

    if (!database.open()) {
        qDebug() << "failed to open database";
    } else {
        qDebug() << "open database is ok" << database.connectionName();
    }
}


void IDatabase::revertPatientEdit() // 返回值void，和头文件声明一致
{
    if (patientTabModel != nullptr) {
        patientTabModel->revertAll(); // 回滚未提交的修改
        patientTabModel->select();
    }
}

bool IDatabase::submitPatientEdit()
{
    if (patientTabModel == nullptr) return false;
    return patientTabModel->submitAll(); // 提交模型修改到数据库
}

// 【教程核心】实现登录验证函数
QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query; // 创建查询对象（绑定到当前数据库）
    // 1. 预处理SQL语句（防止SQL注入，教程里的:USER是参数占位符）
    query.prepare("select username, password from user where username = :USER");
    // 2. 绑定参数（将输入的用户名替换:USER）
    query.bindValue(":USER", userName);
    // 3. 执行查询
    query.exec();

    // 调试输出（教程里的日志，可选保留）
    qDebug() << query.lastQuery() << query.first();

    // 4. 验证查询结果
    if (query.first() && query.value("username").isValid()) {
        // 查到用户，验证密码
        QString passwd = query.value("password").toString();
        if (passwd == password) {
            qDebug() << "login ok";
            return "loginOk"; // 密码正确，返回标识
        } else {
            qDebug() << "wrong password";
            return "wrongPassword"; // 密码错误
        }
    } else {
        // 未查到用户
        qDebug() << "no such user";
        return "wrongUsername"; // 用户名错误
    }
}

// 【教程核心】实现患者模型初始化
bool IDatabase::initPatientModel()
{
    // 1. 检查数据库是否已打开
    if (!database.isOpen()) {
        qDebug() << "数据库未打开，无法初始化患者模型";
        return false;
    }

    // 2. 创建患者表格模型（绑定到当前数据库）
    patientTabModel = new QSqlTableModel(this, database);
    // 3. 设置模型关联的数据库表（教程里是患者表，比如"patient"，需替换为你实际的表名）
    patientTabModel->setTable("patient");
    // 4. 设置编辑策略（按需选，教程常用OnManualSubmit：手动提交修改）
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    // 5. 查询表数据（加载数据到模型）
    if (!patientTabModel->select()) {
        qDebug() << "患者模型加载数据失败：" << patientTabModel->lastError().text();
        return false;
    }

    // 7. 创建选择模型（关联数据模型，供TableView选择行）
    thePatientSelection = new QItemSelectionModel(patientTabModel, this);

    qDebug() << "患者模型初始化成功";
    return true;
}

bool IDatabase::searchPatient(QString filter) // 返回bool+参数QString，和声明一致
{
    if (patientTabModel == nullptr) {
        qDebug() << "患者模型未初始化，无法查询";
        return false;
    }
    patientTabModel->setFilter(filter);
    bool result = patientTabModel->select();
    if (!result) {
        qDebug() << "查询失败：" << patientTabModel->lastError().text();
    }
    return result;
}

bool IDatabase::deleteCurrentPatient() // 返回bool，无参数，和声明一致
{
    if (patientTabModel == nullptr || thePatientSelection == nullptr) {
        qDebug() << "患者模型/选择模型未初始化";
        return false;
    }

    QModelIndex curIndex = thePatientSelection->currentIndex();
    if (!curIndex.isValid()) {
        qDebug() << "请先选择要删除的患者";
        return false;
    }

    int row = curIndex.row();
    patientTabModel->removeRow(row);

    bool result = patientTabModel->submitAll();
    if (!result) {
        qDebug() << "删除失败：" << patientTabModel->lastError().text();
        patientTabModel->revertAll();
        return false;
    }

    patientTabModel->select();
    qDebug() << "删除患者成功";
    return true;
}


int IDatabase::addNewPatient()
{
    if (patientTabModel == nullptr) {
        qDebug() << "患者模型未初始化，无法添加新患者";
        return -1;
    }

    // 1. 在模型末尾插入新行
    int newRow = patientTabModel->rowCount();
    if (!patientTabModel->insertRow(newRow)) {
        qDebug() << "插入新行失败：" << patientTabModel->lastError().text();
        return -1;
    }

    // 2. 创建新行的记录对象（用于赋值）
    QSqlRecord curRec = patientTabModel->record(newRow);

    // 3. 自动生成UUID作为ID（截图逻辑：不带大括号的UUID）
    QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    curRec.setValue("ID", uuid); // 赋值到ID字段

    // 4. 自动生成当前时间作为创建时间
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    curRec.setValue("CREATEDTIMESTAMP", currentTime); // 赋值到CREATEDTIMESTAMP字段

    // 5. 将赋值后的记录写回模型
    patientTabModel->setRecord(newRow, curRec);

    // 6. 返回新行索引（供编辑界面定位）
    QModelIndex curIndex = patientTabModel->index(newRow, 0);
    return curIndex.row();
}
