#include "stdafx.h"
#include "Board.h"
#include <cstdlib>
#include <iostream>
#include <math.h>

Board::Board() {
	reset();
}

bool Board::addRandomNumber(bool isInitialising) {
	bool isFull = true;
	for (size_t i = 0; i < 4 && isFull; i++) {
		for (size_t j = 0; j < 4 && isFull; j++) {
			if (m_board[i][j] == 0) {
				isFull = false;
			}
		}
	}

	if (isFull)
		return false;
	int randomCell;
	do {
		randomCell = getRandomNumber(0, 15);
	} while (m_board[randomCell % 4][randomCell / 4]>0);
	if (isInitialising) {
		m_board[randomCell % 4][randomCell / 4] = 1;
		return true;
	}
	m_board[randomCell % 4][randomCell / 4] = (((double)rand() / (RAND_MAX))<CHANCEOF4)? 2 : 1;
	return true;
}

/*
	w
a		d
	s
*/
short Board::move(char direction) {
	const char KEY_UP = 72;
	const char KEY_DOWN = 80;
	const char KEY_LEFT = 75;
	const char KEY_RIGHT = 77;

	direction = toupper(direction);
	bool hasMoved = false;
	switch (direction) {
	case KEY_UP:
	case 'W':
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 3; j++) {
				for (size_t k = 1; k < 4 - j; k++) {
					if (m_board[i][k] > 0) {
						if ((m_board[i][k - 1] == m_board[i][k])) {
							m_board[i][k - 1]++;
							m_board[i][k] = 0;
							m_score += pow(2, m_board[i][k - 1]);
							hasMoved = true;
						}
						else if (m_board[i][k - 1] == 0) {
							m_board[i][k - 1] = m_board[i][k];
							m_board[i][k] = 0;
							hasMoved = true;
						}
					}
				}
			}
		}
		break;

	case KEY_DOWN:
	case 'S':
		for (size_t i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 2; k > j - 1; k--) {
					if (m_board[i][k] > 0) {
						if ((m_board[i][k + 1] == m_board[i][k])) {
							m_board[i][k + 1]++;
							m_board[i][k] = 0;
							m_score += pow(2, m_board[i][k + 1]);
							hasMoved = true;
						}
						else if (m_board[i][k + 1] == 0) {
							m_board[i][k + 1] = m_board[i][k];
							m_board[i][k] = 0;
							hasMoved = true;
						}
					}
				}
			}
		}
		break;

	case KEY_LEFT:
	case 'A':
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 3; j++) {
				for (size_t k = 1; k < 4 - j; k++) {
					if (m_board[k][i] > 0) {
						if ((m_board[k - 1][i] == m_board[k][i])) {
							m_board[k - 1][i]++;
							m_board[k][i] = 0;
							m_score += pow(2, m_board[k - 1][i]);
							hasMoved = true;
						}
						else if (m_board[k - 1][i] == 0) {
							m_board[k - 1][i] = m_board[k][i];
							m_board[k][i] = 0;
							hasMoved = true;
						}
					}
				}
			}
		}
		break;

	case KEY_RIGHT:
	case 'D':
		for (size_t i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 2; k > j - 1; k--) {
					if (m_board[k][i] > 0) {
						if ((m_board[k + 1][i] == m_board[k][i])) {
							m_board[k + 1][i]++;
							m_board[k][i] = 0;
							m_score += pow(2, m_board[k + 1][i]);
							hasMoved = true;
						}
						else if (m_board[k + 1][i] == 0) {
							m_board[k + 1][i] = m_board[k][i];
							m_board[k][i] = 0;
							hasMoved = true;
						}
					}
				}
			}
		}
		break;
	default: return true;
	}
	short canPlay;
	if (hasMoved) {
		addRandomNumber();
		canPlay = 0;		//could play move fine
	}
	else {
		canPlay = (hasAvailableMoves()) ? 1 : 2;	//2 => game over, 1=> just wrong move
	}
	return canPlay;
}

bool Board::hasAvailableMoves() const {
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 3; j++) {
			for (size_t k = 1; k < 4 - j; k++) {
				if (m_board[i][k] > 0) {
					if ((m_board[i][k - 1] == m_board[i][k])) {
						return true;
					}
					else if (m_board[i][k - 1] == 0) {
						return true;
					}
				}
			}
		}
	}
		for (size_t i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 2; k > j - 1; k--) {
					if (m_board[i][k] > 0) {
						if ((m_board[i][k + 1] == m_board[i][k])) {
							return true;
						}
						else if (m_board[i][k + 1] == 0) {
							return true;
						}
					}
				}
			}
		}

		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 3; j++) {
				for (size_t k = 1; k < 4 - j; k++) {
					if (m_board[k][i] > 0) {
						if ((m_board[k - 1][i] == m_board[k][i])) {
							return true;
						}
						else if (m_board[k - 1][i] == 0) {
							return true;
						}
					}
				}
			}
		}

		for (size_t i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				for (int k = 2; k > j - 1; k--) {
					if (m_board[k][i] > 0) {
						if ((m_board[k + 1][i] == m_board[k][i])) {
							return true;
						}
						else if (m_board[k + 1][i] == 0) {
							return true;
						}
					}
				}
			}
		}
	return false;
}

void Board::reset() {
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			m_board[i][j] = 0;
	addRandomNumber(true);
	addRandomNumber(true);
	m_score = 0;
}

void Board::printBoard()const {
	std::string s = "-------------\n";
	for (size_t i = 0; i < 4; i++) {
		s += "|";
		for (size_t j = 0; j < 4; j++) {
			if (m_board[j][i] == 0) {
				s += "  ";
			}
			else {
				s += (m_board[j][i] >= 10) ? std::to_string(m_board[j][i]) : " " + std::to_string(m_board[j][i]);
			}
			s += "|";
		}
		s += "\n";
	}
	s += "-------------\n\n";
	std::cout << s;
}

char Board::toDirection(int n){
	switch(n) {
		case 0:
			return 'W';
			break;
		case 1:
			return 'A';
			break;
		case 2:
			return 'S';
			break;
		case 3:
			return 'D';
			break;
	}
}

int Board::getRandomNumber(int min, int max){
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  
																				 
	return min + static_cast<int>((max - min + 1) * (rand() * fraction));
}



char Board::randomDirection() {
	return toDirection(getRandomNumber(0, 3));
}

int Board::findMaximum() const {
	int maximum = 0;
	for (size_t i = 0; i < 4; i++)
		for (size_t j = 0; j < 4; j++)
			if (m_board[i][j] > maximum)
				maximum = m_board[i][j];
	return maximum;
}

Matrix Board::getNetworkBoard() {
	Matrix m{ 16,1 };
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			m.at(i, j) = ((double)m_board[i][j])/findMaximum();
		}
	}
	return m;
}

Board::~Board() {}