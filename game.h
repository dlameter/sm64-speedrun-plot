#ifndef GAME_H
#define GAME_H

#include "category.h"
#include "leveled_category.h"

class Game {
public:
    Game(QList<Category> categories, QList<LeveledCategory> leveledCategories);

    QList<Category> getCategories();
    QList<LeveledCategory> getLeveledCategories();

private:
    QList<Category> m_categories;
    QList<LeveledCategory> m_leveledCategories;
};

#endif
