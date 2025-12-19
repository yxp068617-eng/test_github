#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QSqlError>
#include <QModelIndex>

class IDatabase : public QObject
{
    Q_OBJECT

public:
    static IDatabase& getInstance();
    QString userLogin(QString userName, QString password);
    bool initPatientModel(); // 患者模型初始化
    void revertPatientEdit(); // 修正：返回值是void（和cpp实现一致）
    bool searchPatient(QString filter); // 查询患者（返回bool，参数QString）
    bool deleteCurrentPatient(); // 删除患者（返回bool，无参数）
    bool submitPatientEdit(); // 提交患者编辑（返回bool）
    int addNewPatient();      // 添加新患者（返回int行索引）
    QSqlTableModel *patientTabModel;
    QItemSelectionModel *thePatientSelection;

private:
    explicit IDatabase(QObject *parent = nullptr);
    IDatabase(const IDatabase &) = delete;
    void operator=(const IDatabase &) = delete;

    QSqlDatabase database;
    void initDatabase();
};

#endif // IDATABASE_H
