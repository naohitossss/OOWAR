#pragma once

#include "Game.hpp"
#include "IScene.hpp"
#include "Territory.hpp"
#include "GameRule.hpp"
#include "RandomEnemyAI.hpp"
#include "GameSceneUI.hpp"
#include "SelectScene.hpp"
#include "GameScene.hpp"]

#include<vector>
#include <Siv3D.hpp>

namespace MyGame {
	class GameSceneL1 : public IScene {
	private:
		Territory m_playerTerritory;
		Territory m_neutralTerritory1;
		Territory m_neutralTerritory2;
		Territory m_enemyTerritory;
		std::vector<std::reference_wrapper<Territory>> m_territories;
		std::vector<std::reference_wrapper<Territory>> m_enemyTerritories;
		GameRule m_gameRule;
		GameSceneUI UI;
		RandomEnemyAI m_randomAI;
		Effect m_effect;
		Font m_font;
		Stopwatch m_growthTimer;
		Stopwatch m_AITimer;
		const int GROWTH_TIME = 3;
		const int AI_TIME = 4;
		bool m_isWin = false;
		bool m_isLose = false;

		void getEnemyTerritory();
		void updateGrowth();
		void enemyAttack();

	public:
		GameSceneL1(GameState& gameState)
			: IScene(gameState)
			, m_playerTerritory(Vec2(100, 300), 10, 3, Palette::Blue, Territory::Owner::Player)
			, m_neutralTerritory1(Vec2(300, 100), 5, 3, Palette::Gray, Territory::Owner::Neutral)
			, m_neutralTerritory2(Vec2(300, 400), 5, 3, Palette::Gray, Territory::Owner::Neutral)
			, m_enemyTerritory(Vec2(700, 300), 10, 3, Palette::Red, Territory::Owner::Enemy)
			, m_font(FontMethod::MSDF, 48, Typeface::Heavy)
		{
			FontAsset::Register(U"Default", 20);
			setupConnections();
			resetGame();
			m_growthTimer.start();
			m_AITimer.start();
		};

		void setupConnections();
		void resetGame();
		void update();
	};
}
