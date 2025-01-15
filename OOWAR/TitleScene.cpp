#include "TitleScene.hpp"

namespace MyGame {
	TitleScene::TitleScene(GameState& gameState) : IScene(gameState) {}

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
