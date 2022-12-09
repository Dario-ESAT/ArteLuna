// @author Enrique Gil <gilte@esat-alumni.com>
// @file matrix_4 header and inline functions implementation

#ifndef __MATRIX4_H__
#define __MATRIX4_H__ 1

#include "vector_3.h"
#include "vector_4.h"
#include "matrix_3.h"

namespace mathlib {

class Matrix4x4{
 public:

  Matrix4x4();
  Matrix4x4(float values_array[16]);
  Matrix4x4(float value);
  Matrix4x4(const Matrix4x4& copy);
  ~Matrix4x4();

  static Matrix4x4 Identity();
  Matrix4x4 Multiply(const Matrix4x4& other) const;

  float Determinant() const;
  Matrix4x4 Adjoint() const;
  bool GetInverse(Matrix4x4& out) const;
  bool Inverse();
  Matrix4x4 Transpose() const;

  static Matrix4x4 Projection();

  static Matrix4x4 Translate(const Vector3& distance);
  static Matrix4x4 Translate(float x, float y, float z);

  static Matrix4x4 Scale(const Vector3& scale);
  static Matrix4x4 Scale(float x, float y, float z);

  Matrix3x3 Rotation();
  static Matrix4x4 RotateX(float radians);
  static Matrix4x4 RotateY(float radians);
  static Matrix4x4 RotateZ(float radians);

  static Matrix4x4 GetTransform(const Vector3& translate, const Vector3& scale,
                      float rotateX, float rotateY, float rotateZ);

  static Matrix4x4 GetTransform(float trans_x, float trans_y, float trans_z,
                      float scale_x, float scale_y, float scale_z,
                      float rotateX, float rotateY, float rotateZ);

  static Matrix4x4 PerspectiveMatrix(float fov, float aspect,
	  float near, float far);

  static Matrix4x4 OrthoMatrix(float right, float left, float top, float bottom,
	  float near, float far);

  Vector3 TransformVector3(const Vector4& in);

  Vector4 ToVector4(const Vector4& in);
  Vector3 ToVector3(const Vector3& in);

  Vector4 GetColum(int colum) const;
  Vector4 GetLine(int line) const;

  Matrix4x4 operator+(const Matrix4x4& other) const;
  Matrix4x4& operator+=(const Matrix4x4& other);
  Matrix4x4 operator+(float value) const;
  Matrix4x4& operator+=(float value);
  Matrix4x4 operator-(const Matrix4x4& other) const;
  Matrix4x4& operator-=(const Matrix4x4& other);
  Matrix4x4 operator-(float value) const;
  Matrix4x4& operator-=(float value);
  Matrix4x4& operator*=(float value);
  Matrix4x4 operator*(float value) const;
  Matrix4x4& operator/=(float value);
  Matrix4x4 operator/(float value) const;
  bool operator==(const Matrix4x4& other);
  bool operator!=(const Matrix4x4& other);
  void operator=(const Matrix4x4& other);
  void Print() const;

