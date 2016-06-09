#ifndef QGRAPHICSCELLITEM_HPP
#define QGRAPHICSCELLITEM_HPP

#include <QPainter>
#include <QGraphicsItem>
#include <QLineF>
#include <QDebug>
#include "cell.hpp"

const unsigned int SIZE_CELL = 20;

class QGraphicsCellItem : public QGraphicsItem
{
    public:
        QGraphicsCellItem(qreal const x, qreal const y);

        void setOpen(const bool& bottom, const bool& right);
        void setState(Cell::State const state);

        QRectF boundingRect() const;

        // overriding paint()
        void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

    private:
        bool bottom;
        QLineF lineBottom;
        bool right;
        QLineF lineRight;
        Cell::State state;
        QRectF rect;

        QColor getColor(Cell::State const state) const;
};

#endif // QGRAPHICSCELLITEM_HPP
