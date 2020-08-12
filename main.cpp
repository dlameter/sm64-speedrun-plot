/* QCore includes */
#include <QColor>
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
#include "interactive_qchart.h"

#define MARKER_SIZE 10

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
class QScatterSeries;
QT_CHARTS_END_NAMESPACE

QT_USE_NAMESPACE

void buildColorList(QList<QColor>& colors) {
    colors.append(QColor(128, 0, 0));       // Maroon
    colors.append(QColor(170, 110, 40));    // Brown
    colors.append(QColor(128, 128, 0));     // Olive
    colors.append(QColor(0, 128, 128));     // Teal
    colors.append(QColor(0, 0, 128));       // Navy
    colors.append(QColor(230, 25, 75));     // Red
    colors.append(QColor(245, 130, 48));    // Orange
    colors.append(QColor(255, 255, 25));    // Yellow
    colors.append(QColor(210, 245, 60));    // Lime
    colors.append(QColor(60, 180, 75));     // Green
    colors.append(QColor(70, 240, 240));    // Cyan
    colors.append(QColor(0, 130, 200));     // Blue
    colors.append(QColor(145, 30, 180));    // Purple
    colors.append(QColor(240, 50, 230));    // Magenta
    colors.append(QColor(250, 190, 212));   // Pink
    colors.append(QColor(255, 215, 180));   // Apricot
    colors.append(QColor(255, 250, 200));   // Beige
    colors.append(QColor(170, 255, 195));   // Mint
    colors.append(QColor(220, 190, 255));   // Lavender
    colors.append(QColor(0, 0, 0));         // Black
    colors.append(QColor(128, 128, 128));   // Grey
    colors.append(QColor(255, 255, 255));   // White
}

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

    InteractiveQChart* chart = new InteractiveQChart;
    chart->setTitle("Super Mario 64 speedrun completion time vs date submitted");
    chart->legend()->setAlignment(Qt::AlignRight);

    // Create chart axes
    QValueAxis* timeAxis = new QValueAxis;
    timeAxis->setTitleText("Completion Time");
    timeAxis->setTickCount(8);

    chart->addAxis(timeAxis, Qt::AlignLeft);

    QDateTimeAxis* dateAxis = new QDateTimeAxis;
    dateAxis->setFormat("dd/MM/yyyy");
    dateAxis->setTitleText("Date Submitted");
    dateAxis->setLabelsAngle(-75);
    dateAxis->setTickCount(8);

    chart->addAxis(dateAxis, Qt::AlignBottom);

    // Convert to chart data.
    QList<QColor> colors;
    buildColorList(colors);
    int colorPos = 0;

    QScatterSeries* series;

    QList<Category> categories = game.getCategories();
    for (int j = 0; j < categories.size(); ++j) {
        Category category = categories[j];

        series = new QScatterSeries;
        series->setName(category.getName());
        series->setMarkerSize(MARKER_SIZE);
        series->setColor(colors[colorPos++]);
        colorPos = colorPos % colors.size();

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
            series->setColor(colors[colorPos++]);
            colorPos = colorPos % colors.size();

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
