#include "GameText.hpp"

namespace MyGame {
	//自動改行
	String GameText::WrapText(const String& text, const Font& font, double maxWidth)
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

}
