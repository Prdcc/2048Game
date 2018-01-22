#pragma once
#include "../../NeuralNetwork/NeuralNetwork/Matrix.h"
#include "Board.h"
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
	Matrix getResult() const {
		return m_neurons.back();
	}
	size_t getFinalLayerSize() const {
		return m_sizes.back();
	}
	GeneticNeuralNetwork();
	GeneticNeuralNetwork(const std::vector<size_t> &sizes);
	~GeneticNeuralNetwork();
};

