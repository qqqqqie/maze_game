#ifndef MYPUSHBOTTON_H
#define MYPUSHBOTTON_H
#include <QDebug>
#include <QPushButton>
#include <QPropertyAnimation>
#include "QMediaPlayer"
class MyPushBotton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushBotton(QObject *parent = nullptr);
    MyPushBotton(QString imgpath);
    QString imgpath;
    //设置上下跳跃
    void Zoom1();
    void Zoom2();
    QMediaPlayer *btnmusic;
    void music();
    //鼠标按下和释放
signals:

public slots:
};

#endif // MYPUSHBOTTON_H
