#include "Position.hpp"

Position::Position( )
	: Position(0, 0)
{
}

Position::Position(int row, int column)
{
	m_row = row;
	m_colum = column;
}
