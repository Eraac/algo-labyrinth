#ifndef CELL_HPP
#define CELL_HPP

typedef unsigned int idWay;

class Cell
{
    friend class Labyrinth;

    public:
    Cell(unsigned int const& id, idWay const way);

    enum class State {NONE, VISITED, CURRENT, START, FINISH};

    unsigned int getId() const;       

    bool bottomIsOpen() const;
    bool rightIsOpen() const;
    State getState() const;

    private:
    unsigned int id;
    idWay way;

    void setId(unsigned int const &id);

    void openBottom();
    void openRight();
    void setState(Cell::State const state);

    bool bottom;
    bool right;
    State state;
};

#endif // CELL_HPP
