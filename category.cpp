#include "category.h"

Category::Category(): m_name("") {}

Category::Category(const QString& name, const QList<Run>& runs) {
    m_name = QString(name);
    m_runs.append(runs);
}

Category::~Category() {}

QString& Category::getName() {
    return m_name;
}

const QString& Category::getName() const {
    return m_name;
}

void Category::setName(const QString& name) {
    m_name = name;
}

QList<Run>& Category::getRuns() {
    return m_runs;
}

const QList<Run>& Category::getRuns() const {
    return m_runs;
}

void Category::append(const Run& run) {
    m_runs.append(run);
}
