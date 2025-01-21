#include "GameText.hpp"

namespace MyGame {
	//自動改行
	String GameText::wrapText(const String& text, const Font& font, double maxWidth)
	{
		String result;

		Array<String> lines = text.split(U'\n');

		for (auto& line : lines)
		{
			Array<String> words = line.split(U' ');

			String currentLine; 

			for (auto& word : words)
			{
				// 現在の行にさらに word を追加した場合の文字列
				String testLine = currentLine.isEmpty() ? word
					: currentLine + U' ' + word;

				// もし追加後の幅が maxWidth を超えるなら、
				// 今の行を確定させて改行を入れ、新しい行を作る
				if (font(testLine).region().w > maxWidth)
				{
					result += currentLine + U'\n';

					currentLine = word;
				}
				else
				{
					// まだ幅が大丈夫なら行を更新
					currentLine = testLine;
				}
			}
			if (!currentLine.isEmpty())
			{
				result += currentLine + U'\n';
			}
		}

		return result;
	}

	void GameText::titleTextEffect(const Vec2& penPos, double scale, const Glyph& glyph, const ColorF& color, double t)
	{
		const double angle = Sin(t * 1440_deg) * 25_deg * Saturate(1.0 - t / 0.6);
		const double y = Saturate(1 - t / 0.05) * -20.0;
		glyph.texture.scaled(scale).rotated(angle).draw(penPos + glyph.getOffset(scale) + Vec2{ 0, y }, color);
	}

	// Glyph とエフェクトの関数を組み合わせてテキストを描画
	void  GameText::drawText(const Font& font, double fontSize, const String& text, const Vec2& pos, const ColorF& color, double t,
		void f(const Vec2&, double, const Glyph&, const ColorF&, double), double characterPerSec)
	{
		const double scale = (fontSize / font.fontSize());
		Vec2 penPos = pos;
		const ScopedCustomShader2D shader{ Font::GetPixelShader(font.method()) };

		for (auto&& [i, glyph] : Indexed(font.getGlyphs(text)))
		{
			if (glyph.codePoint == U'\n')
			{
				penPos.x = pos.x;
				penPos.y += (font.height() * scale);
				continue;
			}

			const double targetTime = (i * characterPerSec);

			if (t < targetTime)
			{
				break;
			}

			f(penPos, scale, glyph, color, (t - targetTime));

			penPos.x += (glyph.xAdvance * scale);
		}
	}

}
