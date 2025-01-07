#include "GameSceneL1.hpp"
#include "Game.hpp"
#include "SelectScene.hpp"
#include "RandomEnemyAI.hpp"

namespace MyGame {


	/*GameSceneL1::GameSceneL1(GameState& gameState) : IScene(gameState)
		, m_playerTerritory(Vec2(100, 300), 10, 3, Palette::Blue, Owner::Player)
		, m_neutralTerritory1(Vec2(300, 100), 5, 3, Palette::Gray, Owner::Neutral)
		, m_neutralTerritory2(Vec2(300, 400), 5, 3, Palette::Gray, Owner::Neutral)
		, m_enemyTerritory(Vec2(700, 300), 10, 3, Palette::Red, Owner::Enemy)
		, m_font(FontMethod::MSDF, 48, Typeface::Heavy)
	{
		FontAsset::Register(U"Default", 20);
		setupConnections();
		resetGame();
		m_growthTimer.start();
		m_AITimer.start();
	}*/

	void GameSceneL1::setupConnections() {
		m_playerTerritory.addConnection(m_neutralTerritory1);
		m_playerTerritory.addConnection(m_neutralTerritory2);
		m_neutralTerritory1.addConnection(m_playerTerritory);
		m_neutralTerritory1.addConnection(m_neutralTerritory2);
		m_neutralTerritory1.addConnection(m_enemyTerritory);
		m_neutralTerritory2.addConnection(m_playerTerritory);
		m_neutralTerritory2.addConnection(m_neutralTerritory1);
		m_neutralTerritory2.addConnection(m_enemyTerritory);
		m_enemyTerritory.addConnection(m_neutralTerritory1);
		m_enemyTerritory.addConnection(m_neutralTerritory2);

		m_territories = {
			m_playerTerritory,
			m_neutralTerritory1,
			m_neutralTerritory2,
			m_enemyTerritory
		};
	}

	void GameSceneL1::resetGame() {
		// 領地を初期状態に戻す
		for (auto& territory : m_territories) {
			territory.get().resetData();
		}
		setupConnections();
		m_isWin = m_isLose = false;
		m_growthTimer.restart();
		m_AITimer.restart();
	}

	void GameSceneL1::update() {
		drawUI();

		m_stage.checkGameOver(m_territories, m_isWin, m_isLose);

		if (m_isWin || m_isLose) {
			drawGameOverScreen();
			return;
		}

		for (auto& territory : m_territories) {
			territory.get().draw();
			m_stage.drawArrowsAndHandleClicks(territory);
		}

		if (m_growthTimer.s() >= GROWTH_TIME) {
			updateGrowth();
			m_growthTimer.restart();
		}

		if (m_AITimer.s() >= AI_TIME) {
			enemyAttack();
			m_AITimer.restart();
		}

		m_effect.update();
	}

	void GameSceneL1::getEnemyTerritory() {
		for (auto& territory : m_territories) {
			if (territory.get().getOwner() == Owner::Enemy) m_enemyTerritories.push_back(territory);
		}
	}
	void GameSceneL1::enemyAttack() {
		m_enemyTerritories.clear();
		getEnemyTerritory();
		for (auto& territory : m_enemyTerritories) {
			Territory& source = territory.get();
			Territory& target = m_randomAI.randomAttack(source);
			int attackSoldier = m_randomAI.randomSoldierNum(source.getSoldiers());
			m_stage.enemyAttack(source, target, attackSoldier);
		}


	}
	void GameSceneL1::drawUI() {
		if (SimpleGUI::Button(U"Reset", Vec2{ 20, 20 })) {
			resetGame();
		}
		if (SimpleGUI::Button(U"Back to Selet level", Vec2{ 20, 60 })) {
			resetGame();
		}

		const Array<std::pair<String, int>> soldierButtons = {
			{U"兵士数を1に設定", 1},
			{U"兵士数を5に設定", 5},
			{U"兵士数を10に設定", 10}
		};

		for (int i = 0; i < soldierButtons.size(); ++i) {
			if (SimpleGUI::Button(soldierButtons[i].first, Vec2{ 20, 460 + i * 40 })) {
				m_stage.setAttackSoldiers(soldierButtons[i].second);
			}
		}
	}

	void GameSceneL1::drawGameOverScreen() {
		if (m_isWin) {
			FontAsset(U"Default")(U"勝利！").drawAt(Scene::Center(), Palette::Yellow);
		}
		else if (m_isLose) {
			FontAsset(U"Default")(U"敗北...").drawAt(Scene::Center(), Palette::Red);
		}
	}

	void GameSceneL1::updateGrowth() {
		for (auto& territory : m_territories) {
			territory.get().update();
			if (territory.get().getOwner() != Owner::Neutral) {
				m_effect.add<ScoreEffect>(territory.get().getPosition(), 3, m_font);
			}
		}
	}
}
