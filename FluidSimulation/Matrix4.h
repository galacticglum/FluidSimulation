#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <sstream>

#include "MathFunctions.h"

#include "Vector3.h"
#include "Vector4.h"

struct Matrix4f
{
	float Elements[4][4];

	inline Matrix4f() { memset(this->Elements, 0, 16 * sizeof(float)); }
	inline explicit Matrix4f(float* elements) { memcpy(this->Elements, elements, 16 * sizeof(float)); }

	explicit Matrix4f(float scalar);
	Matrix4f(const Vector4f& row0, const Vector4f& row1, const Vector4f& row2, const Vector4f& row3);

	Matrix4f& Multiply(const Matrix4f& matrix);
	Vector4f Multiply(const Vector4f& vector) const;
	Vector3f Multiply(const Vector3f& vector) const;

	Vector4f GetRow(int idx) const;
	void SetRow(uint32_t idx, const Vector4f& row);

	Vector4f GetColumn(int idx) const;
	void SetColumn(uint32_t idx, const Vector4f& column);

	inline Vector3f GetPosition() const { return Vector3f(GetColumn(3)); }
	inline void SetPosition(const Vector3f& position) { SetColumn(3, Vector4f(position, 1)); }

	inline friend Matrix4f operator*(Matrix4f left, const Matrix4f& right) { return left.Multiply(right); }
	inline friend Vector4f operator*(const Matrix4f& left, const Vector4f& right) { return left.Multiply(right); }
	inline friend Vector3f operator*(const Matrix4f& left, const Vector3f& right) { return left.Multiply(right); }
	inline Matrix4f& operator *= (const Matrix4f& matrix) { return this->Multiply(matrix); }

	static Matrix4f Orthographic(float left, float right, float bottom, float top, float near, float far);
	static Matrix4f Perspective(float fov, float aspectRatio, float zNear, float zFar);

	static Matrix4f Translate(float x, float y, float z);
	static Matrix4f Translate(const Vector3f& translation);

	static Matrix4f Rotate(float x, float y, float z);
	static Matrix4f Rotate(const Vector3f& eulerAngles);
	static Matrix4f Rotate(const Vector3f& forward, const Vector3f& up);

	static Matrix4f Scale(float x, float y, float z);
	static Matrix4f Scale(const Vector3f& scale);

	static Matrix4f Transpose(const Matrix4f& matrix);

	static const Matrix4f Identity;

	std::string ToString() const;
	friend std::ostream& operator<<(std::ostream& stream, const Matrix4f& right);
};