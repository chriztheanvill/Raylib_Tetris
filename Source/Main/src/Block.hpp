#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>
#include <map>
#include "./Position.hpp"
#include "./Colors.hpp"

class Block
{
	int m_cellSize;
	int m_rotationState;
	int m_rowOffset;
	int m_columnOffset;

	std::vector<Color> m_colors { Utils::GetCellColors( ) };

  public:
	Block( );

	auto Draw(const int& offsetX, const int& offsetY) -> void;
	auto Move(const int& rows, const int& columns) -> void;
	auto Rotate( ) -> void;
	auto UndoRotation( ) -> void;

	int m_id;
	std::map<int, std::vector<Position>> m_cells;

	auto GetCellPositions( ) -> std::vector<Position>;
};

#endif	 // BLOCK_HPP
