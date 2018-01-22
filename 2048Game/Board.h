#pragma once
#include <string>
#include "../../NeuralNetwork/NeuralNetwork/Matrix.h"
class Board {
public:
	const double CHANCEOF4 = 0.25;
private:
	int m_board[4][4];
	long m_score;
private:
	bool addRandomNumber(bool isInitialising = false);
	
public:
	Board();
	~Board();
	long getScore()const {
		return m_score;
	}
	void reset();
	void printBoard()const;
	static char toDirection(int n);
	static int getRandomNumber(int min, int max);
	short move(char direction);
	bool hasAvailableMoves()const;
	static char randomDirection();
	int findMaximum()const;
	Matrix getNetworkBoard();
};