  float m[16];
};

/**
 * @brief Constructor of the Matrix with an array of float
 * 
 * @param values_array The values to set in the matrix
 */
inline Matrix4x4::Matrix4x4() {
  m[0] = 0.0f;
  m[1] = 0.0f;
  m[2] = 0.0f;
  m[3] = 0.0f;

  m[4] = 0.0f;
  m[5] = 0.0f;
  m[6] = 0.0f;
  m[7] = 0.0f;

  m[8] = 0.0f;
  m[9] = 0.0f;
  m[10] = 0.0f;
  m[11] = 0.0f;

  m[12] = 0.0f;
  m[13] = 0.0f;
  m[14] = 0.0f;
  m[15] = 0.0f;
}

/**
 * @brief Constructor of the Matrix with an array of float
 * 
 * @param values_array The values to set in the matrix
 */
inline Matrix4x4::Matrix4x4(float values_array[16]) {
  m[0] = values_array[0];
  m[1] = values_array[4];
  m[2] = values_array[8];
  m[3] = values_array[12];

  m[4] = values_array[1];
  m[5] = values_array[5];
  m[6] = values_array[9];
  m[7] = values_array[13];

  m[8] = values_array[2];
  m[9] = values_array[6];
  m[10] = values_array[10];
  m[11] = values_array[14];

  m[12] = values_array[3];
  m[13] = values_array[7];
  m[14] = values_array[11];
  m[15] = values_array[15];
}

/**
 * @brief Constructor of the Matrix with a float
 * 
 * @param value The value to set in the matrix
 */
inline Matrix4x4::Matrix4x4(float value) {
  m[0] = value;
  m[1] = value;
  m[2] = value;
  m[3] = value;

  m[4] = value;
  m[5] = value;
  m[6] = value;
  m[7] = value;

  m[8] = value;
  m[9] = value;
  m[10] = value;
  m[11] = value;

  m[12] = value;
  m[13] = value;
  m[14] = value;
  m[15] = value;
}

/**
 * @brief Copy constructor of the Matrix
 * 
 * @param copy The matrix to copy
 */
inline Matrix4x4::Matrix4x4(const Matrix4x4& copy) {
  m[0] = copy.m[0];
  m[1] = copy.m[1];
  m[2] = copy.m[2];
  m[3] = copy.m[3];

  m[4] = copy.m[4];
  m[5] = copy.m[5];
  m[6] = copy.m[6];
  m[7] = copy.m[7];

  m[8] = copy.m[8];
  m[9] = copy.m[9];
  m[10] = copy.m[10];
  m[11] = copy.m[11];

  m[12] = copy.m[12];
  m[13] = copy.m[13];
  m[14] = copy.m[14];
  m[15] = copy.m[15];
  int i = 0;
}

/**
 * @brief Matrix destructor
 */
inline Matrix4x4::~Matrix4x4() {}

/**
 * @brief returns the Identity Matrix.
 * 
 * @return result
 */
inline Matrix4x4 Matrix4x4::Identity() {
  Matrix4x4 result;

  result.m[0] = 1.0f;
  result.m[1] = 0.0f;
  result.m[2] = 0.0f;
  result.m[3] = 0.0f;

  result.m[4] = 0.0f;
  result.m[5] = 1.0f;
  result.m[6] = 0.0f;
  result.m[7] = 0.0f;

  result.m[8] = 0.0f;
  result.m[9] = 0.0f;
  result.m[10] = 1.0f;
  result.m[11] = 0.0f;

  result.m[12] = 0.0f;
  result.m[13] = 0.0f;
  result.m[14] = 0.0f;
  result.m[15] = 1.0f;

	return result;
}

/**
 * @brief returns the Proyection Matrix.
 * 
 * @return result
 */
inline Matrix4x4 Matrix4x4::Projection() {
  Matrix4x4 result;

  result.m[0] = 1.0f;
  result.m[1] = 0.0f;
  result.m[2] = 0.0f;
  result.m[3] = 0.0f;

  result.m[4] = 0.0f;
  result.m[5] = 1.0f;
  result.m[6] = 0.0f;
  result.m[7] = 0.0f;

  result.m[8] = 0.0f;
  result.m[9] = 0.0f;
  result.m[10] = 1.0f;
  result.m[11] = 1.0f;

  result.m[12] = 0.0f;
  result.m[13] = 0.0f;
  result.m[14] = 0.0f;
  result.m[15] = 0.0f;

	return result;
}

/**
 * @brief Multiplies the matrix.
 * 
 * @param other Matrix to multiply with
 * @return result
 */
inline Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& other)const  {
  Matrix4x4 result;

  result.m[0] = m[0] * other.m[0] + m[4] * other.m[1] + m[8] * other.m[2] + m[12] * other.m[3];
  result.m[1] = m[1] * other.m[0] + m[5] * other.m[1] + m[9] * other.m[2] + m[13] * other.m[3];
  result.m[2] = m[2] * other.m[0] + m[6] * other.m[1] + m[10] * other.m[2] + m[14] * other.m[3];
  result.m[3] = m[3] * other.m[0] + m[7] * other.m[1] + m[11] * other.m[2] + m[15] * other.m[3];

  result.m[4] = m[0] * other.m[4] + m[4] * other.m[5] + m[8] * other.m[6] + m[12] * other.m[7];
  result.m[5] = m[1] * other.m[4] + m[5] * other.m[5] + m[9] * other.m[6] + m[13] * other.m[7];
  result.m[6] = m[2] * other.m[4] + m[6] * other.m[5] + m[10] * other.m[6] + m[14] * other.m[7];
  result.m[7] = m[3] * other.m[4] + m[7] * other.m[5] + m[11] * other.m[6] + m[15] * other.m[7];

  result.m[8] = m[0] * other.m[8] + m[4] * other.m[9] + m[8] * other.m[10] + m[12] * other.m[11];
  result.m[9] = m[1] * other.m[8] + m[5] * other.m[9] + m[9] * other.m[10] + m[13] * other.m[11];
  result.m[10] = m[2] * other.m[8] + m[6] * other.m[9] + m[10] * other.m[10] + m[14] * other.m[11];
  result.m[11] = m[3] * other.m[8] + m[7] * other.m[9] + m[11] * other.m[10] + m[15] * other.m[11];

  result.m[12] = m[0] * other.m[12] + m[4] * other.m[13] + m[8] * other.m[14] + m[12] * other.m[15];
  result.m[13] = m[1] * other.m[12] + m[5] * other.m[13] + m[9] * other.m[14] + m[13] * other.m[15];
  result.m[14] = m[2] * other.m[12] + m[6] * other.m[13] + m[10] * other.m[14] + m[14] * other.m[15];
  result.m[15] = m[3] * other.m[12] + m[7] * other.m[13] + m[11] * other.m[14] + m[15] * other.m[15];

	return result;
}

/**
 * @brief Gets the determinant of the Matrix.
 * 
 * @return result
 */
inline float Matrix4x4::Determinant() const {

  Matrix3x3 auxMatrix[4];

  auxMatrix[0].m[0] = m[5]; auxMatrix[0].m[1] = m[6]; auxMatrix[0].m[2] = m[7];
  auxMatrix[0].m[3] = m[9]; auxMatrix[0].m[4] = m[10]; auxMatrix[0].m[5] = m[11];
  auxMatrix[0].m[6] = m[13]; auxMatrix[0].m[7] = m[14]; auxMatrix[0].m[8] = m[15];

  auxMatrix[1].m[0] = m[4]; auxMatrix[1].m[1] = m[6]; auxMatrix[1].m[2] = m[7];
  auxMatrix[1].m[3] = m[8]; auxMatrix[1].m[4] = m[10]; auxMatrix[1].m[5] = m[11];
  auxMatrix[1].m[6] = m[12]; auxMatrix[1].m[7] = m[14]; auxMatrix[1].m[8] = m[15];

  auxMatrix[2].m[0] = m[4]; auxMatrix[2].m[1] = m[5]; auxMatrix[2].m[2] = m[7];
  auxMatrix[2].m[3] = m[8]; auxMatrix[2].m[4] = m[9]; auxMatrix[2].m[5] = m[11];
  auxMatrix[2].m[6] = m[12]; auxMatrix[2].m[7] = m[13]; auxMatrix[2].m[8] = m[15];

  auxMatrix[3].m[0] = m[4]; auxMatrix[3].m[1] = m[5]; auxMatrix[3].m[2] = m[6];
  auxMatrix[3].m[3] = m[8]; auxMatrix[3].m[4] = m[9]; auxMatrix[3].m[5] = m[10];
  auxMatrix[3].m[6] = m[12]; auxMatrix[3].m[7] = m[13]; auxMatrix[3].m[8] = m[14];
	
	return ( m[0] * auxMatrix[0].Determinant() ) - ( m[1] * auxMatrix[1].Determinant() ) + ( m[2] * auxMatrix[2].Determinant() ) - ( m[3] * auxMatrix[3].Determinant() );
}

