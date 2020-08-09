#ifndef GAME_H
#define GAME_H

#include "category.h"
#include "leveled_category.h"

class Game {
public:
    Game(const QList<Category>& categories, const QList<LeveledCategory>& leveledCategories);
    virtual ~Game();

    QList<Category>* getCategories();
    void appendCategory(const Category& category);
    QList<LeveledCategory>* getLeveledCategories();
    void appendLeveledCategory(const LeveledCategory& leveledCategory);

private:
    QList<Category>* m_categories;
    QList<LeveledCategory>* m_leveledCategories;
};

#endif
