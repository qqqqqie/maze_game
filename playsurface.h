#ifndef PLAYSURFACE_H
#define PLAYSURFACE_H

#include "QKeyEvent"
#include <QMainWindow>
#include <primmaze.h>
#include "QPainter"
#include "QMenuBar"
#include "QLabel"
#include "mypushbotton.h"
#include "QTimer"
#include "QTime"
#include "QMediaPlayer"
class PlaySurface : public QMainWindow
{
    Q_OBJECT
public:
    PlaySurface(int mazelength);
    int **QTmaze, mazelength;
    void paintEvent(QPaintEvent *);
    void choose();
    void openpath();
    QLabel *timelabel;
    QLabel *steplabel;
    point* bfspathnode;
    PlaySurface *chooseContinue;
    int widthlength, heigthlength;
    int peopleX = 1, peopleY = 1, endx, endy;
    int stepconut = 0;
    int temp;
    QTimer *timer;
    QTime baseTime;
    void swap(int &x, int &y);
    bool canGo(int x, int y);
    bool start = false;
    void move();
    void keyPressEvent(QKeyEvent * QKevent);
    void timecount();
    QString mytitle;
    QMediaPlayer *victory;
    QMediaPlayer *stepmusic;
signals:
    void backchoose();
    void bgmstop();
public slots:
};

#endif // PLAYSURFACE_H
