#ifndef DATA_HELPER_H
#define DATA_HELPER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

class DataHelper {
    public:
        enum CategoryType {
            REGULAR,
            PER_LEVEL
        };

        QJsonDocument dataDoc;
        bool opened;

        DataHelper(QString filename);

        bool isOpen();

        QList<QString> listCategories();
        QList<QString> listLevels(QString categoryName);
        CategoryType categoryType(QString categoryName);
        int runCount(QString categoryName);
        int runCount(QString categoryName, QString levelName);
        QJsonObject run(QString categoryName, int runNumber);
        QJsonObject run(QString categoryName, QString levelName, int runNumber);

        /* static helpers */
        static int runPlace(QJsonObject runObject);
        static int runTime(QJsonObject runObject);
        static QString runUser(QJsonObject runObject);
        static QDateTime runSubmittedDate(QJsonObject runObject);
};

#endif
