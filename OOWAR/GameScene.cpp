#include "GameScene.hpp"

#include "Game.hpp"
#include "TitleScene.hpp"

#include <Siv3D.hpp>

namespace MyGame {
	GameScene::GameScene(GameState& gameState) : IScene(gameState) {}

	void GameScene::update() {
		if (MouseL.down()) {
			m_gameState.m_scene = std::move(std::make_unique<TitleScene>(m_gameState));
		}
	}
}
