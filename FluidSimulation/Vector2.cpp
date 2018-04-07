#include "Vector2.h"
#include "Vector3.h"

const Vector2f Vector2f::Zero = Vector2f(0, 0);
const Vector2f Vector2f::One = Vector2f(1, 1);

Vector2f::Vector2f(const Vector3f& vector) : Vector2f(vector.X, vector.Y) {}

Vector2f& Vector2f::Add(const Vector2f& right)
{
    X += right.X;
    Y += right.Y;

	return (*this);
}

Vector2f& Vector2f::Subtract(const Vector2f& right)
{
    X -= right.X;
    Y -= right.Y;

	return (*this);
}

Vector2f& Vector2f::Multiply(const Vector2f& right)
{
    X *= right.X;
    Y *= right.Y;

	return (*this);
}

Vector2f& Vector2f::Divide(const Vector2f& right)
{
    X /= right.X;
    Y /= right.Y;

	return (*this);
}

Vector2f& Vector2f::Add(float right)
{
    X += right;
    Y += right;

	return (*this);
}

Vector2f& Vector2f::Subtract(float right)
{
    X -= right;
    Y -= right;

	return (*this);
}

Vector2f& Vector2f::Multiply(float right)
{
    X *= right;
	Y *= right;

	return (*this);
}

Vector2f& Vector2f::Divide(float right)
{
	X /= right;
	Y /= right;

	return (*this);
}

Vector2f& Vector2f::Normalize()
{
	float magnitude = Magnitude();
    X /= magnitude;
    Y /= magnitude;

	return *this;
}

Vector2f Vector2f::Negative() const
{
	return Vector2f(-X, -Y);
}

Vector2f& Vector2f::Negate()
{
    X = -X;
    Y = -Y;

	return *this;
}

Vector2f& Vector2f::Rotate(float angle)
{
	double radian = MathFunctions::DegreesToRadians(angle);
	double cosine = std::cos(radian);
	double sine = std::sin(radian);

    X = static_cast<float>(X * cosine -Y * sine);
    Y = static_cast<float>(X * sine + Y * cosine);

	return *this;
}

Vector2f& Vector2f::Abs()
{
    X = std::abs(X);
    Y = std::abs(Y);

	return *this;
}

float Vector2f::Magnitude() const
{
	return sqrt(SquareMagnitude());
}

float Vector2f::SquareMagnitude() const
{
	return (X * X) + (Y * Y);
}

float Vector2f::Distance(const Vector2f& vector) const
{
    float a = X - vector.X;
    float b = Y - vector.Y;

	return sqrt((a * a) + (b * b));
}

float Vector2f::Dot(const Vector2f& vector) const
{
	return (X * vector.X) + (Y * vector.Y);
}

float Vector2f::Cross(const Vector2f& vector) const
{
	return X * vector.Y - Y * vector.X;
}

float Vector2f::Max() const
{
	return std::max(X, Y);
}

Vector2f Vector2f::Lerp(const Vector2f& start, Vector2f& destination, float blend)
{
	return Vector2f(MathFunctions::Lerp(start.X, destination.X, blend),
		MathFunctions::Lerp(start.Y, destination.Y, blend));
}

// Comparitive Operators
bool Vector2f::operator==(const Vector2f& right) const
{
	return (X == right.X && Y == right.Y);
}

bool Vector2f::operator!=(const Vector2f& right) const
{
	return !(*this == right);
}

bool Vector2f::operator<(const Vector2f& right) const
{
	return (X < right.X && Y < right.Y);
}

bool Vector2f::operator<=(const Vector2f& right) const
{
	return (X <= right.X && Y <= right.Y);
}

bool Vector2f::operator>(const Vector2f& right) const
{
	return (X > right.X && Y > right.Y);
}

bool Vector2f::operator>=(const Vector2f& right) const
{
	return (X >= right.X && Y >= right.Y);
}

// String Operations
std::string Vector2f::ToString() const
{
	return "(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
}

std::ostream& operator<<(std::ostream& stream, const Vector2f& right)
{
	return (stream << right.ToString());
}