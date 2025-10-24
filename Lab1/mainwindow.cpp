#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QtCore/Qt>
#include <math.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->display->setAlignment(Qt::AlignRight | Qt::AlignVCenter);


    connect(ui->btnNum0, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum1, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum2, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum3, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum4, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum5, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum6, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum7, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum8, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    connect(ui->btnNum9, SIGNAL(clicked()), this, SLOT(btnNumClicked()));

    connect(ui->btnPlus, SIGNAL (clicked()), this, SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMinus, SIGNAL (clicked()), this, SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMultiple, SIGNAL (clicked()), this, SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnDivide, SIGNAL (clicked()), this, SLOT(btnBinaryOperatorClicked()));

    connect(ui->btnPercentage, SIGNAL (clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnInverse, SIGNAL (clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquare, SIGNAL (clicked()), this, SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSqrt, SIGNAL (clicked()), this, SLOT(btnUnaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    if (operands.size() < 2 || opcodes.isEmpty()) {
        ui->statusbar->showMessage("缺少操作数或运算符");
        return "";
    }

    // 取出栈顶的两个操作数注意顺序）
    double operand2 = operands.top().toDouble();
    operands.pop();
    double operand1 = operands.top().toDouble();
    operands.pop();

    QString op = opcodes.top();
    opcodes.pop();  // 弹出已使用的运算符

    double result = 0;
    bool valid = true;

    // 执行运算
    if (op == "+") {
        result = operand1 + operand2;
    } else if (op == "-") {
        result = operand1 - operand2;
    } else if (op == "*") {
        result = operand1 * operand2;
    } else if (op == "/") {
        if (qFuzzyCompare(operand2, 0.0)) {
            ui->statusbar->showMessage("错误：除零");
            valid = false;
        } else {
            result = operand1 / operand2;
        }
    } else {
        ui->statusbar->showMessage("未知运算符");
        valid = false;
    }

    if (!valid) {
        return "";
    }

    // 将结果存入 operand（用于显示）
    QString resultStr = QString::number(result);
    operand = resultStr;  // 更新当前 operand

    // 将结果压入 operands 栈（支持连续运算）
    operands.push(resultStr);

    // 显示计算过程
    ui->statusbar->showMessage(QString("计算：%1 %2 %3 = %4").arg(operand1).arg(op).arg(operand2).arg(result));
    return resultStr;
}


void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();

    if (digit=="0" && operand=="0")
        digit= "";
    if (operand=="0" && digit !="0")
        operand= "";

    operand += digit;

    ui->display->setText(operand);

}


void MainWindow::on_btnPeriod_clicked()
{
    QString str = ui->display->text();
    if (!str.contains("."))
        operand += qobject_cast<QPushButton *>(sender())->text();
    ui->display->setText(operand);
}


void MainWindow::on_btnDel_clicked()
{
    operand = operand.left(operand.length() -1);
    ui->display->setText(operand);
}


void MainWindow::on_btnClear_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}


void MainWindow::btnBinaryOperatorClicked() {
    if (!operand.isEmpty()) {
        operands.push(operand);
        operand.clear();
    }

    QString buttonText = qobject_cast<QPushButton*>(sender())->text();
    QString opcode;

    // 将按钮文本转换为标准运算符
    if (buttonText == "×" || buttonText == "*") {
        opcode = "*";
    } else if (buttonText == "÷" || buttonText == "/") {
        opcode = "/";
    } else if (buttonText == "−" || buttonText == "-") {
        opcode = "-";
    } else if (buttonText == "＋") {
        opcode = "+";
    } else {
        ui->statusbar->showMessage("未知运算符按钮");
        return;
    }

    if (!opcodes.isEmpty() && operands.size() >= 2) {
            calculation();
            operand.clear();  // 关键：清空operand，避免后续数字拼接
        }

    opcodes.push(opcode);
    ui->statusbar->showMessage("运算符: " + opcode);
}

void MainWindow::btnUnaryOperatorClicked()
{
    if (operand.isEmpty()) {
        ui->statusbar->showMessage("没有输入操作数");
        return;
    }

    double result = operand.toDouble();
    QString op = qobject_cast<QPushButton*>(sender())->text();

    // 执行单目运算
    if (op == "%") {
        result /= 100.0;
    } else if (op == "1/x") {
        if (qFuzzyCompare(result, 0.0)) {
            ui->statusbar->showMessage("错误：除零");
            return;
        }
        result = 1.0 / result;
    } else if (op == "x^2") {
        result *= result;
    } else if (op == "√" || op == "sqrt") {  // 支持中文和英文符号
        if (result < 0) {
            ui->statusbar->showMessage("错误：负数不能开平方");
            return;
        }
        result = sqrt(result);
    } else {
        ui->statusbar->showMessage("未知运算符");
        return;
    }

    operand = QString::number(result);
    ui->display->setText(operand);
    ui->statusbar->showMessage("运算: " + op + " " + QString::number(result));
}


void MainWindow::on_btnEqual_clicked()
{
    if(operand !="")
    {
        operands.push_back(operand);
        operand ="" ;
    }
    QString result =calculation();
    ui->display->setText(result);
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // 忽略重复按键（可选，避免长按连续触发）
    if (event->isAutoRepeat()) {
        QMainWindow::keyPressEvent(event);
        return;
    }

    // 根据按下的键盘数字键，触发对应按钮的点击动画
    switch (event->key()) {
        case Qt::Key_0:
            ui->btnNum0->animateClick(100); // 触发“0”按钮
            break;
        case Qt::Key_1:
            ui->btnNum1->animateClick(100); // 触发“1”按钮
            break;
        case Qt::Key_2:
            ui->btnNum2->animateClick(100); // 触发“2”按钮
            break;
        case Qt::Key_3:
            ui->btnNum3->animateClick(100);
            break;
        case Qt::Key_4:
            ui->btnNum4->animateClick(100);
            break;
        case Qt::Key_5:
            ui->btnNum5->animateClick(100);
            break;
        case Qt::Key_6:
            ui->btnNum6->animateClick(100);
            break;
        case Qt::Key_7:
            ui->btnNum7->animateClick(100);
            break;
        case Qt::Key_8:
            ui->btnNum8->animateClick(100);
            break;
        case Qt::Key_9:
            ui->btnNum9->animateClick(100);
            break;
        default:
            // 其他按键交给父类处理
            QMainWindow::keyPressEvent(event);
    }
}

