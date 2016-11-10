#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QObject>

enum ButtonType{
    READ_BUTTON,
    BLACK_BUTTON
};

class Button : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Button(QString name, QGraphicsItem * parent=0);

    // public methods
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
//signals:
//    void clicked();

private:
    QString name;
    QGraphicsTextItem * text;
};

#endif // BUTTON_H
