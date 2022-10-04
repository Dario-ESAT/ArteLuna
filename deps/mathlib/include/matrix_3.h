// @author Enrique Gil <gilte@esat-alumni.com>
// @file matrix_3 header and inline functions implementation

#ifndef __MATRIX3_H__
#define __MATRIX3_H__ 1

#include "vector_2.h"
#include "vector_3.h"

namespace mathlib {

class Matrix3x3 {
  public:

	Matrix3x3();
	Matrix3x3(float *values_array);
	Matrix3x3(const float *values_array);
	Matrix3x3(float value);
	Matrix3x3(Vector3 a, Vector3 b, Vector3 c);

	Matrix3x3(const Matrix3x3& copy);
	~Matrix3x3();

	static Matrix3x3 Identity();

	Matrix3x3 Multiply(const Matrix3x3& other) const;

	float Determinant() const;

	Matrix3x3 Adjoint() const;
	bool GetInverse(Matrix3x3& out) const;
	bool Inverse();

	Matrix3x3 Transpose() const;

	static Matrix3x3 Translate(const Vector2& position);
	static Matrix3x3 Translate(float x, float y);
	static Matrix3x3 Scale(const Vector2& scale);
  static Matrix3x3 Scale(float x, float y);
  static Matrix3x3 Rotate(float radian);

  static Matrix3x3 GetTransform(const Vector2& pivot, const Vector2& translate,
                      const Vector2& scale, float radians);
                      
  static Matrix3x3 GetTransform(float pivot_x, float pivot_y, float trans_x,
                      float trans_y, float scale_x, float scale_y, float radians);

  Vector2 TransformVector2(const Vector3& in) const;

  Vector3 ToVector3(const Vector3& in) const;

	Vector3 GetColum(int colum) const;
	Vector3 GetLine(int line) const;

	inline Matrix3x3 operator+(const Matrix3x3& other) const;
	inline Matrix3x3& operator+=(const Matrix3x3& other);
	inline Matrix3x3 operator+(float value) const;
	inline Matrix3x3& operator+=(float value);
	inline Matrix3x3 operator-(const Matrix3x3& other) const;
	inline Matrix3x3& operator-=(const Matrix3x3& other);
	inline Matrix3x3 operator-(float value) const;
	inline Matrix3x3& operator-=(float value);
	inline Matrix3x3 operator*(float value) const;
	inline Matrix3x3& operator*=(float value);
	inline Matrix3x3 operator/(float value) const;
	inline Matrix3x3& operator/=(float value);
	bool operator==(const Matrix3x3& other) const;
	bool operator!=(const Matrix3x3& other) const;
	inline void operator=(const Matrix3x3& other);

  void Print() const;

