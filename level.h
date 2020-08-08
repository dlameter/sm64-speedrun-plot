#ifndef LEVEL_H
#define LEVEL_H

#include "run.h"

class Level {
public:
    Level(QString name, QList<Run> runs);

    QString getName();
    QList<Run> getRuns();

private:
    QString m_name;
    QList<Run> m_runs;
};

#endif
