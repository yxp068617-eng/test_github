#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QMessageBox>  // 新增

SearchDialog::SearchDialog(QWidget *parent, QPlainTextEdit* textEdit) :
    QDialog(parent),
    ui(new Ui::SearchDialog),
    pTextEdit(textEdit)  // 初始化文本控件指针
{
    ui->setupUi(this);
    // 假设UI中有"查找下一个"按钮(btFindNext)、"取消"按钮(btCancel)
    // 查找内容输入框(searchText)、区分大小写复选框(cbCaseSensitive)
    // 方向单选按钮(rbDown、rbUp)
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

// 查找下一个按钮逻辑
void SearchDialog::on_btFindNext_clicked()
{
    QString target = ui->searchText->text();
    if (target.isEmpty() || !pTextEdit) return;

    QString text = pTextEdit->toPlainText();
    QTextCursor cursor = pTextEdit->textCursor();
    int index = -1;
    // 修正：将 cbCaseSensitive 改为 cbCaseSensetive（与UI控件名一致）
    Qt::CaseSensitivity cs = ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

    if (ui->rbDown->isChecked()) {
        // 向下查找
        index = text.indexOf(target, cursor.position(), cs);
    } else {
        // 向上查找
        int startPos = qMax(0, cursor.position() - 1);
        index = text.lastIndexOf(target, startPos, cs);
    }

    if (index >= 0) {
        // 选中找到的文本
        cursor.setPosition(index);
        cursor.setPosition(index + target.length(), QTextCursor::KeepAnchor);
        pTextEdit->setTextCursor(cursor);
    } else {
        QMessageBox::information(this, "提示", "找不到 '" + target + "'");
    }
}

// 取消按钮逻辑
void SearchDialog::on_btCancel_clicked()
{
    accept();  // 关闭对话框
}
