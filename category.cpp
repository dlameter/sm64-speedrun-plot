#include "category.h"

Category::Category(const QString& name, const QList<Run>& runs): m_name(name) {
    m_runs = new QList<Run>;

    m_runs->append(runs);
}

Category::~Category() {
    delete(m_runs);
}

QString Category::getName() {
    return m_name;
}

void Category::setName(const QString& name) {
    m_name = name;
}

QList<Run>* Category::getRuns() {
    return m_runs;
}

void Category::append(const Run& run) {
    m_runs->append(run);
}
