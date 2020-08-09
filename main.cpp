/* QCore includes */
#include <QCoreApplication>
#include <QDateTime>
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
#include "category.h"
#include "game.h"
#include "run.h"

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

    std::cout << "Number of categories: " << game.getCategories().size() << std::endl;
    std::cout << "Number of categories: " << game.getLeveledCategories().size() << std::endl;

    QList<Category> categories = game.getCategories();
    for (int i = 0; i < categories.size(); ++i) {
        std::cout << "CATEGORY " << categories[i].getName().toStdString() << ":" << std::endl;

        QList<Run> runs = categories[i].getRuns();
        for (int j = 0; j < runs.size(); ++j) {
            std::cout << "\tRUN " << runs[j].getUser().toStdString() << ", " << runs[j].getPlace() << std::endl;
        }
    }

    QList<LeveledCategory> leveledCategories = game.getLeveledCategories();
    for (int i = 0; i < leveledCategories.size(); ++i) {
        std::cout << "LEVELED_CATEGORY " << leveledCategories[i].getName().toStdString() << ":" << std::endl;

        QList<Level> levels = leveledCategories[i].getLevels();
        for (int k = 0; k < levels.size(); ++k) {
            std::cout << "\tLEVEL " << levels[k].getName().toStdString() << std::endl;

            QList<Run> runs = levels[k].getRuns();
            for (int j = 0; j < runs.size(); ++j) {
                std::cout << "\t\tRUN " << runs[j].getUser().toStdString() << ", " << runs[j].getPlace() << std::endl;
            }
        }
    }

    // Convert to chart data.

    // Display chart

    return 0;
}
