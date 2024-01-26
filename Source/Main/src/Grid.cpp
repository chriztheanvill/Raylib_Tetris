#include "./Grid.hpp"
#include <fmt/color.h>

#include "Colors.hpp"

Grid::Grid(const std::string& name)
{
	m_name = name;
	// fmt::print("\n\nGrid: {}", m_name);
	for (int row { }; row < m_rows; row++)
	{
		for (int col { }; col < m_cols; col++)
		{
			//
			m_grid.at(row).at(col) = 0;
		}
	}

	m_colors = Utils::GetCellColors( );
}

auto Grid::operator=(const Grid& grid) -> Grid&
{
	// fmt::print("\nOther {}\n", grid.m_name);
	// fmt::print("\nthis {}\n", m_name);
	m_name = grid.m_name;
	m_grid = grid.m_grid;
	m_colors = grid.m_colors;
	return *this;
}

auto Grid::IsCellOutside(const int& row, const int& column) const -> bool
{
	// return !(row >= 0 && row < m_rows && column >= 0 && column < m_cols);
	return row < 0 || row >= m_rows || column < 0 || column >= m_cols;
}

auto Grid::IsCellEmpty(const int& row, const int& column) -> bool
{
	return m_grid.at(row).at(column) == 0;
}

auto Grid::ClearFullRows( ) -> int
{
	int completed = 0;
	for (int row = m_rows - 1; row >= 0; row--)
	{
		auto isFull = IsRowFull(row);
		if (isFull)
		{
			ClearRow(row);
			completed++;
		}
		else if (completed > 0)
		{
			//
			MoveRowDown(row, completed);
		}
	}
	return completed;
}

void Grid::Print( ) const
{
	for (int row { }; row < m_rows; row++)
	{
		for (int col { }; col < m_cols; col++)
		{
			fmt::print("{} ", m_grid.at(row).at(col));
		}
		fmt::print("\n");
	}
}

auto Grid::Draw( ) const -> void
{
	for (int row { }; row < m_rows; row++)
	{
		for (int col { }; col < m_cols; col++)
		{
			int cellValue = m_grid.at(row).at(col);

			DrawRectangle(
			  col * m_cellSize + m_offset,
			  row * m_cellSize + m_offset,
			  m_cellSize - 1,
			  m_cellSize - 1,
			  m_colors.at(cellValue)
			);
		}
	}
}

auto Grid::Reset( ) -> void
{
	for (int row { }; row < m_rows; row++)
	{
		for (int col { }; col < m_cols; col++) { m_grid.at(row).at(col) = 0; }
	}
}

auto Grid::IsRowFull(const int& row) -> bool
{
	for (int column { }; column < m_cols; column++)
	{
		if (m_grid.at(row).at(column) == 0) return false;
	}
	return true;
}

auto Grid::ClearRow(const int& row) -> void
{
	for (int column { }; column < m_cols; column++)
	{
		m_grid.at(row).at(column) = 0;
	}
}

auto Grid::MoveRowDown(const int& row, const int& numRows) -> void
{
	for (int column { }; column < m_cols; column++)
	{
		m_grid.at(row + numRows).at(column) = m_grid.at(row).at(column);
		m_grid.at(row).at(column) = 0;
	}
}

auto Grid::ChangeValue(const int& posX, const int& posY, const int& val) -> void
{
	m_grid.at(posX).at(posY) = val;
}
// constexpr auto Grid::GetGrid( ) const -> std::vector<std::vector<int>>
// {
// 	return m_grid;
// }
