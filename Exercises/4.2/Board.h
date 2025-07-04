// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>
#include "Math.h"

class BoardState
{
public:
	enum SquareState { Empty, Red, Yellow };
	BoardState();
	std::vector<BoardState*> GetPossibleMoves(SquareState player) const;
	bool IsTerminal() const;
	float GetScore() const;
	float AlphaBeta(int depth, float alpha, float beta, bool isMaximizing) const;
	float ScoreWindow(std::vector<SquareState>& window,SquareState cpu,SquareState player) const; 
	

	SquareState mBoard[6][7];
	
protected:
	bool IsFull() const;
	int GetFourInARow() const;
	float CalculateHeuristic() const;
	int GetNextAvailableRow(int col) const;
	
	
	

private:
	float max = Math::NegInfinity; // - inf
	float min = Math::Infinity; // + inf
};

// Try to place the player's piece
bool TryPlayerMove(class BoardState* state, int column);

// Make the next CPU move
void CPUMove(class BoardState* state);