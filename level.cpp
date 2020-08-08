#include "level.h"

Level::Level(QString name, QList<Run> runs): m_name(name), m_runs(runs) {};

QString Level::getName() {
    return m_name;
}

QList<Run> Level::getRuns() {
    return m_runs;
}
