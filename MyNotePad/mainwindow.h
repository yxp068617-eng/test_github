#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();

    void on_actionactionFind_triggered();

    void on_actionactionReplace_triggered();

    void on_actionNew_triggered();

    void on_actionactionOpen_triggered();

    void on_actionactionSave_triggered();

    void on_actionactionSaveAs_triggered();

    void on_textEdit_textChanged();

    void on_actionactionUndo_triggered();

    void on_actionactionCut_triggered();

    void on_actionactionCopy_triggered();

    void on_actionactionPaste_triggered();

    void on_actionactionRedo_triggered();

    void on_textEdit_undoAvailable(bool b);

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_redoAvailable(bool b);

    void on_actionFontColor_triggered();

    void on_actionBackgroundColor_triggered();

    void on_actionFontBackgroundColor_triggered();

    void on_actionactionWrap_triggered();

    void on_actionactionFont_triggered();

    void on_actionactionToolBar_triggered();

    void on_actionactionStatusBar_triggered();

    void on_actionSelectAll_triggered();

    void on_actionactionExit_triggered();

    void on_textEdit_cursorPositionChanged();

    void on_actionactionPrint_triggered();

private:
    Ui::MainWindow *ui;

    QLabel statusCursorLabel;
    QLabel statusLabel;

    QString filePath;
    bool textChanged;

    bool userEditConfirmed();
};
#endif // MAINWINDOW_H
