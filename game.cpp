#include "game.h"

Game::Game(QList<Category> categories, QList<LeveledCategory> leveledCategories):
    m_categories(categories),
    m_leveledCategories(leveledCategories)
{}


QList<Category> Game::getCategories() {
    return m_categories;
}

QList<LeveledCategory> Game::getLeveledCategories() {
    return m_leveledCategories;
}
