#include "category.h"

Category::Category(QString name, QList<Run> runs): m_name(name), m_runs(runs) {}

virtual Category::~Category() {
    delete(m_runs);
}

QString Category::getName() {
    return m_name;
}

QList<Run> Category::getRuns() {
    return m_runs;
}
