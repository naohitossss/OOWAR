#include "GameRule.hpp"

namespace MyGame {

	GameRule::GameRule(int initialAttackSoldiers)
		: m_attackSoldiers(initialAttackSoldiers) {}

	void GameRule::attack(Territory& source, Territory& target) {
		if (source.getSoldiers() < m_attackSoldiers) {
			return;
		}
		

		source.setSoldiers(source.getSoldiers() - m_attackSoldiers);

		if (source.getColor() != target.getColor()) {
			if (target.getSoldiers() > 0) {
				target.setSoldiers(target.getSoldiers() - m_attackSoldiers);

				if (target.getSoldiers() <= 0) {
					target.setColor(source.getColor());
					target.setOwner(source.getOwner());
					target.setSoldiers(-target.getSoldiers());
				}
			}
		}
		else {
			target.setSoldiers(target.getSoldiers() + m_attackSoldiers);
		}
	}

	void GameRule::enemyAttack(Territory& source, Territory& target, int attackSoldiers, Effect& effect) {
		if (source.getSoldiers() < attackSoldiers) {
			return;
		}
		effect.add<LinearBallEffect>(source.getPosition(), target.getPosition(), source.getColor());

		source.setSoldiers(source.getSoldiers() - attackSoldiers);

		if (source.getColor() != target.getColor()) {
			if (target.getSoldiers() > 0) {
				target.setSoldiers(target.getSoldiers() - attackSoldiers);

				if (target.getSoldiers() <= 0) {
					target.setColor(source.getColor());
					target.setOwner(source.getOwner());
					target.setSoldiers(-target.getSoldiers());
				}
			}
		}
		else {
			target.setSoldiers(target.getSoldiers() + attackSoldiers);
		}
	}

	void GameRule::drawArrowsAndHandleClicks(Territory& territory,Effect& effect) {
		for (auto& targetRef : territory.getConnections()) {
			Territory& target = targetRef.get();
			Vec2 direction = (target.getPosition() - territory.getPosition()).normalized();
			double length = territory.getPosition().distanceFrom(target.getPosition()) - 40;

			Vec2 start = territory.getPosition() + (direction * (length / 2 + 25));
			Vec2 end = territory.getPosition() + (direction * (length - 5));

			Line arrowLine{ start, end };

			if (territory.getOwner() == Territory::Owner::Player) {
				arrowLine.drawArrow(30, SizeF{ 20, 40 }, Palette::Green);

				// 線分の周りに幅を持たせた当たり判定を作成
				if (Geometry2D::Distance(Cursor::PosF(), arrowLine) < 10.0) {
					Cursor::RequestStyle(CursorStyle::Hand);
					if (MouseL.down() && territory.getSoldiers() >= m_attackSoldiers) {
						attack(territory, target);
						effect.add<LinearBallEffect>(territory.getPosition(), target.getPosition(), territory.getColor());
					}
				}
			}
			else {
				arrowLine.drawArrow(30, SizeF{ 20, 40 }, Palette::White);
			}
		}
	}

	void GameRule::checkGameOver(const std::vector<std::reference_wrapper<Territory>>& territories, bool& isWin, bool& isLose) {
		bool playerExists = false;
		bool enemyExists = false;

		for (const auto& territory : territories) {
			if (territory.get().getOwner() == Territory::Owner::Player) playerExists = true;
			if (territory.get().getOwner() == Territory::Owner::Enemy) enemyExists = true;
		}

		isWin = !enemyExists;
		isLose = !playerExists;
	}

	void GameRule::setAttackSoldiers(int value) {
		m_attackSoldiers = value;
	}

	int GameRule::getAttackSoldiers() const {
		return m_attackSoldiers;
	}

}
