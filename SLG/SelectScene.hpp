#pragma once

#include "IScene.hpp"

namespace MyGame {
	class SelectScene : public IScene {
	public:
		SelectScene(GameState& gameState);
		void update();

	private:
		void drawUI();
	};
}
