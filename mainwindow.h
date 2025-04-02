#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
//#include <QSound>
#include <QtMultimedia/QSoundEffect>
#include <QTimer>
#include "shop.h"
#include "card.h"
#include "shovel.h"
#include "button.h"
#include "map.h"
#include "mower.h"
#include "basiczombie.h"
#include "conezombie.h"
#include "bucketzombie.h"
#include "screenzombie.h"
#include "footballzombie.h"
#include "flagzombie.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void addZombie();
    void spawnBigWave();
    void check();
private:
    QSoundEffect *sound;
    QTimer *timer;
    QGraphicsScene *scene;
    QGraphicsView *view;
    int waveCount;
};

#endif // MAINWINDOW_H
