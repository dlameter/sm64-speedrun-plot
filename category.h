#ifndef CATEGORY_H
#define CATEGORY_H

#include "run.h"

class Category {
public:
    Category(const QString& name, const QList<Run>& runs);
    virtual ~Category();

    QString getName();
    void setName(const QString& name);
    QList<Run>* getRuns();
    void append(const Run& run);

private:
    QString m_name;
    QList<Run>* m_runs;
};

#endif
