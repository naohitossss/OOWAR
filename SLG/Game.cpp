#include"Game.hpp"

#include "TitleScene.hpp"

namespace MyGame {
	Game::Game() : m_state() {
		m_state.m_scene = std::move(std::make_unique<TitleScene>(m_state));
	}

	bool Game::update() {
		if (m_state.m_scene == nullptr) {
			return false;
		}
		m_state.m_scene->update();

		return true;
	}
}
