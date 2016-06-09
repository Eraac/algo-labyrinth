#include "labyrinth.hpp"
#include <QDebug>

Labyrinth::Labyrinth(const unsigned int &y, const unsigned int &x) : h(y), w(x)
{
    const std::size_t nbCells = static_cast<std::size_t> (y * x);

    // init matrice cells
    for (std::size_t i = 0; i < nbCells; i++)
    {
        unsigned int id = static_cast<unsigned int> (i);
        auto cell = std::make_unique<Cell>(id, id);

        // add cell to the vector
        this->cells.push_back(std::move(cell));

        // stock all way un multimap for easily update way in specific way (avoid iterate on all vector of cell)
        this->ways.insert(std::pair<idWay, position>(id, i));
    }
}

bool Labyrinth::openDoor(const position &from, const Labyrinth::Direction &direction)
{
    bool isValid = false;
    auto cell = this->cells.at(from).get();
    auto neighborPosition = this->getNeighbor(from, direction, isValid);

    // neighboor invalid, next
    if (!isValid) {
        return false;
    }

    auto neighborCell = this->cells.at(neighborPosition).get();

    // open door
    switch (direction)
    {
        case Direction::BOTTOM:
            cell->openBottom();
            break;

        case Direction::RIGHT:
            cell->openRight();
            break;

        case Direction::TOP:
            neighborCell->openBottom();
            break;

        case Direction::LEFT:
            neighborCell->openRight();
            break;
    }

    this->updateWays(cell->way, neighborCell->way);

    return true;
}

bool Labyrinth::canMove(const position &from, const Labyrinth::Direction &direction) const
{
    bool isValid;
    position to = this->getNeighbor(from, direction, isValid);

    // if neighboor is invalid, impossible to move in this direction
    if (!isValid) {
        return false;
    }

    switch (direction)
    {
        case Direction::TOP:
            return this->cells.at(to)->bottomIsOpen();

        case Direction::LEFT:
            return this->cells.at(to)->rightIsOpen();

        case Direction::BOTTOM:
            return this->cells.at(from)->bottomIsOpen();

        case Direction::RIGHT:
            return this->cells.at(from)->rightIsOpen();
    }
}

void Labyrinth::updateWays(const idWay from, const idWay to)
{
    // if the id is the same, not update way
    if (from == to) {
        return;
    }

    // get all cells in one way
    auto way = this->ways.equal_range(to);

    // iterate on each cell
    for (auto it = way.first; it != way.second; ++it)
    {
        auto pos = (*it).second;
        // update way
        this->cells.at(pos)->way = from;

        // add cell in the new way
        ways.insert(std::pair<idWay, position> (from, pos));
    }

    // remove old way (merged with the new way)
    this->ways.erase(to);
}

/**
 * @brief Return adjacency list for Dijkstra algo
 */
adjacency_list_t Labyrinth::getAdjacencyList()
{
    adjacency_list_t adjacency_list(static_cast<int> (this->getNbCells()));

    this->generateGraph(adjacency_list, 0, -1);

    return adjacency_list;
}

/**
 * @brief Recursive method for visit all cells
 */
void Labyrinth::generateGraph(adjacency_list_t &list, const position &current, const position &previous)
{
    int nbDirection = 4;

    for (int i = 0; i < nbDirection; i++)
    {
        Direction direction = static_cast<Labyrinth::Direction> (i);

        if (this->canMove(current, direction))
        {
            bool isValid = false;

            position next = this->getNeighbor(current, direction, isValid);

            if (isValid && next != previous)
            {
                list[current].push_back(neighbor(next, 1));
                this->generateGraph(list, next, current);
            }
        }
    }
}

Cell::State Labyrinth::getState(const position &cell) const
{
    return this->cells.at(cell)->getState();
}

void Labyrinth::setStart(const position &cell)
{
    this->cells.at(cell)->setState(Cell::State::START);
}

void Labyrinth::setFinish(const position &cell)
{
    this->cells.at(cell)->setState(Cell::State::FINISH);
}

void Labyrinth::setVisited(const position &cell)
{
    this->cells.at(cell)->setState(Cell::State::VISITED);
}

idWay Labyrinth::getIdWay(position const& pos) const
{
    return this->cells.at(pos)->way;
}

void Labyrinth::setIdWay(position const& pos, const idWay way)
{
    this->cells.at(pos)->way = way;
}

position &&Labyrinth::getNeighbor(const position &from, const Labyrinth::Direction &direction, bool &valid) const
{
    switch (direction)
    {
        case Direction::TOP:
            return std::move(this->getTop(from, valid));

        case Direction::RIGHT:
            return std::move(this->getRight(from, valid));

        case Direction::BOTTOM:
            return std::move(this->getBottom(from, valid));

        case Direction::LEFT:
            return std::move(this->getLeft(from, valid));

        default:
            valid = false;
            return std::move(std::size_t{});
    }
}

position &&Labyrinth::getTop(const position &from, bool &valid) const
{
    if (from < this->w)
    {
        valid = false;
        return std::move(std::size_t{});
    }

    valid = true;

    return std::move(from - this->w);
}

position &&Labyrinth::getBottom(const position &from, bool &valid) const
{
    if (from >= this->h * (this->w - 1))
    {
        valid = false;
        return std::move(std::size_t{});
    }

    valid = true;

    return std::move(from + this->w);
}

position &&Labyrinth::getLeft(const position &from, bool &valid) const
{
    if (0 == from % this->w)
    {
        valid = false;
        return std::move(std::size_t{});
    }

    valid = true;

    return std::move(from - 1);
}

position &&Labyrinth::getRight(const position &from, bool &valid) const
{
    if (this->w - 1 == from % this->w)
    {
        valid = false;
        return std::move(std::size_t{});
    }

    valid = true;

    return std::move(from + 1);
}

unsigned int Labyrinth::getHeight() const
{
    return this->h;
}

unsigned int Labyrinth::getWidth() const
{
    return this->w;
}

std::size_t Labyrinth::getNbCells() const
{
    return static_cast<std::size_t> (this->w * this->h);
}
