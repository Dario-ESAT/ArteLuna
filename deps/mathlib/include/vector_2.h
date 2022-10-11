// @author Enrique Gil <gilte@esat-alumni.com>
// @file vector_2 header and inline functions implementation
#ifndef __VECTOR2_H__
#define __VECTOR2_H__ 1

#include <math.h>
#include <stdio.h>
#include "math_utils.h"

namespace mathlib {

class Vector2 {
 public:

  Vector2();
  Vector2(float x, float y);
  Vector2(const Vector2& copy);
  ~Vector2();

  Vector2 operator+(const Vector2& other) const;
  Vector2 operator+(float value);
  Vector2& operator+=(const Vector2& other);
  Vector2& operator+=(float value); 
  Vector2 operator-(const Vector2& other) const;
  Vector2 operator-(float value) const;
  Vector2& operator-();
  Vector2& operator-=(const Vector2& other);
  Vector2& operator-=(float value); 
  bool operator==(const Vector2& other) const;
  bool operator!=(const Vector2& other) const;
  void operator=(const Vector2& other);
  void operator=(float value);
  Vector2 operator*(float value) const;
  Vector2& operator*=(float value);
  Vector2 operator/(float value) const;
  Vector2& operator/=(float value);

  float Magnitude() const;
  void Normalize();
  Vector2 Normalized() const;

  void Scale(const Vector2 scale);

  float SqrMagnitude() const;
  static float Distance(const Vector2 a, const Vector2 b);

  static float DotProduct(Vector2 a, Vector2 b);

  static Vector2 Lerp(const Vector2 a, const Vector2 b, float t);
  static Vector2 LerpUnclamped(const Vector2 a, const Vector2 b, float t);

  void Print() const;
  static const Vector2 up;
  static const Vector2 down;
  static const Vector2 right;
  static const Vector2 left;
  static const Vector2 zero;
  static const Vector2 one;

