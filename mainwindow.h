#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "choosesurface.h"
#include <QMainWindow>
#include<mypushbotton.h>
#include<QLabel>
#include"choosesurface.h"
#include "QTimer"
#include "playsurface.h"
#include "QMediaPlayer"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ChooseSurface *choose;
    QMediaPlayer *BGM;
    int musics;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
