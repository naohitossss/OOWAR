#include "TutorialScene.hpp"

namespace MyGame {

	void TutorialScene::setupConnections() {
		m_playerTerritory.addConnection(m_neutralTerritory1);
		m_neutralTerritory1.addConnection(m_playerTerritory);
		m_neutralTerritory1.addConnection(m_enemyTerritory);
		m_enemyTerritory.addConnection(m_neutralTerritory1);

		m_territories = {
			m_playerTerritory,
			m_neutralTerritory1,
			m_enemyTerritory
		};
	}

	void TutorialScene::resetGame() {
		// 領地を初期状態に戻す
		for (auto& territory : m_territories) {
			territory.get().resetData();
		}
		setupConnections();
		m_isWin = m_isLose = false;
		m_growthTimer.restart();
		m_AITimer.restart();
	}

	void TutorialScene::drawArrow(const Vec2& startPos, const Vec2& endPos)
	{
		if (startPos == endPos) return;
		Vec2 direction = (endPos - startPos).normalized();
		s3d::Line arrowLine{ startPos + (direction * 200), startPos + (direction * 50) };
		arrowLine.drawArrow(30, SizeF{20, 40}, Palette::Red);
	}

	void TutorialScene::update() {

		UI.drawGameUI();

		if (SimpleGUI::Button(U"Reset", Vec2{ 20, 20 })) {
			resetGame();
		}
		if (SimpleGUI::Button(U"Back to Title", Vec2{ 20, 60 })) {
			m_gameState.m_scene = std::make_unique<TitleScene>(m_gameState);
		}

		// ステップの範囲チェック
		if (m_currentStep >= m_steps.size())
		{
			m_currentStep = m_steps.size() - 1; // 範囲外なら最後のステップに固定
		}

		// チュートリアル進行
		if (m_currentStep != 6 && m_currentStep != 10 && m_currentStep < m_steps.size())
		{
			if (SimpleGUI::Button(U"Next Tutorial", Vec2{ 600, 550 }))
			{
				if (m_currentStep + 1 < m_steps.size())
				{
					if (m_currentStep == 8)
					{
						m_growthTimer.start();
					}
					m_currentStep++;
				}
			}
		}
		else if (m_currentStep == 6)
		{
			if (m_neutralTerritory1.getOwner() == Territory::Owner::Player)
			{
				m_currentStep++;
			}
		}
		else if (m_currentStep == 10 && !m_AITimer.isRunning())
		{
			m_AITimer.start();
		}

		// テキスト描画と矢印描画
		if (m_currentStep < m_steps.size())
		{
			tutorialTextfont(gameText.wrapText(m_steps[m_currentStep].text, tutorialTextfont, 500)).draw(tutorialTextPos);
			drawArrow(m_steps[m_currentStep].arrowStartPos, m_steps[m_currentStep].arrowEndPos);
		}

		// ゲーム進行
		m_gameRule.checkGameOver(m_territories, m_isWin, m_isLose);

		if (m_isWin || m_isLose) {
			UI.drawGameOverScreen(m_isWin, m_isLose);
			m_currentStep = m_steps.size() - 1; // 最後のステップに固定
			return;
		}

		for (auto& territory : m_territories) {
			territory.get().draw();
			m_gameRule.drawArrowsAndHandleClicks(territory);
		}

		if (m_growthTimer.isRunning() && m_growthTimer.s() >= GROWTH_TIME) {
			updateGrowth();
			m_growthTimer.restart();
		}

		if (m_AITimer.isRunning() && m_AITimer.s() >= AI_TIME) {
			enemyAttack();
			m_AITimer.restart();
		}

		m_effect.update();
	}


	void TutorialScene::getEnemyTerritory() {
		for (auto& territory : m_territories) {
			if (territory.get().getOwner() == Territory::Owner::Enemy) m_enemyTerritories.push_back(territory);
		}
	}
	void TutorialScene::enemyAttack() {
		m_enemyTerritories.clear();
		getEnemyTerritory();
		for (auto& territory : m_enemyTerritories) {
			Territory& source = territory.get();
			Territory& target = m_randomAI.randomAttack(source);
			int attackSoldier = m_randomAI.randomSoldierNum(source.getSoldiers());
			m_gameRule.enemyAttack(source, target, attackSoldier);
		}


	}




	void TutorialScene::updateGrowth() {
		for (auto& territory : m_territories) {
			territory.get().update();
			if (territory.get().getOwner() != Territory::Owner::Neutral) {
				m_effect.add<ScoreEffect>(territory.get().getPosition(), 3, m_font);
			}
		}
	}
}
