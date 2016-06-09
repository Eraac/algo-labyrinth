#ifndef LABYRINTH_HPP
#define LABYRINTH_HPP

#include <vector>
#include <map>
#include "dijkstra.hpp"
#include "cell.hpp"

typedef std::size_t position;

class Labyrinth
{
    public:
        Labyrinth() = delete;
        ~Labyrinth() = default;
        explicit Labyrinth(unsigned int const& y, unsigned int const& x);

        enum Direction {TOP, RIGHT, BOTTOM, LEFT};
        bool openDoor(position const& from, Labyrinth::Direction const& direction);
        bool canMove(position const& from, Labyrinth::Direction const& direction) const;
        Cell::State getState(position const& cell) const;

        unsigned int getHeight() const;
        unsigned int getWidth() const;
        std::size_t getNbCells() const;

        void setStart(position const& cell);
        void setFinish(position const& cell);
        void setVisited(position const& cell);

        idWay getIdWay(position const& pos) const;
        void setIdWay(position const& pos, idWay const way);

        position&& getNeighbor(position const& from, Labyrinth::Direction const &direction, bool &valid) const;
        void updateWays(idWay const from, idWay const to);

        adjacency_list_t getAdjacencyList();

    private:
        std::vector<std::unique_ptr<Cell>> cells;
        std::multimap<idWay, position> ways;
        unsigned int h;
        unsigned int w;

        position&& getTop(position const& from, bool &valid) const;
        position&& getBottom(position const& from, bool &valid) const;
        position&& getLeft(position const& from, bool &valid) const;
        position&& getRight(position const& from, bool &valid) const;

        void generateGraph(adjacency_list_t& list, position const& current, position const& previous);
};

#endif // LABYRINTH_HPP
