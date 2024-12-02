#include "material.h"

bool Lambertian::Scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const
{
    auto scatter_direction = rec.normal + random_unit_vector();

    if(scatter_direction.near_zero())
    {
        scatter_direction = rec.normal;
    }
    
    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

bool Metal::Scatter(const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered) const
{
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}
