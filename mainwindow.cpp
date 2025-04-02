#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), waveCount(0)
{
    QRandomGenerator myGenerator(QTime::currentTime().msec());
    sound = new QSoundEffect();
    sound->setSource(QUrl::fromLocalFile("Grazy Dave.mp3"));
    sound->setLoopCount(QSoundEffect::Infinite);
    timer = new QTimer;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(150, 0, 900, 600);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    Shop *shop = new Shop;
    shop->setPos(520, 45);
    scene->addItem(shop);
    Shovel *shovel = new Shovel;
    shovel->setPos(830, 40);
    scene->addItem(shovel);
    Button *button = new Button(sound, timer);
    button->setPos(970, 20);
    scene->addItem(button);
    Map *map = new Map;
    map->setPos(618, 326);
    scene->addItem(map);
    for (int i = 0; i < 5; ++i)
    {
        Mower *mower = new Mower;
        mower->setPos(210, 130 + 98 * i);
        scene->addItem(mower);
    }
    view = new QGraphicsView(scene, this);
    view->resize(902, 602);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/images/Background.jpg"));
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    connect(timer, &QTimer::timeout, this, &MainWindow::addZombie);
    connect(timer, &QTimer::timeout, this, &MainWindow::check);
    sound->play();
    timer->start(33);
    view->show();
}

MainWindow::~MainWindow()
{
    delete sound;
    delete timer;
    delete scene;
    delete view;
}

void MainWindow::addZombie()
{
    static double elapsedTime = 0; // 记录经过的时间 (单位: 33ms)
    static double spawnInterval = 20 * 1000 / 33; // 初始生成间隔 (20秒)
    static int counter = 0; // 计数器
    static bool bigWaveTriggered = false; // 是否触发过大波僵尸

    elapsedTime += 33; // 每次调用 +33ms
    counter++;

    // 控制僵尸生成频率逐渐加快
    if (counter >= spawnInterval)
    {
        counter = 0;

        // 随着时间推移，减少生成间隔
        if(!bigWaveTriggered){
            if (elapsedTime > 30000) spawnInterval = 15 * 1000 / 33; // 30秒后变快
            if (elapsedTime > 60000) spawnInterval = 10 * 1000 / 33; // 60秒后更快
            if (elapsedTime > 120000) spawnInterval = 7 * 1000 / 33; // 120秒后更快
            if (elapsedTime > 180000) spawnInterval = 5 * 1000 / 33; // 180秒后更快
        }

        int i = QRandomGenerator::global()->generate() % 5; // 随机行
        Zombie *zombie = nullptr; // 使用基类指针

        // 180秒后，触发大波僵尸
         if (elapsedTime > 180000 * (waveCount + 1))
        {
            waveCount++;  // 增加大波次数
            bigWaveTriggered = true;
            QGraphicsPixmapItem *waveItem = scene->addPixmap(QPixmap(":/images/HugeWave.png"));
            waveItem->setScale(0.25);  // 缩小 50% (等比例)
            waveItem->setPos(336, 92);
            QTimer::singleShot(3000, this, [=]() {
                scene->removeItem(waveItem);
                delete waveItem;  // 释放内存
            });
            QTimer::singleShot(3000, this, &MainWindow::spawnBigWave); // 3秒后大波僵尸来袭
            spawnInterval = spawnInterval * 0.8;  // 每次大波僵尸后，减少生成间隔 20%
            return;
        }

        // 选择僵尸类型（基于时间解锁不同类型）
        int type = QRandomGenerator::global()->generate() % 100;
        if (elapsedTime < 30000) // 30秒内只生成普通僵尸
            zombie = new BasicZombie;
        else if (elapsedTime < 60000) // 30秒解锁路障僵尸
            zombie = (type < 60) ? static_cast<Zombie*>(new BasicZombie) : static_cast<Zombie*>(new ConeZombie);
        else if (elapsedTime < 90000) // 60秒解锁铁桶僵尸
            zombie = (type < 40) ? static_cast<Zombie*>(new BasicZombie) :
                         (type < 70) ? static_cast<Zombie*>(new ConeZombie) :
                         static_cast<Zombie*>(new BucketZombie);
        else if (elapsedTime < 120000) // 90秒解锁窗子僵尸
            zombie = (type < 30) ? static_cast<Zombie*>(new BasicZombie) :
                         (type < 60) ? static_cast<Zombie*>(new ConeZombie) :
                         (type < 80) ? static_cast<Zombie*>(new BucketZombie) :
                         static_cast<Zombie*>(new ScreenZombie);
        else // 120秒后解锁橄榄球僵尸
            zombie = (type < 20) ? static_cast<Zombie*>(new BasicZombie) :
                         (type < 40) ? static_cast<Zombie*>(new ConeZombie) :
                         (type < 60) ? static_cast<Zombie*>(new BucketZombie) :
                         (type < 80) ? static_cast<Zombie*>(new ScreenZombie) :
                         static_cast<Zombie*>(new FootballZombie);

        zombie->setPos(1028, 130 + 98 * i);
        scene->addItem(zombie);
    }
}

void MainWindow::check()
{
    static int time = 1 * 1000 / 33;
    static int counter = 0;
    if (++counter >= time)
    {
        counter = 0;
        const QList<QGraphicsItem *> items = scene->items();
        foreach (QGraphicsItem *item, items)
            if (item->type() == Zombie::Type && item->x() < 200)
            {
                scene->addPixmap(QPixmap(":/images/ZombiesWon.png"))->setPos(336, 92);
                scene->advance();
                timer->stop();
                return;
            }
    }
}

void MainWindow::spawnBigWave()
{
    Zombie *flagZombie = new FlagZombie;
    flagZombie->setPos(1028, 130 + 98 * 2);
    scene->addItem(flagZombie);

    int zombieCount = 10 + (waveCount * 10);

    // 额外生成一大波普通僵尸
    for (int j = 0; j < zombieCount; ++j)
    {
        int i = QRandomGenerator::global()->generate() % 5;
        Zombie *zombie = nullptr;
        int type = QRandomGenerator::global()->generate() % 100;

        zombie = (type < 20) ? static_cast<Zombie*>(new BasicZombie) :
                     (type < 40) ? static_cast<Zombie*>(new ConeZombie) :
                     (type < 60) ? static_cast<Zombie*>(new BucketZombie) :
                     (type < 80) ? static_cast<Zombie*>(new ScreenZombie) :
                     static_cast<Zombie*>(new FootballZombie);

        zombie->setPos(1028 + (j * 50), 130 + 98 * i);
        scene->addItem(zombie);
    }
}
