#pragma once

#include <iostream>
#include <cmath>

static const double PI = 3.1415926535897932384626433;
static const double PI_OVER_2 = PI / 2;
static const double PI_OVER_3 = PI / 3;
static const double PI_OVER_4 = PI / 4;
static const double PI_OVER_6 = PI / 6;
static const double TWO_PI = 2 * PI;
static const double THREE_PI_OVER_2 = 3 * PI / 2;

static const double E = 2.71828182845904523536;
static const double LOG_10E = 0.434294482;
static const double LOG_2E = 1.442695041;

struct Vector2f;
struct Vector3f;
struct Vector4f;
struct MathFunctions
{
    static const float Epsilon;
    static const long MaxLong;
    static const int MaxInt;
    static const float MaxFloat;
    static const double MaxDouble;

    static long NextPowerOfTwo(long n);
    static int NextPowerOfTwo(int n);
    static float NextPowerOfTwo(float n);
    static double NextPowerOfTwo(double n);

    static long Factorial(int n);
    static long BinomialCoefficient(int n, int k);

    static float InverseSqrtFast(float x);
    static double InverseSqrtFast(double x) { return InverseSqrtFast(static_cast<float>(x)); }

    static float DegreesToRadians(float degrees);
    static float RadiansToDegrees(float radians);

    static double DegreesToRadians(double degrees);
    static double RadiansToDegree(double radians);

    static void Swap(double& a, double& b);
    static void Swap(float& a, float& b);

    static long Lerp(const long left, const long right, const float blend) { return static_cast<long>(left + (right - left) * blend); }
    static int Lerp(const int left, const int right, const float blend) { return static_cast<int>(left + (right - left) * blend); }
    static float Lerp(const float left, const float right, const float blend) { return left + (right - left) * blend; }
    static double Lerp(const double left, const double right, const double blend) { return left + (right - left) * blend; }

    static bool IsEqualApproximate(const long left, const long right) { return std::abs(left - right) < Epsilon; }
    static bool IsEqualApproximate(const int left, const int right) { return std::abs(left - right) < Epsilon; }
    static bool IsEqualApproximate(const float left, const float right) { return std::abs(left - right) < Epsilon; }
    static bool IsEqualApproximate(const double left, const double right) { return std::abs(left - right) < Epsilon; }

    static bool IsEqualApproximate(const Vector2f& left, const Vector2f& right);
    static bool IsEqualApproximate(const Vector3f& left, const Vector3f& right);
    static bool IsEqualApproximate(const Vector4f& left, const Vector4f& right);
};