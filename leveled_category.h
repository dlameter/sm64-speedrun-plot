#ifndef LEVELED_CATEGORY_H
#define LEVELED_CATEGORY_H

#include "level.h"

class LeveledCategory {
public:
    LeveledCategory(QString name, QList<Level> levels);

    QString getName();
    QList<Level> getLevels();

private:
    QString m_name;
    QList<Level> m_levels;
};

#endif
