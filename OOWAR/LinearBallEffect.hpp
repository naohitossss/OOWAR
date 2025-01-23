#pragma once

#include <Siv3D.hpp>

namespace MyGame {

	class LinearBallEffect : public IEffect
	{
	private:
		Vec2 m_startPos;    // 発射座標
		Vec2 m_endPos;      // 到達座標
		double m_duration;  // アニメーションの総時間
		double m_radius;    // ボールの半径
		ColorF m_color;     // ボールの色

	public:
		// コンストラクタ宣言にデフォルト引数を記載
		LinearBallEffect(
			const Vec2& startPos,
			const Vec2& endPos,
			const ColorF& color = Palette::White,
			double duration = 0.5,  
			double radius = 10.0           
		);

		bool update(double t)override;
	};









}
