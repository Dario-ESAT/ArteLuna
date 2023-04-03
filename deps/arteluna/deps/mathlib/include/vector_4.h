// @author Enrique Gil <gilte@esat-alumni.com>
// @file vector_4 header and inline functions implementation
#ifndef __Vector4_H__
#define __Vector4_H__ 1
#include <math.h>

#include "vector_3.h"
#include "matrix_3.h"

namespace mathlib {

class Vector4 {
public:

	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(Vector3 a, float w);
	Vector4(float a);
	Vector4(float* values_array);
	Vector4(const float* values_array);
	Vector4(const Vector4& other);
	~Vector4();
	
	Vector4 operator+(const Vector4& other) const;
	Vector4 operator+(float value) const;
	void operator+=(const Vector4& other);
	void operator+=(float value);
	Vector4 operator-(const Vector4& other) const;
	Vector4 operator-(float value) const;
	void operator -=(const Vector4& other);
	void operator -=(float value);

	Vector4 operator*(float value) const;
	void operator*=(float value);
	Vector4 operator/(float value) const;
	void operator/=(float value);
	bool operator==(const Vector4& other);
	bool operator!=(const Vector4& other);
	void operator=(const Vector4& other);

	float Magnitude() const;
	void Normalize();
	Vector4 Normalized() const;
	void Scale(Vector4 scale);
	float SqrMagnitude() const;

	static float Distance(const Vector4& a, const Vector4& b);
	static float DotProduct(Vector4 a, Vector4 b);
	static Vector4 Lerp(const Vector4& a, const Vector4& b, float index);	
  void Print() const;
	static const Vector4 one;
	static const Vector4 zero;

