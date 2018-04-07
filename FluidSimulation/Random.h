#pragma once
#include <string>
#include <random>

#include "Maths.h"
#include "Time.h"

class Random
{
public:
    static void Initialize() { Initialize(static_cast<int>(Time::GetTime() * 1000)); }
    static void Initialize(const unsigned int seed) { m_RandomEngine = std::mt19937(seed); }

    static int Range(int min, int max);
    static long Range(long min, long max);
    static float Range(float min, float max);
    static double Range(double min, double max);

    static float Value() { return Range(0.0f, 1.0f); }

    static Vector2f Vector2() { return Vector2(0, MathFunctions::MaxFloat); }
    static Vector2f Vector2(const float min, const float max) { return Vector2(Vector2f(min), Vector2f(max)); }
    static Vector2f Vector2(const float minX, const float maxX, 
        const float minY, const float maxY)
    {
        return Vector2(Vector2f(minX, minY), Vector2f(maxX, maxY));
    }

    static Vector2f Vector2(const Vector2f& min, const Vector2f& max);

    static Vector3f Vector3() { return Vector3(0, MathFunctions::MaxFloat); }
    static Vector3f Vector3(const float min, const float max) { return Vector3(Vector3f(min), Vector3f(max)); }
    static Vector3f Vector3(const float minX, const float maxX, const float minY, 
        const float maxY, const float minZ, const float maxZ)
    {
        return Vector3(Vector3f(minX, minY, minZ), Vector3f(maxX, maxY, maxZ));
    }

    static Vector3f Vector3(const Vector3f& min, const Vector3f& max);

    static Vector4f Vector4() { return Vector4(0, MathFunctions::MaxFloat); }
    static Vector4f Vector4(const float min, const float max) { return Vector4(Vector4f(min), Vector4f(max)); }

    static Vector4f Vector4(const float minX, const float maxX, const float minY, const float maxY, 
        const float minZ, const float maxZ, const float minW, const float maxW)
    {
        return Vector4(Vector4f(minX, minY, minZ, minW), Vector4f(maxX, maxY, maxZ, maxW));
    }

    static Vector4f Vector4(const Vector4f& min, const Vector4f& max);

    static Vector4f RGB(float alpha = 1);
    static Vector4f RGBA();
private:
    static std::mt19937 m_RandomEngine;
};
