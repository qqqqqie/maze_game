#include "playsurface.h"
#include "QDebug"
PlaySurface::PlaySurface(int mazelength)
{
    if(mazelength == 12)
    {
        mytitle = "普通难度";
    }

    else if ( mazelength == 22) {
        mytitle = "中等难度";
    }

    else if ( mazelength == 32) {
        mytitle = "困难难度";
    }
    QString m = tr("游戏中...难度:%1").arg(this->mytitle);
    QString stepstr = tr("已走步数: 0");
    this->setWindowTitle(m);
    steplabel = new QLabel(this);
    timelabel = new QLabel(this);
    steplabel->resize(300,200);
    steplabel->move(1300, 200);
    timelabel->resize(300, 170);
    timelabel->move(1300, 500);
    QFont timefont("华文新魏", 23);
    steplabel->setText(stepstr);
    steplabel->setFont(timefont);
    timelabel->setFont(timefont);
    this->mazelength = mazelength;
    this->setAutoFillBackground(true);
    this->setPalette(QPalette(QColor(255, 255, 255)));
    this->setFixedSize(1600, 900);
    //设置菜单
    QMenuBar *bar = menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu *strmenu = bar->addMenu("菜单");
    //创建菜单项
    QAction *openpath = strmenu->addAction("显示路径");
    QAction *backAction = strmenu->addAction("返回选择页面");
    QAction *quitAction = strmenu->addAction("退出游戏");

    connect(openpath, &QAction::triggered, [=](){

        this->openpath();
    });
    connect(backAction, &QAction::triggered, [=](){
        this->hide();
        emit this->backchoose();
    });

    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    PrimMaze maze(mazelength);
    maze.createwall();
    maze.createmaze();
    maze.setStart(1, 1);
    maze.calculationEnd();
    maze.BFScalculation();
    this->mazelength = maze.returnmazelength();
    this->QTmaze = maze.returnmaze();
    this->widthlength = (this->width() - (this->mazelength * 30)) / 2;
    this->heigthlength = (this->height() - (this->mazelength * 30)) / 2;
    this->bfspathnode = maze.returnpathnode();
    this->endx = maze.returnendX();
    this->endy = maze.returnendY();
    timer = new QTimer(this);
    connect(this->timer,&QTimer::timeout,this,[=]()
    {
        this->timecount();
    });

    stepmusic = new QMediaPlayer(this);
    stepmusic->setMedia(QUrl("qrc://res/music/run2.wav"));
    stepmusic->setPlaybackRate(3);
}

void PlaySurface::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap black, white, people, end, path;
    black.load(":/img/black.png");
    white.load(":/img/white.png");
    people.load(":/img/people.png");
    end.load(":/img/end.png");
    path.load(":/img/path.jpg");
    for(int i = 0; i < this->mazelength; i++)
    {
        for (int j = 0; j < this->mazelength; j++)
        {
            if (QTmaze[i][j] == 1)
            {
                painter.drawPixmap(this->widthlength + (j * 30), this->heigthlength + (i * 30), black);
            }

            else if (QTmaze[i][j] == 0)
            {
                painter.drawPixmap(this->widthlength + (j * 30), this->heigthlength + (i * 30), white);
            }

            else if (QTmaze[i][j] == 2)
            {
                painter.drawPixmap(this->widthlength + (j * 30), this->heigthlength + (i * 30), people);
            }

            else if (QTmaze[i][j] == 3)
            {
                painter.drawPixmap(this->widthlength + (j * 30), this->heigthlength + (i * 30), end);
            }

            else if (QTmaze[i][j] == 4)
            {
                painter.drawPixmap(this->widthlength + (j * 30), this->heigthlength + (i * 30), path);
            }
        }
    }
}

void PlaySurface::openpath()
{
    while(this->bfspathnode->parent != NULL)
    {
        this->QTmaze[bfspathnode->x][bfspathnode->y] = 4;
        bfspathnode = bfspathnode->parent;
    }
    this->QTmaze[this->peopleX][this->peopleY] = 2;
    QMainWindow::update();
}

void PlaySurface::swap(int &x, int &y)
{
    this->temp = x;
    x = y;
    y = temp;
}

