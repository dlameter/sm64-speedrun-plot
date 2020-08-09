#include "leveled_category.h"

LeveledCategory::LeveledCategory(const QString& name, const QList<Level>& levels):
    m_name(name)
{
    m_levels = new QList<Level>;

    m_levels->append(levels);
}

LeveledCategory::~LeveledCategory() {
    delete(m_levels);
}

QString LeveledCategory::getName() {
    return m_name;
}

void LeveledCategory::setName(const QString& name) {
    m_name = name;
}

QList<Level>* LeveledCategory::getLevels() {
    return m_levels;
}

void LeveledCategory::append(const Level& level) {
    m_levels->append(level);
}