/**
 * @brief Gets the Adjoint of the Matrix.
 * 
 * @return result 
 */
inline Matrix4x4 Matrix4x4::Adjoint() const {
  Matrix4x4 result;
  Matrix3x3 aux[16];
  /* 
    m[0] m[4] m[8] m[12]
    m[1] m[5] m[9] m[13]
    m[2] m[6] m[10]m[14]
    m[3] m[7] m[11]m[15]
   */

  // m[0]
  aux[0].m[0] = m[5]; aux[0].m[3] = m[6]; aux[0].m[6] = m[7];
  aux[0].m[1] = m[9]; aux[0].m[4] = m[10]; aux[0].m[7] = m[11];
  aux[0].m[2] = m[13]; aux[0].m[5] = m[14]; aux[0].m[8] = m[15];

  // m[1]
  aux[1].m[0] = m[4]; aux[1].m[3] = m[6]; aux[1].m[6] = m[7];
  aux[1].m[1] = m[8]; aux[1].m[4] = m[10]; aux[1].m[7] = m[11];
  aux[1].m[2] = m[12]; aux[1].m[5] = m[14]; aux[1].m[8] = m[15];

  // m[2]
  aux[2].m[0] = m[4]; aux[2].m[3] = m[5]; aux[2].m[6] = m[7];
  aux[2].m[1] = m[8]; aux[2].m[4] = m[9]; aux[2].m[7] = m[11];
  aux[2].m[2] = m[12]; aux[2].m[5] = m[13]; aux[2].m[8] = m[15];

  // m[3]
  aux[3].m[0] = m[4]; aux[3].m[3] = m[5]; aux[3].m[6] = m[6];
  aux[3].m[1] = m[8]; aux[3].m[4] = m[9]; aux[3].m[7] = m[10];
  aux[3].m[2] = m[12]; aux[3].m[5] = m[13]; aux[3].m[8] = m[14];

  // m[4]
  aux[4].m[0] = m[1]; aux[4].m[3] = m[2]; aux[4].m[6] = m[3];
  aux[4].m[1] = m[9]; aux[4].m[4] = m[10]; aux[4].m[7] = m[11];
  aux[4].m[2] = m[13]; aux[4].m[5] = m[14]; aux[4].m[8] = m[15];

  // m[5]
  aux[5].m[0] = m[0]; aux[5].m[3] = m[2]; aux[5].m[6] = m[3];
  aux[5].m[1] = m[8]; aux[5].m[4] = m[10]; aux[5].m[7] = m[11];
  aux[5].m[2] = m[12]; aux[5].m[5] = m[14]; aux[5].m[8] = m[15];

  // m[6]
  aux[6].m[0] = m[0]; aux[6].m[3] = m[1]; aux[6].m[6] = m[3];
  aux[6].m[1] = m[8]; aux[6].m[4] = m[9]; aux[6].m[7] = m[11];
  aux[6].m[2] = m[12]; aux[6].m[5] = m[13]; aux[6].m[8] = m[15];
  
  // m[7]
  aux[7].m[0] = m[0]; aux[7].m[3] = m[1]; aux[7].m[6] = m[2];
  aux[7].m[1] = m[8]; aux[7].m[4] = m[9]; aux[7].m[7] = m[10];
  aux[7].m[2] = m[12]; aux[7].m[5] = m[13]; aux[7].m[8] = m[14];

  // m[8]
  aux[8].m[0] = m[1]; aux[8].m[3] = m[2]; aux[8].m[6] = m[3];
  aux[8].m[1] = m[5]; aux[8].m[4] = m[6]; aux[8].m[7] = m[7];
  aux[8].m[2] = m[13]; aux[8].m[5] = m[14]; aux[8].m[8] = m[15];

  // m[9]
  aux[9].m[0] = m[0]; aux[9].m[3] = m[2]; aux[9].m[6] = m[3];
  aux[9].m[1] = m[4]; aux[9].m[4] = m[6]; aux[9].m[7] = m[7];
  aux[9].m[2] = m[12]; aux[9].m[5] = m[14]; aux[9].m[8] = m[15];
  
  // m[10]
  aux[10].m[0] = m[0]; aux[10].m[3] = m[1]; aux[10].m[6] = m[3];
  aux[10].m[1] = m[4]; aux[10].m[4] = m[5]; aux[10].m[7] = m[7];
  aux[10].m[2] = m[12]; aux[10].m[5] = m[13]; aux[10].m[8] = m[15];
  
  // m[11]
  aux[11].m[0] = m[0]; aux[11].m[3] = m[1]; aux[11].m[6] = m[2];
  aux[11].m[1] = m[4]; aux[11].m[4] = m[5]; aux[11].m[7] = m[6];
  aux[11].m[2] = m[12]; aux[11].m[5] = m[13]; aux[11].m[8] = m[14];
  
  // m[12]
  aux[12].m[0] = m[1]; aux[12].m[3] = m[2]; aux[12].m[6] = m[3];
  aux[12].m[1] = m[5]; aux[12].m[4] = m[6]; aux[12].m[7] = m[7];
  aux[12].m[2] = m[9]; aux[12].m[5] = m[10]; aux[12].m[8] = m[11];
  
  // m[13]
  aux[13].m[0] = m[0]; aux[13].m[3] = m[2]; aux[13].m[6] = m[3];
  aux[13].m[1] = m[4]; aux[13].m[4] = m[6]; aux[13].m[7] = m[7];
  aux[13].m[2] = m[8]; aux[13].m[5] = m[10]; aux[13].m[8] = m[11];
  
  // m[14]
  aux[14].m[0] = m[0]; aux[14].m[3] = m[1]; aux[14].m[6] = m[3];
  aux[14].m[1] = m[4]; aux[14].m[4] = m[5]; aux[14].m[7] = m[7];
  aux[14].m[2] = m[8]; aux[14].m[5] = m[9]; aux[14].m[8] = m[11];
  
  // m[15]
  aux[15].m[0] = m[0]; aux[15].m[3] = m[1]; aux[15].m[6] = m[2];
  aux[15].m[1] = m[4]; aux[15].m[4] = m[5]; aux[15].m[7] = m[6];
  aux[15].m[2] = m[8]; aux[15].m[5] = m[9]; aux[15].m[8] = m[10];


  result.m[0] = aux[0].Determinant();
  result.m[4] = aux[1].Determinant() * -1.0f;
  result.m[8] = aux[2].Determinant();
  result.m[12] = aux[3].Determinant() * -1.0f;

  result.m[1] = aux[4].Determinant() * -1.0f;
  result.m[5] = aux[5].Determinant();
  result.m[9] = aux[6].Determinant() * -1.0f;
  result.m[13] = aux[7].Determinant();

  result.m[2] = aux[8].Determinant();
  result.m[6] = aux[9].Determinant() * -1.0f;
  result.m[10] = aux[10].Determinant();
  result.m[14] = aux[11].Determinant() * -1.0f;

  result.m[3] = aux[12].Determinant() * -1.0f;
  result.m[7] = aux[13].Determinant();
  result.m[11] = aux[14].Determinant() * -1.0f;
  result.m[15] = aux[15].Determinant();
  
	return result;
}

