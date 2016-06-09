#ifndef QGRAPHICSLABYRINTHITEM_HPP
#define QGRAPHICSLABYRINTHITEM_HPP

#include <QPainter>
#include <QGraphicsItem>
#include "qgraphicscellitem.hpp"
#include "labyrinth.hpp"

class QGraphicsLabyrinthItem : public QGraphicsItem
{
    public:
        QGraphicsLabyrinthItem(Labyrinth const *labyrinth);

        QRectF boundingRect() const;

        // overriding paint()
        void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

    private:
        Labyrinth const * labyrinth;
        std::vector<QGraphicsCellItem*> cellsItem;
};

#endif // QGRAPHICSLABYRINTHITEM_HPP