  float x;
  float y;
};

/**
 * @brief Vector constructor
 */
inline Vector2::Vector2() {
  x = 0.0f;
  y = 0.0f;
}

/**
 * @brief Vector constructor with two floats 
 * 
 * @param value_x value to x
 * @param value_y value to y
 */
inline Vector2::Vector2(float value_x, float value_y) {
	x = value_x;
	y = value_y;
}

/**
 * @brief Vector copy constructor 
 * 
 * @param other Copy vector
 */
inline Vector2::Vector2(const Vector2& other) {
  x = other.x;
  y = other.y;
}

/**
 * @brief Vector destructor
 */
inline Vector2::~Vector2() {}

/**
 * @brief Adds two Vectors.
 * 
 * @param other How much is going to be added to the Vector 
 * @return result 
 */
inline Vector2 Vector2::operator+(const Vector2& other) const {
  
  Vector2 result;
  result.x = x + other.x;
  result.y = y + other.y;

  return result;
}

/**
 * @brief Adds a value to the Vector.
 * 
 * @param value How much is going to be added to the Vector 
 * @return result 
 */
inline Vector2 Vector2::operator+(float value) {

  Vector2 result;
  result.x = x + value;
  result.y = y + value;

  return result;
}

/**
 * @brief Adds two Vectors.
 * 
 * @param other How much is going to be added to the Vector 
 * @return this ptr 
 */
inline Vector2& Vector2::operator+=(const Vector2& other){

  x += other.x;
  y += other.y;

  return *this;
}

/**
 * @brief Adds a value to the Vector.
 * 
 * @param value How much is going to be added to the Vector 
 * @return this ptr 
 */
inline Vector2& Vector2::operator+=(float value){

  x += value;
  y += value;

  return *this;
}

/**
 * @brief Substraction of two Vectors.
 * 
 * @param other How much is going to be substracted to the Vector 
 * @return result 
 */
inline Vector2 Vector2::operator-(const Vector2& other) const {

  Vector2 result;
  result.x = x - other.x;
  result.y = y - other.y;

  return result;
}

/**
 * @brief Substracts a value to the Vector.
 * 
 * @param value How much is going to be substracted to the Vector 
 * @return result 
 */
inline Vector2 Vector2::operator-(float value) const {

  Vector2 result;
  result.x = x - value;
  result.y = y - value;

  return result;
}

/**
 * @brief turns the vector to negative.
 * 
 * @return this ptr 
 */
inline Vector2& Vector2::operator-() {

  x = -x;
  y = -y;

	return *this;
}

/**
 * @brief Substraction of two Vectors.
 * 
 * @param other How much is going to be substracted to the Vector 
 * @return this ptr 
 */
inline Vector2& Vector2::operator-=(const Vector2& other) {

  x -= other.x;
  y -= other.y;

  return *this;
}

/**
 * @brief Substracts a value to the Vector.
 * 
 * @param value How much is going to be substracted to the Vector 
 * @return this ptr 
 */
inline Vector2& Vector2::operator-=(float value){

  x -= value;
  y -= value;

  return *this;
}

/**
 * @brief Checks if a vector is equal to another one.
 * 
 * @param value the vector to compare 
 * @return true if they are equal
 * @return false if they aren't equal 
 */
inline bool Vector2::operator==(const Vector2& value) const {
  return x == value.x && y == value.y;
}

/**
 * @brief Checks if a vector is equal to another one.
 * 
 * @param value the vector to compare 
 * @return true if they aren't equal
 * @return false if they are equal 
 */
inline bool Vector2::operator!=(const Vector2& value) const {
  return x != value.x && y != value.y;
}

/**
 * @brief Equals Vector with a float.
 * 
 * @param value the float to compare 
 */
inline void Vector2::operator=(const Vector2& other) {
  x = other.x;
  y = other.y;
}

/**
 * @brief Multiplies a value to the Vector.
 * 
 * @param value How much is going to be multiplied to the Vector 
 * @return result 
 */
inline void Vector2::operator=(float value) {
  x = value;
  y = value;
}

/**
 * @brief Multiplies a value to the Vector.
 * 
 * @param value How much is going to be multiplied to the Vector 
 * @return this ptr 
 */
inline Vector2 Vector2::operator*(float value) const {

  Vector2 result;
  result.x = x * value;
  result.y = y * value;

	return result;
}

/**
 * @brief Divides a value to the Vector.
 * 
 * @param value How much is going to be divided to the Vector 
 * @return result 
 */
inline Vector2& Vector2::operator*=(float value) {

  x *= value;
  y *= value;

  return *this;
}

/**
 * @brief Divides a value to the Vector.
 * 
 * @param value How much is going to be divided to the Vector 
 * @return this ptr 
 */
inline Vector2 Vector2::operator/(float value) const {

  Vector2 result;
  result.x = x / value;
  result.y = y / value;

	return result;
}

/**
 * @brief Gets the Magnitude of the Vector
 * 
 * @return the magnitude of the vector 
 */
inline Vector2& Vector2::operator/=(float value) {

  x /= value;
  y /= value;

	return *this;
}

/**
 * @brief Gets the Magnitude of the Vector
 * 
 * @return the magnitude of the vector 
 */
inline float Vector2::Magnitude() const {
  return sqrtf ( (x * x) + (y * y) );
}

/**
 * @brief Normalizes de vector
 */
inline void Vector2::Normalize() {

  float vectorMagnitude = Magnitude();
  
  x /= vectorMagnitude;
  y /= vectorMagnitude;

}

/**
 * @brief Gets the normalized vector
 * 
 * @return result
 */
inline Vector2 Vector2::Normalized() const {

  Vector2 result;
  float vectorMagnitude = Magnitude();
  
  result.x = x / vectorMagnitude;
  result.y = y / vectorMagnitude;
  
	return result;
}

/**
 * @brief Scales the vector.
 * 
 * @param scale How much is going to get the Vector scaled 
 * @return this ptr 
 */
inline void Vector2::Scale(const Vector2 scale) {
  x *= scale.x;
  y *= scale.y;
}

/**
 * @brief Sets the Square Root of the vector
 * 
 * @return the square root of the vector 
 */
inline float Vector2::SqrMagnitude() const {
  return (x * x) + (y * y);
}

/**
 * @brief Calculates the distance between two points
 * 
 * @param a first point
 * @param b second point
 * @return the distance between them
 */
inline float Vector2::Distance(const Vector2 a, const Vector2 b) {
  return sqrtf( ( (b.x - a.x)*(b.x - a.x) ) + 
                              ((b.y - a.y)*(b.y - a.y) ) );
}

/**
 * @brief Calculates the dot product of the vector
 * 
 * @param a first point
 * @param b second point
 * @return the dot product of two vector 
 */
inline float Vector2::DotProduct(Vector2 a, Vector2 b) {
	return (a.x * b.x) + (a.y * b.y);
}

/**
 * @brief Lerps two Vectors
 * 
 * @return result 
 */
inline Vector2 Vector2::Lerp(const Vector2 a, const Vector2 b, float t) {

  Vector2 result;

  Clamp(t, 0.0f, 1.0f);

  result.x = a.x + (b.x - a.x) * t;
  result.y = a.y + (b.y - a.y) * t;

	return result;
}

/**
 * @brief Lerps two vectors
 * 
 * @return result 
 */
inline Vector2 Vector2::LerpUnclamped(const Vector2 a, const Vector2 b, float t) {

  Vector2 result;

  result.x = a.x + (b.x - a.x) * t;
  result.y = a.y + (b.y - a.y) * t;

	return result;
}

/**
 * @brief Prints the matrix value in console for debugging.
 */
inline void Vector2::Print() const{
  printf("\nx: % 1.3f y: % 1.3f",
    x, y
  );
}

}

#endif
