#include "choosesurface.h"
#include "mainwindow.h"
#include "QDebug"
ChooseSurface::ChooseSurface(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1600,900);
    QLabel *label = new QLabel(this);
    QPixmap pix;
    pix.load(":/img/migongyouxi2");
    label->resize(pix.width(),pix.height());
    label->setPixmap(pix);
    MyPushBotton *btn1, *btn2, *btn3, *btnback;
    QPixmap btnpix(":/img/startbtn");
    btn1 = new MyPushBotton(":/img/startbtn");
    btn2 = new MyPushBotton(":/img/startbtn");
    btn3 = new MyPushBotton(":/img/startbtn");
    btnback = new MyPushBotton(":/img/startbtn");
    btn1->setParent(this);
    btn2->setParent(this);
    btn3->setParent(this);
    btnback->setParent(this);
    btn1->move(this->width() - (1.4 * btn1->width()), this->height() - 4.5* btn1->height());
    btn2->move(this->width() - (1.4 * btn2->width()), this->height() - 3.4* btn2->height());
    btn3->move(this->width() - (1.4 * btn3->width()), this->height() - 2.3* btn3->height());
    btnback->move(this->width() - (1.4 * btnback->width()), this->height() - 1.2* btnback->height());
    QLabel *btnlabel1, *btnlabel2, *btnlabel3, *btnlabelback;
    btnlabel1 = new QLabel(this);
    btnlabel2 = new QLabel(this);
    btnlabel3 = new QLabel(this);
    btnlabelback = new QLabel(this);
    QFont font("华文新魏", 50);
    btnlabel1->resize(400,200);
    btnlabel2->resize(400,200);
    btnlabel3->resize(400,200);
    btnlabelback->resize(400,200);
    btnlabel1->setText("普通难度");
    btnlabel2->setText("中等难度");
    btnlabel3->setText("困难难度");
    btnlabelback->setText("返回上页");
    btnlabel1->setFont(font);
    btnlabel2->setFont(font);
    btnlabel3->setFont(font);
    btnlabelback->setFont(font);
    btnlabel1->move(this->width() - (1.3 * btnlabel1->width()), this->height() - 4.5* btnlabel1->height());
    btnlabel2->move(this->width() - (1.3 * btnlabel2->width()), this->height() - 3.4* btnlabel2->height());
    btnlabel3->move(this->width() - (1.3 * btnlabel3->width()), this->height() - 2.3* btnlabel3->height());
    btnlabelback->move(this->width() - (1.3 * btnlabelback->width()), this->height() - 1.2* btnlabelback->height());
    btnlabel1->setAttribute(Qt::WA_TransparentForMouseEvents);
    btnlabel2->setAttribute(Qt::WA_TransparentForMouseEvents);
    btnlabel3->setAttribute(Qt::WA_TransparentForMouseEvents);
    btnlabelback->setAttribute(Qt::WA_TransparentForMouseEvents);
    connect(btnback, &QPushButton::clicked,[=]()
    {
        btnback->Zoom1();
        btnback->Zoom2();

        QTimer::singleShot(500, this, [=](){
            emit this->chooseback();

        });
    });

    chooseplay = NULL;

    connect(btn1, &QPushButton::clicked, [=]()
    {
        btn1->Zoom1();
        btn1->Zoom2();
        chooseplay = new PlaySurface(12);
        QTimer::singleShot(300, this, [=]()
        {

            this->hide();
            chooseplay->show();

            connect(chooseplay, &PlaySurface::backchoose, [=]()
            {

                this->show();
                chooseplay->close();
                delete chooseplay;
                chooseplay = NULL;
                emit this->bgmstart();
            });

            connect(chooseplay, &PlaySurface::bgmstop,[=](){
                emit this->bgmstop();
            });
        });
    });

    connect(btn2, &QPushButton::clicked, [=]()
    {
        btn2->Zoom1();
        btn2->Zoom2();
        chooseplay = new PlaySurface(22);

        QTimer::singleShot(300, this, [=]()
        {

            this->hide();
            chooseplay->show();

            connect(chooseplay, &PlaySurface::backchoose, [=]()
            {

                this->show();
                chooseplay->close();
                delete chooseplay;
                chooseplay = NULL;
                emit this->bgmstart();
            });

            connect(chooseplay, &PlaySurface::bgmstop,[=](){
                emit this->bgmstop();
            });
        });
    });

    connect(btn3, &QPushButton::clicked, [=]()
    {
        btn3->Zoom1();
        btn3->Zoom2();
        chooseplay = new PlaySurface(32);

        QTimer::singleShot(300, this, [=]()
        {

            this->hide();
            chooseplay->show();
            connect(chooseplay, &PlaySurface::backchoose, [=]()
            {

                this->show();
                chooseplay->close();
                delete chooseplay;
                chooseplay = NULL;
                emit this->bgmstart();
            });

            connect(chooseplay, &PlaySurface::bgmstop,[=](){
                emit this->bgmstop();
            });
        });
    });
}
