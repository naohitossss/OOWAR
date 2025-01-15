#include "GameSceneUI.hpp"

namespace MyGame {
	void GameSceneUI::drawGameUI()
	{

		const Array<std::pair<String, int>> soldierButtons = {
			{U"兵士数を1に設定", 1},
			{U"兵士数を5に設定", 5},
			{U"兵士数を10に設定", 10}
		};

		for (int i = 0; i < soldierButtons.size(); ++i) {
			if (SimpleGUI::Button(soldierButtons[i].first, Vec2{ 20, 460 + i * 40 })) {
				m_gameRule.setAttackSoldiers(soldierButtons[i].second);
			}
		}

	}
	void GameSceneUI::drawGameOverScreen(bool isWin,bool isLose)
	{
		if (isWin) {
			FontAsset(U"Default")(U"勝利！").drawAt(Scene::Center(), Palette::Yellow);
		}
		else if (isLose) {
			FontAsset(U"Default")(U"敗北...").drawAt(Scene::Center(), Palette::Red);
		}
	}
}
