#pragma once

#include "Territory.hpp"
#include "LinearBallEffect.hpp"

#include<vector>
#include <Siv3D.hpp>

namespace MyGame {
	struct ScoreEffect : IEffect {
	public:
		Vec2 m_start;
		int32 m_score;
		Font m_font;

		ScoreEffect(const Vec2& start, int32 score, const Font& font)
			: m_start{ start }
			, m_score{ score }
			, m_font{ font } {}

		bool update(double t) override {
			// 色の設定 (スコアに応じて色が変化)
			const HSV color{ (180 - m_score * 1.8), 1.0 - (t * 2.0) };
			String text = U"+" + ToString(m_score);
			// スコアを指定された位置に描画
			m_font(text).drawAt(m_start.movedBy(0, t * -120), color);
			// エフェクトの生存期間を 0.5 秒に設定
			return (t < 0.5);
		}
	};

	class GameRule{
	private:
		int m_attackSoldiers; // 攻撃に使用する兵士数

	public:
		// コンストラクタ
		GameRule(int initialAttackSoldiers = 1);

		// 領地間の攻撃処理
		void attack(Territory& source, Territory& target);

		// 敵の攻撃処理
		void enemyAttack(Territory& source, Territory& target, int attackSoldiers, Effect& effect);

		// 矢印の描画とクリック処理
		void drawArrowsAndHandleClicks(Territory& territory, Effect& effect);

		// ゲームオーバー判定
		void checkGameOver(const std::vector<std::reference_wrapper<Territory>>& territories, bool& isWin, bool& isLose);

		// 攻撃に使用する兵士数のセッターとゲッター
		void setAttackSoldiers(int value);
		int getAttackSoldiers() const;
	};

}

