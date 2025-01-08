#pragma once

#include "IScene.hpp"

namespace MyGame {
	class GameScene : public IScene {
	private:
		/*std::vector<Territory> m_territories;*/

	public:
		GameScene(GameState& gameState);
		void update();
	};
}
