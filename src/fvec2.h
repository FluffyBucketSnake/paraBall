#pragma once
#include <math.h>

class FVec2
{
    public:
        float x;
        float y;

        FVec2(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

        FVec2(float n)
        {
            this->x = n;
            this->y = n;
        }

        FVec2()
        {
            x = 0;
            y = 0;
        }

        float length()
        {
            return std::sqrt(x*x + y*y);
        }

        FVec2 operator+(const FVec2& b)
        {
            FVec2 result;
            result.x = x + b.x;
            result.y = y + b.y;
            return result;
        }

        FVec2 operator-(const FVec2& b)
        {
            FVec2 result;
            result.x = x - b.x;
            result.y = y - b.y;
            return result;
        }

        FVec2 operator*(const float& b)
        {
            FVec2 result;
            result.x = x * b;
            result.y = y * b;
            return result;
        }

        FVec2 operator/(const float& b)
        {
            FVec2 result;
            result.x = x / b;
            result.y = y / b;
            return result;
        }

        void operator+=(const FVec2& b)
        {
            x += b.x;
            y += b.y;
        }

        void operator-=(const FVec2& b)
        {
            x += b.x;
            y += b.y;
        }

        void operator*=(const float& b)
        {
            x *= b;
            y *= b;
        }

        void operator/=(const float& b)
        {
            x /= b;
            y /= b;
        }

        bool operator ==(const FVec2& b)
        {
            return (x == b.x) && (y == b.y);
        }

        bool operator !=(const FVec2& b)
        {
            return (x != b.x) || (y != b.y);
        }

        static float Dot(const FVec2& a, const FVec2& b)
        {
            return (a.x * b.x) + (a.y * b.y);
        }

        static float CrossLength(const FVec2& a, const FVec2& b)
        {
            return (a.x*b.y) - (a.y*b.x);
        }
};