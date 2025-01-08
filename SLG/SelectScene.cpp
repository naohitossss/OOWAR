#include "SelectScene.hpp"
#include "TitleScene.hpp"
#include "Game.hpp"
#include "GameScene.hpp"
#include "GameSceneL1.hpp"

#include <Siv3D.hpp>
#include <memory>
#include <vector>
#include <random>

namespace MyGame {
	SelectScene::SelectScene(GameState& gameState) : IScene(gameState) {}

	void SelectScene::update() {
		if (SimpleGUI::Button(U"Level 1", Vec2{ 250, 300 }, 300)) {
			m_gameState.m_scene = std::move(std::make_unique<GameSceneL1>(m_gameState));
		}
	}
}
