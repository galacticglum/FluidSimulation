#pragma once

#include <string>

#include "Vector2.h"
#include "Vector3.h"

struct Vector4f
{
	float X, Y, Z, W;

    Vector4f() : Vector4f(0.0f, 0.0f, 0.0f, 0.0f) { }
    explicit Vector4f(const float scalar) : Vector4f(scalar, scalar, scalar, scalar) { }
    Vector4f(const float x, const float y, const float z, const float w) : X(x), Y(y), Z(z), W(w) { }

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

    friend Vector4f operator+(Vector4f left, const Vector4f& right) { return left.Add(right); }
    friend Vector4f operator-(Vector4f left, const Vector4f& right) { return left.Subtract(right); }
    friend Vector4f operator*(Vector4f left, const Vector4f& right) { return left.Multiply(right); }
    friend Vector4f operator/(Vector4f left, const Vector4f& right) { return left.Divide(right); }

    friend Vector4f operator-(Vector4f left) { return left.Negative(); }

    friend Vector4f operator+(Vector4f left, const float right) { return left.Add(right); }
    friend Vector4f operator-(Vector4f left, const float right) { return left.Subtract(right); }
    friend Vector4f operator*(Vector4f left, const float right) { return left.Multiply(right); }
    friend Vector4f operator/(Vector4f left, const float right) { return left.Divide(right); }

    Vector4f& operator+=(const Vector4f& right) { return Add(right); }
    Vector4f& operator-=(const Vector4f& right) { return Subtract(right); }
    Vector4f& operator*=(const Vector4f& right) { return Multiply(right); }
    Vector4f& operator/=(const Vector4f& right) { return Divide(right); }

	bool operator==(const Vector4f& right) const;
	bool operator!=(const Vector4f& right) const;

    explicit operator Vector2f() const { return { X, Y }; }
    explicit operator Vector3f() const { return { X, Y, Z }; }

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& stream, const Vector4f& right);

	static const Vector4f Zero;
	static const Vector4f One;
};