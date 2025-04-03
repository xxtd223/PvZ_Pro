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

            // 创建 QLabel 作为图片显示
            QLabel *label = new QLabel(imageWindow);
            QPixmap pixmap(":/images/dialog.png");  // 确保路径正确

            // 设定缩放比例 (比如 0.7 倍大小)
            int newWidth = pixmap.width() * 0.5;
            int newHeight = pixmap.height() * 0.5;
            QPixmap scaledPixmap = pixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

            label->setPixmap(scaledPixmap);
            label->setScaledContents(true);

            // 设置窗口大小匹配缩小后的图片
            imageWindow->resize(scaledPixmap.size());

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
