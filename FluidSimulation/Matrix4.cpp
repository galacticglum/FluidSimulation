#include "Matrix4.h"

const Matrix4f Matrix4f::Identity = Matrix4f(1);

Matrix4f::Matrix4f(float scalar)
{
	memset(this->Elements, 0, 16 * sizeof(float));

	this->Elements[0][0] = scalar;
	this->Elements[1][1] = scalar;
	this->Elements[2][2] = scalar;
	this->Elements[3][3] = scalar;
}

Matrix4f::Matrix4f(const Vector4f& row0, const Vector4f& row1, const Vector4f& row2, const Vector4f& row3)
{
	this->SetRow(0, row0);
	this->SetRow(1, row1);
	this->SetRow(2, row2);
	this->SetRow(3, row3);
}

Matrix4f& Matrix4f::Multiply(const Matrix4f& matrix)
{
	float data[4][4];
	for (int32_t row = 0; row < 4; row++)
	{
		for (int32_t column = 0; column < 4; column++)
		{
			float rm = 0;
			for (int32_t i = 0; i < 4; i++)
			{
				rm += this->Elements[row][i] * matrix.Elements[i][column];
			}

			data[row][column] = rm;
		}
	}

	memcpy(this->Elements, data, 16 * sizeof(float));
	return (*this);
}

Vector4f Matrix4f::Multiply(const Vector4f& vector) const
{
	return vector.Multiply(*this);
}

Vector3f Matrix4f::Multiply(const Vector3f& vector) const
{
	return vector.Multiply(*this);
}

Vector4f Matrix4f::GetRow(int idx) const
{
	return Vector4f(this->Elements[idx][0],
		this->Elements[idx][1],
		this->Elements[idx][2],
		this->Elements[idx][3]);
}

void Matrix4f::SetRow(uint32_t idx, const Vector4f& column)
{
	this->Elements[idx][0] = column.X;
	this->Elements[idx][1] = column.Y;
	this->Elements[idx][2] = column.Z;
	this->Elements[idx][3] = column.W;
}

Vector4f Matrix4f::GetColumn(int idx) const
{
	return Vector4f(this->Elements[0][idx],
		this->Elements[1][idx],
		this->Elements[2][idx],
		this->Elements[3][idx]);
}

void Matrix4f::SetColumn(uint32_t idx, const Vector4f& column)
{
	this->Elements[0][idx] = column.X;
	this->Elements[1][idx] = column.Y;
	this->Elements[2][idx] = column.Z;
	this->Elements[3][idx] = column.W;
}

Matrix4f Matrix4f::Orthographic(float left, float right, float bottom, float top, float near, float far)
{
	Matrix4f result = Matrix4f::Identity;
	result.Elements[0][0] = 2.0f / (right - left);
	result.Elements[1][1] = 2.0f / (top - bottom);
	result.Elements[2][2] = 2.0f / (near - far);

	result.Elements[0][3] = (left + right) / (left - right);
	result.Elements[1][3] = (bottom + top) / (bottom - top);
	result.Elements[2][3] = (far + near) / (far - near);

	return result;
}

Matrix4f Matrix4f::Perspective(float fov, float aspectRatio, float zNear, float zFar)
{
	Matrix4f result = Matrix4f::Identity;

	float q = 1.0f / std::tan(MathFunctions::DegreesToRadians(0.5f * fov));
	float a = q / aspectRatio;

	float b = (zNear + zFar) / (zNear - zFar);
	float c = (2.0f * zNear * zFar) / (zNear - zFar);

	result.Elements[0][0] = a;
	result.Elements[1][1] = q;
	result.Elements[2][2] = b;

	result.Elements[3][2] = -1.0f;
	result.Elements[2][3] = c;

	return result;
}

Matrix4f Matrix4f::Translate(float x, float y, float z)
{
	return Matrix4f::Translate(Vector3f(x, y, z));
}

Matrix4f Matrix4f::Translate(const Vector3f& translation)
{
	Matrix4f result = Matrix4f::Identity;

	result.Elements[0][3] = translation.X;
	result.Elements[1][3] = translation.Y;
	result.Elements[2][3] = translation.Z;

	return result;
}

