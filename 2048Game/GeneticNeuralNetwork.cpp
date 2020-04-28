#include "stdafx.h"
#include "GeneticNeuralNetwork.h"
#include <random>
#include <iostream>


void GeneticNeuralNetwork::randomVariation(double standardDeviation, double mean) {
	static std::default_random_engine generator;
	generator.seed(generator.default_seed);
	std::normal_distribution<double> distribution(mean, standardDeviation);
	for (size_t i = 1; i < m_layers; i++) {
		for (size_t j = 0; j < m_sizes[i]; j++) {
			m_biases.at(i-1).at(0, j)+=distribution(generator);
			for (size_t k = 0; k < m_sizes[i-1]; k++) {
				m_weights.at(i-1).at(j,k) += distribution(generator);
			}
		}
	}
}

GeneticNeuralNetwork::GeneticNeuralNetwork() : GeneticNeuralNetwork({ 16,4 }) {}


void GeneticNeuralNetwork::feedForward(Matrix m) {
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


