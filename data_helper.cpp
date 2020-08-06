#include "data_helper.h"

/* QCore includes */
#include <QFile>

/* std includes */
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

QList<QString> DataHelper::listCategories() {
    QList<QString> categories;

    for (auto iter = root.begin(); iter != root.end(); ++iter) {
        categories.append(iter.key());
    }

    return categories;
}

QList<QString> DataHelper::listLevels(QString categoryName) {
    QList<QString> levels;

    if (categoryType(categoryName) == DataHelper::CategoryType::PER_LEVEL) {
        auto categoryObject = root.find(categoryName).value().toObject();

        for (auto iter = categoryObject.begin(); iter != categoryObject.end(); ++iter) {
            levels.append(iter.key());
        }
    }

    return levels;
}

// TO-DO: throw an exception if it does not follow the correct data structure.
DataHelper::CategoryType DataHelper::categoryType(QString categoryName) {
    auto iter = root.find(categoryName);
    if (iter != root.end()) {
        QJsonObject categoryObject = iter.value().toObject();

        iter = categoryObject.find("runs");
        if (iter == categoryObject.end()) {
            return DataHelper::CategoryType::PER_LEVEL;
        }
        else {
            return DataHelper::CategoryType::REGULAR;
        }
    }

    return DataHelper::CategoryType::REGULAR;
}
