#pragma once

#include "IScene.hpp"
#include "Territory.hpp"
#include "GameRule.hpp"
#include "RandomEnemyAI.hpp"
#include "GameSceneUI.hpp"
#include "TitleScene.hpp"
#include "GameScene.hpp"
#include "GameText.hpp"

#include<vector>
#include <Siv3D.hpp>

namespace MyGame {
	class TutorialScene : public IScene {
	private:
		Territory m_playerTerritory;
		Territory m_neutralTerritory1;
		Territory m_enemyTerritory;
		std::vector<std::reference_wrapper<Territory>> m_territories;
		std::vector<std::reference_wrapper<Territory>> m_enemyTerritories;
		GameRule m_gameRule;
		GameSceneUI UI;
		RandomEnemyAI m_randomAI;
		GameText gameText;
		Effect m_effect;
		Font m_font;
		Font tutorialTextfont;
		Vec2 tutorialTextPos;
		Stopwatch m_growthTimer;
		Stopwatch m_AITimer;
		const int GROWTH_TIME = 3;
		const int AI_TIME = 4;
		bool m_isWin = false;
		bool m_isLose = false;

		void getEnemyTerritory();
		void enemyAttack();
		void updateGrowth();
		void drawArrow(const Vec2& startPos, const Vec2& endPos);

		//チュートリアルステップ
		struct TutorialStep
		{
			String text;        
			Vec2 arrowStartPos; // 矢印の始点
			Vec2 arrowEndPos;   // 矢印の終点
		};
		
		std::vector<TutorialStep> m_steps;

		// 現在表示中のチュートリアルステップ
		size_t m_currentStep = 0;

	public:
		TutorialScene(GameState& gameState)
			: IScene(gameState)
			, m_playerTerritory(Vec2(100, 300), 10, 7, Palette::Blue, Territory::Owner::Player)
			, m_neutralTerritory1(Vec2(300, 100), 5, 3, Palette::Gray, Territory::Owner::Neutral)
			, m_enemyTerritory(Vec2(700, 300), 10, 3, Palette::Red, Territory::Owner::Enemy)
			, m_font(FontMethod::MSDF, 48, Typeface::Heavy)
			, tutorialTextfont( 25 )
			, tutorialTextPos( 300,400 )
		{
			FontAsset::Register(U"Default", 20);
			setupConnections();
			resetGame();
			m_growthTimer.pause();
			m_AITimer.pause();
			m_steps = {
			{U"In this game, you need to take all of the clycle's control to win. If all your clycle is taken, you lose." },
			{U"The Blue 〇 is belongs to you.",m_playerTerritory.getPosition(), tutorialTextPos },
			{U"And the gray 〇 don't belong to anyone.", m_neutralTerritory1.getPosition(), tutorialTextPos },
			{U"The Red 〇 is belongs to your Enemy",m_enemyTerritory.getPosition(), tutorialTextPos},
			{U"You can 'clic' the green '→' to attack or move your ● to other one",m_playerTerritory.getPosition() + (m_playerTerritory.getPosition() - m_neutralTerritory1.getPosition()).normalized() * -200, tutorialTextPos},
			{U"one 'clic' move only one ●.But you can use the Bottom to change the number.",Vec2(40, 460), tutorialTextPos},
			{U"Now pleace take concltro of the gray 〇"},
			{U"Good job !"},
			{U"Every 〇 will get their ● per 3 secend.That mean you have more territorys you have more adventage"},
			{U"But be careful.You enemy also can attack or move."},
			{U"Now lets try to win this game"},
			{U"You can reset the game to restart the tutorial or 'Back to Title'."}
			};
		};

		void setupConnections();
		void resetGame();
		void update();
	};
}
