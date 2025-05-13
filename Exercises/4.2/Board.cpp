// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Board.h"
#include "Random.h"

BoardState::BoardState()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			mBoard[i][j] = Empty;
		}
	}
}

std::vector<BoardState*> BoardState::GetPossibleMoves(SquareState player) const
{
	std::vector<BoardState*> retVal;

	// For each column, find if a move is possible
	for (int col = 0; col < 7; col++)
	{
		for (int row = 5; row >= 0; row--)
		{
			if (mBoard[row][col] == BoardState::Empty)
			{
				retVal.emplace_back(new BoardState(*this));
				retVal.back()->mBoard[row][col] = player;
				break;
			}
		}
	}

	return retVal;
}

bool BoardState::IsTerminal() const
{
	// Is the board full?
	if (IsFull())
	{
		return true;
	}

	// Is there a four-in-a-row?
	int fourInRow = GetFourInARow();
	if (fourInRow != 0)
	{
		return true;
	}

	return false;
}

float BoardState::GetScore() const
{
	// If the board is full, the score is 0
	if (IsFull())
	{
		return 0.0f;
	}

	// Is there a four-in-a-row?
	int fourInRow = GetFourInARow();
	if (fourInRow != 0)
	{
		return static_cast<float>(fourInRow);
	}

	return CalculateHeuristic();
}

bool BoardState::IsFull() const
{
	bool isFull = true;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (mBoard[i][j] == Empty)
			{
				isFull = false;
			}
		}
	}

	return isFull;
}

