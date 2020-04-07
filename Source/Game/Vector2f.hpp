#pragma once

#include <SDL.h>
#include <math.h>

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

inline float distance(const Vector2fData &A, const Vector2fData &B)
{
    return sqrtf(((B.x - A.x) * (B.x - A.x)) + ((B.y - A.y)*(B.y - A.y)));
}

inline void operator+=(Vector2fData &A, const Vector2fData &B)
{
    A.x += B.x;
    A.y += B.y;
}


inline void operator-=(Vector2fData &A, const Vector2fData &B)
{
    A.x -= B.x;
    A.y -= B.y;
}



inline Vector2fData operator-(Vector2fData &A, const Vector2fData &B)
{
    return {A.x - B.x, A.y - B.y};
}

inline bool operator==(const Vector2fData &A, const Vector2fData &B)
{
    return A.x == B.x && A.y == B.y;
}

inline bool operator!=(const Vector2fData &A, const Vector2fData &B)
{
    return A.x != B.x || A.y != B.y;
}


inline float magnitude(Vector2fData v)
{
    return sqrtf(v.x*v.x+v.y*v.y);
}


inline Vector2fData &operator*=(Vector2fData &A, const float B)
{
    A.x *= B;
    A.y *= B;
    return A;
}

inline Vector2fData normalize(Vector2fData v)
{
  
    float norm;

    norm = magnitude(v);

    if (norm == 0.0f)
    {
        return {0,0};
    }

    v *= (1.0f / norm);

    return v;
}




inline Vector2fData &operator*=(Vector2fData &A, const int B)
{
    A.x *= B;
    A.y *= B;
    return A;
}

inline Vector2fData &operator+(Vector2fData &A, const Vector2fData &B)
{
    A.x += B.x;
    A.y += B.y;
    return A;
}



}