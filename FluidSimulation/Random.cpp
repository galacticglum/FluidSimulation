#include "Random.h"

std::mt19937 Random::m_RandomEngine;
int Random::Range(const int min, const int max)
{
    const std::uniform_int_distribution<int> distribution(min, max);
    return distribution(m_RandomEngine);
}

long Random::Range(const long min, const long max)
{
    const std::uniform_int_distribution<long> distribution(min, max);
    return distribution(m_RandomEngine);
}

float Random::Range(const float min, const float max)
{
    const std::uniform_real_distribution<float> distribution(min, max);
    return distribution(m_RandomEngine);
}

double Random::Range(const double min, const double max)
{
    const std::uniform_real_distribution<double> distribution(min, max);
    return distribution(m_RandomEngine);
}

Vector2f Random::Vector2(const Vector2f& min, const Vector2f& max)
{
    const std::uniform_real_distribution<float> distrubutionX(min.X, max.X);
    const std::uniform_real_distribution<float> distrubutionY(min.Y, max.Y);

    return { distrubutionX(m_RandomEngine), distrubutionY(m_RandomEngine) };
}

Vector3f Random::Vector3(const Vector3f& min, const Vector3f& max)
{
    const std::uniform_real_distribution<float> distrubutionX(min.X, max.X);
    const std::uniform_real_distribution<float> distrubutionY(min.Y, max.Y);
    const std::uniform_real_distribution<float> distrubutionZ(min.Z, max.Z);

    return { distrubutionX(m_RandomEngine), distrubutionY(m_RandomEngine), distrubutionZ(m_RandomEngine) };
}

Vector4f Random::Vector4(const Vector4f& min, const Vector4f& max)
{
    const std::uniform_real_distribution<float> distrubutionX(min.X, max.X);
    const std::uniform_real_distribution<float> distrubutionY(min.Y, max.Y);
    const std::uniform_real_distribution<float> distrubutionZ(min.Z, max.Z);
    const std::uniform_real_distribution<float> distrubutionW(min.W, max.W);

    return { distrubutionX(m_RandomEngine), distrubutionY(m_RandomEngine), distrubutionZ(m_RandomEngine), distrubutionW(m_RandomEngine) };
}

Vector4f Random::RGB(const float alpha)
{
    return { Value(), Value(), Value(), alpha };
}

Vector4f Random::RGBA()
{
    return { Value() , Value(), Value(), Value() };
}