/**
 * @brief Checks if the matrix can get the Inverse.
 * 
 * @param out Matrix to check
 * @return true if it can get the inverse
 */
inline bool Matrix4x4::GetInverse(Matrix4x4& out) const {

	Matrix4x4 aux = Adjoint().Transpose();

  float determinant = Determinant();
  if (determinant == 0.0f) {
    return false;
  }
  
  out.m[0] = 1.0f / determinant * aux.m[0];
  out.m[4] = 1.0f / determinant * aux.m[1];
  out.m[8] = 1.0f / determinant * aux.m[2];
  out.m[12] = 1.0f / determinant * aux.m[3];

  out.m[1] = 1.0f / determinant * aux.m[4];
  out.m[5] = 1.0f / determinant * aux.m[5];
  out.m[9] = 1.0f / determinant * aux.m[6];
  out.m[13] = 1.0f / determinant * aux.m[7];

  out.m[2] = 1.0f / determinant * aux.m[8];
  out.m[6] = 1.0f / determinant * aux.m[9];
  out.m[10] = 1.0f / determinant * aux.m[10];
  out.m[14] = 1.0f / determinant * aux.m[11];

  out.m[3] = 1.0f / determinant * aux.m[12];
  out.m[7] = 1.0f / determinant * aux.m[13];
  out.m[11] = 1.0f / determinant * aux.m[14];
  out.m[15] = 1.0f / determinant * aux.m[15];
  
	return true;
}

/**
 * @brief Sets the Inverse of the Matrix.
 * 
 * @return true if it can be done.
 */
inline bool Matrix4x4::Inverse() {

  Matrix4x4 aux = Adjoint().Transpose();

  float determinant = Determinant();
  if (determinant == 0.0f) {
    return false;
  }
  m[0] = 1.0f / determinant * aux.m[0];
  m[4] = 1.0f / determinant * aux.m[1];
  m[8] = 1.0f / determinant * aux.m[2];
  m[12] = 1.0f / determinant * aux.m[3];

  m[1] = 1.0f / determinant * aux.m[4];
  m[5] = 1.0f / determinant * aux.m[5];
  m[9] = 1.0f / determinant * aux.m[6];
  m[13] = 1.0f / determinant * aux.m[7];

  m[2] = 1.0f / determinant * aux.m[8];
  m[6] = 1.0f / determinant * aux.m[9];
  m[10] = 1.0f / determinant * aux.m[10];
  m[14] = 1.0f / determinant * aux.m[11];

  m[3] = 1.0f / determinant * aux.m[12];
  m[7] = 1.0f / determinant * aux.m[13];
  m[11] = 1.0f / determinant * aux.m[14];
  m[15] = 1.0f / determinant * aux.m[15];

	return true;
}

/**
 * @brief Gets the transpose of the Matrix.
 * 
 * @return result
 */
inline Matrix4x4 Matrix4x4::Transpose() const {
  Matrix4x4 result;

  result.m[0] = m[0]; result.m[1] = m[4]; result.m[2] = m[8]; result.m[3] = m[12];
  result.m[4] = m[1]; result.m[5] = m[5]; result.m[6] = m[9]; result.m[7] = m[13];
  result.m[8] = m[2]; result.m[9] = m[6]; result.m[10] = m[10]; result.m[11] = m[14];
  result.m[12] = m[3]; result.m[13] = m[7]; result.m[14] = m[11]; result.m[15] = m[15];
		
	return result;
}

/**
 * @brief Translates the Matrix with a Vector3.
 * 
 * @param distance how much the Matrix is going to move
 * @return result
 */
inline Matrix4x4 Matrix4x4::Translate(const Vector3& distance) {
	
	Matrix4x4 result;
  
  result.m[0] = 1.0f;

  result.m[5] = 1.0f;

  result.m[10] = 1.0f;

  result.m[12] = distance.x;
  result.m[13] = distance.y;
  result.m[14] = distance.z;
  result.m[15] = 1.0f;

	return result;
}

