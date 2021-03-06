#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Board.h"
#include <conio.h>
#include <cmath>
#include "GeneticNeuralNetwork.h"
#include "Matrix.h"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <thread>
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

const std::vector<size_t> LAYERS{ 16,8,4 };   //16,5,8,10,4
const size_t NETWORKS_PER_GENERATION = 100;
const size_t NUMBER_OF_GENERATIONS = 75;			//360
const size_t GAMES_TO_PLAY = 100;			//10
const double STANDARD_DEVIATION = 0.01;

struct Player {
	long score;
	GeneticNeuralNetwork network;
	Board board;

	Player(long s, const GeneticNeuralNetwork& net) : score(s), network(net), board() {}
	Player() : score(0), network(GeneticNeuralNetwork{ LAYERS }), board() {}
	Player(const Player & copy): score(copy.score), network(new GeneticNeuralNetwork(copy.network)), board() {}

	bool operator < (const Player& net) const {
		return (score > net.score);					//shhhh no one has to know
	}
};

bool makeMove(GeneticNeuralNetwork & net, Board & board) { //returns true if the game continues
	net.feedForward(board.getNetworkBoard());
	Matrix movePreferences{ net.getResult() };
	short gameStatus;
	do {
		double max = -1;
		int index = -1;
		for (int i = 0; i < 4; i++) {
			if (movePreferences.at(0, i) > max) {
				max = movePreferences.at(0, i);
				index = i;
			}
		}
		movePreferences.at(0, index) = -2;
		gameStatus = board.move(Board::toDirection(index));
	} while (gameStatus == 1);
	return gameStatus == 0;
}

long playGame(GeneticNeuralNetwork & net, Board & board) {
	while (makeMove(net, board)) {}
	return board.getScore();
}

long showGame(GeneticNeuralNetwork & net, Board & board) {
	while (makeMove(net, board)) {
		board.printBoard();
		std::cout << "Score: " << board.getScore() << "\n";


		sleep_for(1s);
	}
	return board.getScore();
}

void printPlayers(const std::vector<Player> & vec) {
	std::string s = "";
	for (size_t i = 0; i < 10; i++) {
		s += "|";
		for (size_t j = 0; j < 10; j++) {
			s += std::to_string(vec[j * 10 + i].score) + "\t";
		}
		s += "\n";
	}
	s += "\n";
	std::cout << s;
}

int main(){


	srand(static_cast<unsigned int>(time(0)));
	rand();
	std::vector<Player> players;
	players.resize(NETWORKS_PER_GENERATION);
	using namespace std;
	clock_t begin = clock();
	for (size_t i = 0; i < NETWORKS_PER_GENERATION; i++) {	//play with new generation
		for (size_t j = 0; j < GAMES_TO_PLAY; j++) {
			players[i].board.reset();
			playGame(players[i].network, players[i].board);
			players[i].score += players[i].board.getScore();
		}
		players[i].score /= GAMES_TO_PLAY;
	}
	std::sort(players.begin(), players.end());
	printPlayers(players);
	long avgScore = 0;
	for (const auto & player : players) {
		avgScore += player.score;
	}
	avgScore /= NETWORKS_PER_GENERATION;
	std::cout <<"Average score: " << avgScore << "\n";
	long lastScore(avgScore);




	for (size_t j = 0; j < NUMBER_OF_GENERATIONS; j++) {
		for (size_t k = 0; k < NETWORKS_PER_GENERATION; k++) {
			players[k].score = 0;
		}
		for (size_t i = 1; i < NETWORKS_PER_GENERATION / 10; i++) {
			for (size_t k = 0; k < 10; k++) {
				players[i * 10 + k] = Player(players[k]);
				players[i * 10 + k].network.randomVariation(STANDARD_DEVIATION);
			}
		}
		for (size_t i = 0; i < NETWORKS_PER_GENERATION; i++) {	//play with new generation
			for (size_t k = 0; k < GAMES_TO_PLAY; k++) {
				players[i].board.reset();
				playGame(players[i].network, players[i].board);
				players[i].score += players[i].board.getScore();
			}
			players[i].score /= GAMES_TO_PLAY;
		}
		std::sort(players.begin(), players.end());
		avgScore = 0;
		for (const auto & player : players) {
			avgScore += player.score;
		}
		avgScore /= NETWORKS_PER_GENERATION;
		long standardDeviation = 0;
		for (const auto & player : players) {
			standardDeviation += (player.score-avgScore)*(player.score-avgScore);
		}
		standardDeviation /= NETWORKS_PER_GENERATION;
		std::cout << "Generation Number: " << j << " Average score: " << avgScore << " Standard deviation: " << std::sqrt(standardDeviation) << " Delta score: " << avgScore - lastScore <<"\n";
		printPlayers(players);
		lastScore = avgScore;
	}

	clock_t end = clock();
	double elapsedSecs = double(end - begin) / CLOCKS_PER_SEC;

	std::cout << "Done in " << elapsedSecs << " seconds\n";

	players[0].board.reset();
	showGame(players[0].network, players[0].board);

    return 0;
}

