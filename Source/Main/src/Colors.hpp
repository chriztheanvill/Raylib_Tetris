#ifndef COLORS_HPP
#define COLORS_HPP

#include <raylib.h>
#include <vector>

namespace Utils
{
	// extern const Color greyDark;
	// extern const Color green;
	// extern const Color red;
	// extern const Color orange;
	// extern const Color yellow;
	// extern const Color purple;
	// extern const Color cyan;
	// extern const Color blue;

	const Color greyDark = { 26, 31, 40, 255 };
	const Color green = { 47, 230, 23, 255 };
	const Color red = { 232, 18, 18, 255 };
	const Color orange = { 226, 116, 17, 255 };
	const Color yellow = { 237, 234, 4, 255 };
	const Color purple = { 166, 0, 247, 255 };
	const Color cyan = { 21, 204, 209, 255 };
	const Color blue = { 13, 64, 216, 255 };
	const Color blueLight = { 59, 85, 162, 255 };
	const Color blueDark = { 44, 44, 127, 255 };

	auto GetCellColors( ) -> std::vector<Color>;

}	// namespace Utils

#endif	 // COLORS_HPP
