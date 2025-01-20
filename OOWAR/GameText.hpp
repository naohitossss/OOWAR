#pragma once

#include <Siv3D.hpp>

namespace MyGame {


	class GameText {
	public:
		String WrapText(const String& text, const Font& font, double maxWidth);

	};
}
