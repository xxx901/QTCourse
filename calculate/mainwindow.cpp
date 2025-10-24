#include "mainwindow.h"
#include "ui_mainwindow.h"


#include<QDebug>
#include<math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    btnNums={{Qt::Key_0,ui->btnNum0},
            {Qt::Key_1,ui->btnNum1},
            {Qt::Key_2,ui->btnNum2},
            {Qt::Key_3,ui->btnNum3},
            {Qt::Key_4,ui->btnNum4},
            {Qt::Key_5,ui->btnNum5},
            {Qt::Key_6,ui->btnNum6},
            {Qt::Key_7,ui->btnNum7},
            {Qt::Key_8,ui->btnNum8},
            {Qt::Key_9,ui->btnNum9}
    };

    foreach(auto btn,btnNums)
            connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    // connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->jiafa,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->jianfa,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->chengfa,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->chufa,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));

    connect(ui->yushu,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->daoshu,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->genhao,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->pingfang,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton*>(sender())->text();

    if(digit=="0" && operand == "0")
        digit = "";

    if(operand == "0" && digit != "0")
        operand = "" ;

    operand += digit;

    ui->display->setText(operand);



}




void MainWindow::on_xiaoshudian_clicked()
{
    if(!operand.contains("."))
        operand += qobject_cast<QPushButton*>(sender())->text();
    ui->display->setText(operand);

}


void MainWindow::on_delete_2_clicked()
{
    operand = operand.left(operand.length()-1);
    ui->display->setText(operand);

}


void MainWindow::on_C_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}

QString MainWindow::calculation(bool *ok)
{
    double result=0;

    if(operands.size()==2&&opcodes.size()>0){
        double operand1=operands.front().toDouble();
        operands.pop_front();
        double operand2=operands.front().toDouble();
        operands.pop_front();

        QString op = opcodes.front();
        opcodes.pop_front();

        if(op=="+"){
            result=operand1 + operand2;
        }else if(op=="-"){
            result=operand1 - operand2;
        }else if(op=="×"){
            result=operand1 * operand2;
        }else if(op=="÷"){
            result=operand1 / operand2;
        }

        operands.push_back(QString::number(result));


        ui->statusbar->showMessage("calculation is in progress");
    }else
        ui->statusbar->showMessage(QString("oprands is %1,opcode is %2").arg(operands.size()).arg(opcodes.size()));

    return QString::number(result);
}

void MainWindow::btnBinaryOperatorClicked()
{
    ui->statusbar->showMessage("last oprand"+operand);
    QString opcode = qobject_cast<QPushButton*>(sender())->text();

    if(operand!=""){
        operands.push_back(operand);
        operand="";

        opcodes.push_back(opcode);
    }

    QString result=calculation();

    ui->display->setText(result);
}

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand!=""){
        double result = operand.toDouble();
        operand="";

        QString op = qobject_cast<QPushButton*>(sender())->text();

        if(op=="%")
            result/=100.0;
        else if(op=="x^2")
            result*=result;
        else if(op=="√x")
            result=sqrt(result);
        else if(op=="1/x")
            result=1/result;

        ui->display->setText(QString::number(result));
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString keyText = event->text();

    if (!keyText.isEmpty() && keyText >= "0" && keyText <= "9") {
        int digit = keyText.toInt();
        QPushButton* numBtn = nullptr;


        switch(digit) {
        case 0: numBtn = ui->btnNum0; break;
        case 1: numBtn = ui->btnNum1; break;
        case 2: numBtn = ui->btnNum2; break;
        case 3: numBtn = ui->btnNum3; break;
        case 4: numBtn = ui->btnNum4; break;
        case 5: numBtn = ui->btnNum5; break;
        case 6: numBtn = ui->btnNum6; break;
        case 7: numBtn = ui->btnNum7; break;
        case 8: numBtn = ui->btnNum8; break;
        case 9: numBtn = ui->btnNum9; break;
        }

        if (numBtn) {
            numBtn->animateClick();
            return;
        }
    }

    if (!keyText.isEmpty()) {
        if (keyText == "+") {
            ui->jiafa->animateClick();
            return;
        } else if (keyText == "-") {
            ui->jianfa->animateClick();
            return;
        } else if (keyText == "*") {
            ui->chengfa->animateClick();
            return;
        } else if (keyText == "/") {
            ui->chufa->animateClick();
            return;
        } else if (keyText == "=") {
            ui->dengyu->animateClick();
            return;
        } else if (keyText == ".") {
            ui->xiaoshudian->animateClick();
            return;
        } else if (keyText == "%") {
            ui->yushu->animateClick();
            return;
        }
    }

    switch(event->key()) {
    case Qt::Key_Enter:
    case Qt::Key_Return:
        ui->dengyu->animateClick();
        break;
    case Qt::Key_Backspace:
        ui->delete_2->animateClick();
        break;
    case Qt::Key_Escape:
    case Qt::Key_Delete:
        ui->C->animateClick();
        break;
    case Qt::Key_Period:
    case Qt::Key_Comma:
        ui->xiaoshudian->animateClick();
        break;
    case Qt::Key_F9:
        ui->jiajian->animateClick();
        break;
    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}


void MainWindow::on_dengyu_clicked()
{
    if(operand!=""){
        operands.push_back(operand);
        operand="";
    }

    QString result=calculation();

    ui->display->setText(result);
}

void MainWindow::on_jiajian_clicked()
{
    if (operand.isEmpty()) {
        operand = "0";
    }

    if (operand != "0") {
        if (operand.startsWith('-')) {
            operand = operand.mid(1);
        } else {
            operand = '-' + operand;
        }

        ui->display->setText(operand);
    }
}

