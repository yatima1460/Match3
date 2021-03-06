#pragma once

#include <SDL.h>
#include "Vector2f.hpp"
#include "Functional.hpp"

struct Vector2i
{
    union {
        int x;
        int w;
    };

    union {
        int y;
        int h;
    };

    inline operator Vector2f::Vector2fData() const
    {
        return {(float)x, (float)y};
    }
};

CONST_FUNCTION inline void operator+=(Vector2i &A, const Vector2i &B)
{
    A.x += B.x;
    A.y += B.y;
}

CONST_FUNCTION inline bool operator==(const Vector2i &A, const Vector2i &B)
{
    return A.x == B.x && A.y == B.y;
}

CONST_FUNCTION inline bool operator!=(const Vector2i &A, const Vector2i &B)
{
    return A.x != B.x || A.y != B.y;
}

CONST_FUNCTION inline Vector2i operator-(const Vector2i &A, const Vector2i &B)
{
    Vector2i d;
    d.x = A.x - B.x;
    d.y = A.y - B.y;
    return d;
}

CONST_FUNCTION inline Vector2i operator+(const Vector2i &A, const Vector2i &B)
{
    Vector2i n = A;
    n.x += B.x;
    n.y += B.y;
    return n;
}

CONST_FUNCTION inline Vector2i operator*(const Vector2i &A, const int B)
{
    Vector2i n = A;
    n.x *= B;
    n.y *= B;
    return n;
}