#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <ctime>
#include <iostream>
#include "mainwindow.h"

int GetRandPositionX(int width);
int GetRandPositionY(int height);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    move(0,0);
    resize(maximumWidth(),maximumHeight());

    auto actionTimer = new QTimer(this);
    auto moveTimer = new QTimer(this);

    auto score = new QLabel("0",this);

    score->setGeometry(0,0,40,60);
    score->show();

    auto label = new QLabel("YOU LOOSE",this);
    label->hide();

    connect(actionTimer, &QTimer::timeout, this,
            [this, actionTimer,moveTimer,label,score]{

                auto btn = new QPushButton(this);

                btn->setGeometry(GetRandPositionX(width()),GetRandPositionY(height()), 30, 30);
                btn->setText("<->");
                btn->show();

                connect(moveTimer,&QTimer::timeout,btn,
                        [=]{
                                int btnX = btn->pos().x();
                                int btnY = btn->pos().y();

                                btn->move(btnX,btnY+1);
                                if(btn->pos().y() > height()-btn->height())
                                {
                                    actionTimer->stop();
                                    moveTimer->stop();
                                    this->setDisabled(true);
                                    btn->styleSheet();
                                    setStyleSheet(("QPushButton {background-color:rgb(0,255,0);border-radius:8px;} "
                                                   "QMainWindow{background-color:#FD7279;} "
                                                   "QLabel{font-size:60px; }"));

                                    label->adjustSize();
                                    label->move(width()/2-(label->width()/2),0);
                                    label->show();
                                }
                        });
                connect(btn,&QPushButton::clicked,this,
                        [=]{
                            bool ok;
                            btn->deleteLater();
                            score->setText(QString::number(score->text().toInt(&ok,10)+1));
                            score->adjustSize();
                        });

                setStyleSheet(("QPushButton {background-color:rgb(0,255,0); border-radius:8px;} "
                               "QMainWindow{background-color:#009999;}"
                               "QLabel{font-size:60px; }"));
            });

    actionTimer->setInterval(500);
    actionTimer->start();

    moveTimer->setInterval(1000/60);
    moveTimer->start();
}

int GetRandPositionX(int width)
{
   return rand() % (width-30 + 1);
}

int GetRandPositionY(int height)
{
   return rand() % ((height/3 + 1));
}

MainWindow::~MainWindow()
{


}
