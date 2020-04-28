#include "stdafx.h"
#include "Matrix.h"
#include <cassert>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>

Matrix::Matrix() : Matrix(1, 1) {}

Matrix::Matrix(const Matrix & copy) :
	m_rows{ copy.m_rows },
	m_columns{ copy.m_columns },
	m_size{ copy.m_size },
	m_matrix{ copy.m_matrix } {}

Matrix::Matrix(const size_t rows, const size_t columns, bool randomise) :
	m_rows{ rows }, m_columns{ columns }, m_size{ rows*columns } {
	m_matrix.resize(m_size);
	if (randomise)
		for (size_t i = 0; i < m_size; i++) {
			m_matrix.at(i) = ((double)rand() / RAND_MAX) * MAX_WEIGHT_VALUE - MAX_WEIGHT_VALUE / 2;
		}
}

Matrix::Matrix(const size_t rows, const size_t columns, short randomNormal, double mean, double stDeviation) :
	m_rows{ rows }, m_columns{ columns }, m_size{ rows*columns } {
	std::default_random_engine generator;
	generator.seed(generator.default_seed);
	std::normal_distribution<double> distribution(mean, stDeviation);
	m_matrix.resize(m_size);
	if (randomNormal == 0) {
		for (size_t i = 0; i < m_size; i++) {
			m_matrix.at(i) = distribution(generator);
		}
	}
	else {
		for (size_t i = 0; i < m_size; i++) {
			m_matrix.at(i) = ((double)rand() / RAND_MAX) * MAX_WEIGHT_VALUE - MAX_WEIGHT_VALUE / 2;
		}
	}
}



Matrix::Matrix(const size_t rows, const size_t columns, const std::vector<double>& vector) :
	m_rows{ rows }, m_columns{ columns }, m_size{ rows*columns } {
	assert(m_size == vector.size());
	m_matrix = vector;
}

Matrix::~Matrix() {}

Matrix & Matrix::operator*=(double scalar) {
	for (size_t i = 0; i < m_size; i++)
		m_matrix.at(i) *= scalar;
	return *this;
}

Matrix & Matrix::operator+=(const Matrix &mat) {
	*this = *this + mat;
	return *this;
}

std::string Matrix::print() {
	std::string s = "";
	for (size_t i = 0; i < m_rows; i++) {
		for (size_t j = 0; j < m_columns; j++) {
			s += std::to_string(at(i, j)) + " ";
		}
		s += "\n";
	}

	return s;
}

double Matrix::getTotalSum() const {
	double sum = 0.0;
	for (size_t i = 0; i < m_size; i++) {
		sum += m_matrix.at(i);
	}
	return sum;
}

Matrix & Matrix::setToZero() {
	for (size_t i = 0; i < m_size; i++) {
		m_matrix.at(i) = 0;
	}
	return *this;
}

Matrix & Matrix::sigmoid() {
	for (size_t i = 0; i < m_size; i++) {
		m_matrix.at(i) = sigmoidFun(m_matrix.at(i));
	}
	return *this;
}

Matrix Matrix::getTranspose() const {
	if ((m_rows == 1) || (m_columns == 1)) {   //no need to modify order in case of vector
		return Matrix(m_columns, m_rows, m_matrix);
	}

	std::vector<double> tempVec;
	tempVec.resize(m_size);
	size_t k = 0;
	for (size_t i = 0; i < m_columns; i++)
		for (size_t j = 0; j < m_rows; j++, k++)
			tempVec.at(k) = at(j, i);
	return Matrix(m_columns, m_rows, tempVec);
}

Matrix Matrix::getColumn(int column) const {
	std::vector<double> tempVec;
	tempVec.resize(m_rows);
	for (size_t i = 0; i < m_rows; i++)
		tempVec.at(i) = at(0, i);
	return Matrix(m_rows, 1, tempVec);
}


