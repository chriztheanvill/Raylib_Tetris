#ifndef GAME_HPP
#define GAME_HPP

#include "./Grid.hpp"
#include "./Blocks.cpp"

class Game
{
	Block m_currentBlock;
	Block m_nextBlock;

	std::vector<Block> m_blocks;
	Grid m_grid;

	Sound m_rotateSound;
	Sound m_clearSound;

	auto IsBlockOutside( ) -> bool;
	auto RotateBlock( ) -> void;
	auto LockBlock( ) -> void;
	auto BlockFits( ) -> bool;
	auto Reset( ) -> void;
	auto UpdateScore(const int& linesCleared, const int& moveDownPoints)
	  -> void;

  public:
	Game( );
	~Game( );

	bool m_gameOver { };
	int m_score;

	Music m_music;

	auto GetRandomBlock( ) -> Block;
	auto GetAllBlocks( ) -> std::vector<Block>;
	auto Draw( ) -> void;
	auto HandleInput( ) -> void;

	auto MoveBlockLeft( ) -> void;
	auto MoveBlockRight( ) -> void;
	auto MoveBlockDown( ) -> void;
};

#endif	 // GAME_HPP
