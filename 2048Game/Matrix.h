#pragma once
#include <vector>
#include <array>
class Matrix {
private:
	size_t m_rows;
	size_t m_columns;
	size_t m_size;
	std::vector<double> m_matrix;
public:
	static const double MAX_WEIGHT_VALUE;
public:
	Matrix();
	Matrix(const Matrix &copy);
	Matrix(const size_t rows, const size_t columns, bool randomise = true);
	Matrix(const size_t rows, const size_t columns, short randomNormal, double mean = 0.0, double stDeviation = 1.0);
	Matrix(const size_t rows, const size_t columns, const std::vector<double>& vector);
	~Matrix();
	double & at(const size_t row, const size_t column) {
		return m_matrix.at(row*m_columns + column);
	}
	const double & at(const size_t row, const size_t column) const {
		return m_matrix.at(row*m_columns + column);
	}
	size_t getSize() const {
		return m_size;
	}
	friend Matrix operator*(const Matrix & matrix1, const Matrix & matrix2);
	friend Matrix operator*(const Matrix & matrix1, double scalar);
	friend Matrix operator*(double scalar, const Matrix & matrix2);
	friend Matrix schurProduct(const Matrix & matrix1, const Matrix & matrix2);
	friend Matrix kroneckerProduct(const Matrix & matrix1, const Matrix & matrix2);
	friend Matrix operator+(const Matrix & matrix1, const Matrix & matrix2);
	friend Matrix operator-(const Matrix & matrix1, const Matrix & matrix2);
	friend Matrix operator-(const Matrix & matrix, const double scalar);
	friend Matrix operator-(const double scalar, const Matrix & matrix);
	friend Matrix operator+(const Matrix & matrix, const double scalar);
	friend Matrix operator+(const double scalar, const Matrix & matrix);
	Matrix & operator*=(double scalar);
	Matrix & operator+=(const Matrix &mat);
	std::string print();
	double getTotalSum() const;
	friend std::ostream& operator<< (std::ostream &out, const Matrix &matrix);

	Matrix & setToZero();
	Matrix & sigmoid();
	Matrix getTranspose() const;
	Matrix getColumn(int column) const;
	Matrix getRow(int row) const;
	double sigmoidFun(double val);
};