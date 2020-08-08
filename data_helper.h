#ifndef DATA_HELPER_H
#define DATA_HELPER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

#include "game.h"

class DataHelper {
    public:
        DataHelper(QString filename);

        bool isOpen();
        Game getGame();

    private:
        Run buildRun(QJsonObject runObject);
        Category buildCategory(QString name, QJsonObject object);
        Level buildLevel(QString name, QJsonArray levelArray);
        LeveledCategory buildLeveledCategory(QString name, QJsonObject object);
        Game buildGame(QJsonObject rootObject);

        QJsonDocument dataDoc;
        QJsonObject root;
        bool opened;
};

#endif
