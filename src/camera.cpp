#include "camera.h"

void Camera::Render(const Hittable& world)
{
    Init();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = 0; j < image_height; ++j)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for(int i = 0; i < image_width; ++i)
        {
            color pixel_color(0, 0, 0);
            for(int sample = 0; sample < samples_per_pixel; sample++)
            {
                ray r = GetRay(i, j);
                pixel_color += RayColor(r, max_depth, world);
            }
            
            write_color(std::cout, pixel_samples_scale * pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}

void Camera::Init()
{
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = point3(0, 0, 0);

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    pixel_change_u = viewport_u / image_width;
    pixel_change_v = viewport_v / image_height;

    auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_change_u + pixel_change_v);
}

color Camera::RayColor(const ray& r, int depth, const Hittable& world) const
{
    if(depth <= 0)
        return color(0,0,0);
    
    HitRecord rec;

    if(world.hit(r, Interval(0.001, infinity), rec))
    {
        ray scattered;
        color attenuation;
        if(rec.mat->Scatter(r, rec, attenuation, scattered))
            return attenuation * RayColor(scattered, depth-1, world);
        return color(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.784, 0.635, 0.784);
}

ray Camera::GetRay(int i, int j) const
{
    auto offset = SampleSquare();
    auto pixel_sample = pixel00_loc
                        + ((i + offset.x()) * pixel_change_u)
                        + ((j + offset.y()) * pixel_change_v);

    auto ray_origin = center;
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
}

vec3 Camera::SampleSquare() const
{
    return vec3(RandomDouble() - 0.5, RandomDouble() - 0.5, 0);   
}
