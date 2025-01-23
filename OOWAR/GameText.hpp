#pragma once

#include <Siv3D.hpp>
#include <functional>


namespace MyGame {


	class GameText {
	public:
		String wrapText(const String& text, const Font& font, double maxWidth);
		static void titleTextEffect(const Vec2& penPos, double scale, const Glyph& glyph, const ColorF& color, double t);
		void drawText(const Font& font, double fontSize, const String& text, const Vec2& pos, const ColorF& color, double t,
	void f(const Vec2&, double, const Glyph&, const ColorF&, double),
	double characterPerSec);
	};

}
