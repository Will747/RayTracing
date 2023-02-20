#pragma once

constexpr double PI = 3.14159265359;

inline double DegreesToRadians(const double degrees)
{
    return degrees * (PI / 180);
}