Matrix Matrix::getRow(int row) const {
	std::vector<double> tempVec;
	tempVec.resize(m_columns);
	for (size_t i = 0; i < m_columns; i++)
		tempVec.at(i) = at(i, 0);
	return Matrix(1, m_columns, tempVec);
}

double Matrix::sigmoidFun(double val) {
	return 1.0 / (1.0 + std::exp(-val));
}



Matrix operator*(const Matrix & matrix1, const Matrix & matrix2) {
	assert(matrix1.m_columns == matrix2.m_rows);

	Matrix matrix{ matrix1.m_rows, matrix2.m_columns, false };
	for (size_t i = 0; i < matrix1.m_rows; ++i)
		for (size_t j = 0; j < matrix2.m_columns; ++j)
			for (size_t k = 0; k < matrix1.m_columns; ++k) {
				matrix.at(i, j) += matrix1.at(i, k) * matrix2.at(k, j);
			}
	return matrix;
}

Matrix operator*(const Matrix &matrix1, double scalar) {
	Matrix temp(matrix1);
	temp *= scalar;
	return temp;
}

Matrix operator*(double scalar, const Matrix & matrix2) {
	return matrix2*scalar;
}

Matrix schurProduct(const Matrix & matrix1, const Matrix & matrix2) {
	assert((matrix1.m_columns == matrix2.m_columns) && (matrix1.m_rows == matrix2.m_rows));
	Matrix temp{ matrix1.m_rows, matrix1.m_columns, false };
	for (size_t i = 0; i < matrix1.m_rows; ++i)
		for (size_t j = 0; j < matrix2.m_columns; ++j)
			temp.at(i, j) = matrix1.at(i, j) * matrix2.at(i, j);
	return temp;
}

Matrix kroneckerProduct(const Matrix & matrix1, const Matrix & matrix2) {
	assert((matrix2.m_columns == 1) && (matrix1.m_rows == 1));
	Matrix temp{ matrix1.m_columns, matrix2.m_rows, false };
	for (size_t i = 0; i < matrix1.m_columns; i++) {
		for (size_t j = 0; j < matrix2.m_rows; j++) {
			temp.at(i, j) = matrix1.at(0, i)*matrix2.at(j, 0);
		}
	}
	return temp;
}

Matrix operator+(const Matrix & matrix1, const Matrix & matrix2) {
	assert((matrix1.m_columns == matrix2.m_columns) && (matrix1.m_rows == matrix2.m_rows));
	Matrix temp{ matrix1.m_rows, matrix2.m_columns, false };
	for (size_t i = 0; i < matrix1.m_rows; ++i)
		for (size_t j = 0; j < matrix2.m_columns; ++j)
			temp.at(i, j) = matrix1.at(i, j) + matrix2.at(i, j);
	return temp;
}

Matrix operator-(const Matrix & matrix1, const Matrix & matrix2) {
	return matrix1 + (-1) * matrix2;
}

Matrix operator-(const Matrix & matrix, const double scalar) {
	return matrix + (-scalar);
}

Matrix operator-(const double scalar, const Matrix & matrix) {
	return scalar + (-1)*matrix;
}

Matrix operator+(const Matrix & matrix, const double scalar) {
	Matrix temp{ matrix };
	for (size_t i = 0; i < temp.m_size; i++) {
		temp.m_matrix.at(i) += scalar;
	}
	return temp;
}

Matrix operator+(const double scalar, const Matrix & matrix) {
	return matrix + scalar;
}



std::ostream & operator<<(std::ostream & out, const Matrix & matrix) {
	std::string s = "";
	for (size_t i = 0; i < matrix.m_rows; i++) {
		for (size_t j = 0; j < matrix.m_columns; j++) {
			s += std::to_string(matrix.at(i, j)) + " ";
		}
		s += "\n";
	}
	s += "\n";
	out << s;
	return out;
}


const double Matrix::MAX_WEIGHT_VALUE{ 2.0 };
