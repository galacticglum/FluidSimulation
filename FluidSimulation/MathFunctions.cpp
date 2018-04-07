#include "MathFunctions.h"
#include "Maths.h"

const float MathFunctions::Epsilon = std::numeric_limits<float>::epsilon();

const long MathFunctions::MaxLong = std::numeric_limits<long>::max();
const int MathFunctions::MaxInt = std::numeric_limits<int>::max();
const float MathFunctions::MaxFloat = std::numeric_limits<float>::max();
const double MathFunctions::MaxDouble = std::numeric_limits<double>::max();

long MathFunctions::NextPowerOfTwo(long n)
{
    if (n < 0)
    {
        // TODO: Logging system
        std::cerr << "FrostyMath::NextPowerOfTwo: long 'n' must be positive!\n";
        exit(1);
    }

    return static_cast<long>(std::pow(2, std::ceil(std::log2(static_cast<double>(n)))));
}

int MathFunctions::NextPowerOfTwo(int n)
{
    if (n < 0)
    {
        // TODO: Logging system
        std::cerr << "FrostyMath::NextPowerOfTwo: int 'n' must be positive!\n";
        exit(1);
    }

    return static_cast<int>(std::pow(2, std::ceil(std::log2(static_cast<double>(n)))));
}

float MathFunctions::NextPowerOfTwo(float n)
{
    if (n < 0)
    {
        // TODO: Logging system
        std::cerr << "FrostyMath::NextPowerOfTwo: float 'n' must be positive!\n";
        exit(1);
    }

    return static_cast<float>(std::pow(2, std::ceil(std::log2(static_cast<double>(n)))));
}

double MathFunctions::NextPowerOfTwo(double n)
{
    if (n < 0)
    {
        // TODO: Logging system
        std::cerr << "FrostyMath::NextPowerOfTwo: double 'n' must be positive!\n";
        exit(1);
    }

    return static_cast<double>(std::pow(2, std::ceil(std::log2(static_cast<double>(n)))));
}

long MathFunctions::Factorial(int n)
{
    long result = 1;

    for (; n > 1; n--)
    {
        result *= n;
    }

    return result;
}

long MathFunctions::BinomialCoefficient(int n, int k)
{
    return Factorial(n) / (Factorial(k) * Factorial(n - k));
}

float MathFunctions::InverseSqrtFast(float x)
{
    float halfX = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f375a86 - (i >> 1);
    x = *(float*)&i;
    x = x * (1.5f - halfX * x * x);
    return x;
}

float MathFunctions::DegreesToRadians(float degrees)
{
    const float degreeToRadian = static_cast<float>(PI / 180.0f);
    return degrees * degreeToRadian;
}

float MathFunctions::RadiansToDegrees(float radians)
{
    const float radianToDegree = 180.0f / static_cast<float>(PI);
    return radians * radianToDegree;
}

double MathFunctions::DegreesToRadians(double degrees)
{
    const double degreeToRadian = PI / 180.0;
    return degrees * degreeToRadian;
}

double MathFunctions::RadiansToDegree(double radians)
{
    const double radianToDegree = 180.0 / PI;
    return radians * radianToDegree;
}

void MathFunctions::Swap(double& a, double& b)
{
    double temp = a;
    a = b;
    b = temp;
}

void MathFunctions::Swap(float& a, float& b)
{
    float temp = a;
    a = b;
    b = temp;
}

bool MathFunctions::IsEqualApproximate(const Vector2f& left, const Vector2f& right)
{
    return IsEqualApproximate(left.X, right.X) &&
        IsEqualApproximate(left.Y, right.Y);
}

bool MathFunctions::IsEqualApproximate(const Vector3f& left, const Vector3f& right)
{
    return IsEqualApproximate(left.X, right.X) &&
        IsEqualApproximate(left.Y, right.Y) &&
        IsEqualApproximate(left.Z, right.Z);
}

bool MathFunctions::IsEqualApproximate(const Vector4f& left, const Vector4f& right)
{
    return IsEqualApproximate(left.X, right.X) &&
        IsEqualApproximate(left.Y, right.Y) &&
        IsEqualApproximate(left.Z, right.Z) &&
        IsEqualApproximate(left.W, right.W);
}