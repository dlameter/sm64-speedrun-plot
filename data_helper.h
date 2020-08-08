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
        Level buildLevel(QJsonObject levelObject);
        LeveledCategory buildLeveledCategory(QJsonObject object);
        Game buildGame(QJsonObject root);

        QJsonDocument dataDoc;
        QJsonObject root;
        bool opened;
};

#endif
