#include "card.h"
#include "shop.h"

const QMap<QString, int> Card::map = {{"SunFlower", 0}, {"Peashooter", 1}, {"CherryBomb", 2}, {"WallNut", 3},
                                      {"SnowPea", 4}, {"PotatoMine", 5}, {"Repeater", 6}};
const QVector<QString> Card::name = {"SunFlower", "Peashooter", "CherryBomb", "WallNut",
                                     "SnowPea", "PotatoMine", "Repeater"};
const QVector<int> Card::cost = {50, 100, 150, 50, 175, 25, 200}; // 阳光花费
const QVector<int> Card::cool = {151, 227, 606, 454, 227, 303, 227}; // 冷却时间（*33/1000秒）

Card::Card(QString s)
{
    text = s;
    counter = 0;
}

QRectF Card::boundingRect() const
{
    return QRectF(-50, -30, 100, 60);
}

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->scale(0.6, 0.58);
    painter->drawPixmap(QRect(-50, -70, 100, 140), QPixmap(":/images/Card.png"));
    painter->drawPixmap(QRect(-35, -42, 70, 70), QPixmap(":/images/" + text + ".png"));
    QFont font;
    font.setPointSizeF(15);
    painter->setFont(font);
    painter->drawText(-30, 60, QString::asprintf("%3d", cost[map[text]]));
    if (counter < cool[map[text]])
    {
        QBrush brush(QColor(0, 0, 0, 200));
        painter->setBrush(brush);
        painter->drawRect(QRectF(-48, -68, 98, 132 * (1 - qreal(counter) / cool[map[text]])));
    }

    Shop *shop = qgraphicsitem_cast<Shop *>(parentItem());
    if (shop->selectedCard == text)
    {
        QBrush brush(QColor(255, 255, 0, 100));
        painter->setBrush(brush);
        painter->drawRect(QRectF(-50, -70, 100, 140));
    }
}

void Card::advance(int phase)
{
    if (!phase)
        return;
    update();
    if (counter < cool[map[text]])
        ++counter;
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (counter < cool[map[text]])
    {
        event->setAccepted(false);
        return;
    }

    Shop *shop = qgraphicsitem_cast<Shop *>(parentItem());
    if (cost[map[text]] > shop->sun)
    {
        event->setAccepted(false);
        return;
    }

    if (shop->selectedCard == text)
    {
        shop->selectedCard = "";
    }
    else
    {
        shop->selectedCard = text;
    }
    shop->update();
    update();
}
