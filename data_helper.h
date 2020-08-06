#ifndef DATA_HELPER_H
#define DATA_HELPER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

class DataHelper {
    public:
        enum class CategoryType {
            REGULAR,
            PER_LEVEL
        };

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

    private:
        QJsonDocument dataDoc;
        QJsonObject root;
        bool opened;
};

#endif
