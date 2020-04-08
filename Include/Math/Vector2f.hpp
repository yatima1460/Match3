#pragma once

#include <SDL.h>
#include <math.h>
#include "Functional.hpp"

namespace Vector2f
{

struct Vector2fData
{
    union {
        float x;
        float w;
    };

    union {
        float y;
        float h;
    };
};

CONST_FUNCTION inline float distance(const Vector2fData &A, const Vector2fData &B)
{
    return sqrtf(((B.x - A.x) * (B.x - A.x)) + ((B.y - A.y) * (B.y - A.y)));
}

CONST_FUNCTION inline void operator+=(Vector2fData &A, const Vector2fData &B)
{
    A.x += B.x;
    A.y += B.y;
}

CONST_FUNCTION inline void operator-=(Vector2fData &A, const Vector2fData &B)
{
    A.x -= B.x;
    A.y -= B.y;
}

CONST_FUNCTION inline Vector2fData operator-(Vector2fData &A, const Vector2fData &B)
{
    return {A.x - B.x, A.y - B.y};
}

CONST_FUNCTION inline bool operator==(const Vector2fData &A, const Vector2fData &B)
{
    return A.x == B.x && A.y == B.y;
}

CONST_FUNCTION inline bool operator!=(const Vector2fData &A, const Vector2fData &B)
{
    return A.x != B.x || A.y != B.y;
}

CONST_FUNCTION inline float magnitude(Vector2fData v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}

CONST_FUNCTION inline Vector2fData &operator*=(Vector2fData &A, const float B)
{
    A.x *= B;
    A.y *= B;
    return A;
}

CONST_FUNCTION inline Vector2fData normalize(Vector2fData v)
{

    float norm;

    norm = magnitude(v);

    if (norm == 0.0f)
    {
        return {0, 0};
    }

    v *= (1.0f / norm);

    return v;
}

CONST_FUNCTION inline Vector2fData &operator*=(Vector2fData &A, const int B)
{
    A.x *= B;
    A.y *= B;
    return A;
}

CONST_FUNCTION inline Vector2fData &operator+(Vector2fData &A, const Vector2fData &B)
{
    A.x += B.x;
    A.y += B.y;
    return A;
}

} // namespace Vector2f