	float m[9];
};
/**
 * @brief Matrix constructor
 */
inline Matrix3x3::Matrix3x3() {
  m[0] = 0.0f;
  m[1] = 0.0f;
  m[2] = 0.0f;

  m[3] = 0.0f;
  m[4] = 0.0f;
  m[5] = 0.0f;

  m[6] = 0.0f;
  m[7] = 0.0f;
  m[8] = 0.0f;
}

/**
 * @brief Constructor of the Matrix with a float
 * 
 * @param value The value to set in the matrix
 */
inline Matrix3x3::Matrix3x3(float value) {
  m[0] = value;
  m[1] = value;
  m[2] = value;

  m[3] = value;
  m[4] = value;
  m[5] = value;

  m[6] = value;
  m[7] = value;
  m[8] = value;
}

/**
 * @brief Constructor of the Matrix with an array of float
 * 
 * @param values_array The values to set in the matrix
 */
inline Matrix3x3::Matrix3x3(float *values_array) {
  m[0] = values_array[0];
  m[1] = values_array[3];
  m[2] = values_array[6];

  m[3] = values_array[1];
  m[4] = values_array[4];
  m[5] = values_array[7];

  m[6] = values_array[2];
  m[7] = values_array[5];
  m[8] = values_array[8];
}

inline Matrix3x3::Matrix3x3(const float *values_array) {
  m[0] = values_array[0];
  m[1] = values_array[3];
  m[2] = values_array[6];

  m[3] = values_array[1];
  m[4] = values_array[4];
  m[5] = values_array[7];

  m[6] = values_array[2];
  m[7] = values_array[5];
  m[8] = values_array[8];
}

/**
 * @brief Constructor of the Matrix with a three vectors
 * 
 * @param a The value to set in the first column
 * @param b The value to set in the second column
 * @param c The value to set in the third column
 */
inline Matrix3x3::Matrix3x3(Vector3 a, Vector3 b, Vector3 c) {
  m[0] = a.x;
  m[1] = a.y;
  m[2] = a.z;

  m[3] = b.x;
  m[4] = b.y;
  m[5] = b.z;

  m[6] = c.x;
  m[7] = c.y;
  m[8] = c.z;
}

/**
 * @brief Copy constructor of the Matrix
 * 
 * @param copy The matrix to copy
 */
inline Matrix3x3::Matrix3x3(const Matrix3x3& copy) {
  m[0] = copy.m[0];
  m[1] = copy.m[1];
  m[2] = copy.m[2];
  m[3] = copy.m[3];
  m[4] = copy.m[4];
  m[5] = copy.m[5];
  m[6] = copy.m[6];
  m[7] = copy.m[7];
  m[8] = copy.m[8];
}

/**
 * @brief Matrix destructor
 */
inline Matrix3x3::~Matrix3x3() { }

/**
 * @brief returns the Identity Matrix.
 * 
 * @return result
 */
inline Matrix3x3 Matrix3x3::Identity(){
	Matrix3x3 result;

  result.m[0] = 1.0f;
  result.m[1] = 0.0f;
  result.m[2] = 0.0f;

  result.m[3] = 0.0f;
  result.m[4] = 1.0f;
  result.m[5] = 0.0f;

  result.m[6] = 0.0f;
  result.m[7] = 0.0f;
  result.m[8] = 1.0f;
  
  return result;
}

/**
 * @brief Multiplies the matrix.
 * 
 * @param other Matrix to multiply with
 * @return result
 */
inline Matrix3x3 Matrix3x3::Multiply(const Matrix3x3& other) const {

	Matrix3x3 result;

  result.m[0] = m[0] * other.m[0] + m[3] * other.m[1] + m[6] * other.m[2];
  result.m[1] = m[1] * other.m[0] + m[4] * other.m[1] + m[7] * other.m[2];
  result.m[2] = m[2] * other.m[0] + m[5] * other.m[1] + m[8] * other.m[2];

  result.m[3] = m[0] * other.m[3] + m[3] * other.m[4] + m[6] * other.m[5];
  result.m[4] = m[1] * other.m[3] + m[4] * other.m[4] + m[7] * other.m[5];
  result.m[5] = m[2] * other.m[3] + m[5] * other.m[4] + m[8] * other.m[5];

  result.m[6] = m[0] * other.m[6] + m[3] * other.m[7] + m[6] * other.m[8];
  result.m[7] = m[1] * other.m[6] + m[4] * other.m[7] + m[7] * other.m[8];
  result.m[8] = m[2] * other.m[6] + m[5] * other.m[7] + m[8] * other.m[8];

  return result;
}

/**
 * @brief Gets the determinant of the Matrix.
 * 
 * @return result
 */
inline float Matrix3x3::Determinant() const {
  Matrix2x2 auxMatrix[3];

  auxMatrix[0].m[0] = m[4]; auxMatrix[0].m[1] = m[5];
  auxMatrix[0].m[2] = m[7]; auxMatrix[0].m[3] = m[8];

  auxMatrix[1].m[0] = m[3]; auxMatrix[1].m[1] = m[5];
  auxMatrix[1].m[2] = m[6]; auxMatrix[1].m[3] = m[8];

  auxMatrix[2].m[0] = m[3]; auxMatrix[2].m[1] = m[4];
  auxMatrix[2].m[2] = m[6]; auxMatrix[2].m[3] = m[7];

	return ( m[0] * auxMatrix[0].Determinant() - m[1] * auxMatrix[1].Determinant() + m[2] * auxMatrix[2].Determinant()  );
}

/**
 * @brief Gets the Adjoint of the Matrix.
 * 
 * @return result 
 */
inline Matrix3x3 Matrix3x3::Adjoint() const {
  Matrix3x3 result;
  Matrix2x2 aux[9];
  /* 
    m[0] m[3] m[6] 
    m[1] m[4] m[7] 
    m[2] m[5] m[8]
   */
  aux[0].m[0] = m[4]; aux[0].m[2] = m[5]; 
  aux[0].m[1] = m[7]; aux[0].m[3] = m[8];

  aux[1].m[0] = m[3]; aux[1].m[2] = m[5];
  aux[1].m[1] = m[6]; aux[1].m[3] = m[8];

  aux[2].m[0] = m[3]; aux[2].m[2] = m[4];
  aux[2].m[1] = m[6]; aux[2].m[3] = m[7];

  aux[3].m[0] = m[1]; aux[3].m[2] = m[2];
  aux[3].m[1] = m[7]; aux[3].m[3] = m[8];

  aux[4].m[0] = m[0]; aux[4].m[2] = m[2];
  aux[4].m[1] = m[6]; aux[4].m[3] = m[8];

  aux[5].m[0] = m[0]; aux[5].m[2] = m[1];
  aux[5].m[1] = m[6]; aux[5].m[3] = m[7];

  aux[6].m[0] = m[1]; aux[6].m[2] = m[2];
  aux[6].m[1] = m[4]; aux[6].m[3] = m[5];

  aux[7].m[0] = m[0]; aux[7].m[2] = m[2];
  aux[7].m[1] = m[3]; aux[7].m[3] = m[5];

  aux[8].m[0] = m[0]; aux[8].m[2] = m[1];
  aux[8].m[1] = m[3]; aux[8].m[3] = m[4];


  result.m[0] = aux[0].Determinant();
  result.m[1] = aux[1].Determinant() * -1;
  result.m[2] = aux[2].Determinant();
  result.m[3] = aux[3].Determinant() * -1;
  result.m[4] = aux[4].Determinant();
  result.m[5] = aux[5].Determinant() * -1;
  result.m[6] = aux[6].Determinant();
  result.m[7] = aux[7].Determinant() * -1;
  result.m[8] = aux[8].Determinant();

  return result;
}

/**
 * @brief Checks if the matrix can get the Inverse, if true, inverts it.
 * 
 * @param out Inverted Matrix
 * @return true if it can get the inverse
 */
inline bool Matrix3x3::GetInverse(Matrix3x3& out) const {

   Matrix3x3 aux = Adjoint().Transpose();

  float determinant = Determinant();

  out.m[0] = 1 / determinant * aux.m[0];
  out.m[1] = 1 / determinant * aux.m[1];
  out.m[2] = 1 / determinant * aux.m[2];

  out.m[3] = 1 / determinant * aux.m[3];
  out.m[4] = 1 / determinant * aux.m[4];
  out.m[5] = 1 / determinant * aux.m[5];

  out.m[6] = 1 / determinant * aux.m[6];
  out.m[7] = 1 / determinant * aux.m[7];
  out.m[8] = 1 / determinant * aux.m[8];

	return true;
}

/**
 * @brief Sets the Inverse of the Matrix.
 * 
 * @return true if it can be done.
 */
inline bool Matrix3x3::Inverse() {

  Matrix3x3 aux = Adjoint().Transpose();

  float determinant = Determinant();
  if (determinant == 0.0f) {
    return false;
  }

  m[0] = 1.0f / determinant * aux.m[0];
  m[1] = 1.0f / determinant * aux.m[1];
  m[2] = 1.0f / determinant * aux.m[2];

  m[3] = 1.0f / determinant * aux.m[3];
  m[4] = 1.0f / determinant * aux.m[4];
  m[5] = 1.0f / determinant * aux.m[5];

  m[6] = 1.0f / determinant * aux.m[6];
  m[7] = 1.0f / determinant * aux.m[7];
  m[8] = 1.0f / determinant * aux.m[8];

	return true;
}

/**
 * @brief Gets the transpose of the Matrix.
 * 
 * @return result
 */
inline Matrix3x3 Matrix3x3::Transpose() const {

  Matrix3x3 result;

  result.m[0] = m[0]; result.m[1] = m[3]; result.m[2] = m[6];
  result.m[3] = m[1]; result.m[4] = m[4]; result.m[5] = m[7];
  result.m[6] = m[2]; result.m[7] = m[5]; result.m[8] = m[8];
	return result;
}

/**
 * @brief Translates the Matrix with a Vector2.
 * 
 * @param mov_vector how much the Matrix is going to move
 * @return result
 */
inline Matrix3x3 Matrix3x3::Translate(const Vector2& mov_vector) {
	Matrix3x3 result;
  result.m[0] = 1.0f;
  
  result.m[4] = 1.0f;

  result.m[6] = mov_vector.x;
  result.m[7] = mov_vector.y;
  result.m[8] = 1.0f;

	return result;
}

/**
 * @brief Translates the Matrix in x and y with two floats.
 * 
 * @param x How much is the Matrix is going to moved on x axis.
 * @param y How much is the Matrix is going to moved on y axis.
 * @return result
 */
inline Matrix3x3 Matrix3x3::Translate(float x, float y) {
	Matrix3x3 result;
  result.m[0] = 1.0f;
  
  result.m[4] = 1.0f;

  result.m[6] = x;
  result.m[7] = y;
  result.m[8] = 1.0f;
	return result;
}

/**
 * @brief Rotates the Matrix on radians.
 * 
 * @param radian Radians to rotate.
 * @return result
 */
inline Matrix3x3 Matrix3x3::Rotate(float radian){
  	Matrix3x3 result;

  result.m[0] = (float)cos(radian);
  result.m[1] = (float)sin(radian);

  result.m[3] = (float)-sin(radian);
  result.m[4] = (float)cos(radian);
  
  result.m[8] = 1.0f;
  
  return result;
}

/**
 * @brief Scales the Matrix in x and y axis.
 * 
 * @param x How much is the Matrix is going to scaled on x axis.
 * @param y How much is the Matrix is going to scaled on y axis.
 * @return result
 */
inline Matrix3x3 Matrix3x3::Scale(float x, float y){
  Matrix3x3 result;

  result.m[0] = x;
  
  result.m[4] = y;
  
  result.m[8] = 1.0f;
  
  return result;
}

/**
 * @brief Scales the Matrix in x and y axis.
 * 
 * @param scale How much is the Matrix is going to scaled on both axis.
 * @return result
 */
inline Matrix3x3 Matrix3x3::Scale(const Vector2& scale){
  Matrix3x3 result;

  result.m[0] = scale.x;
  
  result.m[4] = scale.y;
  
  result.m[8] = 1.0f;
  
  return result;
}

/**
 * @brief Gets the the Matrix transformed by the parameters
 * 
 * @param pivot Sets the pivot of the transformation
 * @param translate How much the matrix is going to translate
 * @param scale How much the matrix is going to scale
 * @param rotateX How much the matrix is going to be rotated.
 * 
 * @return result
 */
inline Matrix3x3 Matrix3x3::GetTransform(const Vector2& pivot, const Vector2& translate,
                    const Vector2& scale, float radians){
  Matrix3x3 result = Matrix3x3::Identity();

  result = Matrix3x3::Translate(pivot).Multiply(result);
  result = Matrix3x3::Scale(scale).Multiply(result);
  result = Matrix3x3::Rotate(radians).Multiply(result);
  result = Matrix3x3::Translate(translate).Multiply(result);

  return result;
}

/**
 * @brief Gets the transformed by the parameters
 * 
 * @param trans_x Sets the pivot of the transformation on x axis
 * @param trans_y Sets the pivot of the transformation on y axis
 * @param trans_x How much the matrix is going to translate on x axis
 * @param trans_y How much the matrix is going to translate on y axis
 * @param scale_x How much the matrix is going to scale on x axis
 * @param scale_y How much the matrix is going to scale on y axis
 * @param radians How much the matrix is going to be rotated
 * 
 * @return result
 */
inline Matrix3x3 Matrix3x3::GetTransform(float pivot_x, float pivot_y, float trans_x,
                      float trans_y, float scale_x, float scale_y, float radians){
  Matrix3x3 result = Matrix3x3::Identity();

  result = Matrix3x3::Translate(pivot_x, pivot_y).Multiply(result);
  result = Matrix3x3::Scale(scale_x,scale_y).Multiply(result);
  result = Matrix3x3::Rotate(radians).Multiply(result);
  result = Matrix3x3::Translate(trans_x,trans_y).Multiply(result);
  
  return result;
}
/**
 * @brief Gets the Vector2 result by a transformation of a Vector3
 * 
 * @param Vector3 Vector3 to transform.
 * 
 * @return Vector2 result
 */
inline Vector2 Matrix3x3::TransformVector2(const Vector3& in) const{
  Vector3 aux = ToVector3(in);
  Vector2 result;
  result.x = aux.x;
  result.y = aux.y;
  return result;
}

/**
 * @brief Gets the Vector3 result by a transformation of a Vector3
 * 
 * @param Vector3 Vector3 to transform.
 * 
 * @return Vector3 result
 */
inline Vector3 Matrix3x3::ToVector3(const Vector3& in) const{
  Vector3 result;
  
  result.x = m[0] * in.x + m[3] * in.y + m[6] * in.z;
  result.y = m[1] * in.x + m[4] * in.y + m[7] * in.z;
  result.z = m[2] * in.x + m[5] * in.y + m[8] * in.z;

  return result;
}


/**
 * @brief Gets a column of the Matrix.
 * 
 * @param colum Which colum of the Matrix is going to return
 * @return result
 */
inline Vector3 Matrix3x3::GetColum(int colum) const {
  Vector3 result;

  result.x = m[0 + colum * 3];
  result.y = m[1 + colum * 3];
  result.z = m[2 + colum * 3];

	return result;
}

/**
 * @brief Gets a line of the Matrix.
 * 
 * @param line Which line of the Matrix is going to return
 * @return result
 */
inline Vector3 Matrix3x3::GetLine(int line) const {
  Vector3 result;

  result.x = m[0 + line];
  result.y = m[3 + line];
  result.z = m[6 + line];

	return result;
}

/* ----- OPERATOR FUNCTIONS ----- */

/**
 * @brief Adds two Matrix.
 * 
 * @param other How much is going to be added to the Matrix 
 * @return result 
 */
inline Matrix3x3 Matrix3x3::operator+(const Matrix3x3& other) const {
  Matrix3x3 result;

  result.m[0] = m[0] + other.m[0];
  result.m[1] = m[1] + other.m[1];
  result.m[2] = m[2] + other.m[2];

  result.m[3] = m[3] + other.m[3];
  result.m[4] = m[4] + other.m[4];
  result.m[5] = m[5] + other.m[5];

  result.m[6] = m[6] + other.m[6];
  result.m[7] = m[7] + other.m[7];
  result.m[8] = m[8] + other.m[8];
	return result;
}

/**
 * @brief Sets the sum of the matrix.
 * 
 * @param other How much is going to be added to the Matrix 
 * @return this ptr 
 */
inline Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& other) {
  m[0] += other.m[0];
  m[1] += other.m[1];
  m[2] += other.m[2];

  m[3] += other.m[3];
  m[4] += other.m[4];
  m[5] += other.m[5];

  m[6] += other.m[6];
  m[7] += other.m[7];
  m[8] += other.m[8];

	return *this;
}

