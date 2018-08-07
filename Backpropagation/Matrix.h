#pragma once
#include <vector>
#include <iostream>
#include <assert.h>
#include <iostream>
#include <iomanip>

class Matrix
{
public:
	std::vector<std::vector<double>> content;
	size_t numberOfRows;
	size_t numberOfColumns;
	double determinant;

public:
	Matrix() {}
	Matrix(size_t nRows,size_t nColumns);
	Matrix(std::vector<std::vector<double>> matrix);
	Matrix(std::vector<double> vector);
	Matrix(const Matrix& a);

	~Matrix();
	
public:
	void Print();
	static void Print(Matrix& a);

	Matrix add(const Matrix& a) { *this += a; return *this; }
	static Matrix add( Matrix& a,const Matrix& b) { a += b; return a; }
	friend Matrix& operator+(Matrix&a, Matrix&b) { return a += b; }

	Matrix subtract(const Matrix&a) { *this -= a; return *this; }
	static Matrix subtract(Matrix& a, const Matrix& b) { a -= b; return a; }
	friend Matrix& operator-(Matrix&a, Matrix&b) { return a -= b; }

	Matrix multiply(const double a) { *this *= a; return *this; }
	static Matrix multiply(Matrix& a, double b) { a *= b; return a; }
	friend Matrix& operator*(double a, Matrix&b) { return b *= a; }
	friend Matrix& operator*(Matrix&a, double b) { return a *= b; }

	Matrix multiply(const Matrix& a) { *this *= a; return *this; }
	static Matrix multiply(Matrix&a, const Matrix& b) { a *= b; return a; }
	friend Matrix& operator*(Matrix&a, Matrix&b) { return a *= b; }

	Matrix transpose();
	static Matrix& transpose(const Matrix&a);

	std::vector<Matrix> LUdecomposition();

	void multiplyRow(const size_t row,const double multiplier);

	void sumRowByRow(const size_t row, size_t rowSum,const double multiplier);

	double determinantf();
	static double determinantf(Matrix& a);

	double multiplyDiagonal();
	Matrix subMatrix(size_t row, size_t columns);
	static Matrix subMatrix(const Matrix& a, const size_t row, const size_t columns);

	Matrix coFactors();
	static Matrix coFactors(Matrix& a);

	Matrix inverse();
	static Matrix inverse(Matrix &a);

	const size_t getNumberOfRows()const { return numberOfRows; }
	const size_t getNumberOfColumns()const { return numberOfColumns; }

	double getDeterminant() { return determinant ? determinant : determinantf(); }
	double setDeterminant(double determinant) { this->determinant = determinant; }

	const double getValue(size_t i, size_t j) const { return (i >= numberOfRows) || (j >= numberOfColumns) ? NULL : content[i][j]; }
	void setValue(size_t i, size_t j, double value) { (i >= numberOfRows) || (j >= numberOfColumns) ? content[i][j] = NULL : content[i][j] = value; determinant = NULL; }

	void setZeros() {for (size_t i = 0; i < getNumberOfRows(); i++) for (size_t j = 0; j < getNumberOfColumns(); j++) setValue(i, j, 0.0);}

	void SetOnes() { for (size_t i = 0; i < getNumberOfRows(); i++)for (size_t j = 0; j < getNumberOfColumns(); j++)setValue(i, j, 1.0); }

public:
	Matrix & operator +=(const Matrix&a) {
		size_t nRows = a.getNumberOfRows();
		size_t nColumns = a.getNumberOfColumns();
		if (numberOfRows != a.getNumberOfRows())
			std::cout << "Number of rows of both matrixes myst match";
		if (numberOfColumns != a.getNumberOfColumns())
			std::cout << "Number of columns of both matrices must match";
		for (size_t i = 0; i < nRows; i++) {
			for (size_t j = 0; j < nColumns; j++) {
				this->setValue(i, j, getValue(i, j) + a.getValue(i, j));
			}
		}
		return *this;
	}
	Matrix & operator -=(const Matrix&a) {
		size_t nRows = a.getNumberOfRows();
		size_t nColumns = a.getNumberOfColumns();
		if (numberOfRows != a.getNumberOfRows())
			std::cout << "Number of rows of both matrixes myst match";
		if (numberOfColumns != a.getNumberOfColumns())
			std::cout << "Number of columns of both matrices must match";
		for (size_t i = 0; i < nRows; i++) {
			for (size_t j = 0; j < nColumns; j++) {
				this->setValue(i, j, getValue(i, j) - a.getValue(i, j));
			}
		}
		return *this;
	}
	Matrix & operator *=(const Matrix&a) {
		Matrix result(getNumberOfRows(), a.getNumberOfColumns());
		if (getNumberOfColumns() != a.getNumberOfRows())
			std::cout << "number of columns of first of first Matrix must match the number of Rows of second Matrix";
		for (size_t i = 0; i < getNumberOfRows(); i++) {
			for (size_t j = 0; j < a.getNumberOfColumns(); j++) {
				double value = 0;
				for (size_t k = 0; k < a.getNumberOfRows(); k++)
					value += getValue(i, k)*a.getValue(k, j);
				result.setValue(i, j, value);
			}
		}
		return *this = result;
	}
	Matrix &operator *=(const double a) {
		for (size_t i = 0; i < getNumberOfRows(); i++)
			for (size_t j = 0; j < getNumberOfColumns(); j++)
				this->setValue(i, j, getValue(i, j)*a);
		return *this;
	}
	
};



