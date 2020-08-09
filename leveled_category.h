#ifndef LEVELED_CATEGORY_H
#define LEVELED_CATEGORY_H

#include "level.h"

class LeveledCategory {
public:
    LeveledCategory(const QString& name, const QList<Level>& levels);
    virtual ~LeveledCategory();

    QString getName();
    void setName(const QString& name);
    QList<Level>* getLevels();
    void append(const Level& level);

private:
    QString m_name;
    QList<Level>* m_levels;
};

#endif