/**
 * @brief Adds a matrix and a float.
 * 
 * @param value How much is going to be added to the Matrix 
 * @return result 
 */
inline Matrix3x3 Matrix3x3::operator+(float value) const {
	Matrix3x3 result;

  result.m[0] = m[0] + value;
  result.m[1] = m[1] + value;
  result.m[2] = m[2] + value;

  result.m[3] = m[3] + value;
  result.m[4] = m[4] + value;
  result.m[5] = m[5] + value;
  
  result.m[6] = m[6] + value;
  result.m[7] = m[7] + value;
  result.m[8] = m[8] + value;

	return result;
}

/**
 * @brief Sets the sum of the matrix and a float.
 * 
 * @param value How much is going to be added to the Matrix 
 * @return this ptr 
 */
inline Matrix3x3& Matrix3x3::operator+=(float value) {
  m[0] += value;
  m[1] += value;
  m[2] += value;

  m[3] += value;
  m[4] += value;
  m[5] += value;

  m[6] += value;
  m[7] += value;
  m[8] += value;

	return *this;
}

/**
 * @brief Substracts two Matrix.
 * 
 * @param other How much is going to be substracted to the Matrix 
 * @return result 
 */
inline Matrix3x3 Matrix3x3::operator-(const Matrix3x3& other) const {
  Matrix3x3 result;

  result.m[0] = m[0] - other.m[0];
  result.m[1] = m[1] - other.m[1];
  result.m[2] = m[2] - other.m[2];

  result.m[3] = m[3] - other.m[3];
  result.m[4] = m[4] - other.m[4];
  result.m[5] = m[5] - other.m[5];

  result.m[6] = m[6] - other.m[6];
  result.m[7] = m[7] - other.m[7];
  result.m[8] = m[8] - other.m[8];
	return result;
}

