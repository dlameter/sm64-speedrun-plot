#include "data_helper.h"

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

    opened = true;
}

bool DataHelper::isOpen() {
    return opened;
}
