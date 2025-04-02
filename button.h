#ifndef BUTTON_H
#define BUTTON_H

#include <QTimer>
//#include <QSoundEffect>
#include <QtMultimedia/QSoundEffect>
#include "other.h"

class Button : public Other
{
public:
    Button(QSoundEffect *s, QTimer *t);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QSoundEffect *sound;
    QTimer *timer;
};

#endif // BUTTON_H
