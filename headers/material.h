#pragma once

#include "hittable.h"

class Material
{
public:
    virtual ~Material() = default;

    virtual bool Scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const
    {
        return false;
    }
};

class Lambertian : public Material
{
public:
    Lambertian(const color& albedo) : albedo(albedo) {}

    bool Scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override;
private:
    color albedo;
};

class Metal : public Material
{
public:
    Metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool Scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const override;
private:
    color albedo;
    double fuzz;
};
