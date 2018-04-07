#include "Vector4.h"
#include "Maths.h"

const Vector4f Vector4f::Zero = Vector4f{ 0, 0, 0, 0 };
const Vector4f Vector4f::One = Vector4f{ 1, 1, 1, 1 };

Vector4f::Vector4f(const Vector3f& vector, float w) : X(vector.X), Y(vector.Y), Z(vector.Z), W(w) {}

Vector4f& Vector4f::Add(const Vector4f& right)
{
    X += right.X;
    Y += right.Y;
    Z += right.Z;
    W += right.W;

	return *this;
}

Vector4f& Vector4f::Subtract(const Vector4f& right)
{
    X -= right.X;
    Y -= right.Y;
    Z -= right.Z;
    W -= right.W;

	return *this;
}

Vector4f& Vector4f::Multiply(const Vector4f& right)
{
    X *= right.X;
    Y *= right.Y;
    Z *= right.Z;
    W *= right.W;

	return *this;
}

Vector4f& Vector4f::Divide(const Vector4f& right)
{
	X /= right.X;
	Y /= right.Y;
	Z /= right.Z;
	W /= right.W;

	return *this;
}

Vector4f& Vector4f::Add(float right)
{
    X += right;
    Y += right;
    Z += right;
    W += right;

	return *this;
}

Vector4f& Vector4f::Subtract(float right)
{
    X -= right;
    Y -= right;
    Z -= right;
    W -= right;

	return *this;
}

Vector4f& Vector4f::Multiply(float right)
{
    X *= right;
    Y *= right;
    Z *= right;
    W *= right;

	return *this;
}

Vector4f& Vector4f::Divide(float right)
{
    X /= right;
    Y /= right;
    Z /= right;
    W /= right;

	return *this;
}

Vector4f& Vector4f::Normalize()
{
	float length = Magnitude();
	X /= length;
	Y /= length;
	Z /= length;
	W /= length;

	return *this;
}

Vector4f Vector4f::Normalized() const
{
	float length = Magnitude();
	return Vector4f(X / length, Y / length, Z / length, W / length);
}

Vector4f Vector4f::Negative() const
{
	return Vector4f(-X, -Y, -Z, -W);
}

Vector4f& Vector4f::Negate()
{
    X = -X;
    Y = -Y;
    Z = -Z;
    W = -W;

	return *this;
}

Vector4f& Vector4f::Abs()
{
    X = std::abs(X);
    Y = std::abs(Y);
    Z = std::abs(Z);
    W = std::abs(W);

	return *this;
}

Vector4f Vector4f::Cross(const Vector4f& vector) const
{
    float x = (Y * vector.Z) - (Z * vector.Y);
    float y = (Z * vector.X) - (X * vector.Z);
    float z = (X * vector.Y) - (Y * vector.X);

	return Vector4f(x, y, z, 1);
}

float Vector4f::Magnitude() const
{
	return sqrt(SquareMagnitude());
}

float Vector4f::SquareMagnitude() const
{
	return (X * X) + (Y * Y) + (Z * Z) + (W * W);
}

float Vector4f::Distance(const Vector4f& vector) const
{
    float a = X - vector.X;
    float b = Y - vector.Y;
    float c = Z - vector.Z;
    float d = W - vector.W;

	return sqrt((a * a) + (b * b) + (c * c) + (d * d));
}

float Vector4f::Dot(const Vector4f& vector) const
{
	return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z) + (W * vector.W);
}

float Vector4f::Max() const
{
	return std::max(X, std::max(Y, std::max(Z, W)));
}

Vector4f Vector4f::Lerp(const Vector4f& start, const Vector4f& destination, float blend)
{
	return Vector4f(MathFunctions::Lerp(start.X, start.X, blend),
		MathFunctions::Lerp(start.Y, start.Y, blend),
		MathFunctions::Lerp(start.Z, start.Z, blend),
		MathFunctions::Lerp(start.W, start.W, blend));
}

bool Vector4f::operator==(const Vector4f& right) const
{
	return (X == right.X && Y == right.Y && Z == right.Z && W == right.W);
}

bool Vector4f::operator!=(const Vector4f& right) const
{
	return !(*this == right);
}

// String Operations
std::string Vector4f::ToString() const
{
	return "(" + std::to_string(X) + ", " + std::to_string(Y) + ", " + std::to_string(Z) + ", " + std::to_string(W) + ")";
}

std::ostream& operator<<(std::ostream& stream, const Vector4f& right)
{
	return (stream << right.ToString());
}