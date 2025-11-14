#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QColorDialog>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textChanged = false;
    on_actionNew_triggered();


    statusLabel.setMaximumWidth(180);
    statusLabel.setText("length: " + QString::number(0) + "   lines: " + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);


    statusCursorLabel.setMaximumWidth(180);
    statusCursorLabel.setText("Ln: " + QString::number(0) + "   Col: " + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel    );

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("伊晓鹏"));
    ui->statusbar->addPermanentWidget(author);

    ui->actionactionUndo->setEnabled(false);
    ui->actionactionRedo->setEnabled(false);
    ui->actionactionCopy->setEnabled(false);
    ui->actionactionCut->setEnabled(false);
    ui->actionactionPaste->setEnabled(false);

    // Reflect current wrap mode in the action (checked == wrap enabled)
    QPlainTextEdit::LineWrapMode mode = ui->textEdit->lineWrapMode();
    ui->actionactionWrap->setChecked(mode == QPlainTextEdit::WidgetWidth);

    ui->actionactionStatusBar->setChecked(true);
    ui->actionactionToolBar->setChecked(true);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionactionFind_triggered()
{
    SearchDialog dlg(this, ui->textEdit);  // 传递文本控件
    dlg.exec();
}


void MainWindow::on_actionactionReplace_triggered()
{
    ReplaceDialog dlg(this, ui->textEdit);
    dlg.exec();
}

void MainWindow::on_actionactionPrint_triggered()
{
    // Print action placeholder - not implemented yet
    QMessageBox::information(this, tr("打印"), tr("打印功能未实现。"));
}


void MainWindow::on_actionNew_triggered()
{

    if(!userEditConfirmed())
        return ;

    filePath = "";
    ui->textEdit->clear();
    this->setWindowTitle(tr("新建文本文件 - 编辑器"));

    textChanged = false;
}


void MainWindow::on_actionactionOpen_triggered()
{
    if(!userEditConfirmed())
        return ;

    QString filename = QFileDialog::getOpenFileName(this,"打开文件", ".",tr("Text files (*.txt) ;; All (*.*)"));
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, ".." , "打开文件失败");
        return;
    }

    filePath = filename;

    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->insertPlainText(text);
    file.close();

    this->setWindowTitle(QFileInfo(filename).absoluteFilePath());

    textChanged = false;

}


void MainWindow::on_actionactionSave_triggered()
{
    if(filePath == "" ){
        QString filename = QFileDialog::getSaveFileName(this,"保存文件", ".",tr("Text files (*.txt) "));

        QFile file(filename);
         if(!file.open(QFile::WriteOnly | QFile::Text)){

                 QMessageBox::warning(this, ".." , "保存文件失败");
                 return;
          }
         file.close();
           filePath = filename;
    }

    QFile file(filePath);

     if(!file.open(QFile::WriteOnly | QFile::Text)){

             QMessageBox::warning(this, ".." , "保存文件失败");
             return;
      }

    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());

    textChanged = false;

}


void MainWindow::on_actionactionSaveAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"保存文件", ".",tr("Text files (*.txt) "));

    QFile file(filename);
     if(!file.open(QFile::WriteOnly | QFile::Text)){

             QMessageBox::warning(this, ".." , "保存文件失败");
             return;

      }

     filePath = filename;
     QTextStream out(&file);
     QString text = ui->textEdit->toPlainText();
     out<<text;
     file.flush();
     file.close();

     this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
}


void MainWindow::on_textEdit_textChanged()
{
    if(!textChanged){
        this->setWindowTitle("*" + this->windowTitle());
        textChanged = true;
    }

      statusLabel.setText("length: " + QString::number(ui->textEdit->toPlainText().length()) + "   lines: " + QString::number(ui->textEdit->document()->lineCount()));
}