/**
 * @brief Sets the substraction of the matrix.
 * 
 * @param other How much is going to be substracted to the Matrix 
 * @return this ptr 
 */
inline Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& other) {
  m[0] -= other.m[0];
  m[1] -= other.m[1];
  m[2] -= other.m[2];

  m[3] -= other.m[3];
  m[4] -= other.m[4];
  m[5] -= other.m[5];

  m[6] -= other.m[6];
  m[7] -= other.m[7];
  m[8] -= other.m[8];
	return *this;
}

/**
 * @brief substracts a matrix and a float.
 * 
 * @param value How much is going to be substracted to the Matrix 
 * @return result 
 */
inline Matrix3x3 Matrix3x3::operator-(float value) const {
  Matrix3x3 result;

  result.m[0] = m[0] - value;
  result.m[1] = m[1] - value;
  result.m[2] = m[2] - value;

  result.m[3] = m[3] - value;
  result.m[4] = m[4] - value;
  result.m[5] = m[5] - value;

  result.m[6] = m[6] - value;
  result.m[7] = m[7] - value;
  result.m[8] = m[8] - value;

	return result;
}

/**
 * @brief Sets the subtraction of the matrix and a float.
 * 
 * @param value How much is going to be substracted to the Matrix 
 * @return this ptr 
 */
