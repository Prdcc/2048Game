#pragma once
#include "Matrix.h"
#include "Board.h"
#include <iostream>
class GeneticNeuralNetwork {
private:
	std::vector<Matrix> m_neurons;
	std::vector<Matrix> m_weights;
	std::vector<Matrix> m_biases;
	std::vector<size_t> m_sizes;
	size_t m_layers;
private:
	template <size_t size_x, size_t size_y>
	void func(double(&arr)[size_x][size_y]) {
		std::cout << arr[1][1];
	}
public:
	void feedForward(Matrix m);
	Matrix getResult() {
		return m_neurons.back();
	}
	size_t getFinalLayerSize() const {
		return m_sizes.back();
	}
	void randomVariation(double standardDeviation = 0.2, double mean = 0.0 );
	GeneticNeuralNetwork();
	GeneticNeuralNetwork(const std::vector<size_t> &sizes);
	~GeneticNeuralNetwork();
};
