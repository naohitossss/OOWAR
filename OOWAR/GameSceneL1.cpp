#include "GameSceneL1.hpp"

namespace MyGame {

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
		UI.drawGameUI();

		if (SimpleGUI::Button(U"Reset", Vec2{ 20, 20 })) {
			resetGame();
		}
		if (SimpleGUI::Button(U"Back to Selet level", Vec2{ 20, 60 })) {
			m_gameState.m_scene = std::move(std::make_unique<SelectScene>(m_gameState));
		}

		m_gameRule.checkGameOver(m_territories, m_isWin, m_isLose);

		if (m_isWin || m_isLose) {
			UI.drawGameOverScreen(m_isWin,m_isLose);
			return;
		}

		for (auto& territory : m_territories) {
			territory.get().draw();
			m_gameRule.drawArrowsAndHandleClicks(territory,m_effect);
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
			if (territory.get().getOwner() == Territory::Owner::Enemy) m_enemyTerritories.push_back(territory);
		}
	}
	void GameSceneL1::enemyAttack() {
		m_enemyTerritories.clear();
		getEnemyTerritory();
		for (auto& territory : m_enemyTerritories) {
			Territory& source = territory.get();
			Territory& target = m_randomAI.randomAttack(source);
			int attackSoldier = m_randomAI.randomSoldierNum(source.getSoldiers());
			m_gameRule.enemyAttack(source, target, attackSoldier, m_effect);
		}


	}

	void GameSceneL1::updateGrowth() {
		for (auto& territory : m_territories) {
			territory.get().update();
			if (territory.get().getOwner() != Territory::Owner::Neutral) {
				m_effect.add<ScoreEffect>(territory.get().getPosition(), 3, m_font);
			}
		}
	}
}