inline Matrix3x3& Matrix3x3::operator-=(float value) {
  m[0] -= value;
  m[1] -= value;
  m[2] -= value;

  m[3] -= value;
  m[4] -= value;
  m[5] -= value;

  m[6] -= value;
  m[7] -= value;
  m[8] -= value;

	return *this;
}

/**
 * @brief Multiplies a matrix and a float.
 * 
 * @param value How much is going to be multiplied to the Matrix 
 * @return result 
 */
inline Matrix3x3 Matrix3x3::operator*(float value) const {
  Matrix3x3 result;

  result.m[0] = m[0] * value;
  result.m[1] = m[1] * value;
  result.m[2] = m[2] * value;

  result.m[3] = m[3] * value;
  result.m[4] = m[4] * value;
  result.m[5] = m[5] * value;

  result.m[6] = m[6] * value;
  result.m[7] = m[7] * value;
  result.m[8] = m[8] * value;

	return result;
}

/**
 * @brief Sets the multiplication of the matrix and a float.
 * 
 * @param value How much is going to be multiplied to the Matrix 
 * @return this ptr 
 */
inline Matrix3x3& Matrix3x3::operator*=(float value) {
  m[0] *= value;
  m[1] *= value;
  m[2] *= value;

  m[3] *= value;
  m[4] *= value;
  m[5] *= value;

  m[6] *= value;
  m[7] *= value;
  m[8] *= value;

	return *this;
}

