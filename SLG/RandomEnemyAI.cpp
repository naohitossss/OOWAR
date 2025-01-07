#include "RandomEnemyAI.hpp"

#include <Siv3D.hpp>
#include <random>

namespace MyGame {

	int RandomEnemyAI::randomSoldierNum(int maxSoldier) {
		return Random(0, maxSoldier); // 0 から maxSoldier までのランダム値を生成
	}

	Territory& RandomEnemyAI::randomAttack(Territory& territory) {
		const auto& connections = territory.getConnections();
		if (connections.empty()) {
			throw std::runtime_error("No connections available for attack.");
		}
		// ランダムに接続先を選択して参照を返す
		return connections[Random(connections.size() - 1)].get();
	}

}
