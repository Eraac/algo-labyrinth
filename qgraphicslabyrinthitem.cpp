#include "qgraphicslabyrinthitem.hpp"

QGraphicsLabyrinthItem::QGraphicsLabyrinthItem(const Labyrinth *labyrinth) : QGraphicsItem(), labyrinth(labyrinth)
{
    qreal x = 0;
    qreal y = 0;
    std::size_t size = this->labyrinth->getNbCells();

    // for each cell
    for (std::size_t i = 0; i < size; i++)
    {
        auto cell = new QGraphicsCellItem(x, y);
        cell->setParentItem(this);
        cell->setOpen(
            this->labyrinth->canMove(i, Labyrinth::BOTTOM),
            this->labyrinth->canMove(i, Labyrinth::RIGHT)
        );
        cell->setState(this->labyrinth->getState(i));

        this->cellsItem.push_back(cell);

        x += SIZE_CELL;

        // line if complete, pass to the next
        if (x == SIZE_CELL * this->labyrinth->getWidth()) {
            x = 0;
            y += SIZE_CELL;
        }
    }
}

void QGraphicsLabyrinthItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    auto rect = this->boundingRect();
    painter->drawRect(rect);
    std::size_t position = 0;

    // draw each cell
    std::for_each(this->cellsItem.begin(), this->cellsItem.end(),
    [&] (QGraphicsCellItem *cell) {
        cell->setState(this->labyrinth->getState(position));
        cell->paint(painter, option, widget);

        position++;
    });
}

QRectF QGraphicsLabyrinthItem::boundingRect() const
{
    qreal w = this->labyrinth->getWidth() * SIZE_CELL;
    qreal h = this->labyrinth->getHeight() * SIZE_CELL;

    return QRectF(0, 0, w, h);
}
