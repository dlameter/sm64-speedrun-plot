#include "data_helper.h"

/* QCore includes */
#include <QFile>
#include <QJsonArray>

/* std includes */
#include <exception>
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

Run DataHelper::buildRun(QJsonObject runObject) {
    auto iter = runObject.find("place");
    if (iter == runObject.end() || !iter.value().isInt()) {
        throw std::exception("Could not find int member 'place'");
    }
    int place = iter.value().toInt();

    iter = runObject.find("time");
    if (iter == runObject.end() || !iter.value().isInt()) {
        throw std::exception("Could not find int member 'time'");
    }
    int time = iter.value().toInt();

    iter = runObject.find("username");
    if (iter == runObject.end() || !iter.value().isString()) {
        throw std::exception("Could not find string member 'username'");
    }
    QString user = iter.value().toString();

    iter = runObject.find("submitted_date");
    if (iter == runObject.end() || !iter.value().isString()) {
        throw std::exception("Could not find string member 'submitted_date'");
    }
    QDateTime submittedDate = QDateTime::fromString(iter.value().toString(), Qt::ISODate);

    return Run(place, time, user, submittedDate);
}

Category DataHelper::buildCategory(QString name, QJsonObject object) {
    QList<Run> runs;

    auto iter = object.find("runs");
    if (iter == object.end() || !iter.value().isArray()) { throw std::exception("Could not find array member 'runs'");
    }

    QJsonArray runArray = iter.value().toArray();

    auto arrayIter = runArray.begin();
    while (arrayIter != runArray.end()) {
        if (!arrayIter.value().isObject()) {
            throw std::exception("Run array element is not an object.");
        }

        try {
            runs.append(buildRun(arrayIter.value().toObject()));
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
        if (!iter.value().isObject()) {
            throw std::exception("Run array element is not an object.");
        }

        try {
            runs.append(buildRun(iter.value().toObject()));
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
            throw std::exception("Leveled category member is not an array.");
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

Game DataHelper::buildGame(QJsonObject root) {
    QList<Category> categories;
    QList<LeveledCategory> leveledCategories;
    
    auto iter = root.begin();
    while (iter != root.end()) {
        if (!iter.value().isObject()) {
            throw std::exception("Root object member is not an object.");
        }

        QJsonObject object = iter.value().toObject();
        if (object.contains("runs")) {
            try {
                categories.append(buildCategory(iter.value(), object));
            }
            catch (const std::exception& e) {
                // Rethrow exception
                throw;
            }
        }
        else {
            try {
                leveledCategories.append(buildLeveledCategory(iter.value(), object));
            }
            catch (const std::exception& e) {
                //Rethrow exception
                throw;
            }
        }
    }

    return Game(categories, leveledCategories);
}
