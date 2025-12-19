#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QWidget>
#include <QMessageBox>
#include <QAbstractItemView>

namespace Ui {
class PatientView;
}

class PatientView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientView(QWidget *parent = nullptr);
    ~PatientView();

private slots:
    void slot_btAdd_clicked();    // 之前的添加按钮槽函数
    void slot_btEdit_clicked();   // 之前的编辑按钮槽函数
    void on_btSearch_clicked();   // 新增：查询按钮槽函数声明
    void on_btDelete_clicked();   // 新增：删除按钮槽函数声明


signals:
    void goPatientEditView(int rowNo); // 传递行索引的信号

private:
    Ui::PatientView *ui;
};

#endif // PATIENTVIEW_H
