#include "Territory.hpp"

namespace MyGame {

	// 更新処理
	void Territory::update() {
		if (m_owner != Owner::Neutral) {
			m_soldiers += m_growthRate;
		}
	}

	// リセット処理
	void Territory::resetData() {
		m_position = m_initialPosition;
		m_soldiers = m_initialSoldiers;
		m_growthRate = m_initialGrowthRate;
		m_color = m_initialColor;
		m_owner = m_initialOwner;
		m_connections.clear(); // 接続をリセット
	}

	// 接続を追加
	void Territory::addConnection(Territory& target) {
		m_connections.push_back(target);
	}

	// 描画
	void Territory::draw() const {
		s3d::Circle(m_position, 40).draw(m_color);
		s3d::FontAsset(U"Default")(U"{:02}"_fmt(m_soldiers)).drawAt(m_position, s3d::Palette::White);
	}

	// ゲッター・セッター
	const s3d::Vec2& Territory::getPosition() const { return m_position; }
	int Territory::getSoldiers() const { return m_soldiers; }
	void Territory::setSoldiers(int value) { m_soldiers = value; }
	const s3d::Color& Territory::getColor() const { return m_color; }
	void Territory::setColor(const s3d::Color& color) { m_color = color; }
	Territory::Owner Territory::getOwner() const { return m_owner; }
	void Territory::setOwner(Owner owner) { m_owner = owner; }
	const std::vector<std::reference_wrapper<Territory>>& Territory::getConnections() const { return m_connections; }

}
