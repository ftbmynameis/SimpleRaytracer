#ifndef VECTOR_HPP
#define VECTOR_HPP

#pragma once

#include <cmath>

template <typename T>
struct Vector3
{
	T x, y, z;
	
	Vector3()
		: x(0), y(0), z(0)
	{
	}

	Vector3(T v)
		: x(v), y(v), z(v)
	{
	}

	Vector3(const Vector3<T>& v)
		: x(v.x), y(v.y), z(v.z)
	{
	}

	Vector3(T _x, T _y, T _z) 
		:	x(_x), y(_y), z(_z)
	{
	}

	Vector3& operator = (const Vector3& v)	{x = v.x; y = v.y; z = v.z; return *this;}
	Vector3& operator += (const Vector3& v)	{x += v.x; y += v.y; z += v.z; return *this;}
	Vector3& operator -= (const Vector3& v)	{x -= v.x; y -= v.y; z -= v.z; return *this;}
	Vector3& operator *= (const Vector3& v)	{x *= v.x; y *= v.y; z *= v.z; return *this;}
	Vector3& operator *= (const float f)		{x *= f; y *= f; z *= f; return *this;}
	Vector3& operator /= (const Vector3& v)	{x /= v.x; y /= v.y; z /= v.z; return *this;}
	Vector3& operator /= (const float f)		{x /= f; y /= f; z /= f; return *this;}

};

template <typename T>
Vector3<T> operator + (const Vector3<T>& a, const Vector3<T>& b)	{return Vector3<T>(a.x + b.x, a.y + b.y, a.z + b.z);}
template <typename T>
Vector3<T> operator - (const Vector3<T>& a, const Vector3<T>& b)	{return Vector3<T>(a.x - b.x, a.y - b.y, a.z - b.z);}
template <typename T>
Vector3<T> operator - (const Vector3<T>& v)						{return Vector3<T>(-v.x, -v.y, -v.z);}
template <typename T>
Vector3<T> operator * (const Vector3<T>& a, const Vector3<T>& b)	{return Vector3<T>(a.x * b.x, a.y * b.y, a.z * b.z);}
template <typename T>
Vector3<T> operator * (const Vector3<T>& v, const float f)			{return Vector3<T>(v.x * f, v.y * f, v.z * f);}
template <typename T>
Vector3<T> operator * (const float f, const Vector3<T>& v)			{return Vector3<T>(v.x * f, v.y * f, v.z * f);}
template <typename T>
Vector3<T> operator / (const Vector3<T>& a, const Vector3<T>& b)	{return Vector3<T>(a.x / b.x, a.y / b.y, a.z / b.z);}
template <typename T>
Vector3<T> operator / (const Vector3<T>& v, const float f)			{return Vector3<T>(v.x / f, v.y / f, v.z / f);}

template <typename T>
bool operator == (const Vector3<T>& a, const Vector3<T>& b) {if(a.x != b.x) return false; if(a.y != b.y) return false; return a.z == b.z;}
template <typename T>
bool operator != (const Vector3<T>& a, const Vector3<T>& b) {if(a.x != b.x) return true; if(a.y != b.y) return true; return a.z != b.z;}

template <typename T>
float length(const Vector3<T>& v) {return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);}
template <typename T>
Vector3<T> normalize(const Vector3<T>& v) {float l = length(v); return Vector3<T>(v.x / l, v.y / l, v.z / l);}
template <typename T>
float dot(const Vector3<T>& a, const Vector3<T>& b) {return a.x * b.x + a.y * b.y + a.z * b.z;}
template <typename T>
Vector3<T> reflect(const Vector3<T>& v, const Vector3<T>& n) {return 2 * dot(v, n) * n - v;}

#endif