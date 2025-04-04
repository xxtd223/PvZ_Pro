#include "startmenu.h"
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>

StartMenu::StartMenu(QWidget *parent) : QWidget(parent)
{
    // 设置窗口大小和标题
    setFixedSize(900, 600);
    setWindowTitle("植物大战僵尸 - 开始菜单");

    // 创建背景
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 900, 600);

    QGraphicsPixmapItem *bg = new QGraphicsPixmapItem(QPixmap(":/images/StartBackground.jpg"));
    bg->setPos(0, 0);
    scene->addItem(bg);

    // 添加标题
    QGraphicsPixmapItem *title = new QGraphicsPixmapItem(QPixmap(":/images/Title.png"));
    title->setPos(150, 50);
    title->setScale(0.8);
    scene->addItem(title);

    // 创建开始按钮
    QPushButton *startButton = new QPushButton("开始游戏");
    startButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #FFA500;"
        "   border: 2px solid #8B4513;"
        "   border-radius: 10px;"
        "   color: white;"
        "   font-size: 24px;"
        "   padding: 10px 20px;"
        "   min-width: 200px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #FF8C00;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #FF6347;"
        "}"
        );

    // 创建退出按钮
    QPushButton *exitButton = new QPushButton("退出游戏");
    exitButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #FF4500;"
        "   border: 2px solid #8B4513;"
        "   border-radius: 10px;"
        "   color: white;"
        "   font-size: 24px;"
        "   padding: 10px 20px;"
        "   min-width: 200px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #FF6347;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #FF0000;"
        "}"
        );

    // 垂直布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(startButton, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(exitButton, 0, Qt::AlignCenter);
    layout->addStretch();

    // 按钮信号连接
    connect(startButton, &QPushButton::clicked, this, [this]() {
        emit startGame();
        close();
    });

    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);

    // 背景音乐
    bgm = new QSoundEffect(this);
    bgm->setSource(QUrl::fromLocalFile("StartMenu.mp3"));
    bgm->setLoopCount(QSoundEffect::Infinite);
    bgm->play();

    // 显示视图
    QGraphicsView *view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("background: transparent; border: none;");
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setGeometry(0, 0, 900, 600);

    setLayout(layout);
}
