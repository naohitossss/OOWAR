#pragma once

#include <Siv3D.hpp>
#include <vector>
#include <functional>
namespace MyGame {
	

	class Territory {

	public:
		enum class Owner { Player, Enemy, Neutral };
	private:
		// メンバ変数
		s3d::Vec2 m_position;
		int m_soldiers;
		int m_growthRate;
		s3d::Color m_color;
		Owner m_owner;
		std::vector<std::reference_wrapper<Territory>> m_connections;

		// 初期値を保存するメンバ変数
		s3d::Vec2 m_initialPosition;
		int m_initialSoldiers;
		int m_initialGrowthRate;
		s3d::Color m_initialColor;
		Owner m_initialOwner;

	public:
		// コンストラクタ
		Territory(s3d::Vec2 pos, int soldiers, int growth, s3d::Color color, Owner owner);

		void update();

		// リセット処理
		void resetData();

		// 接続を追加
		void addConnection(Territory& target);

		// 描画
		void draw() const;

		// ゲッター・セッター
		const s3d::Vec2& getPosition() const;
		int getSoldiers() const;
		void setSoldiers(int value);
		const s3d::Color& getColor() const;
		void setColor(const s3d::Color& color);
		Owner getOwner() const;
		void setOwner(Owner owner);
		const std::vector<std::reference_wrapper<Territory>>& getConnections() const;
	};

}
