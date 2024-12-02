#pragma once

#include "tracer.h"

class Material;

class HitRecord
{
public:
    point3 p;
    vec3 normal;
    shared_ptr<Material> mat;
    double t;
    bool front_face;

    void SetFaceNormal(const ray& r, const vec3& outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
public:
    virtual ~Hittable() = default;

    virtual bool hit(const ray& r, Interval ray_t, HitRecord& rec) const = 0;
};
