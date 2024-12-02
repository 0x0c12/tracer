#pragma once

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable
{
public:
    Sphere(const point3& center, double radius, shared_ptr<Material> mat) : center(center), radius(std::fmax(0, radius)), mat(mat) {}

    bool hit(const ray& r, Interval ray_t, HitRecord& rec) const override;

private:
    point3 center;
    double radius;
    shared_ptr<Material> mat;
};
