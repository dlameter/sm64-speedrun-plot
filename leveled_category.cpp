#include "leveled_category.h"

LeveledCategory::LeveledCategory(QString name, QList<Level> levels):
    m_name(name),
    m_levels(levels)
{}

QString LeveledCategory::getName() {
    return m_name;
}

QList<Level> LeveledCategory::getLevels() {
    return m_levels;
}
