#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>  // 必须包含

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr, QPlainTextEdit* textEdit = nullptr);
    ~SearchDialog();

private slots:
    void on_btFindNext_clicked();  // 查找下一个
    void on_btCancel_clicked();    // 取消

private:
    Ui::SearchDialog *ui;
    QPlainTextEdit *pTextEdit;  // 指向主窗口的文本编辑控件
};

#endif // SEARCHDIALOG_H
