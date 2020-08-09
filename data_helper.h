#ifndef DATA_HELPER_H
#define DATA_HELPER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

#include "game.h"

class DataHelper {
    public:
        DataHelper(const QString& filename);

        bool isOpen();
        Game getGame();

    private:
        Run buildRun(const QJsonObject& runObject);
        Category buildCategory(const QString& name, const QJsonObject& object);
        Level buildLevel(const QString& name, const QJsonArray& levelArray);
        LeveledCategory buildLeveledCategory(const QString& name, const QJsonObject& object);
        Game buildGame(const QJsonObject& rootObject);

        QJsonDocument dataDoc;
        QJsonObject root;
        bool opened;
};

#endif
