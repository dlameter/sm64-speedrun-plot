#ifndef LEVEL_H
#define LEVEL_H

#include "run.h"

class Level {
public:
    Level(const QString& name, const QList<Run>& runs);
    virtual ~Level();

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
