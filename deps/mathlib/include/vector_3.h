// @author Enrique Gil <gilte@esat-alumni.com>
// @file vector_3 header and inline functions implementation
#ifndef __VECTOR3_H__
#define __VECTOR3_H__ 1

#include "math_utils.h"
#include "matrix_2.h"

namespace mathlib {

class Vector3 {

public:
	Vector3();
	Vector3(float value);
	Vector3(float x, float y, float z);
	Vector3(float* values_array);
	Vector3(const float* values_array);
	Vector3(const Vector3& other);
	~Vector3();

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator+(float value) const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator+=(float value);
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator-(float value) const;
	Vector3& operator-=(const Vector3& other);
	Vector3& operator-=(float value);
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	Vector3& operator=(const Vector3& other);
	Vector3& operator=(float value);
	Vector3 operator*(float value) const;
	Vector3& operator*=(float value);
	Vector3 operator/(float value) const;
	Vector3& operator/=(float value);

	float Magnitude() const;
	Vector3 Normalized() const;
	void Normalize();
	float SqrMagnitude() const;
	void Scale(const Vector3& other);

	static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
	static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);
	static float DotProduct(const Vector3& a, const Vector3& b);
	static float Angle(const Vector3& a, const Vector3& b);
	static Vector3 CrossProduct(const Vector3& a,const Vector3& b);	
	static float Distance(const Vector3& a, const Vector3& b);
	static Vector3 Reflect(const Vector3& direction, const Vector3& normal);

  void Print() const;
  
	static const Vector3 up;
	static const Vector3 down;
	static const Vector3 right;
	static const Vector3 left;
	static const Vector3 forward;
	static const Vector3 back;
	static const Vector3 zero;
	static const Vector3 unit;

	float x;
	float y;
	float z;
};

/**
 * @brief Vector constructor
 */
inline Vector3::Vector3() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

/**
 * @brief Vector constructor with a float 
 * 
 * @param value value of the vector's atributes
 */
inline Vector3::Vector3(float value) {
  x = value;
	y = value;
	z = value;
}

/**
 * @brief Vector constructor with three floats 
 * 
 * @param value_x value to x
 * @param value_y value to y
 * @param value_z value to z
 */
inline Vector3::Vector3(float value_x, float value_y, float value_z) {
	x = value_x;
	y = value_y;
	z = value_z;
}

/**
 * @brief Vector constructor with an array of floats 
 * 
 * @param values_array the values to set on the matrix
 */
inline Vector3::Vector3(float * values_array) {
	x = values_array[0];
	y = values_array[1];
	z = values_array[2];
}

inline Vector3::Vector3(const float * values_array) {
	x = values_array[0];
	y = values_array[1];
	z = values_array[2];
}

/**
 * @brief Vector copy constructor 
 * 
 * @param other Copy vector
 */
inline Vector3::Vector3(const Vector3& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}

/**
 * @brief Vector destructor
 */
inline Vector3::~Vector3() {}

/**
 * @brief Adds two Vectors.
 * 
 * @param other How much is going to be added to the Vector 
 * @return result 
 */
inline Vector3 Vector3::operator+(const Vector3& other) const {
	Vector3 result;

  result.x = x + other.x;
  result.y = y + other.y;
	result.z = z + other.z;

	return result;
}

/**
 * @brief Adds a value to the Vector.
 * 
 * @param value How much is going to be added to the Vector 
 * @return result 
 */
inline Vector3 Vector3::operator+(float value) const {
  Vector3 result;

  result.x = x + value;
  result.y = y + value;
	result.z = z + value;

	return result;
}

/**
 * @brief Adds two Vectors.
 * 
 * @param other How much is going to be added to the Vector 
 * @return this ptr 
 */
