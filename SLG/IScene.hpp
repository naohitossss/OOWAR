#pragma once

#include <Siv3D.hpp>

namespace MyGame {
	struct GameState;

	class IScene {
	protected:
		GameState& m_gameState;

	public:
		IScene(GameState& gameState) : m_gameState(gameState) {}
		virtual ~IScene() {
			//Print << U"deleted";
		}

		virtual void update() = 0;
	};
}