bool MainWindow::userEditConfirmed()
{
    if(textChanged){

        QString path = (filePath != "") ? filePath : "无标题.txt";

        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("...");
        msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("是否将更改保存到\n") + "\"" + path + "\" ?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        int r = msg.exec();
        switch (r) {
        case QMessageBox::Yes:
            on_actionactionSave_triggered();
            break;
        case QMessageBox::No:
            textChanged = false;
            break;
        case QMessageBox::Cancel:
            return false;

        }

    }

    return true;

}


void MainWindow::on_actionactionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionactionCut_triggered()
{
    ui->textEdit->cut();
     ui->actionactionPaste->setEnabled(true);

}

void MainWindow::on_actionactionCopy_triggered()
{
    ui->textEdit->copy();
    ui->actionactionPaste->setEnabled(true);
}


void MainWindow::on_actionactionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionactionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_textEdit_undoAvailable(bool b)
{
    ui->actionactionUndo->setEnabled(b);

}


void MainWindow::on_textEdit_copyAvailable(bool b)
{
        ui->actionactionCopy->setEnabled(b);
        ui->actionactionCut->setEnabled(b);
}


void MainWindow::on_textEdit_redoAvailable(bool b)
{
    ui->actionactionRedo->setEnabled(b);
}


void MainWindow::on_actionFontColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this , "选择颜色");
    if(color.isValid()){
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit {color: %1}").arg(color.name()));
    }

}


void MainWindow::on_actionBackgroundColor_triggered()
{

    QColor color = QColorDialog::getColor(Qt::black, this , "选择颜色");
    if(color.isValid()){
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit {background-color: %1}").arg(color.name()));
    }

}


void MainWindow::on_actionFontBackgroundColor_triggered()
{
    // 这里添加设置字体背景色的逻辑（例如打开颜色选择对话框）
    QColor color = QColorDialog::getColor(Qt::white, this, "选择背景色");
    if (color.isValid()) {
        QPalette palette = ui->textEdit->palette();
        palette.setColor(QPalette::Base, color); // 设置文本编辑区背景色
        ui->textEdit->setPalette(palette);
    }
}



void MainWindow::on_actionactionWrap_triggered()
{
    // 获取当前的换行模式
    QPlainTextEdit::LineWrapMode mode = ui->textEdit->lineWrapMode();

    // 对比当前模式，切换自动换行状态
    if (mode == QPlainTextEdit::NoWrap) {
         // 若当前不换行，则切换为按窗口宽度自动换行
          ui->textEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
          ui->actionactionWrap->setChecked(true); // 同步菜单勾选状态
     } else {
          // 若当前已换行，则切换为不自动换行
          ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
          ui->actionactionWrap->setChecked(false); // 同步菜单勾选状态
     }
}


void MainWindow::on_actionactionFont_triggered()
{
    bool ok =false;
    QFont font = QFontDialog::getFont(&ok,this);

    if(ok)
        ui->textEdit->setFont(font);
}


void MainWindow::on_actionactionToolBar_triggered()
{
    bool visible = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visible);
    ui->actionactionToolBar->setChecked(!visible);

}


void MainWindow::on_actionactionStatusBar_triggered()
{
    bool visible = ui->statusbar->isVisible();
    ui->statusbar->setVisible(!visible);
    ui->actionactionStatusBar->setChecked(!visible);
}


void MainWindow::on_actionSelectAll_triggered()
{
    ui->textEdit->selectAll();
}


void MainWindow::on_actionactionExit_triggered()
{
    if(userEditConfirmed())
        exit(0);

}


void MainWindow::on_textEdit_cursorPositionChanged()
{
    int col = 0;
    int ln = 0;
    int flg = -1;
    int pos = ui ->textEdit->textCursor().position();
    QString text = ui->textEdit->toPlainText();

    for (int i = 0; i < pos; i++) {
        if ( text[i] == '\n' ) {
            ln ++;
            flg = i;
        }
    }

    flg ++;
    col = pos - flg;
    statusCursorLabel.setText("Ln: " + QString::number(ln + 1) + "   Col: " + QString::number(col + 1));
}