int BoardState::GetFourInARow() const
{
	// Returns -1 if yellow wins, 1 if red wins, 0 otherwise

	// Check if there's a row with four in a row
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (mBoard[row][col] == mBoard[row][col + 1] &&
				mBoard[row][col] == mBoard[row][col + 2] &&
				mBoard[row][col] == mBoard[row][col + 3])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1;
				}
			}
		}
	}

	// Check if there's a column with four in a row
	for (int col = 0; col < 7; col++)
	{
		for (int row = 0; row < 3; row++)
		{
			if (mBoard[row][col] == mBoard[row + 1][col] &&
				mBoard[row][col] == mBoard[row + 2][col] &&
				mBoard[row][col] == mBoard[row + 3][col])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1;
				}
			}
		}
	}

	// Check if there's a right diagonal four in a row
	for (int col = 0; col < 4; col++)
	{
		for (int row = 0; row < 3; row++)
		{
			if (mBoard[row][col] == mBoard[row + 1][col + 1] &&
				mBoard[row][col] == mBoard[row + 2][col + 2] &&
				mBoard[row][col] == mBoard[row + 3][col + 3])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1;
				}
			}
		}
	}

	// Check if there's a left diagonal for in a row
	for (int col = 0; col < 4; col++)
	{
		for (int row = 3; row < 6; row++)
		{
			if (mBoard[row][col] == mBoard[row - 1][col + 1] &&
				mBoard[row][col] == mBoard[row - 2][col + 2] &&
				mBoard[row][col] == mBoard[row - 3][col + 3])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

float BoardState::AlphaBeta(int depth, float alpha, float beta, bool isMaximizing) const
{
	if (depth == 0 || IsTerminal())
		return GetScore();

	std::vector<BoardState*> moves = GetPossibleMoves(isMaximizing ? Red : Yellow);
	float bestScore = isMaximizing ? -FLT_MAX : FLT_MAX;

	for (auto move : moves)
	{
		float score = move->AlphaBeta(depth - 1, alpha, beta, !isMaximizing);

		if (isMaximizing)
		{
			bestScore = std::max(bestScore, score);
			alpha = std::max(alpha, bestScore);
		}
		else
		{
			bestScore = std::min(bestScore, score);
			beta = std::min(beta, bestScore);
		}

		delete move;

		if (beta <= alpha)
			break; // pruning
	}

	return bestScore;
}


float BoardState::CalculateHeuristic() const
{
	const SquareState cpu = Red;
	const SquareState player = Yellow;

	float score = 0;

	// Analizza tutte le righe (orizzontali)
	for (int row = 0; row < 6; ++row)
	{
		for (int col = 0; col <= 7 - 4; ++col) // finestre da 4
		{
			std::vector<SquareState> window = {
				mBoard[row][col],
				mBoard[row][col + 1],
				mBoard[row][col + 2],
				mBoard[row][col + 3]
			};
			if (col == 4)
				score += 600; //aumenti il valore se ci troviamo nella cella centrale che è la più forte
			score += ScoreWindow(window, cpu, player);
		}
	}

	// Colonne (verticali)
	for (int col = 0; col < 7; ++col)
	{
		for (int row = 0; row <= 6 - 4; ++row)
		{
			std::vector<SquareState> window = {
				mBoard[row][col],
				mBoard[row + 1][col],
				mBoard[row + 2][col],
				mBoard[row + 3][col]
			};
			if (col == 4)
				score += 600; //aumenti il valore se ci troviamo nella cella centrale che è la più forte
			score += ScoreWindow(window, cpu, player);
		}
	}

	// Diagonali ↘
	for (int row = 0; row <= 6 - 4; ++row)
	{
		for (int col = 0; col <= 7 - 4; ++col)
		{
			std::vector<SquareState> window = {
				mBoard[row][col],
				mBoard[row + 1][col + 1],
				mBoard[row + 2][col + 2],
				mBoard[row + 3][col + 3]
			};
			if (col == 4)
				score += 600; //aumenti il valore se ci troviamo nella cella centrale che è la più forte
			score += ScoreWindow(window, cpu, player);
		}
	}

	// Diagonali ↙
	for (int row = 0; row <= 6 - 4; ++row)
	{
		for (int col = 3; col < 7; ++col)
		{
			std::vector<SquareState> window = {
				mBoard[row][col],
				mBoard[row + 1][col - 1],
				mBoard[row + 2][col - 2],
				mBoard[row + 3][col - 3]
			};
			if (col == 4)
				score += 600; //aumenti il valore se ci troviamo nella cella centrale che è la più forte
			score += ScoreWindow(window, cpu, player);
		}
	}

	return score;
}

float BoardState::ScoreWindow(std::vector<BoardState::SquareState>& window, BoardState::SquareState cpu, BoardState::SquareState player) const
{
	int cpuCount = 0;
	int playerCount = 0;
	int emptyCount = 0;

	for (auto s : window)
	{
		if (s == cpu) cpuCount++;
		else if (s == player) playerCount++;
		else emptyCount++;
	}

	// Valutazione semplice:
	if (cpuCount == 4) return 1000;
	if (cpuCount == 3 && emptyCount == 1) return 100;
	if (cpuCount == 2 && emptyCount == 2) return 10;
	if (playerCount == 3 && emptyCount == 1) return -100; // minaccia avversaria
	if (playerCount == 2 && emptyCount == 2) return -10;

	return 0;
}

bool TryPlayerMove(BoardState* state, int column)
{
	// Find the first row in that column that's available
	// (if any)
	for (int row = 5; row >= 0; row--)
	{
		if (state->mBoard[row][column] == BoardState::Empty)
		{
			state->mBoard[row][column] = BoardState::Yellow;
			return true;
		}
	}

	return false;
}


//this one need a modified AI to choose a correct move using alpha-beta pruning with a depth cutoff.
void CPUMove(BoardState* state)
{

	std::vector<BoardState*> moves = state->GetPossibleMoves(BoardState::Red);
	float bestScore = -FLT_MAX;
	BoardState* bestMove = nullptr;

	for (auto move : moves)
	{
		float score = move->AlphaBeta(4, -FLT_MAX, FLT_MAX, true); // depth cutoff = 5, the larger, the better but more complex in term of cost
		if (score > bestScore)
		{
			bestScore = score;
			bestMove = move;
		}
	}

	if (bestMove)
		*state = *bestMove;

	// Clean up
	for (auto move : moves)
		delete move;
}
