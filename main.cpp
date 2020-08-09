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

#include "data_helper.h"
#include "game.h"

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
class QScatterSeries;
QT_CHARTS_END_NAMESPACE

QT_USE_NAMESPACE


int main(int argc, char** argv) {
    // Read in data from file
    DataHelper helper("data/output.json");

    if (!helper.isOpen()) {
        std::cerr << "json wasn't opened successfully!" << std::endl;
        return 1;
    }

    Game game = helper.getGame();

    std::cout << "Number of categories: " << game.getCategories()->size() << std::endl;
    std::cout << "Number of categories: " << game.getLeveledCategories()->size() << std::endl;

    // Display chart


    return 0;
}
