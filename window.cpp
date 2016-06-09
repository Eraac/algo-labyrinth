#include "window.hpp"
#include "ui_window.h"

Window::Window(QWidget *parent) : QWidget(parent), ui(new Ui::Window), labyrinth()
{
    ui->setupUi(this);
    this->scene = new QGraphicsScene(this);
    this->ui->view->setScene(this->scene);
}

Window::~Window()
{
    delete ui;
}

void Window::draw()
{
    scene->clear();

    auto labyrinthItem = new QGraphicsLabyrinthItem(this->labyrinth.get());

    scene->addItem(labyrinthItem);
}

void Window::generateLabyrinth()
{
    std::size_t y = static_cast<std::size_t> (this->ui->Y->value());
    std::size_t x = static_cast<std::size_t> (this->ui->X->value());

    GeneratorLabyrinth generator{};
    this->labyrinth = generator.generate(y, x);

    this->enableButton();

    this->draw();
}

void Window::saveToJson()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save your file", QDir::homePath());

    if (filename.isEmpty()) {
        return;
    }

    PersistLabyrinth persist;
    bool ok = persist.save(this->labyrinth, filename);

    if (!ok) {
        QMessageBox::warning(this, "Error", "File not save");
    }
}

void Window::resolveLabyrinth()
{
    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;
    auto adjacency_list = this->labyrinth->getAdjacencyList();

    DijkstraComputePaths(0, adjacency_list, min_distance, previous);

    std::list<vertex_t> path = DijkstraGetShortestPathTo(this->labyrinth->getNbCells() - 1, previous);

    std::for_each(path.cbegin(), path.cend(),
        [&] (vertex_t const vertex) {
            this->labyrinth->setVisited(vertex);
        }
    );

    this->scene->update();
}

void Window::importJson()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load your file", QDir::homePath());

    if (filename.isEmpty()) {
        return;
    }

    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Error", "Could not open the file");
        return;
    }

    QByteArray byte = file.readAll();

    QJsonDocument json(QJsonDocument::fromJson(byte));

    if (json.isNull())
    {
        QMessageBox::warning(this, "Error", "Json format is invalid");
        return;
    }

    bool isValid = false;

    PersistLabyrinth load;
    auto tmpLabyrinth = load.fromJson(json.object(), isValid);

    if (!isValid)
    {
        QMessageBox::warning(this, "Error", "Json invalid");
        return;
    }

    this->labyrinth = std::move(tmpLabyrinth);
    this->draw();
    this->enableButton();
}

void Window::enableButton()
{
    this->ui->downloadJSON->setEnabled(true);
    this->ui->resolve->setEnabled(true);
}
