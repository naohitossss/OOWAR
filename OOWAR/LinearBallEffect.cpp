# include "LinearBallEffect.hpp"

namespace MyGame {

	LinearBallEffect::LinearBallEffect(
		const Vec2& startPos,
		const Vec2& endPos,
		const ColorF& color,
		double duration,
		double radius
	)
		: m_startPos{ startPos }
		, m_endPos{ endPos }
		, m_color{ color }
		, m_duration{ duration }
		, m_radius{ radius }
	{
	}

	bool LinearBallEffect::update(double t)
		{
			double progress = t / m_duration;

			// 終了したら消滅
			/*if (progress >= 1.0)
			{
				return false;
			}*/

			// 線形補間で現在位置を計算
			Vec2 position = m_startPos.lerp(m_endPos, progress);
			FontAsset(U"Default")(U"1000").drawAt(Scene::Center(), Palette::Yellow);

			// ボールを描画
			Circle{ position, m_radius }.draw(m_color);

			return true; // エフェクトは存続
		}
	

}
