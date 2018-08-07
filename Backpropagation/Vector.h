#pragma once

#include <vector>
#include <iostream>

template<class T>
class Vector
{
public:
	Vector();
	Vector(int);
	Vector(int, int);

	~Vector();

	std::vector<std::vector<T>> v;

	bool Check_Size();
	template<typename T1> bool Check_Size(std::vector<T1>&);
	template<typename T1> bool Check_Size_Fast(std::vector<T1>&);

	void Print();

	void Transponse();

	T Determinant();

	void Inverse();
	void Inverse2();


	template<class T, class Q>
	friend std::vector<std::vector<T>> operator* (const Q, Vector<T>);
	template<class T, class Q>
	friend std::vector<std::vector<T>> operator* (Vector<T>, const Q);
	template<class T>
	friend Vector<T> operator*(Vector<T>&, Vector<T>&);
	template<typename T>
	friend Vector<T>& operator+(Vector<T> &, Vector<T> &);
	template<typename T>
	friend Vector<T>& operator-(Vector<T> &, Vector<T> &);



	Vector<T>& operator = (const std::vector<std::vector<T>>& v)
	{
		this->v = v;
		return *this;
	}

	Vector<T>& operator +=(Vector<T>&b) {
		std::vector<size_t>N1(2), N2(2);
		if (!(this->Check_Size_Fast(N1) && b.Check_Size_Fast(N2)))
			return *this;

		if ((N1[0] != N2[0]) || (N1[1] != N2[1]))
			return *this;
		for (int i = 0; i < N1[0]; i++) {
			for (int j = 0; j < N1[1]; j++) {
				this->v[i][j] += b.v[i][j];
			}
		}
		return *this;
	}

	Vector<T>& operator -=(Vector<T>&b) {
		std::vector<size_t>N1(2), N2(2);
		if (!(this->Check_Size_Fast(N1) && b.Check_Size_Fast(N2)))
			return *this;

		if ((N1[0] != N2[0]) || (N1[1] != N2[1]))
			return *this;
		for (int i = 0; i < N1[0]; i++) {
			for (int j = 0; j < N1[1]; j++) {
				this->v[i][j] -= b.v[i][j];
			}
		}
		return *this;
	}

	Vector<T>& operator *=(Vector<T>&v) {
		std::vector<size_t>N1(2), N2(2);
		this->Check_Size_Fast(N1);
		v.Check_Size_Fast(N2);

		if (N1[1] != N2[0])
			return *this;

		std::vector<std::vector<T>> Result(N1[0], std::vector<T>(N2[1]));
		int i = 0;
		for (typename std::vector<std::vector<T>>::iterator it1 = Result.begin(); it1 != Result.end(); it1++, i++) {
			int j = 0;
			for (typename std::vector<T>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++, j++) {
				for (int k = 0; k < N1[1]; k++) {
					*it2 += this->v[i][k] * v.v[k][j];
				}
			}
		}
		this->v = Result;
		return *this;
	}


private:

	void Recursive_Check(std::vector<T>&);

};



template <typename T>
Vector<T>::Vector() {
}

template<class T>
inline Vector<T>::Vector(int size) :
	v(size, std::vector<T>(size))
{
}

template<class T>
inline Vector<T>::Vector(int size_x, int size_y) :
	v(size_x, std::vector<T>(size_y))
{
}

template <typename T>
Vector<T>::~Vector() {
}


template <class T, class Q>
std::vector<std::vector<T>> operator* (const Q c, Vector<T> v1)
{
	for (typename std::vector<std::vector<T>>::iterator it = v1.v.begin(); it != v1.v.end(); it++) {
		for (typename std::vector<T>::iterator it2 = it->begin(); it2 != it->end(); it2++) {
			*it2 *= c;
		}
	}
	return v1.v;
}

template <class T, class Q>
std::vector<std::vector<T>> operator* (Vector<T> v1, const Q c)
{
	for (typename std::vector<std::vector<T>>::iterator it = v1.v.begin(); it != v1.v.end(); it++) {
		for (typename std::vector<T>::iterator it2 = it->begin(); it2 != it->end(); it2++) {
			*it2 *= c;
		}
	}
	return v1.v;
}

template<class T>
Vector<T> operator*(Vector<T>& v1, Vector<T>&v2) {
	v1*=v2;
	return v1;
}

template<typename T>
Vector<T>& operator+(Vector<T> &a, Vector<T> &b)
{
	a += b;
	return a;
}


template<typename T>
Vector<T>& operator-(Vector<T> &a, Vector<T> &b)
{
	a -= b;
	return a;
}


template<typename T>
void Vector<T>::Recursive_Check(std::vector<T>& v1) {

}
template<typename T>
bool Vector<T>::Check_Size()
{
	if (std::is_fundamental<T>::value) {
		return true;
	}
	else {
		size_t size_y = 0;
		for (typename std::vector<std::vector<T>>::iterator it = this->v.begin(); it != this->v.end(); ++it) {
			if (size_y != 0) {
				if (size_y != it->size())
				{
					std::cout << "matriz invalida" << std::endl;
					return false;
				}
			}
			else {
				size_y = it->size();
			}
		}
	}
}
template<typename T>
template<typename T1>
bool Vector<T>::Check_Size_Fast(std::vector<T1>&mysize)
{
	mysize[0] = this->v.size();
	mysize[1] = this->v[0].size();
	return true;
}


