#ifndef GAME_H
#define GAME_H

#include "category.h"
#include "leveled_category.h"

class Game {
public:
    Game();
    Game(const QList<Category>& categories, const QList<LeveledCategory>& leveledCategories);
    virtual ~Game();

    QList<Category>& getCategories();
    const QList<Category>& getCategories() const;
    void appendCategory(const Category& category);
    QList<LeveledCategory>& getLeveledCategories();
    const QList<LeveledCategory>& getLeveledCategories() const;
    void appendLeveledCategory(const LeveledCategory& leveledCategory);

private:
    QList<Category> m_categories;
    QList<LeveledCategory> m_leveledCategories;
};

#endif