/**
 * @brief Translates the Matrix in x and y with three floats.
 * 
 * @param x How much is the Matrix is going to move on x axis.
 * @param y How much is the Matrix is going to move on y axis.
 * @param z How much is the Matrix is going to move on z axis.
 * @return result
 */
inline Matrix4x4 Matrix4x4::Translate(float x, float y, float z) { 

	Matrix4x4 result;

  result.m[0] = 1.0f;

  result.m[5] = 1.0f;

  result.m[10] = 1.0f;

  result.m[12] = x;
  result.m[13] = y;
  result.m[14] = z;
  result.m[15] = 1.0f;

	return result;
}

/**
 * @brief Scales the Matrix using a Vector3
 * 
 * @param scale How much the matrix is going to be scaled
 * @return result
 */
inline Matrix4x4 Matrix4x4::Scale(const Vector3& scale) {
	Matrix4x4 result;

	result.m[0] = scale.x;

	result.m[5] = scale.y;

	result.m[10] = scale.z;

  result.m[15] = 1.0f;

	return result;
}

/**
 * @brief Scales the Matrix using three floats
 * 
 * @param x How much the matrix is going to be scaled on x axis
 * @param y How much the matrix is going to be scaled on y axis
 * @param z How much the matrix is going to be scaled on z axis
 * @return result
 */
inline Matrix4x4 Matrix4x4::Scale(float x, float y, float z) {
	Matrix4x4 result;

	result.m[0] = x;
  
	result.m[5] = y;
  
	result.m[10] = z;
  
  result.m[15] = 1.0f;

	return result;
}

inline Matrix3x3 Matrix4x4::Rotation() {
    Vector3 r1{ m[0], m[1], m[2] };
    Vector3 r2{ m[4], m[5], m[6] };
    Vector3 r3{ m[8], m[9], m[10]};
    Matrix3x3 result(r1,r2,r3);
    return result;
}
    
/**
 * @brief Rotates the Matrix on x axis
 * 
 * @param radians How much the matrix is going to be rotated
 * @return result
 */
inline Matrix4x4 Matrix4x4::RotateX(float radians) {

	Matrix4x4 result;
  
  result.m[0] = 1.0f;

	result.m[5] = cosf(radians);
	result.m[6] = sinf(radians);
  
	result.m[9] = -sinf(radians);
	result.m[10] = cosf(radians);
  
  result.m[15] = 1.0f;


	return result;
}

/**
 * @brief Rotates the Matrix on y axis
 * 
 * @param radians How much the matrix is going to be rotated
 * @return result
 */
inline Matrix4x4 Matrix4x4::RotateY(float radians) {
	
	Matrix4x4 result;

	result.m[0] = cosf(radians);
  
	result.m[2] = -sinf(radians);
  
  result.m[5] = 1.0f;

	result.m[8] = sinf(radians);
  
	result.m[10] = cosf(radians);
  
  result.m[15] = 1.0f;
	
	return result;
}

/**
 * @brief Rotates the Matrix on z axis
 * 
 * @param radians How much the matrix is going to be rotated
 * @return result
 */
inline Matrix4x4 Matrix4x4::RotateZ(float radians) {
	
	Matrix4x4 result;

	result.m[0] = cosf(radians);
	result.m[1] = sinf(radians);

	result.m[4] = -sinf(radians);
	result.m[5] = cosf(radians);
  
  result.m[10] = 1.0f;
  
  result.m[15] = 1.0f;
	
	return result;
}

/**
 * @brief Gets the the Matrix transformed by the parameters
 * 
 * @param translate How much the matrix is going to translate
 * @param scale How much the matrix is going to scale
 * @param rotateX How much the matrix is going to be rotated on x axis
 * @param rotateY How much the matrix is going to be rotated on y axis
 * @param rotateZ How much the matrix is going to be rotated on z axis
 * 
 * @return result
 */
inline Matrix4x4 Matrix4x4::GetTransform(const Vector3& translate,
								const Vector3& scale,
								float rotateX, float rotateY, float rotateZ)   {

	Matrix4x4 result;
	Matrix4x4 translation;
	Matrix4x4 scaling;
	Matrix4x4 rotation;

  rotation = rotation.RotateX(rotateX).Multiply(
    rotation.RotateY(rotateY).Multiply(
      rotation.RotateZ(rotateZ)));

  result = translation.Translate(translate.x,translate.y,translate.z).Multiply(
    rotation.Multiply(scaling.Scale(scale.x,scale.y,scale.z))
  );

	return result;
}

/**
 * @brief Gets the the Matrix transformed by the parameters
 * 
 * @param trans_x How much the matrix is going to translate on x axis
 * @param trans_y How much the matrix is going to translate on y axis
 * @param trans_z How much the matrix is going to translate on z axis
 * @param scale_x How much the matrix is going to scale on x axis
 * @param scale_y How much the matrix is going to scale on y axis
 * @param scale_z How much the matrix is going to scale on z axis
 * @param rotateX How much the matrix is going to be rotated on x axis
 * @param rotateY How much the matrix is going to be rotated on y axis
 * @param rotateZ How much the matrix is going to be rotated on z axis
 * 
 * @return result
 */
inline Matrix4x4 Matrix4x4::GetTransform(float trans_x, float trans_y, float trans_z,
								float scale_x, float scale_y, float scale_z,
								float rotateX, float rotateY, float rotateZ)  {
	
	Matrix4x4 result;
	Matrix4x4 translation;
	Matrix4x4 scaling;
	Matrix4x4 rotation;

  rotation = rotation.RotateX(rotateX).Multiply(
    rotation.RotateY(rotateY).Multiply(
      rotation.RotateZ(rotateZ)));
      
  result = translation.Translate(trans_x,trans_y,trans_z).Multiply(
    rotation.Multiply(scaling.Scale(scale_x,scale_y,scale_z))
  );

	return result;
}

