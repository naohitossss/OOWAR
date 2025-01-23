#pragma once
#include "Game.hpp"
#include "GameScene.hpp"
#include "GameText.hpp"
#include "SelectScene.hpp"
#include "TutorialScene.hpp"


#include <Siv3D.hpp>
#include <memory>

namespace MyGame {
	class TitleScene : public IScene {
	private:
		Stopwatch textStopwatch{ StartImmediately::Yes };
		const Font titleTextfont{ FontMethod::MSDF, 100, Typeface::Bold };
		const String titleText = U"〇●大戦";
		GameText gametext;

	public:
		TitleScene(GameState& gameState);
		void update();
	};
}
