#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QUrl"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BGM = new QMediaPlayer(this);
    musics = 12;
    BGM->setMedia(QUrl("qrc://res/music/bgm.mp3"));
    BGM->setVolume(musics);
    BGM->play();
    QLabel *label = new QLabel;
    QPixmap pix;
    pix.load(":/img/migongyouxi");
    label->setParent(this);
    label->resize(pix.width(),pix.height());
    label->setPixmap(pix);
    this->setFixedSize(1600, 900);
    MyPushBotton *btnstart, *btnquit;
    btnstart = new MyPushBotton(":/img/startbtn.png");
    btnquit = new MyPushBotton(":/img/startbtn.png");
    btnstart->setParent(this);
    btnquit->setParent(this);
    btnstart->move(this->width() - (1.5 * btnstart->width()), this->height() - (3 * btnstart->height()));
    btnquit->move(this->width() - (1.5 * btnquit->width()), this->height() - (1.5 * btnquit->height()));
    QLabel *btnlabel1 = new QLabel(this);
    QLabel *btnlabel2 = new QLabel(this);
    btnlabel1->resize(400, 200);
    btnlabel2->resize(400, 200);
    QFont font("华文新魏", 50);
    btnlabel1->setText("开始游戏");
    btnlabel2->setText("退出游戏");
    btnlabel1->setFont(font);
    btnlabel2->setFont(font);
    btnlabel1->move(this->width() - (1.4 * btnlabel1->width()), this->height() - (3 * btnlabel1->height()));
    btnlabel2->move(this->width() - (1.4 * btnlabel1->width()), this->height() - (1.5 * btnlabel1->height()));
    btnlabel1->setAttribute(Qt::WA_TransparentForMouseEvents);
    btnlabel2->setAttribute(Qt::WA_TransparentForMouseEvents);
    choose = new ChooseSurface;

    connect(btnstart, &QPushButton::clicked,[=]()
    {
        btnstart->Zoom1();
        btnstart->Zoom2();
        QTimer::singleShot(300, this, [=]()
        {
            //自身隐藏调用
            this->hide();

            choose->show();

        });
    });

    connect(choose, &ChooseSurface::chooseback, [=]()
    {
        choose->hide();
        this->show();

    });

    connect(btnquit, &QPushButton::clicked,[=]()
    {
        btnquit->Zoom1();
        btnquit->Zoom2();
        QTimer::singleShot(300, this, [=]()
        {
            this->close();
        });
    });

    connect(choose, &ChooseSurface::bgmstop, [=](){
        BGM->stop();
    });

    connect(choose, &ChooseSurface::bgmstart, [=](){
        BGM->setMedia(QUrl("qrc://res/music/bgm.mp3"));
        BGM->setVolume(musics);
        BGM->play();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
