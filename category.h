#ifndef CATEGORY_H
#define CATEGORY_H

#include "run.h"

class Category {
public:
    Category(QString name, QList<Run>* runs);
    virtual ~Category();

    QString getName();
    QList<Run>* getRuns();

private:
    QString m_name;
    QList<Run>* m_runs;
};

#endif
