#include "level.h"

Level::Level(const QString& name, const QList<Run>& runs): m_name(name) {
    m_runs = new QList<Run>;

    m_runs->append(runs);
}

Level::~Level() {
    delete(m_runs);
}

QString Level::getName() {
    return m_name;
}

void Level::setName(const QString& name) {
    m_name = name;
}

QList<Run>* Level::getRuns() {
    return m_runs;
}

void Level::append(const Run& run) {
    m_runs->append(run);
}
