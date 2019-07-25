#ifndef CHOOSESURFACE_H
#define CHOOSESURFACE_H
#include "QTimer"
#include <QMainWindow>
#include "mypushbotton.h"
#include "QLabel"
#include "playsurface.h"
class ChooseSurface : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseSurface(QWidget *parent = nullptr);
    PlaySurface *chooseplay;
signals:
    void chooseback();
    void bgmstop();
    void bgmstart();
public slots:
};

#endif // CHOOSESURFACE_H
