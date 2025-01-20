#pragma once

#include <Siv3D.hpp>

namespace MyGame {
	struct GameState;

	class IScene {
	protected:
		GameState& m_gameState;

	public:
		IScene(GameState& gameState) : m_gameState(gameState) {}
		virtual ~IScene() {}

		virtual void update() = 0;
	};
}
