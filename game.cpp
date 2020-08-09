#include "game.h"

Game::Game() {}

Game::Game(const QList<Category>& categories, const QList<LeveledCategory>& leveledCategories) {
    m_categories.append(categories);
    m_leveledCategories.append(leveledCategories);
}

Game::~Game() {}

QList<Category>& Game::getCategories() {
    return m_categories;
}

const QList<Category>& Game::getCategories() const {
    return m_categories;
}

void Game::appendCategory(const Category& category) {
    m_categories.append(category);
}

QList<LeveledCategory>& Game::getLeveledCategories() {
    return m_leveledCategories;
}

const QList<LeveledCategory>& Game::getLeveledCategories() const {
    return m_leveledCategories;
}

void Game::appendLeveledCategory(const LeveledCategory& leveledCategory) {
    m_leveledCategories.append(leveledCategory);
}
