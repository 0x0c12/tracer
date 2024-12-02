#pragma once

#include "hittable.h"
#include "material.h"

class Camera
{
public:
    void Render(const Hittable& world);
public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;
private:
    int image_height;
    double pixel_samples_scale;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_change_u;
    vec3 pixel_change_v;
private:
    void Init();
    color RayColor(const ray& r, int max_depth, const Hittable& world) const;
    ray GetRay(int i, int j) const;
    vec3 SampleSquare() const;
};