/**
 * @brief Gets the perspective Matrix
 * 
 * @param fov
 * @param aspect
 * @param fnear
 * @param ffar
 * @return result
 */
inline Matrix4x4 Matrix4x4::PerspectiveMatrix(float fov, float aspect,
	float near, float far) {

	Matrix4x4 result;

	result.m[0] = ( 1 / (aspect * tanf(fov/2) ) );

	result.m[5] = ( 1 / tanf(fov/2) );

	result.m[10] = -( (far + near) / (far - near) );

	result.m[11] = -1;

	result.m[14] = -( (2 * far * near) / (far - near) );
	
	return result;
}

/**
 * @brief Gets the Orthodox Matrix
 * 
 * @param right
 * @param left
 * @param top
 * @param bottom
 * @param fnear
 * @param ffar
 * @return result
 */
inline Matrix4x4 Matrix4x4::OrthoMatrix(float right, float left, float top, float bottom,
	float near, float far) {
	Matrix4x4 result = result.Identity();
	result.m[0] = ( 2/(right - left) );
  
	result.m[5] = ( 2/(top - bottom) );
  
	result.m[10] = ( -2/(far - near) );
  

	result.m[12] = -( (right + left)/(right - left) );
	result.m[13] = -( (top + bottom)/(top - bottom) );
	result.m[14] = -( (far + near)/(far - near) );
  result.m[15] = 1.0f;

	return result;
}


/**
 * @brief Gets the Vector3 result by a transformation of a Vector4
 * 
 * @param Vector4 Vector4 to transform.
 * 
 * @return Vector3 result
 */
inline Vector3 Matrix4x4::TransformVector3(const Vector4& in) {
  Vector4 aux = ToVector4(in);
  Vector3 result;

  result.x = aux.x / aux.w;
  result.y = aux.y / aux.w;
  result.z = aux.z / aux.w;

  return result;
}

/**
 * @brief Gets the Vector4 result by a transformation of a Vector4
 * 
 * @param Vector4 Vector4 to transform.
 * 
 * @return Vector4 result
 */
inline Vector4 Matrix4x4::ToVector4(const Vector4& in) {
  Vector4 result;
  result.x = m[0] * in.x + m[4] * in.y + m[8] * in.z + m[12] * in.w;
  result.y = m[1] * in.x + m[5] * in.y + m[9] * in.z + m[13] * in.w;
  result.z = m[2] * in.x + m[6] * in.y + m[10] * in.z + m[14] * in.w;
  result.w = m[3] * in.x + m[7] * in.y + m[11] * in.z + m[15] * in.w;
  
  return result;
}

/**
 * @brief Gets a column of the Matrix.
 * 
 * @param colum Which colum of the Matrix is going to return
 * @return result
 */
inline Vector4 Matrix4x4::GetColum(int colum) const {

	Vector4 result;

  result.x = m[0 + colum * 4];
  result.y = m[1 + colum * 4];
  result.z = m[2 + colum * 4];
	result.w = m[3 + colum * 4];

	return result;
}

/**
 * @brief Gets a line of the Matrix.
 * 
 * @param line Which line of the Matrix is going to return
 * @return result
 */
inline Vector4 Matrix4x4::GetLine(int line) const {

	Vector4 result;

	result.x = m[0 + line];
  result.y = m[4 + line];
  result.z = m[8 + line];
	result.w = m[12 + line];

	return result;
}

/* ----- OPERATOR FUNCTIONS ----- */

/**
 * @brief Adds two Matrix.
 * 
 * @param other How much is going to be added to the Matrix 
 * @return result 
 */
inline Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other) const {
  Matrix4x4 result;

  result.m[0] = m[0] + other.m[0];
  result.m[1] = m[1] + other.m[1];
  result.m[2] = m[2] + other.m[2];
  result.m[3] = m[3] + other.m[3];

  result.m[4] = m[4] + other.m[4];
  result.m[5] = m[5] + other.m[5];
  result.m[6] = m[6] + other.m[6];
  result.m[7] = m[7] + other.m[7];

  result.m[8] = m[8] + other.m[8];
  result.m[9] = m[9] + other.m[9];
  result.m[10] = m[10] + other.m[10];
  result.m[11] = m[11] + other.m[11];

  result.m[12] = m[12] + other.m[12];
  result.m[13] = m[13] + other.m[13];
  result.m[14] = m[14] + other.m[14];
  result.m[16] = m[16] + other.m[16];
	return result;
}

/**
 * @brief Sets the sum of the matrix.
 * 
 * @param other How much is going to be added to the Matrix 
 * @return this ptr 
 */
inline Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& other) {
	m[0] += other.m[0];
  m[1] += other.m[1];
  m[2] += other.m[2];
  m[3] += other.m[3];

  m[4] += other.m[4];
  m[5] += other.m[5];
  m[6] += other.m[6];
  m[7] += other.m[7];

  m[8] += other.m[8];
  m[9] += other.m[9];
  m[10] += other.m[10];
  m[11] += other.m[11];

  m[12] += other.m[12];
  m[13] += other.m[13];
  m[14] += other.m[14];
  m[16] += other.m[16];

	return *this;
}

/**
 * @brief Adds a matrix and a float.
 * 
 * @param value How much is going to be added to the Matrix 
 * @return result 
 */
