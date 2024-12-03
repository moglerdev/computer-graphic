
#include "Matrix.h"
#include "Vector.h"


CMat4d affineInverse(const CMat4d& M)
// Computes the inverse of a 4x4 matrix M of the form 
//             ⎡ R  P ⎤
//         M = ⎢      ⎥,
//             ⎣ 0  1 ⎦
// with an orthonormal 3x3 matrix R, a 3d-column vector P and a 3d-row vector 0=(0,0,0).
//
// The inverse if computed as
//				⎡ Rᵗ -Rᵗ·P ⎤
//      M⁻¹ =	⎢          ⎥ .
//				⎣  0   1   ⎦
//
// The steps in the computation are 
//			⎡ R  P ⎤		⎡ R  0 ⎤		⎡ Rᵗ  0 ⎤		⎡ Rᵗ -Rᵗ·P ⎤     ⎡ Rᵗ -Rᵗ·P ⎤
//		M = ⎢      ⎥	⇒¹	⎢      ⎥	⇒²	⎢       ⎥	⇒³	⎢          ⎥ ⇒⁴	⎢          ⎥ = M⁻¹ .
//			⎣ 0  1 ⎦		⎣ 0  1 ⎦		⎣ 0   1 ⎦		⎣  0   -1  ⎦     ⎣  0   1   ⎦
//
{
	CMat4d T = M;
	CVec4d P = M.getCol(3);	// step 0: copy P from M
	CVec4d b;
	b[0] = 0.0f;
	b[1] = 0.0f;
	b[2] = 0.0f;
	b[3] = 1.0f;


	T.setCol(b, 3);			// step ⇒¹: remove P from M		-> the upper left 3x3 block of M is R
	T.transpose();			// step ⇒²: transpose M			-> the upper left 3x3 block of M is Rᵗ 
	T.setCol(-(M * P), 3);	// step ⇒³: insert -Rᵗ·P into M	-> M⁻¹ with a negative entry M(3,3)
	T(3, 3) = 1.0;			// step ⇒⁴: correct M(3,3) to 1	-> M⁻¹

	return T;
}

CMat4f affineInverse(const CMat4f& M)
// Computes the inverse of a 4x4 matrix M of the form 
//             ⎡ R  P ⎤
//         M = ⎢      ⎥,
//             ⎣ 0  1 ⎦
// with an orthonormal 3x3 matrix R, a 3d-column vector P and a 3d-row vector 0=(0,0,0).
//
// The inverse if computed as
//				⎡ Rᵗ -Rᵗ·P ⎤
//      M⁻¹ =	⎢          ⎥ .
//				⎣  0   1   ⎦
//
// The steps in the computation are 
//			⎡ R  P ⎤		⎡ R  0 ⎤		⎡ Rᵗ  0 ⎤		⎡ Rᵗ -Rᵗ·P ⎤     ⎡ Rᵗ -Rᵗ·P ⎤
//		M = ⎢      ⎥	⇒¹	⎢      ⎥	⇒²	⎢       ⎥	⇒³	⎢          ⎥ ⇒⁴	⎢          ⎥ = M⁻¹ .
//			⎣ 0  1 ⎦		⎣ 0  1 ⎦		⎣ 0   1 ⎦		⎣  0   -1  ⎦     ⎣  0   1   ⎦
//
{
	CMat4f T = M;
	CVec4f P = M.getCol(3);	// step 0: copy P from M
	CVec4f b;
	b[0] = 0.0f;
	b[1] = 0.0f;
	b[2] = 0.0f;
	b[3] = 1.0f;


	T.setCol(b, 3);			// step ⇒¹: remove P from M		-> the upper left 3x3 block of M is R
	T.transpose();			// step ⇒²: transpose M			-> the upper left 3x3 block of M is Rᵗ 
	T.setCol(-(M * P), 3);	// step ⇒³: insert -Rᵗ·P into M	-> M⁻¹ with a negative entry M(3,3)
	T(3, 3) = 1.0;			// step ⇒⁴: correct M(3,3) to 1	-> M⁻¹

	return T;
}

CMat3f affineInverse(const CMat3f& M)
// Computes the inverse of a 4x4 matrix M of the form 
//             ⎡ R  P ⎤
//         M = ⎢      ⎥,
//             ⎣ 0  1 ⎦
// with an orthonormal 3x3 matrix R, a 3d-column vector P and a 3d-row vector 0=(0,0,0).
//
// The inverse if computed as
//				⎡ Rᵗ -Rᵗ·P ⎤
//      M⁻¹ =	⎢          ⎥ .
//				⎣  0   1   ⎦
//
// The steps in the computation are 
//			⎡ R  P ⎤		⎡ R  0 ⎤		⎡ Rᵗ  0 ⎤		⎡ Rᵗ -Rᵗ·P ⎤     ⎡ Rᵗ -Rᵗ·P ⎤
//		M = ⎢      ⎥	⇒¹	⎢      ⎥	⇒²	⎢       ⎥	⇒³	⎢          ⎥ ⇒⁴	⎢          ⎥ = M⁻¹ .
//			⎣ 0  1 ⎦		⎣ 0  1 ⎦		⎣ 0   1 ⎦		⎣  0   -1  ⎦     ⎣  0   1   ⎦
//
{
	CMat3f T = M;
	CVec3f P = M.getCol(2);	// step 0: copy P from M
	CVec3f b;
	b[0] = 0.0f;
	b[1] = 0.0f;
	b[2] = 1.0f;


	T.setCol(b, 2);			// step ⇒¹: remove P from M		-> the upper left 3x3 block of M is R
	T.transpose();			// step ⇒²: transpose M			-> the upper left 3x3 block of M is Rᵗ 
	T.setCol(-(M * P), 2);	// step ⇒³: insert -Rᵗ·P into M	-> M⁻¹ with a negative entry M(3,3)
	T(2, 2) = 1.0;			// step ⇒⁴: correct M(3,3) to 1	-> M⁻¹

	return T;
}

