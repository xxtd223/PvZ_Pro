#include "button.h"

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

            // 使用布局管理器
            QVBoxLayout *layout = new QVBoxLayout(imageWindow);

            // 创建 QLabel 作为图片显示
            QLabel *label = new QLabel();
            QPixmap pixmap(":/images/dialog.png");  // 确保路径正确

            // 设定缩放比例
            int newWidth = pixmap.width() * 0.5;
            int newHeight = pixmap.height() * 0.5;
            QPixmap scaledPixmap = pixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            label->setPixmap(scaledPixmap);
            label->setAlignment(Qt::AlignCenter);

            // 创建按钮
            QPushButton *closeButton = new QPushButton("关闭");
            closeButton->setIconSize(QSize(115, 40));
            closeButton->setFixedSize(115, 40);
            closeButton->setStyleSheet("QPushButton { background-image: url(:/images/Button.png); "
                                       "color: white; border: none; font-size: 14px; }");

            // 连接按钮信号
            QObject::connect(closeButton, &QPushButton::clicked, imageWindow, &QWidget::close);

            // 将控件添加到布局
            layout->addWidget(label);
            layout->addWidget(closeButton, 0, Qt::AlignCenter);
            layout->setSpacing(10);
            layout->setContentsMargins(20, 20, 20, 20);

            // 设置窗口大小
            imageWindow->setFixedSize(newWidth + 40, newHeight + 80); // 留出按钮和边距的空间

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
