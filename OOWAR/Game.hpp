#pragma once

#include "IScene.hpp"

#include <memory>

namespace MyGame {
	struct GameState {
		std::unique_ptr<IScene> m_scene;

		GameState() : m_scene(nullptr) {}
		GameState(const IScene&) = delete;
		void operator=(const IScene&) = delete;
	};

	class Game {
	private:
		GameState m_state;

	public:
		Game();
		bool update();
	};
}
