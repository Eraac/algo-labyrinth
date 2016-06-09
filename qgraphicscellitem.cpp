#include "qgraphicscellitem.hpp"

QGraphicsCellItem::QGraphicsCellItem(const qreal x, const qreal y) :
    QGraphicsItem(), bottom(false), right(false), state(Cell::State::NONE)
{
    // point for wall bottom
    QPointF pb1(x, SIZE_CELL + y);
    QPointF pb2(x + SIZE_CELL, y + SIZE_CELL);

    lineBottom = QLineF(pb1, pb2);

    // point for wall right
    QPointF pr1(SIZE_CELL + x, y);
    QPointF pr2(SIZE_CELL + x, SIZE_CELL + y);

    lineRight = QLineF(pr1, pr2);

    rect = QRectF(x, y, SIZE_CELL, SIZE_CELL);
}

void QGraphicsCellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // background color
    QColor color = this->getColor(this->state);

    // remove border for QRectF
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(color));
    painter->drawRect(rect);

    // re-set pen for draw wall
    QPen pen(Qt::black);
    painter->setPen(pen);

    if (!this->bottom) {
        painter->drawLine(this->lineBottom);
    }

    if (!this->right) {
        painter->drawLine(this->lineRight);
    }
}

QRectF QGraphicsCellItem::boundingRect() const
{
    // outer most edges
    return QRectF(0, 0, SIZE_CELL, SIZE_CELL);
}

void QGraphicsCellItem::setOpen(const bool &bottom, const bool &right)
{
    this->bottom = bottom;
    this->right = right;
}

void QGraphicsCellItem::setState(const Cell::State state)
{
    this->state = state;
}

QColor QGraphicsCellItem::getColor(const Cell::State state) const
{
    switch(state)
    {
        case Cell::State::NONE:
            return Qt::white;

        case Cell::State::CURRENT:
            return Qt::yellow;

        case Cell::State::VISITED:
            return Qt::gray;

        case Cell::State::START:
            return Qt::blue;

        case Cell::State::FINISH:
            return Qt::green;

        default:
            return Qt::red;
    }
}
