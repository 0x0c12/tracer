#pragma once

#include "tracer.h"
#include "hittable.h"

#include <vector>

class HittableList : public Hittable
{
public:
    std::vector<shared_ptr<Hittable>> objects;

    HittableList() {}
    HittableList(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<Hittable> object)
    {
        objects.push_back(object);
    }

    bool hit(const ray& r, Interval ray_t, HitRecord& rec) const override;
};
