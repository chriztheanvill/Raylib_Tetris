#include "./Game.hpp"
#include <fmt/core.h>
#include <random>

Game::Game( )
{
	m_grid = Grid("Other");
	m_blocks = GetAllBlocks( );
	m_currentBlock = GetRandomBlock( );
	m_nextBlock = GetRandomBlock( );
	m_score = 0;
	InitAudioDevice( );

	m_music = LoadMusicStream("assets/sounds/music.mp3");
	m_rotateSound = LoadSound("assets/sounds/rotate.mp3");
	m_clearSound = LoadSound("assets/sounds/clear.mp3");

	PlayMusicStream(m_music);
	SetMusicVolume(m_music, .1);
	SetSoundVolume(m_rotateSound, .3);
	SetSoundVolume(m_clearSound, .1);
}

Game::~Game( )
{
	UnloadSound(m_rotateSound);
	UnloadSound(m_clearSound);
	UnloadMusicStream(m_music);
	CloseAudioDevice( );
}

auto Game::GetRandomBlock( ) -> Block
{
	if (m_blocks.empty( )) { m_blocks = GetAllBlocks( ); }

	int randomIdex = rand( ) % static_cast<int>(m_blocks.size( ));
	Block block = m_blocks[randomIdex];
	m_blocks.erase(m_blocks.begin( ) + randomIdex);

	return block;
}

auto Game::GetAllBlocks( ) -> std::vector<Block>
{
	return			   //
	  {
		  IBlock( ),   //
		  JBlock( ),   //
		  LBlock( ),   //
		  OBlock( ),   //
		  SBlock( ),   //
		  TBlock( ),   //
		  ZBlock( )	   //
	  };
}

auto Game::Draw( ) -> void
{
	m_grid.Draw( );
	m_currentBlock.Draw(11, 11);
	switch (m_nextBlock.m_id)
	{
		case 3:	 m_nextBlock.Draw(255, 290); break;
		case 4:	 m_nextBlock.Draw(255, 280); break;
		default: m_nextBlock.Draw(270, 270); break;
	}
}

auto Game::HandleInput( ) -> void
{
	int keyPressed = GetKeyPressed( );
	if (m_gameOver && keyPressed != 0)
	{
		m_gameOver = false;
		Reset( );
	}
	switch (keyPressed)
	{
		case KEY_LEFT:	MoveBlockLeft( ); break;
		case KEY_RIGHT: MoveBlockRight( ); break;
		case KEY_DOWN:
			MoveBlockDown( );
			UpdateScore(0, 1);
			break;
		case KEY_UP: RotateBlock( ); break;
		default:	 break;
	}
}

auto Game::MoveBlockLeft( ) -> void
{
	if (m_gameOver) return;
	m_currentBlock.Move(0, -1);
	if (IsBlockOutside( ) || !BlockFits( )) m_currentBlock.Move(0, 1);
}

auto Game::MoveBlockRight( ) -> void
{
	if (m_gameOver) return;
	m_currentBlock.Move(0, 1);
	if (IsBlockOutside( ) || !BlockFits( )) m_currentBlock.Move(0, -1);
}

auto Game::MoveBlockDown( ) -> void
{
	if (m_gameOver) return;
	m_currentBlock.Move(1, 0);
	if (IsBlockOutside( ) || !BlockFits( ))
	{
		m_currentBlock.Move(-1, 0);
		LockBlock( );
	}
}

auto Game::RotateBlock( ) -> void
{
	if (m_gameOver) return;
	m_currentBlock.Rotate( );
	if (IsBlockOutside( ) || !BlockFits( )) m_currentBlock.UndoRotation( );
	else PlaySound(m_rotateSound);
}

auto Game::LockBlock( ) -> void
{
	std::vector<Position> tiles = m_currentBlock.GetCellPositions( );
	for (const Position& eachTile : tiles)
	{
		m_grid.GetGrid( ).at(eachTile.m_row).at(eachTile.m_colum)
		  = m_currentBlock.m_id;
	}
	m_currentBlock = m_nextBlock;

	if (!BlockFits( )) { m_gameOver = true; }

	m_nextBlock = GetRandomBlock( );

	int rowsCleared = m_grid.ClearFullRows( );
	if (rowsCleared > 0)
	{
		PlaySound(m_clearSound);
		UpdateScore(rowsCleared, 0);
	}
}

auto Game::BlockFits( ) -> bool
{
	std::vector<Position> tiles = m_currentBlock.GetCellPositions( );

	for (const Position& eachTile : tiles)
	{
		if (!m_grid.IsCellEmpty(eachTile.m_row, eachTile.m_colum)) return false;
	}
	return true;
}

auto Game::Reset( ) -> void
{
	m_grid.Reset( );
	m_blocks = GetAllBlocks( );
	m_currentBlock = GetRandomBlock( );
	m_nextBlock = GetRandomBlock( );
	m_score = 0;
}

auto Game::UpdateScore(const int& linesCleared, const int& moveDownPoints)
  -> void
{
	switch (linesCleared)
	{
		case 1:			m_score += 100; break;
		case 2:			m_score += 300; break;
		case 3:			m_score += 500; break;
		case 5:			m_score += 1000; break;
		case 6 ... 999: m_score += 2000; break;
		default:		break;
	}
	m_score += moveDownPoints;
}

auto Game::IsBlockOutside( ) -> bool
{
	std::vector<Position> tiles = m_currentBlock.GetCellPositions( );
	for (const Position& eachTile : tiles)
	{
		if (m_grid.IsCellOutside(eachTile.m_row, eachTile.m_colum)) return true;
	}
	return false;
}