#include "button.h"
#include "catalogwindow.h"
#include "mainwindow.h"
#include "startmenu.h"

Button::Button(QSoundEffect *s, QTimer *t)
{
    sound = s;
    timer = t;
}

QRectF Button::boundingRect() const
{
    return QRectF(-80, -20, 160, 40);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(QRect(-80, -20, 160, 40), QPixmap(":/images/Button.png"));
    painter->setPen(Qt::green);
    QFont font("Calibri", 18, QFont::Bold, true);
    painter->setFont(font);
    if (timer->isActive())
        painter->drawText(boundingRect(), Qt::AlignCenter, "MENU");
    else
        painter->drawText(boundingRect(), Qt::AlignCenter, "CONTINUE");
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (timer->isActive()) // 当前是 "MENU" 状态
        {
            sound->stop();
            timer->stop();

            // 创建无边框窗口
            QWidget *imageWindow = new QWidget();
            imageWindow->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
            imageWindow->setAttribute(Qt::WA_TranslucentBackground);

            // 创建 QLabel 显示背景图
            QLabel *label = new QLabel(imageWindow);
            QPixmap pixmap(":/images/dialog.png");
            QPixmap scaledPixmap = pixmap.scaled(pixmap.width() * 0.5, pixmap.height() * 0.5, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            label->setPixmap(scaledPixmap);
            label->setFixedSize(scaledPixmap.size());
            label->move(0, 0);

            // 设置窗口大小为背景图加底部空间
            int windowWidth = scaledPixmap.width();
            int windowHeight = scaledPixmap.height() + 60;
            imageWindow->setFixedSize(windowWidth, windowHeight);

            // 图鉴按钮
            QPushButton *encyclopediaButton = new QPushButton("图鉴", imageWindow);
            encyclopediaButton->setFixedSize(115, 40);
            encyclopediaButton->move((windowWidth - 115) / 2, 140);  // 图像内部
            encyclopediaButton->setStyleSheet("QPushButton { "
                                              "background-image: url(:/images/Button.png); "
                                              "background-size: 200% 200%; "
                                              "color: #00FF00; font: bold 18px 'Calibri'; border: none; }");

            // 回到主菜单按钮
            QPushButton *menuButton = new QPushButton("回到主菜单", imageWindow);
            menuButton->setFixedSize(115, 40);
            menuButton->move((windowWidth - 115) / 2, 220);  // 图像内部偏下
            menuButton->setStyleSheet("QPushButton { "
                                      "background-image: url(:/images/Button.png); "
                                      "background-size: 200% 200%; "
                                      "color: #00FF00; font: bold 18px 'Calibri'; border: none; }");

            // 关闭按钮
            QPushButton *closeButton = new QPushButton("关闭", imageWindow);
            closeButton->setFixedSize(115, 40);
            closeButton->move((windowWidth - 115) / 2, scaledPixmap.height() + 10);  // 图像下方
            closeButton->setStyleSheet("QPushButton { "
                                       "background-image: url(:/images/Button.png); "
                                       "background-size: 200% 200%; "
                                       "color: #00FF00; font: bold 18px 'Calibri'; border: none; }");

            // 按钮信号槽
            QObject::connect(closeButton, &QPushButton::clicked, imageWindow, [=]() {
                imageWindow->close();
                sound->play();
                timer->start();
            });

            QObject::connect(encyclopediaButton, &QPushButton::clicked, imageWindow, [=]() {
                imageWindow->close();
                QWidget *parentWidget = this->scene()->views().first();
                CatalogWindow *catalogWindow = new CatalogWindow(parentWidget);
                catalogWindow->exec();
            });

            QObject::connect(menuButton, &QPushButton::clicked, imageWindow, [=]() {
                // 关闭当前弹窗
                imageWindow->close();

                // 关闭主游戏窗口
                QWidget *parentWidget = this->scene()->views().first();
                MainWindow *mainWindow = qobject_cast<MainWindow*>(parentWidget->parentWidget());
                if (mainWindow) {
                    mainWindow->hide();
                }

                // 创建新的开始菜单并显示
                StartMenu *startMenu = new StartMenu();
                startMenu->show();
            });


            // 显示窗口
            imageWindow->show();
        }
        else // 当前是 "CONTINUE" 状态
        {
            sound->play();
            timer->start();
        }
    }
    update();
}
