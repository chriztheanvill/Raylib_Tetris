#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <raylib.h>

class Grid
{
	const int m_offset { 11 };
	const int m_rows { 20 };
	const int m_cols { 10 };
	const int m_cellSize { 30 };

	std::string m_name;

	std::vector<std::vector<int>> m_grid { //
										   static_cast<size_t>(m_rows),
										   std::vector<int>(m_cols)
	};
	std::vector<Color> m_colors { };

	auto IsRowFull(const int& row) -> bool;
	auto ClearRow(const int& row) -> void;
	auto MoveRowDown(const int& row, const int& numRows) -> void;

  public:
	Grid(const std::string& name = "empty");
	auto operator=(const Grid& grid) -> Grid&;

	[[nodiscard]] auto IsCellOutside(const int& row, const int& column) const
	  -> bool;
	auto IsCellEmpty(const int& row, const int& column) -> bool;
	auto ClearFullRows( ) -> int;
	auto Print( ) const -> void;
	auto Draw( ) const -> void;
	auto Reset( ) -> void;
	auto SetGrid(const std::vector<std::vector<int>>& t_grid) -> void
	{
		m_grid = t_grid;
	}
	auto GetGrid( ) -> std::vector<std::vector<int>>& { return m_grid; }
	auto ChangeValue(const int& posX, const int& posY, const int& val) -> void;

	// [[nodiscard]] consteval auto dSome( ) -> int { return 1; }
};

#endif	 // GRID_HPP
