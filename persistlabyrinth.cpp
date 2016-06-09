#include "persistlabyrinth.hpp"

bool PersistLabyrinth::save(const std::unique_ptr<Labyrinth> &labyrinth, const QString &filename) const
{
    QJsonObject json;
    QJsonArray cells;
    std::size_t count = labyrinth->getNbCells();

    // for each cell
    for (std::size_t i = 0; i < count; i++)
    {
        QJsonObject cell;
        cell.insert("down", labyrinth->canMove(i, Labyrinth::BOTTOM));
        cell.insert("right", labyrinth->canMove(i, Labyrinth::RIGHT));

        cells.append(cell);
    }

    json.insert("cells", cells);
    json.insert("height", static_cast<int> (labyrinth->getHeight()));
    json.insert("width", static_cast<int> (labyrinth->getWidth()));

    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QJsonDocument jsonLabyrinth{json};

    auto bytes = file.write(jsonLabyrinth.toJson(QJsonDocument::Compact));

    // -1 = error
    return bytes != -1;
}

std::unique_ptr<Labyrinth> PersistLabyrinth::fromJson(const QJsonObject &json, bool &isValid)
{
    isValid = false;
    auto labyrinth = std::unique_ptr<Labyrinth>{};

    // if one key miss, return empty labyrinth
    if (!json.contains("cells") || !json.contains("height") || !json.contains("width")) {
        return labyrinth;
    }

    int y = json["height"].toInt();
    int x = json["width"].toInt();

    // if the size is impossible return empty labyrinth
    if (y < 1 || x < 1) {
        return labyrinth;
    }

    labyrinth = std::make_unique<Labyrinth>(y, x);
    const std::size_t nbCells = y * x;

    QJsonArray cells = json["cells"].toArray();

    const std::size_t count = static_cast<std::size_t> (cells.count());

    // if count and width * height => error, return empty labyrinth
    if (count != nbCells) {
        return labyrinth;
    }

    // for each cell in json
    for (unsigned int i = 0; i < count; i++)
    {
        QJsonObject cell = cells[i].toObject();

        if (cell["down"].toBool()) {
            isValid = labyrinth->openDoor(i, Labyrinth::BOTTOM);

            // if impossible to open bottom, json is bad, return empty labyrinth
            if (!isValid) {
                return labyrinth;
            }
        }

        if (cell["right"].toBool()) {
            isValid = labyrinth->openDoor(i, Labyrinth::RIGHT);

            // if impossible to open right, json is bad, return empty labyrinth
            if (!isValid) {
                return labyrinth;
            }
        }        
    }

    isValid = true;

    labyrinth->setStart(0);
    labyrinth->setFinish(nbCells - 1);

    return labyrinth;
}
