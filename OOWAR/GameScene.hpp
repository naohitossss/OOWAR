#pragma once
#include "Game.hpp"
#include "IScene.hpp"
#include "Territory.hpp"
#include "GameRule.hpp"
#include "RandomEnemyAI.hpp"
#include "GameSceneUI.hpp"
#include "SelectScene.hpp"

namespace MyGame {
	class GameScene : public IScene {
	private:
		/*std::vector<Territory> m_territories;*/

	public:
		GameScene(GameState& gameState);
		void update();
	};
}
