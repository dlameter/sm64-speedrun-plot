#include "data_helper.h"

/* QCore includes */
#include <QFile>
#include <QJsonArray>

/* std includes */
#include <exception>
#include <stdexcept>
#include <iostream>

DataHelper::DataHelper(QString filename) {
    opened = false;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Failed to open data file!" << std::endl;
        return;
    }

    QJsonParseError json_error;
    dataDoc = QJsonDocument::fromJson(file.readAll(), &json_error);
    if (json_error.error != QJsonParseError::ParseError::NoError) {
        std::cerr << "DataHelper: Failed to parse JSON file. " << json_error.errorString().toStdString() << std::endl;
        return;
    }

    if (!dataDoc.isObject()) {
        std::cerr << "DataHelper: Document root is not an object." << std::endl;
        return;
    }
    root = dataDoc.object();

    opened = true;
}

bool DataHelper::isOpen() {
    return opened;
}

Game DataHelper::getGame() {
    return buildGame(root);
}

Run DataHelper::buildRun(QJsonObject runObject) {
    auto iter = runObject.find("place");
    if (iter == runObject.end() || !iter.value().isDouble()) {
        throw std::runtime_error("Could not find int member 'place'");
    }
    int place = iter.value().toInt();

    iter = runObject.find("time");
    if (iter == runObject.end() || !iter.value().isDouble()) {
        throw std::runtime_error("Could not find int member 'time'");
    }
    int time = iter.value().toInt();

    iter = runObject.find("username");
    if (iter == runObject.end() || !iter.value().isString()) {
        throw std::runtime_error("Could not find string member 'username'");
    }
    QString user = iter.value().toString();

    iter = runObject.find("submitted_date");
    if (iter == runObject.end()) {
        throw std::runtime_error("Could not find string member 'submitted_date'");
    }
    else if (!iter.value().isString()) {
        throw std::runtime_error("Member 'submitted_date' is not a string");
    }
    QDateTime submittedDate = QDateTime::fromString(iter.value().toString(), Qt::ISODate);

    return Run(place, time, user, submittedDate);
}

Category DataHelper::buildCategory(QString name, QJsonObject object) {
    QList<Run> runs;

    auto iter = object.find("runs");
    if (iter == object.end() || !iter.value().isArray()) { 
        throw std::runtime_error("Could not find array member 'runs'");
    }

    QJsonArray runArray = iter.value().toArray();

    auto arrayIter = runArray.begin();
    while (arrayIter != runArray.end()) {
        if (!arrayIter->isObject()) {
            throw std::runtime_error("Run array element is not an object.");
        }

        try {
            runs.append(buildRun(arrayIter->toObject()));
        }
        catch (const std::exception& e) {
            // Catch, display, and rethrow exceptions.
            std::cerr << e.what() << std::endl;
            throw;
        }
        
        ++arrayIter;
    }

    return Category(name, runs);
}

Level DataHelper::buildLevel(QString name, QJsonArray levelArray) {
    QList<Run> runs;

    auto iter = levelArray.begin();
    while (iter != levelArray.end()) {
        if (!iter->isObject()) {
            throw std::runtime_error("Run array element is not an object.");
        }

        try {
            runs.append(buildRun(iter->toObject()));
        }
        catch (const std::exception& e) {
            // Catch, display, and rethrow exceptions.
            std::cerr << e.what() << std::endl;
            throw;
        }
        
        ++iter;
    }

    return Level(name, runs);
}

LeveledCategory DataHelper::buildLeveledCategory(QString name, QJsonObject object) {
    QList<Level> levels;

    auto iter = object.begin();
    while (iter != object.end()) {
        if (!iter.value().isArray()) {
            throw std::runtime_error("Leveled category member is not an array.");
        }

        try {
            levels.append(buildLevel(iter.key(), iter.value().toArray()));
        }
        catch (const std::exception& e) {
            // Catch, display, and rethrow exceptions.
            std::cerr << e.what() << std::endl;
            throw;
        }

        ++iter;
    }

    return LeveledCategory(name, levels);
}

Game DataHelper::buildGame(QJsonObject rootObject) {
    QList<Category> categories;
    QList<LeveledCategory> leveledCategories;
    
    auto iter = rootObject.begin();
    while (iter != rootObject.end()) {
        if (!iter.value().isObject()) {
            throw std::runtime_error("Root object member is not an object.");
        }

        QJsonObject object = iter.value().toObject();
        if (object.contains("runs")) {
            try {
                categories.append(buildCategory(iter.key(), object));
            }
            catch (const std::exception& e) {
                // Rethrow exception
                throw;
            }
        }
        else {
            try {
                leveledCategories.append(buildLeveledCategory(iter.key(), object));
            }
            catch (const std::exception& e) {
                //Rethrow exception
                throw;
            }
        }
    }

    return Game(categories, leveledCategories);
}
