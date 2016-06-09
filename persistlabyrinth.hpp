#ifndef PERSISTLABYRINTH_HPP
#define PERSISTLABYRINTH_HPP

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "labyrinth.hpp"

class PersistLabyrinth
{
    public:
    PersistLabyrinth() = default;
    ~PersistLabyrinth() = default;

    bool save(std::unique_ptr<Labyrinth> const& labyrinth, QString const& filename) const;
    std::unique_ptr<Labyrinth> fromJson(QJsonObject const& json, bool &isValid);
};

#endif // PERSISTLABYRINTH_HPP