inline Matrix4x4 Matrix4x4::operator+(float value) const {
  Matrix4x4 result;

	result.m[0] = m[0] + value;
  result.m[1] = m[1] + value;
  result.m[2] = m[2] + value;
  result.m[3] = m[3] + value;

  result.m[4] = m[4] + value;
  result.m[5] = m[5] + value;
  result.m[6] = m[6] + value;
  result.m[7] = m[7] + value;

  result.m[8] = m[8] + value;
  result.m[9] = m[9] + value;
  result.m[10] = m[10] + value;
  result.m[11] = m[11] + value;

  result.m[12] = m[12] + value;
  result.m[13] = m[13] + value;
  result.m[14] = m[14] + value;
  result.m[16] = m[16] + value;

  return result;
}

/**
 * @brief Sets the sum of the matrix and a float.
 * 
 * @param value How much is going to be added to the Matrix 
 * @return this ptr 
 */
inline Matrix4x4& Matrix4x4::operator+=(float value) {
  m[0] += value;
  m[1] += value;
  m[2] += value;
  m[3] += value;

  m[4] += value;
  m[5] += value;
  m[6] += value;
  m[7] += value;

  m[8] += value;
  m[9] += value;
  m[10] += value;
  m[11] += value;

  m[12] += value;
  m[13] += value;
  m[14] += value;
  m[16] += value;

	return *this;
}

/**
 * @brief Substracts two Matrix.
 * 
 * @param other How much is going to be substracted to the Matrix 
 * @return result 
 */
inline Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other) const  {
	Matrix4x4 result;

  result.m[0] = m[0] - other.m[0];
  result.m[1] = m[1] - other.m[1];
  result.m[2] = m[2] - other.m[2];
  result.m[3] = m[3] - other.m[3];

  result.m[4] = m[4] - other.m[4];
  result.m[5] = m[5] - other.m[5];
  result.m[6] = m[6] - other.m[6];
  result.m[7] = m[7] - other.m[7];

  result.m[8] = m[8] - other.m[8];
  result.m[9] = m[9] - other.m[9];
  result.m[10] = m[10] - other.m[10];
  result.m[11] = m[11] - other.m[11];

  result.m[12] = m[12] - other.m[12];
  result.m[13] = m[13] - other.m[13];
  result.m[14] = m[14] - other.m[14];
  result.m[16] = m[16] - other.m[16];

  return result;
}

/**
 * @brief Sets the substraction of the matrix.
 * 
 * @param other How much is going to be substracted to the Matrix 
 * @return this ptr 
 */
inline Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& other) {

  m[0] -= other.m[0];
  m[1] -= other.m[1];
  m[2] -= other.m[2];
  m[3] -= other.m[3];

  m[4] -= other.m[4];
  m[5] -= other.m[5];
  m[6] -= other.m[6];
  m[7] -= other.m[7];

  m[8] -= other.m[8];
  m[9] -= other.m[9];
  m[10] -= other.m[10];
  m[11] -= other.m[11];

  m[12] -= other.m[12];
  m[13] -= other.m[13];
  m[14] -= other.m[14];
  m[16] -= other.m[16];

	return *this;
}

/**
 * @brief substracts a matrix and a float.
 * 
 * @param value How much is going to be substracted to the Matrix 
 * @return result 
 */
inline Matrix4x4 Matrix4x4::operator-(float value) const  {
  Matrix4x4 result;

  result.m[0] = m[0] - value;
  result.m[1] = m[1] - value;
  result.m[2] = m[2] - value;
  result.m[3] = m[3] - value;

  result.m[4] = m[4] - value;
  result.m[5] = m[5] - value;
  result.m[6] = m[6] - value;
  result.m[7] = m[7] - value;

  result.m[8] = m[8] - value;
  result.m[9] = m[9] - value;
  result.m[10] = m[10] - value;
  result.m[11] = m[11] - value;

  result.m[12] = m[12] - value;
  result.m[13] = m[13] - value;
  result.m[14] = m[14] - value;
  result.m[16] = m[16] - value;
	return  result;
}

/**
 * @brief Sets the subtraction of the matrix and a float.
 * 
 * @param value How much is going to be substracted to the Matrix 
 * @return this ptr 
 */
inline Matrix4x4& Matrix4x4::operator-=(float value) {

  m[0] -= value;
  m[1] -= value;
  m[2] -= value;
  m[3] -= value;

  m[4] -= value;
  m[5] -= value;
  m[6] -= value;
  m[7] -= value;

  m[8] -= value;
  m[9] -= value;
  m[10] -= value;
  m[11] -= value;

  m[12] -= value;
  m[13] -= value;
  m[14] -= value;
  m[16] -= value;

	return *this;
}

/**
 * @brief Sets the multiplication of the matrix and a float.
 * 
 * @param value How much is going to be multiplied to the Matrix 
 * @return this ptr 
 */
inline Matrix4x4& Matrix4x4::operator*=(float value) {

  m[0] *= value;
  m[1] *= value;
  m[2] *= value;
  m[3] *= value;

  m[4] *= value;
  m[5] *= value;
  m[6] *= value;
  m[7] *= value;

  m[8] *= value;
  m[9] *= value;
  m[10] *= value;
  m[11] *= value;

  m[12] *= value;
  m[13] *= value;
  m[14] *= value;
  m[16] *= value;

	return *this;
}

/**
 * @brief Multiplies a matrix and a float.
 * 
 * @param value How much is going to be multiplied to the Matrix 
 * @return result 
 */
inline Matrix4x4 Matrix4x4::operator*(float value) const  {
  Matrix4x4 result;

  result.m[0] = m[0] * value;
  result.m[1] = m[1] * value;
  result.m[2] = m[2] * value;
  result.m[3] = m[3] * value;

  result.m[4] = m[4] * value;
  result.m[5] = m[5] * value;
  result.m[6] = m[6] * value;
  result.m[7] = m[7] * value;

  result.m[8] = m[8] * value;
  result.m[9] = m[9] * value;
  result.m[10] = m[10] * value;
  result.m[11] = m[11] * value;

  result.m[12] = m[12] * value;
  result.m[13] = m[13] * value;
  result.m[14] = m[14] * value;
  result.m[16] = m[16] * value;

	return  result;
}

