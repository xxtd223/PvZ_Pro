#include "map.h"

Map::Map()
{
    dragOver = false;
    setAcceptDrops(true);
}

QRectF Map::boundingRect() const
{
    return QRectF(-369, -235, 738, 470);
}

void Map::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void Map::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText() && event->mimeData()->text() == "Shovel")
    {
        event->setAccepted(true);
        dragOver = true;
        update();
    }
    else
        event->setAccepted(false);
}

void Map::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    dragOver = false;
    update();
}

void Map::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    dragOver = false;
    if (event->mimeData()->hasText() && event->mimeData()->text() == "Shovel")
    {
        QPointF pos = mapToScene(event->pos());
        pos.setX((int(pos.x()) - 249) / 82 * 82 + 290);
        pos.setY((int(pos.y()) - 81) / 98 * 98 + 130);
        Shovel *shovel = qgraphicsitem_cast<Shovel *>(scene()->items(QPointF(830, 15))[0]);
        shovel->removePlant(pos);
    }
    update();
}

void Map::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = mapToScene(event->pos());
    pos.setX((int(pos.x()) - 249) / 82 * 82 + 290);
    pos.setY((int(pos.y()) - 81) / 98 * 98 + 130);

    Shop *shop = qgraphicsitem_cast<Shop *>(scene()->items(QPointF(300, 15))[0]);
    if (shop->selectedCard != "")
    {
        shop->addPlant(shop->selectedCard, pos);
        shop->selectedCard = "";
        shop->update();
    }
}
