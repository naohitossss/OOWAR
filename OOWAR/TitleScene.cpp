#include "TitleScene.hpp"

namespace MyGame {
	TitleScene::TitleScene(GameState& gameState) : IScene(gameState) {}

	/*void TitleScene::TitleTextEffect(const Vec2& penPos, double scale, const Glyph& glyph, const ColorF& color, double t)
	{
		const double angle = Sin(t * 1440_deg) * 25_deg * Saturate(1.0 - t / 0.6);
		const double y = Saturate(1 - t / 0.05) * -20.0;
		glyph.texture.scaled(scale).rotated(angle).draw(penPos + glyph.getOffset(scale) + Vec2{ 0, y }, color);
	}*/

	void TitleScene::update() {
		if (SimpleGUI::Button(U"Turial", Vec2{ 250, 200 }, 300)) {
			m_gameState.m_scene = std::move(std::make_unique<TutorialScene>(m_gameState));
		}
		if (SimpleGUI::Button(U"Select level", Vec2{ 250, 300 }, 300)) {
			m_gameState.m_scene = std::move(std::make_unique<SelectScene>(m_gameState));
		}
		if (SimpleGUI::Button(U"Eixt", Vec2{ 250, 400 }, 300)) {
			m_gameState.m_scene = nullptr;
		}
	}
}
