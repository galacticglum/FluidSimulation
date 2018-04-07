#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"

const Vector3f Vector3f::Zero = Vector3f(0);
const Vector3f Vector3f::One = Vector3f(1);

const Vector3f Vector3f::Up = Vector3f(0, 1, 0);
const Vector3f Vector3f::Down = Vector3f(0, -1, 0);
const Vector3f Vector3f::Left = Vector3f(-1, 0, 0);
const Vector3f Vector3f::Right = Vector3f(1, 0, 0);

const Vector3f Vector3f::Forward = Vector3f(0, 0, 1);
const Vector3f Vector3f::Back = Vector3f(0, 0, -1);

const Vector3f Vector3f::XAxis = Vector3f(1, 0, 0);
const Vector3f Vector3f::YAxis = Vector3f(0, 1, 0);
const Vector3f Vector3f::ZAxis = Vector3f(0, 0, 1);

Vector3f::Vector3f(const Vector2f& vector) : Vector3f(vector.X, vector.Y, 0) {}
Vector3f::Vector3f(const Vector4f& vector) : Vector3f(vector.X, vector.Y, vector.Z) {}

Vector3f& Vector3f::Add(const Vector3f& right)
{
	X += right.X;
	Y += right.Y;
	Z += right.Z;

	return *this;
}

Vector3f& Vector3f::Subtract(const Vector3f& right)
{
	X -= right.X;
	Y -= right.Y;
	Z -= right.Z;

	return *this;
}

Vector3f& Vector3f::Multiply(const Vector3f& right)
{
	X *= right.X;
	Y *= right.Y;
	Z *= right.Z;

	return *this;
}

Vector3f& Vector3f::Divide(const Vector3f& right)
{
    X /= right.X;
    Y /= right.Y;
    Z /= right.Z;

	return *this;
}

Vector3f& Vector3f::Add(float right)
{
    X += right;
    Y += right;
    Z += right;

	return *this;
}

Vector3f& Vector3f::Subtract(float right)
{
	X -= right;
	Y -= right;
	Z -= right;

	return *this;
}

Vector3f& Vector3f::Multiply(float right)
{
    X *= right;
    Y *= right;
    Z *= right;

	return *this;
}

Vector3f& Vector3f::Divide(float right)
{
	X /= right;
	Y /= right;
	Z /= right;

	return *this;
}

Vector3f& Vector3f::Normalize()
{
	float length = Magnitude();
	X /= length;
	Y /= length;
	Z /= length;

	return *this;
}

Vector3f Vector3f::Normalized() const
{
	float length = Magnitude();
	return Vector3f(X / length, Y / length, Z / length);
}

Vector3f Vector3f::Negative() const
{
	return Vector3f(-X, -Y, -Z);
}

Vector3f& Vector3f::Negate()
{
    X = -X;
    Y = -Y;
    Z = -Z;

	return *this;
}

Vector3f& Vector3f::Rotate(float angle, const Vector3f& axis)
{
	const float sin = sinf(-angle);
	const float cos = cosf(-angle);

	Vector3f rotation = Cross(axis * sin) + (*this * cos) + axis * Dot(axis * (1 - cos));
	X = rotation.X;
	Y = rotation.Y;
	Z = rotation.Z;

	return *this;
}

Vector3f& Vector3f::Abs()
{
    X = std::abs(X);
    Y = std::abs(Y);
    Z = std::abs(Z);

	return *this;
}

Vector3f Vector3f::Cross(const Vector3f& vector) const
{
    float x = (Y * vector.Z) - (Z * vector.Y);
    float y = (Z * vector.X) - (X * vector.Z);
    float z = (X * vector.Y) - (Y * vector.X);

	return Vector3f(x, y, z);
}

float Vector3f::Magnitude() const
{
	return sqrt(SquareMagnitude());
}

float Vector3f::SquareMagnitude() const
{
	return (X * X) + (Y * Y) + (Z * Z);
}

float Vector3f::Distance(const Vector3f& vector) const
{
    float a = X - vector.X;
    float b = Y - vector.Y;
    float c = Z - vector.Z;

	return sqrt((a * a) + (b * b) + (c * c));
}

float Vector3f::Dot(const Vector3f& vector) const
{
	return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z);
}

float Vector3f::Max() const
{
	return std::max(X, std::max(Y, Z));
}

Vector3f Vector3f::Lerp(const Vector3f& start, const Vector3f& destination, float blend)
{
	return Vector3f(MathFunctions::Lerp(start.X, destination.X, blend),
		MathFunctions::Lerp(start.Y, destination.Y, blend),
		MathFunctions::Lerp(start.Z, destination.Z, blend));
}

// Comparative Operators
bool Vector3f::operator==(const Vector3f& right) const
{
	return (X == right.X && Y == right.Y && Z == right.Z);
}

bool Vector3f::operator!=(const Vector3f& right) const
{
	return !(*this == right);
}

bool Vector3f::operator<(const Vector3f& right) const
{
	return (X < right.X && Y < right.Y && Z < right.Z);
}

bool Vector3f::operator<=(const Vector3f& right) const
{
	return (X <= right.X && Y <= right.Y && Z <= right.Z);
}

bool Vector3f::operator>(const Vector3f& right) const
{
	return (X > right.X && Y > right.Y && Z > right.Z);
}

bool Vector3f::operator>=(const Vector3f& right) const
{
	return (X >= right.X && Y >= right.Y && Z >= right.Z);
}

// String Operations
std::string Vector3f::ToString() const
{
	return "(" + std::to_string(X) + ", " + std::to_string(Y) + ", " + std::to_string(Z) + ")";
}

std::ostream& operator<<(std::ostream& stream, const Vector3f& right)
{
	return (stream << right.ToString());
}