inline Vector3& Vector3::operator+=(const Vector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

/**
 * @brief Adds a value to the Vector.
 * 
 * @param value How much is going to be added to the Vector 
 * @return this ptr 
 */
inline Vector3& Vector3::operator+=(float value) {
  x += value;
	y += value;
	z += value;
	return *this;
}

/**
 * @brief Substraction of two Vectors.
 * 
 * @param other How much is going to be substracted to the Vector 
 * @return result 
 */
inline Vector3 Vector3::operator-(const Vector3& other) const {
  Vector3 result;

  result.x = x - other.x;
  result.y = y - other.y;
	result.z = z - other.z;

	return result;
}

/**
 * @brief Substracts a value to the Vector.
 * 
 * @param value How much is going to be substracted to the Vector 
 * @return result 
 */
inline Vector3 Vector3::operator-(float value) const {
  Vector3 result;

  result.x = x - value;
  result.y = y - value;
  result.z = z - value;

  return result;
}

/**
 * @brief Substraction of two Vectors.
 * 
 * @param other How much is going to be substracted to the Vector 
 * @return this ptr 
 */
inline Vector3& Vector3::operator-=(const Vector3& other) {
  x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

/**
 * @brief Substracts a value to the Vector.
 * 
 * @param value How much is going to be substracted to the Vector 
 * @return this ptr 
 */
inline Vector3& Vector3::operator-=(float value) {
  x -= value;
	y -= value;
	z -= value;
	return *this;
}

/**
 * @brief Checks if a vector is equal to another one.
 * 
 * @param other the vector to compare 
 * @return true if they are equal
 * @return false if they aren't equal 
 */
inline bool Vector3::operator==(const Vector3& other) const {
  if (x != other.x) {
	  return false;
  }
  if (y != other.y) {
	  return false;
  }
  if (z != other.z) {
	  return false;
  }
	return true;
}

/**
 * @brief Checks if a vector is equal to another one.
 * 
 * @param other the vector to compare 
 * @return true if they are equal
 * @return false if they aren't equal 
 */
inline bool Vector3::operator!=(const Vector3& other) const {
  if (x == other.x) {
    return false;
  }
  if (y == other.y) {
	  return false;
  }
  if (z == other.z) {
	  return false;
  }
	return true;
}

/**
 * @brief Equals two Vectors.
 * 
 * @param other The Vector to compare 
 */
inline Vector3& Vector3::operator=(const Vector3& other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

/**
 * @brief Equals Vector with a float.
 * 
 * @param value the float to compare 
 */
inline Vector3& Vector3::operator=(float value) {	
  x = value;
	y = value;
	z = value;
	return *this;
}

/**
 * @brief Multiplies a value to the Vector.
 * 
 * @param value How much is going to be multiplied to the Vector 
 * @return result 
 */
inline Vector3 Vector3::operator*(float value) const {
  Vector3 result;

  result.x = x * value;
  result.y = y * value;
	result.z = z * value;

	return result;
}

/**
 * @brief Multiplies a value to the Vector.
 * 
 * @param value How much is going to be multiplied to the Vector 
 * @return this ptr 
 */
inline Vector3& Vector3::operator*=(float value) {	
  x *= value;
	y *= value;
	z *= value;
	return *this;
}

/**
 * @brief Divides a value to the Vector.
 * 
 * @param value How much is going to be divided to the Vector 
 * @return result 
 */
inline Vector3 Vector3::operator/(float value) const {

	Vector3 result;
  result.x = x / value;
  result.y = y / value;
	result.z = z / value;

	return result;
}

/**
 * @brief Divides a value to the Vector.
 * 
 * @param value How much is going to be divided to the Vector 
 * @return this ptr 
 */
inline Vector3& Vector3::operator/=(float value) {	
  x /= value;
	y /= value;
	z /= value;
	return *this;
}

/**
 * @brief Gets the Magnitude of the Vector
 * 
 * @return the magnitude of the vector 
 */
inline float Vector3::Magnitude() const {
  return sqrtf( (x * x) + (y * y) + (z * z) );
}

/**
 * @brief Gets the normalized vector
 * 
 * @return result
 */
inline Vector3 Vector3::Normalized() const {
	
	Vector3 result;

	float vectorMagnitude = Magnitude();

	result.x = x/vectorMagnitude;
	result.y = y/vectorMagnitude;
	result.z = z/vectorMagnitude;

	return result;
}
/**
 * @brief Normalizes de vector
 */
inline void Vector3::Normalize() {

	float vectorMagnitude = Magnitude();

	x /= vectorMagnitude;
	y /= vectorMagnitude;
	z /= vectorMagnitude;
}

/**
 * @brief Sets the Square Root of the vector
 * 
 * @return the square root of the vector 
 */
inline float Vector3::SqrMagnitude() const {
	return (x * x) + (y * y) + (z * z);
}

/**
 * @brief Scales the vector.
 * 
 * @param other How much is going to get the Vector scaled 
 */
inline void Vector3::Scale(const Vector3& other) {

	x *= other.x;
	y *= other.y;
	z *= other.z;

}

/**
 * @brief Lerps two Vectors with a clamp
 * 
 * @return result 
 */
inline Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t) {
	Vector3 result;

  t = Clamp(t, 0.0f, 1.0f);
  
  result.x = a.x + ((b.x - a.x) * t);
  result.y = a.y + ((b.y - a.y) * t);
  result.z = a.z + ((b.z - a.z) * t);
  // printf("t: %.3f ->  %.3f\nx: %.3f y: %.3f z: %.3f\nx: %.3f y: %.3f z: %.3f\nx: %.3f y: %.3f z: %.3f\n", a.x, a.y, a.z, b.x, b.y, b.z, result.x, result.y, result.z);
	
	return result;
}

/**
 * @brief Lerps two Vectors without a clamp
 * 
 * @return result 
 */
inline Vector3 Vector3::LerpUnclamped(const Vector3& a, const Vector3& b, float t) {

	Vector3 result;

  result.x = a.x + (b.x - a.x) * t;
  result.y = a.y + (b.y - a.y) * t;
  result.z = a.z + (b.z - a.z) * t;

	return result;
}

/**
 * @brief Calculates the dot product of the vector
 * 
 * @param a first point
 * @param other second point
 * @return the dot product of two vector 
 */
inline float Vector3::DotProduct(const Vector3& a, const Vector3& other)  {
	return (a.x * other.x) + (a.y * other.y) + (a.z * other.z);
}

/**
 * @brief Calculates the angle between two products
 * 
 * @param a first point
 * @param other second point
 * @return angle between both vectors 
 */
inline float Vector3::Angle(const Vector3& a, const Vector3& other)  {
	return (float)acos( DotProduct(a, other) / ( a.Magnitude() * other.Magnitude
	() ) );
}

/**
 * @brief Calculates the cross product of the vector
 * 
 * @param a first point
 * @param other second point
 * @return result
 */
inline Vector3 Vector3::CrossProduct(const Vector3& a, const Vector3& other)  {

	Vector3 result;
	Matrix2x2 matrix[3];

	matrix[0].m[0] = a.y;
	matrix[0].m[1] = other.y;
	matrix[0].m[2] = a.z;
	matrix[0].m[3] = other.z;
	
	matrix[1].m[0] = a.x;
	matrix[1].m[1] = other.x;
	matrix[1].m[2] = a.z;
	matrix[1].m[3] = other.z;

	matrix[2].m[0] = a.x;
	matrix[2].m[1] = other.x;
	matrix[2].m[2] = a.y;
	matrix[2].m[3] = other.y;

	result.x = matrix[0].Determinant();
	result.y = -matrix[1].Determinant();
	result.z = matrix[2].Determinant();

	return result;
}

/**
 * @brief Calculates the distance between two points
 * 
 * @param a first point
 * @param b second point
 * @return the distance between them
 */
inline float Vector3::Distance(const Vector3& a, const Vector3& b) {
  return sqrtf( ( (b.x - a.x)*(b.x - a.x) ) + ( (b.y - a.y)*(b.y - a.y) ) + ( (b.z - a.z)*(b.z - a.z) ) );
}

/**
 * @brief Calculates the reflection of a vector with the normal
 * 
 * @param direction the vector that is about to hit the normal point
 * @param normal where direction vector collides
 * @return the reflected direction vector with the normal
 */
inline Vector3 Vector3::Reflect(const Vector3& direction, const Vector3& normal) {

	Vector3 result;
  float dot_product = Vector3::DotProduct(direction, normal);

	result.x = direction.x - 2 * dot_product * normal.x;
	result.y = direction.y - 2 *dot_product * normal.y;
	result.z = direction.z - 2 *dot_product * normal.z;

	return result;
}

/**
 * @brief Prints the matrix value in console for debugging.
 */
inline void Vector3::Print() const{
  printf("\nx: %1.3f y: %1.3f z: %1.3f\n",
    x, y, z
  );
}

}

#endif 
