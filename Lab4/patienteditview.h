#ifndef PATIENTEDITVIEW_H
#define PATIENTEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper> // 新增：数据绑定需要
#include <QMessageBox>       // 新增：弹窗提示需要

namespace Ui {
class PatientEditView;
}

class PatientEditView : public QWidget
{
    Q_OBJECT

public:

    explicit PatientEditView(QWidget *parent = nullptr, int index = 0);
    ~PatientEditView();


private slots:
    void on_pushButton_2_clicked(); // 保存按钮槽函数

signals:
    void goPreviousView(); // 编辑完成返回列表

private:
    Ui::PatientEditView *ui;
    QDataWidgetMapper *dataMapper; // 新增：数据绑定对象
};

#endif // PATIENTEDITVIEW_H
