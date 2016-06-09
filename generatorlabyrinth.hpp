#ifndef GENERATORLABYRINTH_HPP
#define GENERATORLABYRINTH_HPP

#include <random>
#include "labyrinth.hpp"

class Labyrinth;

class GeneratorLabyrinth
{
    public:
    explicit GeneratorLabyrinth() = default;

    std::unique_ptr<Labyrinth> generate(std::size_t const& y, std::size_t const& x);

    private:
    bool tryOpenDoor(Labyrinth *labyrinth, position const& from, Labyrinth::Direction const& direction);
};

#endif // GENERATORLABYRINTH_HPP
