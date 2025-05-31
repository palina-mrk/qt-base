#include <QApplication>
#include <QDebug>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QToolButton>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <stdlib.h>
#include "logic.h"
#include "logic.cpp"

QLineEdit* line = nullptr;
Logic* calc = nullptr;
void printText();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget* widget = new QWidget;

    widget->setWindowTitle("calc");
    //widget->setMinimumWidth(250);
    //widget->setMinimumHeight(500);

    QGridLayout *layout = new QGridLayout(widget);
    layout->setRowMinimumHeight(1,60);
    layout->setVerticalSpacing(5);
    layout->setHorizontalSpacing(5);

    QToolButton* btnNum[10];
    const QSize btnSqrSize = QSize(50, 50);
    const char* nums = "0123456789";
    btnNum[0] = new QToolButton{widget};
    btnNum[0]->setText(QString(nums[0]));
    btnNum[0]->setMinimumSize(btnSqrSize);
    layout->addWidget(btnNum[0], 8, 1);
    for(int i = 1; i < 10; ++i){
        btnNum[i] = new QToolButton{widget};
        btnNum[i]->setText(QString(nums[i]));
        btnNum[i]->setMinimumSize(btnSqrSize);
        layout->addWidget(btnNum[i], 7 - (i - 1)/3, 1 + (i - 1)%3);
    }

    QToolButton* btnOn = new QToolButton{widget};
    const QSize btnRectSize = QSize(50, 20);
    btnOn->setText("on");
    btnOn->setMinimumSize(btnRectSize);
    layout->addWidget(btnOn, 2, 1);

    QToolButton* btnOff = new QToolButton{widget};
    btnOff->setText("off");
    btnOff->setMinimumSize(btnRectSize);
    layout->addWidget(btnOff, 2, 5);

    QToolButton* btnSin = new QToolButton{widget};
    btnSin->setText("sin");
    btnSin->setMinimumSize(btnRectSize);
    layout->addWidget(btnSin, 2, 2);

    QToolButton* btnCos = new QToolButton{widget};
    btnCos->setText("cos");
    btnCos->setMinimumSize(btnRectSize);
    layout->addWidget(btnCos, 2, 3);

    QToolButton* btnPow = new QToolButton{widget};
    btnPow->setText("a^b");
    btnPow->setMinimumSize(btnRectSize);
    layout->addWidget(btnPow, 2, 4);

    QToolButton* btnEqual = new QToolButton{widget};
    btnEqual->setText("=");
    btnEqual->setMinimumSize(btnSqrSize);
    layout->addWidget(btnEqual, 8, 5);

    QToolButton* btnMult = new QToolButton{widget};
    btnMult->setText("x");
    btnMult->setMinimumSize(btnSqrSize);
    layout->addWidget(btnMult, 6, 4);

    QToolButton* btnDiv = new QToolButton{widget};
    btnDiv->setText(":");
    btnDiv->setMinimumSize(btnSqrSize);
    layout->addWidget(btnDiv, 6, 5);

    QToolButton* btnAdd = new QToolButton{widget};
    btnAdd->setText("+");
    btnAdd->setMinimumSize(50,105);
    layout->addWidget(btnAdd, 7, 4, 8,4,Qt::AlignTop);

    QToolButton* btnSub = new QToolButton{widget};
    btnSub->setText("-");
    btnSub->setMinimumSize(btnSqrSize);
    layout->addWidget(btnSub, 7, 5);

    QToolButton* btnLog = new QToolButton{widget};
    btnLog->setText("log");
    btnLog->setMinimumSize(btnSqrSize);
    layout->addWidget(btnLog, 5, 4);

    QToolButton* btnSqr = new QToolButton{widget};
    btnSqr->setText("sqr");
    btnSqr->setMinimumSize(btnSqrSize);
    layout->addWidget(btnSqr, 5, 5);

    QToolButton* btnDot = new QToolButton{widget};
    btnDot->setText(".");
    btnDot->setMinimumSize(btnSqrSize);
    layout->addWidget(btnDot, 8, 3);

    QToolButton* btnSign = new QToolButton{widget};
    btnSign->setText("+/-");
    btnSign->setMinimumSize(btnSqrSize);
    layout->addWidget(btnSign, 4, 4);

    QToolButton* btnMemAdd = new QToolButton{widget};
    btnMemAdd->setText("M+");
    btnMemAdd->setMinimumSize(btnSqrSize);
    layout->addWidget(btnMemAdd, 4, 2);

    QToolButton* btnMemSub = new QToolButton{widget};
    btnMemSub->setText("M-");
    btnMemSub->setMinimumSize(btnSqrSize);
    layout->addWidget(btnMemSub, 4, 3);

    QToolButton* btnMemShow = new QToolButton{widget};
    btnMemShow->setText("MRC");
    btnMemShow->setMinimumSize(btnSqrSize);
    layout->addWidget(btnMemShow, 4, 1);

    QToolButton* btnDouble0 = new QToolButton{widget};
    btnDouble0->setText("00");
    btnDouble0->setMinimumSize(btnSqrSize);
    layout->addWidget(btnDouble0, 8, 2);

    QToolButton* btnDel = new QToolButton{widget};
    btnDel->setText("->");
    btnDel->setMinimumSize(btnSqrSize);
    layout->addWidget(btnDel, 4, 5);

    line = new QLineEdit{widget};
    line->setMinimumHeight(40);
    line->setAlignment(Qt::AlignTop);
    layout->addWidget(line, 1, 1, 1, 5);

    calc = new Logic{widget};
    QObject::connect(btnOn, &QToolButton::clicked, calc, &Logic::turnOn);
    QObject::connect(btnOff, &QToolButton::clicked, calc, &Logic::turnOff);
    QObject::connect(btnNum[0], &QToolButton::clicked, calc, &Logic::input0);
    QObject::connect(btnNum[1], &QToolButton::clicked, calc, &Logic::input1);
    QObject::connect(btnNum[2], &QToolButton::clicked, calc, &Logic::input2);
    QObject::connect(btnNum[3], &QToolButton::clicked, calc, &Logic::input3);
    QObject::connect(btnNum[4], &QToolButton::clicked, calc, &Logic::input4);
    QObject::connect(btnNum[5], &QToolButton::clicked, calc, &Logic::input5);
    QObject::connect(btnNum[6], &QToolButton::clicked, calc, &Logic::input6);
    QObject::connect(btnNum[7], &QToolButton::clicked, calc, &Logic::input7);
    QObject::connect(btnNum[8], &QToolButton::clicked, calc, &Logic::input8);
    QObject::connect(btnNum[9], &QToolButton::clicked, calc, &Logic::input9);
    QObject::connect(btnDouble0, &QToolButton::clicked, calc, &Logic::input00);
    QObject::connect(btnDot, &QToolButton::clicked, calc, &Logic::inputDot);
    QObject::connect(btnDel, &QToolButton::clicked, calc, &Logic::delDig);
    QObject::connect(btnSign, &QToolButton::clicked, calc, &Logic::chSign);


    QObject::connect(calc, &Logic::onChanged, printText);

    widget->show();
    return a.exec();
}

void printText(){
    line->setText(calc->getCurrent());
}