/**
 * @brief Sets the division of the matrix and a float.
 * 
 * @param value How much is going to be divided to the Matrix 
 * @return this ptr 
 */
inline Matrix4x4& Matrix4x4::operator/=(float value) {
  m[0] /= value;
  m[1] /= value;
  m[2] /= value;
  m[3] /= value;

  m[4] /= value;
  m[5] /= value;
  m[6] /= value;
  m[7] /= value;

  m[8] /= value;
  m[9] /= value;
  m[10] /= value;
  m[11] /= value;

  m[12] /= value;
  m[13] /= value;
  m[14] /= value;
  m[16] /= value;

	return *this;
}

/**
 * @brief Divides a matrix and a float.
 * 
 * @param value How much is going to be divided to the Matrix 
 * @return result 
 */
inline Matrix4x4 Matrix4x4::operator/(float value) const {
  Matrix4x4 result;

  result.m[0] = m[0] / value;
  result.m[1] = m[1] / value;
  result.m[2] = m[2] / value;
  result.m[3] = m[3] / value;

  result.m[4] = m[4] / value;
  result.m[5] = m[5] / value;
  result.m[6] = m[6] / value;
  result.m[7] = m[7] / value;

  result.m[8] = m[8] / value;
  result.m[9] = m[9] / value;
  result.m[10] = m[10] / value;
  result.m[11] = m[11] / value;

  result.m[12] = m[12] / value;
  result.m[13] = m[13] / value;
  result.m[14] = m[14] / value;
  result.m[16] = m[16] / value;

	return  result;
}

/**
 * @brief Checks if a matrix is equal to another one.
 * 
 * @param other the matrix to compare 
 * @return true if they aren equal
 * @return false if they aren't equal 
 */
inline bool Matrix4x4::operator==(const Matrix4x4& other) {
	if (m[0] != other.m[0]) {
    return false;
  }
  if (m[1] != other.m[1]) {
    return false;
  }
  if (m[2] != other.m[2]) {
    return false;
  }
  if (m[3] != other.m[3]) {
    return false;
  }
  if (m[4] != other.m[4]) {
    return false;
  }
  if (m[5] != other.m[5]) {
    return false;
  }
  if (m[6] != other.m[6]) {
    return false;
  }
  if (m[7] != other.m[7]) {
    return false;
  }
  if (m[8] != other.m[8]) {
    return false;
  }
  if (m[9] != other.m[9]) {
    return false;
  }
  if (m[10] != other.m[10]) {
    return false;
  }
  if (m[11] != other.m[11]) {
    return false;
  }
  if (m[12] != other.m[12]) {
    return false;
  }
  if (m[13] != other.m[13]) {
    return false;
  }
  if (m[14] != other.m[14]) {
    return false;
  }
  if (m[15] != other.m[15]) {
    return false;
  }
	return true;
}

/**
 * @brief Checks if a matrix isn't equal to another one.
 * 
 * @param other the matrix to compare 
 * @return true if they aren't equal
 * @return false if they are equal 
 */
inline bool Matrix4x4::operator!=(const Matrix4x4& other) {
	if (m[0] == other.m[0]) {
    return false;
  }
  if (m[1] == other.m[1]) {
    return false;
  }
  if (m[2] == other.m[2]) {
    return false;
  }
  if (m[3] == other.m[3]) {
    return false;
  }
  if (m[4] == other.m[4]) {
    return false;
  }
  if (m[5] == other.m[5]) {
    return false;
  }
  if (m[6] == other.m[6]) {
    return false;
  }
  if (m[7] == other.m[7]) {
    return false;
  }
  if (m[8] == other.m[8]) {
    return false;
  }
  if (m[9] == other.m[9]) {
    return false;
  }
  if (m[10] == other.m[10]) {
    return false;
  }
  if (m[11] == other.m[11]) {
    return false;
  }
  if (m[12] == other.m[12]) {
    return false;
  }
  if (m[13] == other.m[13]) {
    return false;
  }
  if (m[14] == other.m[14]) {
    return false;
  }
  if (m[15] == other.m[15]) {
    return false;
  }
	return true;
}

/**
 * @brief Equals two Matrix.
 * 
 * @param other The new matrix 
 */
inline void Matrix4x4::operator=(const Matrix4x4& other) {
  m[0] = other.m[0];
  m[1] = other.m[1];
  m[2] = other.m[2];
  m[3] = other.m[3];

  m[4] = other.m[4];
  m[5] = other.m[5];
  m[6] = other.m[6];
  m[7] = other.m[7];

  m[8] = other.m[8];
  m[9] = other.m[9];
  m[10] = other.m[10];
  m[11] = other.m[11];

  m[12] = other.m[12];
  m[13] = other.m[13];
  m[14] = other.m[14];
  m[15] = other.m[15];
}

/**
 * @brief Prints the matrix value in console for debugging.
 */
inline void Matrix4x4::Print() const{
  printf("\n[0]: % 1.3f [1]: % 1.3f [2]: % 1.3f [3]: % 1.3f\n[4]: % 1.3f [5]: % 1.3f [6]: % 1.3f [7]: % 1.3f\n[8]: % 1.3f [9]: % 1.3f [10]: % 1.3f [11]: % 1.3f\n[12]: % 1.3f [13]: % 1.3f [14]: % 1.3f [15]: % 1.3f",
    m[0], m[1], m[2], m[3],
    m[4], m[5], m[6], m[7],
    m[8], m[9], m[10], m[11],
    m[12], m[13], m[14], m[15]
  );
}

}

#endif
