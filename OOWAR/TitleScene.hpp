#pragma once
#include "Game.hpp"
#include "GameScene.hpp"
#include "SelectScene.hpp"
#include "TutorialScene.hpp"


#include <Siv3D.hpp>
#include <memory>

namespace MyGame {
	class TitleScene : public IScene {
	public:
		TitleScene(GameState& gameState);
		void update();
	};
}
