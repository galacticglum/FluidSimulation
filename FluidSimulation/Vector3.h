#pragma once

#include <string>
#include <algorithm>

struct Vector2f;
struct Vector4f;
struct Vector3f
{
	float X, Y, Z;

    Vector3f() : Vector3f(0.0f, 0.0f, 0.0f) { }
    explicit Vector3f(const float scalar) : Vector3f(scalar, scalar, scalar) { }
    Vector3f(const float x, const float y, const float z) : X(x), Y(y), Z(z) { }
    Vector3f(const float x, const float y) : X(x), Y(y), Z(0) {}

    explicit Vector3f(const Vector2f& vector);
    explicit Vector3f(const Vector4f& vector);

	Vector3f& Add(const Vector3f& right);
	Vector3f& Subtract(const Vector3f& right);
	Vector3f& Multiply(const Vector3f& right);
	Vector3f& Divide(const Vector3f& right);

	Vector3f& Add(float right);
	Vector3f& Subtract(float right);
	Vector3f& Multiply(float right);
	Vector3f& Divide(float right);

	Vector3f& Normalize();
	Vector3f Normalized() const;

	Vector3f Negative() const;
	Vector3f& Negate();

	Vector3f& Rotate(float angle, const Vector3f& axis);

	Vector3f& Abs();
	Vector3f Cross(const Vector3f& vector) const;

	float Magnitude() const;
	float SquareMagnitude() const;
	float Distance(const Vector3f& vector) const;
	float Dot(const Vector3f& vector) const;
	float Max() const;

	static Vector3f Lerp(const Vector3f& start, const Vector3f& destination, float blend);

    friend Vector3f operator+(Vector3f left, const Vector3f& right) { return left.Add(right); }
    friend Vector3f operator-(Vector3f left, const Vector3f& right) { return left.Subtract(right); }
    friend Vector3f operator*(Vector3f left, const Vector3f& right) { return left.Multiply(right); }
    friend Vector3f operator/(Vector3f left, const Vector3f& right) { return left.Divide(right); }

    friend Vector3f operator-(Vector3f left) { return left.Negative(); }

    friend Vector3f operator+(Vector3f left, float right) { return left.Add(right); }
    friend Vector3f operator-(Vector3f left, float right) { return left.Subtract(right); }
    friend Vector3f operator*(Vector3f left, float right) { return left.Multiply(right); }
    friend Vector3f operator/(Vector3f left, float right) { return left.Divide(right); }

    Vector3f& operator+=(const Vector3f& right) { return Add(right); }
    Vector3f& operator-=(const Vector3f& right) { return Subtract(right); }
    Vector3f& operator*=(const Vector3f& right) { return Multiply(right); }
    Vector3f& operator/=(const Vector3f& right) { return Divide(right); }

    Vector3f& operator+=(const float right) { return Add(right); }
    Vector3f& operator-=(const float right) { return Subtract(right); }
    Vector3f& operator*=(const float right) { return Multiply(right); }
    Vector3f& operator/=(const float right) { return Divide(right); }

	bool operator==(const Vector3f& right) const;
	bool operator!=(const Vector3f& right) const;

	bool operator<(const Vector3f& right) const;
	bool operator<=(const Vector3f& right) const;
	bool operator>(const Vector3f& right) const;
	bool operator>=(const Vector3f& right) const;

    explicit operator Vector2f() const;
    explicit operator Vector4f() const;

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& stream, const Vector3f& right);

	static const Vector3f Zero;
	static const Vector3f One;

	static const Vector3f Up;
	static const Vector3f Down;
	static const Vector3f Left;
	static const Vector3f Right;

	static const Vector3f Forward;
	static const Vector3f Back;

	static const Vector3f XAxis;
	static const Vector3f YAxis;
	static const Vector3f ZAxis;
};