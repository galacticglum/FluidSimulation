#pragma once

#include <string>
#include <algorithm>

struct Vector3f;
struct Vector4f;
struct Vector2f
{
	float X, Y;

    Vector2f() : Vector2f(0.0f, 0.0f) { }
    explicit Vector2f(const float scalar) : Vector2f(scalar, scalar) { }
    Vector2f(const float x, const float y) : X(x), Y(y) { }

    explicit Vector2f(const Vector3f& vector);

	Vector2f& Add(const Vector2f& right);
	Vector2f& Subtract(const Vector2f& right);
	Vector2f& Multiply(const Vector2f& right);
	Vector2f& Divide(const Vector2f& right);

	Vector2f& Add(float right);
	Vector2f& Subtract(float right);
	Vector2f& Multiply(float right);
	Vector2f& Divide(float right);

	Vector2f& Normalize();

	Vector2f Negative() const;
	Vector2f& Negate();

	Vector2f& Rotate(float angle);
	Vector2f& Abs();

	float Magnitude() const;
	float SquareMagnitude() const;

	float Distance(const Vector2f& vector) const;
	float Dot(const Vector2f& vector) const;
	float Cross(const Vector2f& vector) const;
	float Max() const;

	static Vector2f Lerp(const Vector2f& start, Vector2f& destination, float blend);

    friend Vector2f operator+(Vector2f left, const Vector2f& right) { return left.Add(right); }
    friend Vector2f operator-(Vector2f left, const Vector2f& right) { return left.Subtract(right); }
    friend Vector2f operator*(Vector2f left, const Vector2f& right) { return left.Multiply(right); }
    friend Vector2f operator/(Vector2f left, const Vector2f& right) { return left.Divide(right); }

    friend Vector2f operator-(Vector2f left) { return left.Negative(); }

    friend Vector2f operator+(Vector2f left, const float right) { return left.Add(right); }
    friend Vector2f operator-(Vector2f left, const float right) { return left.Subtract(right); }
    friend Vector2f operator*(Vector2f left, const float right) { return left.Multiply(right); }
    friend Vector2f operator/(Vector2f left, const float right) { return left.Divide(right); }

    Vector2f& operator+=(const Vector2f& right) { return Add(right); }
    Vector2f& operator-=(const Vector2f& right) { return Subtract(right); }
    Vector2f& operator*=(const Vector2f& right) { return Multiply(right); }
    Vector2f& operator/=(const Vector2f& right) { return Divide(right); }

    Vector2f& operator+=(const float right) { return Add(right); }
    Vector2f& operator-=(const float right) { return Subtract(right); }
    Vector2f& operator*=(const float right) { return Multiply(right); }
    Vector2f& operator/=(const float right) { return Divide(right); }

	bool operator==(const Vector2f& right) const;
	bool operator!=(const Vector2f& right) const;

	bool operator<(const Vector2f& right) const;
	bool operator<=(const Vector2f& right) const;
	bool operator>(const Vector2f& right) const;
	bool operator>=(const Vector2f& right) const;

    explicit operator Vector3f() const;
    explicit operator Vector4f() const;

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& stream, const Vector2f& right);

	static const Vector2f Zero;
	static const Vector2f One;
};