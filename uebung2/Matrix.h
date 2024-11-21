////////////////////////////////////////////////////////////////////////////
//																	      //
// Code framework for lecture computer graphics WS 2024/25 assignment 2   //
//										                                  //
// A generic class for n x n matrices                                     //
//										                                  //
// (c) Georg Umlauf						                                  //
//										                                  //
////////////////////////////////////////////////////////////////////////////

#pragma once

template <class T, unsigned n> class CVector;				// forward declaration of n-dimensional vector

//
//
// generic n x n matrix class for SIMPLE data types T
//
//
template <class T, unsigned n> class CMatrix {
private:
	T m_aatData[n][n];		// array of size n x n of type T

public:
	// default/standard constructor
	CMatrix<T, n> (T t=T(0)) {								
		for (int j=0; j<n; j++) 
			for (int i=0; i<n; i++) 
				m_aatData[i][j] = t;// initialize all elements with t or zero						
	}

	// constructor from array
	CMatrix<T, n> (const T aatData[n][n]) {					
		for (int j=0; j<n; j++) {
			for (int i=0; i<n; i++) {
				m_aatData[i][j] = aatData[i][j];
			}
		}
	}

	// copy constructor
	CMatrix<T, n> (const CMatrix<T, n> &mat) {				
		for (int j=0; j<n; j++) {
			for (int i=0; i<n; i++) {
				m_aatData[i][j] = mat.m_aatData[i][j];
			}
		}
	}

	// destructor
	~CMatrix<T, n>() {/* nothing to do here ...*/ }	

	// index operator
	T &operator () (unsigned i, unsigned j) {				
		if (i>=n) i = n-1;
		if (j>=n) j = n-1;
		return m_aatData[i][j];
	}

	// index operator
	T operator () (unsigned i, unsigned j) const {			
		if (i>=n) i = n-1;
		if (j>=n) j = n-1;
		return m_aatData[i][j];
	}

	// matrix-matrix-multiplication
	CMatrix<T, n> operator * (const CMatrix<T, n> &mat) const {
		CMatrix<T, n> buf(T(0));
		for (int i=0; i<n; i++)				// row i
			for (int j=0; j<n; j++)			// column j
				for (int k=0; k<n; k++)		// k
					buf(i,j) += m_aatData[i][k] * mat(k,j);
		return buf;
	}

	// matrix-matrix-multiplication
	CVector<T, n> operator * (const CVector<T, n> &vec) const {	
		CVector<T, n> buf(T(0));
		for (int j=0; j<n; j++)				// column j
			for (int i=0; i<n; i++)			// row i
				buf[i] += m_aatData[i][j]*vec[j];
		return buf;
	}

	CVector<T, n> getCol(int j)  const {
		CVector<T, n> buf;				// Nullvektor
		for (int i = 0; i < n; i++)			// ZEILE i
			buf[i] = m_aatData[i][j % n];
		return buf;
	}

	void setCol(const CVector<T, n>& buf, int j) {
		for (int i = 0; i < n; i++)			// ZEILE i
			m_aatData[i][j % n] = buf[i];
	}

	CVector<T, n> getRow(int i) const {
		CVector<T, n> buf;				// Nullvektor
		for (int j = 0; j < n; j++)			// SPALTE j
			buf[j] = m_aatData[i % n][j];
		return buf;
	}

	void setRow(const CVector<T, n>& buf, int i) {
		for (int j = 0; j < n; j++)			// SPALTE j
			m_aatData[i % n][j] = buf[j];
	}


	void transpose() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++)
				swap(i, j);
	}

	void swap(int i, int j) {
		int I = i % n, J = j % n;
		T x = m_aatData[I][J];
		m_aatData[I][J] = m_aatData[J][I];
		m_aatData[J][I] = x;
	}

	// CMatrix<T, SIZE>operator + (const Matrix<T, SIZE> &mat)	// implement yourself, if required
	// CMatrix<T, SIZE>operator - (const Matrix<T, SIZE> &mat)	// implement yourself, if required
};

// some common vector classes (abbr. names)
typedef CMatrix<float, 2> CMat2f;
typedef CMatrix<float, 3> CMat3f;
typedef CMatrix<float, 4> CMat4f;

typedef CMatrix<double, 2> CMat2d;
typedef CMatrix<double, 3> CMat3d;
typedef CMatrix<double, 4> CMat4d;

CMat4d affineInverse(const CMat4d& M);	// inverse of AFFINE MAP only!!!

CMat2f rotateMat(const float theta) {
	CMat2f m;
	m.setRow(CVec2f(cos(theta), -sin(theta)), 0);
	m.setRow(CVec2f(sin(theta), cos(theta)), 1);
	return m;
}