/**
 * @brief Divides a matrix and a float.
 * 
 * @param value How much is going to be divided to the Matrix 
 * @return result 
 */
inline Matrix3x3 Matrix3x3::operator/(float value) const {
  Matrix3x3 result;

  result.m[0] = m[0] / value;
  result.m[1] = m[1] / value;
  result.m[2] = m[2] / value;

  result.m[3] = m[3] / value;
  result.m[4] = m[4] / value;
  result.m[5] = m[5] / value;

  result.m[6] = m[6] / value;
  result.m[7] = m[7] / value;
  result.m[8] = m[8] / value;

	return result;
}

/**
 * @brief Sets the division of the matrix and a float.
 * 
 * @param value How much is going to be divided to the Matrix 
 * @return this ptr 
 */
inline Matrix3x3& Matrix3x3::operator/=(float value) {
  m[0] /= value;
  m[1] /= value;
  m[2] /= value;

  m[3] /= value;
  m[4] /= value;
  m[5] /= value;

  m[6] /= value;
  m[7] /= value;
  m[8] /= value;
	return *this;
}

/**
 * @brief Checks if a matrix is equal to another one.
 * 
 * @param other the matrix to compare 
 * @return true if they are equal
 * @return false if they aren't equal 
 */
inline bool Matrix3x3::operator==(const Matrix3x3& other) const {
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
	return true;
}

/**
 * @brief Checks if a matrix isn't equal to another one.
 * 
 * @param other the matrix to compare 
 * @return true if they aren't equal
 * @return false if they are equal 
 */
inline bool Matrix3x3::operator!=(const Matrix3x3& other) const {
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
	return true;
}

/**
 * @brief Equals two Matrix.
 * 
 * @param other The new matrix 
 */
inline void Matrix3x3::operator=(const Matrix3x3& other) {
  m[0] = other.m[0];
  m[1] = other.m[1];
  m[2] = other.m[2];

  m[3] = other.m[3];
  m[4] = other.m[4];
  m[5] = other.m[5];

  m[6] = other.m[6];
  m[7] = other.m[7];
  m[8] = other.m[8];
}

/**
 * @brief Prints the matrix value in console for debugging.
 */
inline void Matrix3x3::Print() const{
  printf("\n[0]: % 1.3f [1]: % 1.3f [2]: % 1.3f\n[3]: % 1.3f [4]: % 1.3f [5]: % 1.3f\n[6]: % 1.3f [7]: % 1.3f [8]: % 1.3f\n",
    m[0], m[1], m[2],
    m[3], m[4], m[5],
    m[6], m[7], m[8]
  );
}

}

#endif 