Matrix4f Matrix4f::Rotate(float x, float y, float z)
{
	return Matrix4f::Rotate(Vector3f(x, y, z));
}

Matrix4f Matrix4f::Rotate(const Vector3f& eulerAngles)
{
	Matrix4f rx = Matrix4f::Identity;
	Matrix4f ry = Matrix4f::Identity;
	Matrix4f rz = Matrix4f::Identity;

	float x = MathFunctions::DegreesToRadians(eulerAngles.X);
	float y = MathFunctions::DegreesToRadians(eulerAngles.Y);
	float z = MathFunctions::DegreesToRadians(eulerAngles.Z);


	rx.Elements[1][1] = cosf(x);  rx.Elements[1][2] = -sinf(x);
	rx.Elements[2][1] = sinf(x);  rx.Elements[2][2] = cosf(x);

	ry.Elements[0][0] = cosf(y);  ry.Elements[0][2] = -sinf(y);
	ry.Elements[2][0] = sinf(y);  ry.Elements[2][2] = cosf(y);

	rz.Elements[0][0] = cosf(z);  rz.Elements[0][1] = -sinf(z);
	rz.Elements[1][0] = sinf(z);  rz.Elements[1][1] = cosf(z);

	return rx * ry * rz;
}

Matrix4f Matrix4f::Rotate(const Vector3f& forward, const Vector3f& up)
{
	Matrix4f result = Matrix4f::Identity;

	Vector3f n = forward.Normalized();
	Vector3f u = up.Normalized().Cross(n);
	Vector3f v = n.Cross(u);

	result.Elements[0][0] = u.X;   result.Elements[0][1] = u.Y;   result.Elements[0][2] = u.Z;   result.Elements[0][3] = 0.0f;
	result.Elements[1][0] = v.X;   result.Elements[1][1] = v.Y;   result.Elements[1][2] = v.Z;   result.Elements[1][3] = 0.0f;
	result.Elements[2][0] = n.X;   result.Elements[2][1] = n.Y;   result.Elements[2][2] = n.Z;   result.Elements[2][3] = 0.0f;
	result.Elements[3][0] = 0.0f;  result.Elements[3][1] = 0.0f;  result.Elements[3][2] = 0.0f;  result.Elements[3][3] = 1.0f;

	return result;
}

Matrix4f Matrix4f::Scale(float x, float y, float z)
{
	return Matrix4f::Scale(Vector3f(x, y, z));
}

Matrix4f Matrix4f::Scale(const Vector3f& scale)
{
	Matrix4f result = Matrix4f::Identity;

	result.Elements[0][0] = scale.X;
	result.Elements[1][1] = scale.Y;
	result.Elements[2][2] = scale.Z;

	return result;
}

Matrix4f Matrix4f::Transpose(const Matrix4f& matrix)
{
	return Matrix4f
	(
		Vector4f(matrix.GetRow(0).X, matrix.GetRow(1).X, matrix.GetRow(2).X, matrix.GetRow(3).X),
		Vector4f(matrix.GetRow(0).Y, matrix.GetRow(1).Y, matrix.GetRow(2).Y, matrix.GetRow(3).Y),
		Vector4f(matrix.GetRow(0).Z, matrix.GetRow(1).Z, matrix.GetRow(2).Z, matrix.GetRow(3).Z),
		Vector4f(matrix.GetRow(0).W, matrix.GetRow(1).W, matrix.GetRow(2).W, matrix.GetRow(3).W)
	);
}

std::string Matrix4f::ToString() const
{
	std::stringstream result;

	result << "(" << GetRow(0).X << ", " << GetRow(1).X << ", " << GetRow(2).X << ", " << GetRow(3).X << "),\n";
	result << "(" << GetRow(0).Y << ", " << GetRow(1).Y << ", " << GetRow(2).Y << ", " << GetRow(3).Y << "),\n";
	result << "(" << GetRow(0).Z << ", " << GetRow(1).Z << ", " << GetRow(2).Z << ", " << GetRow(3).Z << "),\n";
	result << "(" << GetRow(0).W << ", " << GetRow(1).W << ", " << GetRow(2).W << ", " << GetRow(3).W << ")";

	return result.str();
}

std::ostream& operator<<(std::ostream& stream, const Matrix4f& right)
{
	return (stream << right.ToString());
}