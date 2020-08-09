#include "game.h"

Game::Game(const QList<Category>& categories, const QList<LeveledCategory>& leveledCategories) {
    m_categories = new QList<Category>;
    m_leveledCategories = new QList<LeveledCategory>;

    m_categories->append(categories);
    m_leveledCategories->append(leveledCategories);
}

Game::~Game() {
    delete(m_categories);
    delete(m_leveledCategories);
}

QList<Category>* Game::getCategories() {
    return m_categories;
}

void Game::appendCategory(const Category& category) {
    m_categories->append(category);
}

QList<LeveledCategory>* Game::getLeveledCategories() {
    return m_leveledCategories;
}

void Game::appendLeveledCategory(const LeveledCategory& leveledCategory) {
    m_leveledCategories->append(leveledCategory);
}
