# include <Siv3D.hpp> // Siv3D v0.6.15

#include "Game.hpp"

void Main()
{
	// setup
	MyGame::Game game;

	// game loop
	while (System::Update())
	{
		if (!game.update()) {
			break;
		}
	}
}