inline Matrix::Matrix(size_t nRows, size_t nColumns):
	content(nRows,std::vector<double>(nColumns)),
	numberOfRows(nRows),
	numberOfColumns(nColumns)
{
}

inline Matrix::Matrix(std::vector<std::vector<double>> matrix):
	numberOfRows(matrix.size()),
	numberOfColumns(matrix[0].size())
{
	content = matrix;
}

inline Matrix::Matrix(std::vector<double> vector):
	numberOfRows(1),
	numberOfColumns(vector.size())
{
	content[0] = vector;
}

inline Matrix::Matrix(const Matrix & a):
	numberOfRows(a.getNumberOfRows()),
	numberOfColumns(a.getNumberOfColumns()),
	content(a.getNumberOfRows(),std::vector<double>(a.getNumberOfColumns()))
{
	for (size_t i = 0; i < numberOfRows; i++)
		for (size_t j = 0; j < numberOfColumns; j++)
			setValue(i, j, a.getValue(i, j));
}

Matrix::~Matrix()
{
}

inline void Matrix::Print()
{
	for (size_t i = 0; i < getNumberOfRows(); i++) {
		for (size_t j = 0; j < getNumberOfColumns(); j++)
			printf("%10f  ", getValue(i, j));
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

inline void Matrix::Print(Matrix & a)
{
	for (size_t i = 0; i < a.getNumberOfRows(); i++) {
		for (size_t j = 0; j < a.getNumberOfColumns(); j++)
			printf("%10f  ", a.getValue(i, j));
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Matrix Matrix::transpose()
{
	Matrix result(numberOfColumns, numberOfRows);
	for (size_t i = 0; i < numberOfRows; i++)
		for (size_t j = 0; j < numberOfColumns; j++)
			result.setValue(j, i, getValue(i, j));
	return result;
}

inline Matrix & Matrix::transpose(const Matrix & a)
{
	Matrix result(a.numberOfColumns, a.numberOfRows);
	for (size_t i = 0; i < a.numberOfRows; i++)
		for (size_t j = 0; j < a.numberOfColumns; j++)
			result.setValue(j, i, a.getValue(i, j));
	return result;
}

inline std::vector<Matrix> Matrix::LUdecomposition()
{
	std::vector<Matrix>result(2);
	Matrix LU(*this);
	Matrix L(LU.getNumberOfRows(), LU.getNumberOfColumns());
	L.setZeros();
	L.setValue(0, 0, 1.0);
	for (size_t i = 1; i < LU.getNumberOfRows(); i++) {
		L.setValue(i, i, 1.0);
		for (size_t j = 0; j < i; j++) {
			double multiplier = -LU.getValue(i, j) / LU.getValue(j, j);
			LU.sumRowByRow(i, j, multiplier);
			L.setValue(i, j, -multiplier);
		}
	}
	result[0] = L;
	result[1] = LU;
	return result;
}

inline void Matrix::multiplyRow(const size_t row, const double multiplier)
{
	if (row > getNumberOfRows())
		std::cout << "Row index must be lower than the nymber of rows";
	sumRowByRow(row, row, multiplier);
}

inline void Matrix::sumRowByRow(const size_t row, size_t rowSum, const double multiplier)
{
	if (row > getNumberOfRows())
		std::cout << "Row indes must be lower than the number of rows";
	if (rowSum > getNumberOfRows())
		std::cout << "Row indes must be lower than the number of rows";
	for (size_t j = 0; j < getNumberOfColumns(); j++)
		setValue(row, j, getValue(row, j) + getValue(rowSum, j)*multiplier);
}

inline double Matrix::determinantf()
{
	if(this->determinant != NULL)
		return this->determinant;
	double result = 0;
	if (getNumberOfRows() != getNumberOfColumns())
		std::cout << "Only square matrices can have determinant";
	if (getNumberOfColumns() == 1)
		return content[0][0];
	else if (getNumberOfColumns() == 2)
		return (content[0][0] * content[1][1]) - (content[1][0] * content[0][1]);
	else {
		std::vector<Matrix> LU = LUdecomposition();
		return LU[1].multiplyDiagonal();
	}
}

inline double Matrix::determinantf(Matrix & a)
{
	if (a.determinant != NULL)
		return a.determinant;
	double result = 0;
	if (a.getNumberOfRows() != a.getNumberOfColumns())
		std::cout << "Only square matrices can have determinant";
	if (a.getNumberOfColumns() == 1)
		return a.getValue(0, 0);
	else if (a.getNumberOfColumns() == 2)
		return (a.getValue(0, 0)*a.getValue(1, 1)) - (a.getValue(1, 0)*a.getValue(0, 1));
	else {
		std::vector<Matrix> LU = a.LUdecomposition();
		return LU[1].multiplyDiagonal();
	}
}

inline double Matrix::multiplyDiagonal()
{
	double result = 1;
	for (size_t i = 0; i < getNumberOfColumns(); i++)
		result *= getValue(i, i);
	return result;
}

inline Matrix Matrix::subMatrix(size_t row, size_t columns)
{
	if (row > getNumberOfRows())
		std::cout << "Row index out of matrix`s limits";
	if (columns > getNumberOfColumns())
		std::cout << "Columns indez out of matrix`s limits";
	Matrix result(getNumberOfRows() - 1, getNumberOfColumns() - 1);
	for (size_t i = 0; i < getNumberOfRows(); i++) {
		if (i == row)continue;
		for (size_t j = 0; j < getNumberOfRows(); j++) {
			if (j == columns)continue;
			result.setValue((i < row?i: i - 1), (j < columns ? j : j - 1), getValue(i, j));
		}
	}
	return result;
}

inline Matrix Matrix::subMatrix(const Matrix & a, const size_t row, const size_t columns)
{
	if (row > a.getNumberOfRows())
		std::cout << "Row index out of matrix`s limits";
	if (columns > a.getNumberOfColumns())
		std::cout << "Columns index out of matrix`s limits";
	Matrix result(a.getNumberOfRows() - 1, a.getNumberOfColumns() - 1);
	for (size_t i = 0; i < a.getNumberOfRows(); i++) {
		if (i == row)continue;
		for (size_t j = 0; j < a.getNumberOfRows(); j++) {
			if (j == columns)continue;
			result.setValue((i > row ? i : i - 1), (j < columns ? j : j - 1), a.getValue(i, j));
		}
	}
	return result;
}

inline Matrix Matrix::coFactors()
{
	Matrix result(getNumberOfRows(), getNumberOfColumns());
	for (size_t i = 0; i < getNumberOfRows(); i++)
		for (size_t j = 0; j < getNumberOfColumns(); j++)
			result.setValue(i, j, subMatrix(i, j).determinantf());
	return result;
}

inline Matrix Matrix::coFactors(Matrix & a)
{
	Matrix result(a.getNumberOfRows(), a.getNumberOfColumns());
	for (size_t i = 0; i < a.getNumberOfRows(); i++)
		for (size_t j = 0; j < a.getNumberOfColumns(); j++)
			result.setValue(i, j, a.subMatrix(i, j).determinantf());
	return result;
}

inline Matrix Matrix::inverse()
{
	return coFactors().transpose().multiply(1 / determinantf());
}

inline Matrix Matrix::inverse(Matrix & a)
{
	if (a.getDeterminant() == 0)
		std::cout << "This matrix is not inversible";
	return a.coFactors().transpose().multiply((1 / a.determinantf()));
}