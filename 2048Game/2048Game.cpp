#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Board.h"
#include <conio.h>
#include <cmath>
#include "GeneticNeuralNetwork.h"


int main(){
	srand(static_cast<unsigned int>(time(0)));
	rand();
	Board board;
	GeneticNeuralNetwork net;
	net.feedForward(board.getNetworkBoard());
	/*
	const size_t GAMES_TO_PLAY = 100000;
	Board board;
	
	int scores[GAMES_TO_PLAY];
	
	for (size_t i = 0; i < GAMES_TO_PLAY; i++) {
		short cont = 1;
		while (cont != 2) {
			cont = board.move(Board::randomDirection());
		}
		scores[i] = board.getScore();
		board.reset();
	}

	std::string s = "";
	for (size_t i = 0; i < 10; i++) {
		s += "|";
		for (size_t j = 0; j < 10; j++) {
			s += std::to_string(scores[j * 10 + i]) + "\t";
		}
		s += "\n";
	}
	s += "\n";
	std::cout << s;*/
    return 0;
}

