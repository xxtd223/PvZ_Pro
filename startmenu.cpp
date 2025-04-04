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

    QGraphicsPixmapItem *bg = new QGraphicsPixmapItem(QPixmap(":/images/MainMenu.png"));
    bg->setPos(0, 0);
    scene->addItem(bg);

    // 创建开始按钮（使用图片）
    QPushButton *startButton = new QPushButton;
    startButton->setIcon(QIcon(":/images/StartButton.png"));
    startButton->setIconSize(QSize(200, 80));
    startButton->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 30%);"
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(255, 255, 255, 50%);"
        "}"
        );

    // 创建退出按钮（使用图片）
    QPushButton *exitButton = new QPushButton;
    exitButton->setIcon(QIcon(":/images/ExitButton.png"));
    exitButton->setIconSize(QSize(200, 80));
    exitButton->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"
        "   border: none;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 30%);"
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(255, 255, 255, 50%);"
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
    view->lower();  // 确保视图在按钮下方

    setLayout(layout);
}
