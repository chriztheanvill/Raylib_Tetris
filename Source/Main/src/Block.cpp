#include "./Block.hpp"
#include <fmt/core.h>

Block::Block( )
{
	m_cellSize = 30;
	m_rotationState = 0;
	m_rowOffset = 0;
	m_columnOffset = 0;
	Move(0, 3);
}

auto Block::Draw(const int& offsetX, const int& offsetY) -> void
{
	std::vector<Position> tiles = GetCellPositions( );
	for (const Position& item : tiles)
	{
		DrawRectangle(
		  item.m_colum * m_cellSize + offsetX,
		  item.m_row * m_cellSize + offsetY,
		  m_cellSize - 1,
		  m_cellSize - 1,
		  m_colors.at(m_id)
		);
	}
}

auto Block::Move(const int& rows, const int& columns) -> void
{
	m_rowOffset += rows;
	m_columnOffset += columns;
}

auto Block::Rotate( ) -> void
{
	m_rotationState++;
	if (m_rotationState == m_cells.size( )) m_rotationState = 0;
}

auto Block::UndoRotation( ) -> void
{
	m_rotationState--;
	if (m_rotationState == -1) { m_rotationState = m_cells.size( ) - 1; }
}

auto Block::GetCellPositions( ) -> std::vector<Position>
{
	std::vector<Position> tiles = m_cells[m_rotationState];
	std::vector<Position> movedTiles;

	for (const auto& v : tiles)
	{
		Position newPos {
			v.m_row + m_rowOffset,
			v.m_colum + m_columnOffset	 //
		};
		movedTiles.push_back(newPos);
	}

	return movedTiles;
}