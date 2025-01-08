#pragma once

#include "IScene.hpp"

namespace MyGame {
	class TitleScene : public IScene {
	public:
		TitleScene(GameState& gameState);
		void update();
	};
}
