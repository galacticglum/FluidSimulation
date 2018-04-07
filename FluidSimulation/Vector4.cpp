#include "Vector4.h"
#include "Matrix4.h"
#include "MathFunctions.h"

const Vector4f Vector4f::Zero = Vector4f{ 0, 0, 0, 0 };
const Vector4f Vector4f::One = Vector4f{ 1, 1, 1, 1 };

Vector4f::Vector4f(const Vector3f& vector, float w) : X(vector.X), Y(vector.Y), Z(vector.Z), W(w) {}

Vector4f& Vector4f::Add(const Vector4f& right)
{
	this->X += right.X;
	this->Y += right.Y;
	this->Z += right.Z;
	this->W += right.W;

	return *this;
}

Vector4f& Vector4f::Subtract(const Vector4f& right)
{
	this->X -= right.X;
	this->Y -= right.Y;
	this->Z -= right.Z;
	this->W -= right.W;

	return *this;
}

Vector4f& Vector4f::Multiply(const Vector4f& right)
{
	this->X *= right.X;
	this->Y *= right.Y;
	this->Z *= right.Z;
	this->W *= right.W;

	return *this;
}

Vector4f& Vector4f::Divide(const Vector4f& right)
{
	this->X /= right.X;
	this->Y /= right.Y;
	this->Z /= right.Z;
	this->W /= right.W;

	return *this;
}

Vector4f& Vector4f::Add(float right)
{
	this->X += right;
	this->Y += right;
	this->Z += right;
	this->W += right;

	return *this;
}

Vector4f& Vector4f::Subtract(float right)
{
	this->X -= right;
	this->Y -= right;
	this->Z -= right;
	this->W -= right;

	return *this;
}

Vector4f& Vector4f::Multiply(float right)
{
	this->X *= right;
	this->Y *= right;
	this->Z *= right;
	this->W *= right;

	return *this;
}

Vector4f& Vector4f::Divide(float right)
{
	this->X /= right;
	this->Y /= right;
	this->Z /= right;
	this->W /= right;

	return *this;
}

Vector4f Vector4f::Multiply(const Matrix4f& matrix) const
{
	return Vector4f
	(
		matrix.GetRow(0).X * this->X + matrix.GetRow(0).Y * this->Y + matrix.GetRow(0).Z * this->Z + matrix.GetRow(0).W * this->W,
		matrix.GetRow(1).X * this->X + matrix.GetRow(1).Y * this->Y + matrix.GetRow(1).Z * this->Z + matrix.GetRow(1).W * this->W,
		matrix.GetRow(2).X * this->X + matrix.GetRow(2).Y * this->Y + matrix.GetRow(2).Z * this->Z + matrix.GetRow(2).W * this->W,
		matrix.GetRow(3).X * this->X + matrix.GetRow(3).Y * this->Y + matrix.GetRow(3).Z * this->Z + matrix.GetRow(3).W * this->W
	);
}

Vector4f& Vector4f::Normalize()
{
	float length = Magnitude();
	this->X /= length;
	this->Y /= length;
	this->Z /= length;
	this->W /= length;

	return *this;
}

Vector4f Vector4f::Normalized() const
{
	float length = Magnitude();
	return Vector4f(this->X / length, this->Y / length, this->Z / length, this->W / length);
}

Vector4f Vector4f::Negative() const
{
	return Vector4f(-this->X, -this->Y, -this->Z, -this->W);
}

Vector4f& Vector4f::Negate()
{
	this->X = -this->X;
	this->Y = -this->Y;
	this->Z = -this->Z;
	this->W = -this->W;

	return *this;
}

Vector4f& Vector4f::Abs()
{
	this->X = std::abs(this->X);
	this->Y = std::abs(this->Y);
	this->Z = std::abs(this->Z);
	this->W = std::abs(this->W);

	return *this;
}

Vector4f Vector4f::Cross(const Vector4f& vector) const
{
	float x = (this->Y * vector.Z) - (this->Z * vector.Y);
	float y = (this->Z * vector.X) - (this->X * vector.Z);
	float z = (this->X * vector.Y) - (this->Y * vector.X);

	return Vector4f(x, y, z, 1);
}

float Vector4f::Magnitude() const
{
	return sqrt(SquareMagnitude());
}

float Vector4f::SquareMagnitude() const
{
	return (this->X * this->X) + (this->Y * this->Y) + (this->Z * this->Z) + (this->W * this->W);
}

float Vector4f::Distance(const Vector4f& vector) const
{
	float a = this->X - vector.X;
	float b = this->Y - vector.Y;
	float c = this->Z - vector.Z;
	float d = this->W - vector.W;

	return sqrt((a * a) + (b * b) + (c * c) + (d * d));
}

float Vector4f::Dot(const Vector4f& vector) const
{
	return (this->X * vector.X) + (this->Y * vector.Y) + (this->Z * vector.Z) + (this->W * vector.W);
}

float Vector4f::Max() const
{
	return std::max(this->X, std::max(this->Y, std::max(this->Z, this->W)));
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
	return "(" + std::to_string(this->X) + ", " + std::to_string(this->Y) + ", " + std::to_string(this->Z) + ", " + std::to_string(this->W) + ")";
}

std::ostream& operator<<(std::ostream& stream, const Vector4f& right)
{
	return (stream << right.ToString());
}