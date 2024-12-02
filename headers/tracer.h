#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159126535897932385;

inline double DegreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double RandomDouble()
{
    return std::rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(double min, double max)
{
    return min + (max-min)*RandomDouble();
}

#include "interval.h"
#include "ray.h"
#include "vec3.h"
#include "color.h"