	float x;
	float y;
	float z;
	float w;

};

/**
 * @brief Vector constructor
 */
inline Vector4::Vector4() { }

/**
 * @brief Vector constructor with four floats 
 * 
 * @param value_x value to x
 * @param value_y value to y
 * @param value_z value to z
 * @param value_w value to w
 */
inline Vector4::Vector4(float value_x, float value_y, float value_z, float value_w) {
  x = value_x;
  y = value_y;
  z = value_z;
  w = value_w;
}

/**
 * @brief Vector constructor with a float and a Vector3 
 * 
 * @param vec3 the values of axis x, y and z
 * @param value_w value of w's axis
 */
inline Vector4::Vector4(Vector3 vec3, float value_w) {
  x = vec3.x;
  y = vec3.y;
  z = vec3.z;
  w = value_w;
}

/**
 * @brief Vector constructor with a float 
 * 
 * @param value value of the vector's atributes
 */
inline Vector4::Vector4(float value) {
  x = value;
  y = value;
  z = value;
  w = value;
}

/**
 * @brief Vector constructor with an array of floats 
 * 
 * @param values_array the values to set on the matrix
 */
inline Vector4::Vector4(float* values_array) {
  x = values_array[0];
	y = values_array[1];
	z = values_array[2];
  w = values_array[3];
}

inline Vector4::Vector4(const float* values_array) {
  x = values_array[0];
	y = values_array[1];
	z = values_array[2];
  w = values_array[3];
}

/**
 * @brief Vector copy constructor 
 * 
 * @param other Copy vector
 */
inline Vector4::Vector4(const Vector4& other) {
  x = other.x;
  y = other.y;
  z = other.z;
  w = other.w;
}

/**
 * @brief Vector destructor
 */
inline Vector4::~Vector4() { }

/**
 * @brief Adds two Vectors.
 * 
 * @param other How much is going to be added to the Vector 
 * @return result 
 */
inline Vector4 Vector4::operator+(const Vector4& other) const{
  Vector4 result;
  
  result.x = x + other.x;
  result.y = y + other.y;
  result.z = z + other.z;
  result.w = w + other.w;

	return result;
}

/**
 * @brief Adds a value to the Vector.
 * 
 * @param value How much is going to be added to the Vector 
 * @return result 
 */
inline Vector4 Vector4::operator+(float value) const{
  Vector4 result;
  
  result.x = x + value;
  result.y = y + value;
  result.z = z + value;
  result.w = w + value;

	return result;
}

/**
 * @brief Adds two Vectors.
 * 
 * @param other How much is going to be added to the Vector 
 * @return this ptr 
 */
inline void Vector4::operator+=(const Vector4& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  w += other.w;
}

/**
 * @brief Adds a value to the Vector.
 * 
 * @param value How much is going to be added to the Vector 
 * @return this ptr 
 */
inline void Vector4::operator+=(float value) {
  x += value;
  y += value;
  z += value;
  w += value;
}

/**
 * @brief Substraction of two Vectors.
 * 
 * @param other How much is going to be substracted to the Vector 
 * @return result 
 */
inline Vector4 Vector4::operator-(const Vector4& other) const{
  Vector4 result;
  
  result.x = x - other.x;
  result.y = y - other.y;
  result.z = z - other.z;
  result.w = w - other.w;

	return result;
}

/**
 * @brief Substracts a value to the Vector.
 * 
 * @param value How much is going to be substracted to the Vector 
 * @return result 
 */
inline Vector4 Vector4::operator-(float value) const{
  Vector4 result;
  
  result.x = x - value;
  result.y = y - value;
  result.z = z - value;
  result.w = w - value;

	return result;
}

/**
 * @brief Substraction of two Vectors.
 * 
 * @param other How much is going to be substracted to the Vector 
 * @return this ptr 
 */
inline void Vector4::operator -=(const Vector4& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  w -= other.w;
}

/**
 * @brief Substracts a value to the Vector.
 * 
 * @param value How much is going to be substracted to the Vector 
 * @return this ptr 
 */
inline void Vector4::operator -=(float value) {
  x -= value;
  y -= value;
  z -= value;
  w -= value;
}

/**
 * @brief Multiplies a value to the Vector.
 * 
 * @param value How much is going to be multiplied to the Vector 
 * @return result 
 */
inline Vector4 Vector4::operator*(float value) const{
	Vector4 result;
  
  result.x = x * value;
  result.y = y * value;
  result.z = z * value;
  result.w = w * value;

	return result;
}

/**
 * @brief Multiplies a value to the Vector.
 * 
 * @param value How much is going to be multiplied to the Vector 
 * @return this ptr 
 */
inline void Vector4::operator*=(float value) {
  x *= value;
  y *= value;
  z *= value;
  w *= value;
}

/**
 * @brief Divides a value to the Vector.
 * 
 * @param value How much is going to be divided to the Vector 
 * @return result 
 */
inline Vector4 Vector4::operator/(float value) const{
  Vector4 result;
  
  result.x = x / value;
  result.y = y / value;
  result.z = z / value;
  result.w = w / value;

	return result;
}

/**
 * @brief Divides a value to the Vector.
 * 
 * @param value How much is going to be divided to the Vector 
 * @return this ptr 
 */
inline void Vector4::operator/=(float value) {
  x /= value;
  y /= value;
  z /= value;
  w /= value;
}

/**
 * @brief Checks if a vector is equal to another one.
 * 
 * @param other the vector to compare 
 * @return true if they are equal
 * @return false if they aren't equal 
 */
inline bool Vector4::operator==(const Vector4& other) {
  if (x != other.x) {
    return false;
  }
  if (y != other.y) {
	  return false;
  }
  if (z != other.z) {
	  return false;
  }
  if (w != other.w) {
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
inline bool Vector4::operator!=(const Vector4& other) {
  if (x == other.x) {
    return false;
  }
  if (y == other.y) {
	  return false;
  }
  if (z == other.z) {
	  return false;
  }
  if (w == other.w) {
	  return false;
  }
	return true;
}

/**
 * @brief Equals two Vectors.
 * 
 * @param other The Vector to compare 
 */
inline void Vector4::operator=(const Vector4& other) {
  x = other.x;
  y = other.y;
  z = other.z;
  w = other.w;
}

/**
 * @brief Gets the Magnitude of the Vector
 * 
 * @return the magnitude of the vector 
 */
inline float Vector4::Magnitude() const{
  return sqrtf( (x * x) + (y * y) + (z * z) + (w * w) );
}

/**
 * @brief Normalizes de vector
 */
inline void Vector4::Normalize() {	// duda
  float inverseMagnitude = 1.0f / Magnitude();

	x *= inverseMagnitude;
	y *= inverseMagnitude;
	z *= inverseMagnitude;
  w *= inverseMagnitude;

	float vectorMagnitude = Magnitude();

	x /= vectorMagnitude;
	y /= vectorMagnitude;
	z /= vectorMagnitude;
	w /= vectorMagnitude;

}

/**
 * @brief Gets the normalized vector
 * 
 * @return result
 */
inline Vector4 Vector4::Normalized() const {
	Vector4 result;

	float vectorMagnitude = Magnitude();

	result.x = x/vectorMagnitude;
	result.y = y/vectorMagnitude;
	result.z = z/vectorMagnitude;
	result.w = w/vectorMagnitude;
	return result;
}

/**
 * @brief Scales the vector.
 * 
 * @param scale How much is going to get the Vector scaled 
 * @return this ptr 
 */
inline void Vector4::Scale(Vector4 scale) {
  x *= scale.x;
  y *= scale.y;
  z *= scale.z;
  w *= scale.w;
}

/**
 * @brief Sets the Square Root of the vector
 * 
 * @return the square root of the vector 
 */
inline float Vector4::SqrMagnitude() const {
	return (x * x) + (y * y) + (z * z) + (w * w);
}

/**
 * @brief Calculates the distance between two points
 * 
 * @param a first point
 * @param b second point
 * @return the distance between them
 */
inline float Vector4::Distance(const Vector4& a, const Vector4& b) {
  return sqrtf( ( (b.x - a.x)*(b.x - a.x) ) + ( (b.y - a.y)*(b.y - a.y) ) + ( (b.z - a.z)*(b.z - a.z) ) + ( (b.w - a.w)*(b.w - a.w) ) );
}

/**
 * @brief Calculates the dot product of the vector
 * 
 * @param a first point
 * @param other second point
 * @return the dot product of two vector 
 */
inline float Vector4::DotProduct(Vector4 a, Vector4 b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

/**
 * @brief Lerps two Vectors with a clamp
 * 
 * @return result 
 */
inline Vector4 Vector4::Lerp(const Vector4& a, const Vector4& b, float index) {	
	Vector4 result;

  index = Clamp(index, 0.0f, 1.0f);

  result.x = a.x + (b.x - a.x) * index;
  result.y = a.y + (b.y - a.y) * index;
  result.z = a.z + (b.z - a.z) * index;
  result.w = a.w + (b.w - a.w) * index;
	
	return result;
}

/**
 * @brief Prints the matrix value in console for debugging.
 */
inline void Vector4::Print() const{
  printf("\nx: % 1.3f y: % 1.3f z: % 1.3f w: % 1.3f\n",
    x, y, z, w
  );
}

}

#endif 
