/* QCore includes */
#include <QCoreApplication>
#include <QFile>

/* QJson includes */
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValueRef>
#include <QJsonValue>

/* QtCharts includes */
#include <QtCharts>

/* std includes */
#include <iostream>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
class QScatterSeries;
QT_CHARTS_END_NAMESPACE

QT_USE_NAMESPACE


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

    if (json_doc.isObject()) {
        std::cout << "Document is a json object!" << std::endl;
    }

    QJsonObject root_object = json_doc.object();

    // move data to displayable qtchart objects
    QScatterSeries* series1 = new QScatterSeries();
    series1->setName("Test data");

    QJsonObject::iterator json_iter = root_object.find("120 Star");
    if (json_iter == root_object.end()) {
        std::cerr << "Could not find 120 Star in json object!" << std::endl;
        return 0;
    }

    std::cout << json_iter.key().toStdString() << std::endl;

    QJsonValueRef star120 = json_iter.value();
    if (!star120.isObject()) {
        std::cerr << "120 Star value is not an object!" << std::endl;
        return 0;
    }

    std::cout << "finding runs" << std::endl;

    QJsonObject temp_obj = star120.toObject();
    json_iter = temp_obj.find("runs");
    if (json_iter == temp_obj.end()) {
        std::cerr << "Could not find runs member!" << std::endl;
    }

    std::cout << "runs array" << std::endl;

    QJsonValueRef runs = json_iter.value();
    if (!runs.isArray()) {
        std::cerr << "run value is not an array!" << std::endl;
        return 0;
    }
    else {
        std::cout << "runs value is an array!" << std::endl;
    }
    QJsonArray runs_array = runs.toArray();

    std::cout << runs_array[0].toObject().find("place").value().toInt() << std::endl;

    // Display chart

    return 0;
}
