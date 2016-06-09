#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QWidget>
#include <QDebug>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMessageBox>
#include <iostream>>
#include "qgraphicslabyrinthitem.hpp"
#include "generatorlabyrinth.hpp"
#include "persistlabyrinth.hpp"
#include "labyrinth.hpp"

namespace Ui {
    class Window;
}

class Window : public QWidget
{
    Q_OBJECT

    public:
        explicit Window(QWidget *parent = 0);
        ~Window();

        void draw();

    public slots:
        void generateLabyrinth();
        void resolveLabyrinth();
        void saveToJson();
        void importJson();

    private:
        std::unique_ptr<Labyrinth> labyrinth;
        Ui::Window *ui;

        QGraphicsScene *scene;

        void enableButton();
};

#endif // WINDOW_HPP