bool PlaySurface::canGo(int x, int y)
{
    if (x < 0 && x > this->mazelength)
    {
        return 0;
    }
    else if (y < 0 && y > this->mazelength)
    {
        return 0;
    }
    else if (this->QTmaze[x][y] == 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


void PlaySurface::keyPressEvent(QKeyEvent *QKevent)
{
    if(!start)
    {
        timer->start(10);
        start = true;
        baseTime.start();
    }
    if((QKevent->key() == Qt::Key_Left) || QKevent->key() == Qt::Key_A)
    {
        if(canGo(peopleX, peopleY - 1))
        {
            stepmusic->play();
            swap(this->QTmaze[peopleX][peopleY], this->QTmaze[peopleX][peopleY - 1]);
            peopleY -=1;
            stepconut++;
            QMainWindow::update();
        }
    }


    if((QKevent->key() == Qt::Key_Right) || QKevent->key() == Qt::Key_D)
    {
        if(canGo(peopleX, peopleY + 1))
        {
            stepmusic->play();
            swap(this->QTmaze[peopleX][peopleY], this->QTmaze[peopleX][peopleY + 1]);
            peopleY +=1;
            stepconut++;
            QMainWindow::update();
            if(peopleX == endx && peopleY == endy)
            {
                choose();
            }
        }
    }

    if((QKevent->key() == Qt::Key_Up) || QKevent->key() == Qt::Key_W)
    {
        if(canGo(peopleX - 1, peopleY))
        {
            stepmusic->play();
            swap(this->QTmaze[peopleX][peopleY], this->QTmaze[peopleX - 1][peopleY]);
            peopleX -=1;
            stepconut++;
            QMainWindow::update();
        }
    }

    if((QKevent->key() == Qt::Key_Down) || QKevent->key() == Qt::Key_S)
    {
        if(canGo(peopleX + 1, peopleY))
        {
            stepmusic->play();
            swap(this->QTmaze[peopleX][peopleY], this->QTmaze[peopleX + 1][peopleY]);
            peopleX +=1;
            stepconut++;
            QMainWindow::update();
        }
    }
    QString stepstr = tr("已走步数: %1").arg(stepconut);
    steplabel->setText(stepstr);
}

void PlaySurface::choose()
{
    victory = new QMediaPlayer(this);
    victory->setMedia(QUrl("qrc://res/music/victory.mp3"));
    victory->setVolume(50);
    victory->play();
    QString endstr = tr("总计步数: %1 步  总花费时间: %2 s").arg(stepconut).arg(baseTime.elapsed() / 1000);
    MyPushBotton *chooseback, *choosequit;
    chooseback = new MyPushBotton(":/img/startbtn.png");
    choosequit = new MyPushBotton(":/img/startbtn.png");
    chooseback->setParent(this);
    choosequit->setParent(this);
    QLabel *labelback, *labelquit, *label, *label2, *labelend;
    labelback = new QLabel(this);
    labelquit = new QLabel(this);
    label = new QLabel(this);
    label2 = new QLabel(this);
    labelend = new QLabel(this);
    label2->resize(1600,900);
    label2->show();
    label2->setStyleSheet("background-color:white");
    labelend->resize(800, 200);
    QFont font("华文新魏", 50);
    QFont font2("华文新魏", 150);
    labelback->resize(410,200);
    labelquit->resize(410,200);
    label->resize(800,350);
    labelback->setText("返回选择");
    labelquit->setText("退出游戏");
    label->setText("你赢了");
    labelend->setText(endstr);
    chooseback->move(266, 500);
    choosequit->move(932, 500);
    labelback->move(294, 500);
    labelquit->move(950, 500);
    labelend->move(410, 330);
    labelback->setFont(font);
    labelquit->setFont(font);
    labelend->setFont(QFont("华文新魏", 30));
    label->setFont(font2);
    label->move(420, 80);
    labelback->setAttribute(Qt::WA_TransparentForMouseEvents);
    labelquit->setAttribute(Qt::WA_TransparentForMouseEvents);
    labelend->setAttribute(Qt::WA_TransparentForMouseEvents);
    choosequit->show();
    chooseback->show();
    choosequit->raise();
    chooseback->raise();
    labelend->raise();
    labelend->show();
    label->show();
    labelback->show();
    labelquit->show();
    label->raise();
    labelback->raise();
    labelquit->raise();
    emit this->bgmstop();
    connect(chooseback, &QPushButton::clicked, [=]()
    {
        chooseback->Zoom1();
        chooseback->Zoom2();
        QTimer::singleShot(300, this, [=]()
        {
            victory->stop();
            this->hide();
            emit this->backchoose();
        });

    });

    connect(choosequit, &QPushButton::clicked, [=](){
        choosequit->Zoom1();
        choosequit->Zoom2();
        QTimer::singleShot(300, this, [=]()
        {
            victory->stop();
            chooseback->btnmusic->stop();
            this->close();
        });
    });
}

void PlaySurface::timecount()
{
    QString str = tr("已花费时间: %1 s").arg(baseTime.elapsed() / 1000);
    timelabel->setText(str);
}
