#include "level.h"

Level::Level(const QString& name, const QList<Run>& runs): m_name(name) {
    m_name = QString(name);
    m_runs.append(runs);
}

Level::~Level() {}

QString& Level::getName() {
    return m_name;
}

const QString& Level::getName() const {
    return m_name;
}

void Level::setName(const QString& name) {
    m_name = name;
}

QList<Run>& Level::getRuns() {
    return m_runs;
}

const QList<Run>& Level::getRuns() const {
    return m_runs;
}

void Level::append(const Run& run) {
    m_runs.append(run);
}
