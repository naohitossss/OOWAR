#pragma once
#include "Game.hpp"
#include "GameScene.hpp"
#include "SelectScene.hpp"
#include "TutorialScene.hpp"


#include <Siv3D.hpp>
#include <memory>

namespace MyGame {
	class TitleScene : public IScene {
	private:
		void TitleTextEffect(const Vec2& penPos, double scale, const Glyph& glyph, const ColorF& color, double t);
	public:
		TitleScene(GameState& gameState);
		void update();
	};
}
