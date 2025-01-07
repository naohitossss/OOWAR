#pragma once

#include "Territory.hpp" 

#include <Siv3D.hpp>
#include <random>
#include <vector>
#include <functional>


namespace MyGame {

	class RandomEnemyAI {
	public:
		// ランダムな兵士の数を決定する
		int randomSoldierNum(int maxSoldier);

		// ランダムに攻撃ターゲットを選択する
		Territory& randomAttack(Territory& territory);
	};

}
