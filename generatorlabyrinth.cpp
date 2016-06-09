#include "generatorlabyrinth.hpp"

std::unique_ptr<Labyrinth> GeneratorLabyrinth::generate(const std::size_t &y, const std::size_t &x)
{
    std::unique_ptr<Labyrinth> labyrinth = std::make_unique<Labyrinth>(y, x);

    const std::size_t nbCells = y * x;

    std::random_device rd;
    std::mt19937 gen(rd());

    // choice random cell
    std::uniform_int_distribution<position> randomCell(0, nbCells - 1);

    // choice random direction
    std::uniform_int_distribution<Labyrinth::Direction> randomDirection(Labyrinth::TOP, Labyrinth::LEFT);

    const unsigned int doorToOpen = static_cast<unsigned int> (nbCells) - 1;

    for (unsigned int i = 0; i < doorToOpen;)
    {
        // 1. get random cell position
        position pos = randomCell(gen);

        // 2. random direction
        Labyrinth::Direction direction = randomDirection(gen);

        // 3. Try to open the door
        if (this->tryOpenDoor(labyrinth.get(), pos, direction)) {
            i++;
        }
    }

    // set start in the first cell (top & left)
    labyrinth->setStart(0);

    // set finish in the last cell (bottom & right)
    labyrinth->setFinish(nbCells - 1);

    return labyrinth;
}

bool GeneratorLabyrinth::tryOpenDoor(Labyrinth *labyrinth, const position &from, const Labyrinth::Direction &direction)
{
    bool isValid = false;

    // get neighbor
    position positionNeighbor = labyrinth->getNeighbor(from, direction, isValid);

    // if is not valid, door can not be open
    if (!isValid) {
        return false;
    }

    // get way id from the two cell
    idWay idWayFrom = labyrinth->getIdWay(from);
    idWay idWayTo = labyrinth->getIdWay(positionNeighbor);

    // if id is the same, cells is already connected
    if (idWayFrom == idWayTo) {
        return false;
    }

    isValid = labyrinth->openDoor(from, direction);

    return isValid;
}
