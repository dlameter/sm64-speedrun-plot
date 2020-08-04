#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <iostream>

int main(int argc, char** argv) {
    // Read in data from file
    QFile json_file("data/output.json");

    if (!json_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Failed to open data file!" << std::endl;
        return 0;
    }

    QJsonParseError json_error;
    QJsonDocument json_doc = QJsonDocument::fromJson(json_file.readAll(), &json_error);
    if (json_error.error != QJsonParseError::ParseError::NoError) {
        std::cerr << "Failed to parse json file." << json_error.errorString().toStdString() << std::endl;
        return 0;
    }

    // move data to displayable qtchart objects

    // Display chart

    return 0;
}