template<typename T>
template<typename T1>
bool Vector<T>::Check_Size(std::vector<T1>&mysize)
{
	if (!std::is_fundamental<T1>::value) {
		std::cout << "error parametro dimension";
		return false;
	}

	T1 size_x = 0;
	T1 size_y = 0;

	for (int i = 0; i < this->v.size(); i++) {
		if (size_y != 0) {
			if (size_y != this->v[i].size())
			{
				std::cout << "matriz invalida" << std::endl;
				return false;
			}
		}
		else {
			size_y = this->v[i].size();
		}
		size_x++;
	}
	mysize[0] = size_x;
	mysize[1] = size_y;
	return true;
}


template<typename T>
void Vector<T>::Print()
{
	if (!this->Check_Size())
		return;

	for (typename std::vector<std::vector<T>>::iterator it1 = this->v.begin(); it1 != this->v.end(); it1++) {
		for (typename std::vector<T>::iterator it2 = it1->begin(); it2 != it1->end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}

template<typename T>
inline void Vector<T>::Transponse()
{
	std::vector<size_t> mysize(2);
	if (!this->Check_Size_Fast(mysize)) {
		return;
	}
	std::vector<std::vector<T>>v2(mysize[1], std::vector<T>(mysize[0]));
	int i = 0;
	for (typename std::vector<std::vector<T>>::iterator it1 = this->v.begin(); it1 != this->v.end(); ++it1, i++) {
		int j = 0;
		for (typename std::vector<T>::iterator it2 = it1->begin(); it2 != it1->end(); ++it2, j++) {
			v2[j][i] = *it2;
		}
	}
	this->v = v2;
	return;
}

template<class T>
inline T Vector<T>::Determinant()
{

	return T();
}



template<class T>
inline void Vector<T>::Inverse()
{
	size_t n = this->v.size();
	std::vector< std::vector<T> > B(n, std::vector<T>(n, 0));

	for (int i = 0; i<n; i++) {
		B[i][i] = 1;
	}

	for (int i = 0; i<n; i++) {
		// Search for maximum in this column
		T maxEl = abs(this->v[i][i]);
		int maxRow = i;
		for (int k = i + 1; k<n; k++) {
			if (abs(this->v[k][i]) > maxEl) {
				maxEl = this->v[k][i];
				maxRow = k;
			}
		}

		// Swap maximum row with current row (column by column)
		for (int k = i; k<n; k++) {
			double tmp = this->v[maxRow][k];
			this->v[maxRow][k] = this->v[i][k];
			this->v[i][k] = tmp;
		}
		for (int k = 0; k<n; k++) {
			double tmp = B[maxRow][k];
			B[maxRow][k] = B[i][k];
			B[i][k] = tmp;
		}

		// Make all rows below this one 0 in current column
		for (int k = i + 1; k<n; k++) {
			T c = -this->v[k][i] / this->v[i][i];
			for (int j = i; j<n; j++) {
				if (i == j) {
					this->v[k][j] = 0;
				}
				else {
					this->v[k][j] += c * this->v[i][j];
				}
			}
			for (int j = 0; j< n; j++) {
				B[k][j] += c * B[i][j];
			}
		}
	}



	// Solve equation Ax=b for an upper triangular matrix A
	for (size_t i = n - 1; i >= 0; i--) {
		for (int k = 0; k<n; k++) {
			B[i][k] /= this->v[i][i];
		}


		for (size_t rowModify = i - 1; rowModify >= 0; rowModify--) {
			for (int columModify = 0; columModify<n; columModify++) {
				B[rowModify][columModify] -= B[i][columModify]
					* this->v[rowModify][i];
			}
		}
	}
	this->v = B;
}



template<class T>
inline void Vector<T>::Inverse2()
{
	if (this->v.size() != this->v[0].size())
	{
		std::cout << "ERROR on inverse() not square array" << std::endl; getchar(); return;//returns a null
	}

	size_t dim = this->v.size();
	int i, j, ord;
	std::vector< std::vector<T> > y(dim, std::vector<T>(dim));
	for (i = 0; i < dim; i++)
	{
		y[i][i] = 1.0;
		for (j = i + 1; j < dim; j++)
		{
			y[i][j] = y[j][i] = 0.0;
		}
	}

	double diagon, coef;
	double *ptrx, *ptry, *ptrx2, *ptry2;
	for (ord = 0; ord<dim; ord++)
	{
		//2 Hacemos diagonal de x =1
		int i2;
		if (fabs(this->v[ord][ord])<1e-15)
		{
			for (i2 = ord + 1; i2<dim; i2++)
			{
				if (fabs(this->v[i2][ord])>1e-15) break;
			}
			if (i2 >= dim)
				return;//error, returns null
			for (i = 0; i<dim; i++)//sumo la linea que no es 0 el de la misma fila de ord
			{
				this->v[ord][i] += this->v[i2][i];
				y[ord][i] += y[i2][i];
			}
		}
		diagon = 1.0 / this->v[ord][ord];
		ptry = &y[ord][0];
		ptrx = &this->v[ord][0];
		for (i = 0; i < dim; i++)
		{
			*ptry++ *= diagon;
			*ptrx++ *= diagon;
		}

		//Hacemos '0' la columna ord salvo elemento diagonal:
		for (i = 0; i<dim; i++)//Empezamos por primera fila
		{
			if (i == ord) continue;
			coef = this->v[i][ord];//elemento ha hacer 0 
			if (fabs(coef)<1e-15) continue; //si es cero se evita
			ptry = &y[i][0];
			ptry2 = &y[ord][0];
			ptrx = &this->v[i][0];
			ptrx2 = &this->v[ord][0];
			for (j = 0; j < dim; j++)
			{
				*ptry++ = *ptry - coef * (*ptry2++);
				*ptrx++ = *ptrx - coef * (*ptrx2++);
			}
		}
	}//end ord
	this->v = y;
}