#pragma once

#include "GameRule.hpp"

#include<vector>
#include <Siv3D.hpp>

namespace MyGame {
	class GameSceneUI {

	private:
		GameRule m_gameRule;
	public:
		void drawGameUI();
		void drawGameOverScreen(bool isWin, bool isLose);
	};
}

