#include "mypushbotton.h"

MyPushBotton::MyPushBotton(QString imgpath)
{
    this->imgpath = imgpath;
    QPixmap pix;
    bool ret = pix.load(this->imgpath);
    if(!ret)
    {
        QString str = QString("%1 图片加载失败").arg(this->imgpath);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则样式
    this->setStyleSheet("QPushBotton{border:0px;}");

    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(), pix.height()));

    btnmusic = new QMediaPlayer(this);
    btnmusic->setMedia(QUrl("qrc://res/music/button.wav"));
}



void MyPushBotton::Zoom1()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    btnmusic->play();
    //设定时间间隔
    animation->setDuration(200);
    //设置动态的起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置动画结束位置
    animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyPushBotton::Zoom2()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    btnmusic->play();
    //设定时间间隔
    animation->setDuration(200);
    //设置动态的起始位置
    animation->setStartValue(QRect(this->x(),this->y() + 10, this->width(), this->height()));
    //设置动画结束位置
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}
