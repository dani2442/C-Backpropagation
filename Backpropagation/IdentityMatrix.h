#pragma once
#include "Matrix.h"

class IdentityMatrix:public Matrix
{
public:
	IdentityMatrix(size_t);
	~IdentityMatrix();

	void setValue(int row, int column) {}
private:

};

IdentityMatrix::IdentityMatrix(size_t order) : Matrix(order,order)
{
	for (size_t i = 0; i < order; i++)
		for (size_t j = 0; j < order; j++)
			Matrix::setValue(i, j, i == j ? 1 : 0);
}

IdentityMatrix::~IdentityMatrix()
{
}