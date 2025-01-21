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
		const double t = textStopwatch.sF();
		//gametext.drawText(
		//titleTextfont,          // フォント
		//30,                     // 文字サイズ(ピクセル)
		//titleText,              // 描画する文字列
		//Vec2{ 40, 40 },         // 描画座標
		//Palette::Skyblue,       // 色
		//t,                      // エフェクトに渡す経過時間
		//gametext.titleTextEffect, // エフェクト関数
		//0.1                     // 1文字あたり0.1秒で表示（タイピング風速度）
		//);
	}
}
