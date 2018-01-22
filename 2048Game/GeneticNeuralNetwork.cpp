#include "stdafx.h"
#include "GeneticNeuralNetwork.h"


GeneticNeuralNetwork::GeneticNeuralNetwork() : GeneticNeuralNetwork({ 16,4 }) {}


inline void GeneticNeuralNetwork::feedForward(Matrix m) {
	m_neurons.at(0) = m;
	for (size_t i = 0; i < m_layers - 1; i++) {
		m_neurons.at(i + 1) = (m_weights.at(i) * m_neurons.at(i)) + m_biases.at(i);
		m_neurons.at(i + 1).sigmoid();
	}
}

GeneticNeuralNetwork::GeneticNeuralNetwork(const std::vector<size_t>& sizes) : m_layers{ (size_t)sizes.size() }, m_sizes{ sizes } {
	m_neurons.resize(m_layers);
	m_biases.resize(m_layers - 1);
	m_weights.resize(m_layers - 1);
	for (size_t i = 0; i < m_layers - 1; i++) {
		m_neurons.at(i) = Matrix(sizes.at(i), 1, false);
		m_biases.at(i) = Matrix(sizes.at(i + 1), 1, short(0));
		m_weights.at(i) = Matrix(sizes.at(i + 1), sizes.at(i), short(0));
	}
	m_neurons.at(m_layers - 1) = Matrix(sizes.at(m_layers - 1), 1, false);
}

GeneticNeuralNetwork::~GeneticNeuralNetwork() {}
