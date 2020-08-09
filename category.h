#ifndef CATEGORY_H
#define CATEGORY_H

#include "run.h"

class Category {
public:
    Category();
    Category(const QString& name, const QList<Run>& runs);
    virtual ~Category();

    QString& getName();
    const QString& getName() const;
    void setName(const QString& name);
    QList<Run>& getRuns();
    const QList<Run>& getRuns() const;
    void append(const Run& run);

private:
    QString m_name;
    QList<Run> m_runs;
};

#endif
