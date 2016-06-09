#include "cell.hpp"

Cell::Cell(unsigned int const& id, const idWay way) : id(id), way(way), bottom(false), right(false), state(State::NONE) {}

unsigned int Cell::getId() const
{
    return this->id;
}

void Cell::setId(const unsigned int &id)
{
    this->id = id;
}

void Cell::openBottom()
{
    this->bottom = true;
}

void Cell::openRight()
{
    this->right = true;
}

void Cell::setState(const Cell::State state)
{
    this->state = state;
}

bool Cell::bottomIsOpen() const
{
    return this->bottom;
}

bool Cell::rightIsOpen() const
{
    return this->right;
}

Cell::State Cell::getState() const
{
    return this->state;
}
