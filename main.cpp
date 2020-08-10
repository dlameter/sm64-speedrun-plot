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

#define MARKER_SIZE 7

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
class QScatterSeries;
QT_CHARTS_END_NAMESPACE

QT_USE_NAMESPACE


int main(int argc, char** argv) {
    // Init qt application
    QApplication app(argc, argv);

    // Read in data from file
    DataHelper helper("data/output.json");

    if (!helper.isOpen()) {
        std::cerr << "json wasn't opened successfully!" << std::endl;
        return 1;
    }

    Game game = helper.getGame();

    // Create chart view and chart objects
    QChartView* view = new QChartView;

    QChart* chart = new QChart;
    chart->setTitle("Super Mario 64 speedrun completion time vs date submitted");

    // Create chart axes
    QValueAxis* timeAxis = new QValueAxis;
    timeAxis->setTitleText("Completion Time");

    chart->addAxis(timeAxis, Qt::AlignLeft);

    QDateTimeAxis* dateAxis = new QDateTimeAxis;
    dateAxis->setFormat("yyyy MM dd");
    dateAxis->setTitleText("Date Submitted");

    chart->addAxis(dateAxis, Qt::AlignBottom);

    // Convert to chart data.
    QScatterSeries* series;

    QList<Category> categories = game.getCategories();
    for (int j = 0; j < categories.size(); ++j) {
        Category category = categories[j];

        series = new QScatterSeries;
        series->setName(category.getName());
        series->setMarkerSize(MARKER_SIZE);

        QList<Run> runs = category.getRuns();
        for (int i = 0; i < runs.size(); ++i) {
            series->append(runs[i].getSubmittedDate().toMSecsSinceEpoch(), runs[i].getTime());
        }
        chart->addSeries(series);

        series->attachAxis(timeAxis);
        series->attachAxis(dateAxis);
    }

    QList<LeveledCategory> leveledCategories = game.getLeveledCategories();
    for (int i = 0; i < leveledCategories.size(); ++i) {
        LeveledCategory leveledCategory = leveledCategories[i];

        QList<Level> levels = leveledCategory.getLevels();
        for (int j = 0; j < levels.size(); ++j) {
            Level level = levels[j];

            series = new QScatterSeries;
            series->setName(leveledCategory.getName() + ": " + level.getName());
            series->setMarkerSize(MARKER_SIZE);

            QList<Run> runs = level.getRuns();
            for (int k = 0; k < runs.size(); ++k) {
                series->append(runs[k].getSubmittedDate().toMSecsSinceEpoch(), runs[k].getTime());
            }
            chart->addSeries(series);

            series->attachAxis(timeAxis);
            series->attachAxis(dateAxis);
        }
    }

    view->setChart(chart);

    // Display chart
    QMainWindow window;
    window.setCentralWidget(view);
    window.resize(800, 600);
    window.show();

    return app.exec();
}
