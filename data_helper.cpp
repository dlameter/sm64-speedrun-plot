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
