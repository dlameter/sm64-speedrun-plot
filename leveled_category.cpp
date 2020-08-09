#include "leveled_category.h"

LeveledCategory::LeveledCategory(const QString& name, const QList<Level>& levels):
    m_name(name)
{
    m_levels.append(levels);
}

LeveledCategory::~LeveledCategory() {}

QString& LeveledCategory::getName() {
    return m_name;
}

const QString& LeveledCategory::getName() const {
    return m_name;
}

void LeveledCategory::setName(const QString& name) {
    m_name = name;
}

QList<Level>& LeveledCategory::getLevels() {
    return m_levels;
}

const QList<Level>& LeveledCategory::getLevels() const {
    return m_levels;
}

void LeveledCategory::append(const Level& level) {
    m_levels.append(level);
}
