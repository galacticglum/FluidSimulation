#pragma once

#include <iostream>
#include <string>

#include "Vector3.h"

struct Vector4f
{
	float X, Y, Z, W;

	inline Vector4f() : Vector4f(0.0f, 0.0f, 0.0f, 0.0f) { }
	inline explicit Vector4f(float scalar) : Vector4f(scalar, scalar, scalar, scalar) { }
	inline Vector4f(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) { }

	Vector4f(const Vector3f& vector, float w);

	Vector4f& Add(const Vector4f& right);
	Vector4f& Subtract(const Vector4f& right);
	Vector4f& Multiply(const Vector4f& right);
	Vector4f& Divide(const Vector4f& right);

	Vector4f& Add(float right);
	Vector4f& Subtract(float right);
	Vector4f& Multiply(float right);
	Vector4f& Divide(float right);

	Vector4f& Normalize();
	Vector4f Normalized() const;

	Vector4f Negative() const;
	Vector4f& Negate();

	Vector4f& Abs();
	Vector4f Cross(const Vector4f& vector) const;

	float Magnitude() const;
	float SquareMagnitude() const;
	float Distance(const Vector4f& vector) const;
	float Dot(const Vector4f& vector) const;
	float Max() const;

	static Vector4f Lerp(const Vector4f& start, const Vector4f& destination, float blend);

	inline friend Vector4f operator+(Vector4f left, const Vector4f& right) { return left.Add(right); }
	inline friend Vector4f operator-(Vector4f left, const Vector4f& right) { return left.Subtract(right); }
	inline friend Vector4f operator*(Vector4f left, const Vector4f& right) { return left.Multiply(right); }
	inline friend Vector4f operator/(Vector4f left, const Vector4f& right) { return left.Divide(right); }
				  
	inline friend Vector4f operator-(Vector4f left) { return left.Negative(); }
				  
	inline friend Vector4f operator+(Vector4f left, float right) { return left.Add(right); }
	inline friend Vector4f operator-(Vector4f left, float right) { return left.Subtract(right); }
	inline friend Vector4f operator*(Vector4f left, float right) { return left.Multiply(right); }
	inline friend Vector4f operator/(Vector4f left, float right) { return left.Divide(right); }

	inline Vector4f& operator+=(const Vector4f& right) { return this->Add(right); }
	inline Vector4f& operator-=(const Vector4f& right) { return this->Subtract(right); }
	inline Vector4f& operator*=(const Vector4f& right) { return this->Multiply(right); }
	inline Vector4f& operator/=(const Vector4f& right) { return this->Divide(right); }

	bool operator==(const Vector4f& right) const;
	bool operator!=(const Vector4f& right) const;

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& stream, const Vector4f& right);

	static const Vector4f Zero;
	static const Vector4f One;
};