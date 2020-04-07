#pragma once

#include <SDL.h>

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
};

inline void operator+=(Vector2i &A, const Vector2i &B)
{
    A.x += B.x;
    A.y += B.y;
}


inline bool operator==(const Vector2i &A, const Vector2i &B)
{
    return A.x == B.x && A.y == B.y;
}

inline bool operator!=(const Vector2i &A, const Vector2i &B)
{
    return A.x != B.x || A.y != B.y;
}

inline Vector2i &operator+(Vector2i &A, const Vector2i &B)
{
    A.x += B.x;
    A.y += B.y;
    return A;
}

inline Vector2i &operator*(Vector2i &A, const int B)
{
    A.x *= B;
    A.y *= B;
    return A;
}