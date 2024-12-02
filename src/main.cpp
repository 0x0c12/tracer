#include "tracer.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"


int main()
{
   HittableList world;

   auto material_ground = make_shared<Metal>(color(0.8, 0.8, 0.0), 0.82);
   auto material_center = make_shared<Lambertian>(color(0.1, 0.25, 0.57));
   auto material_left = make_shared<Metal>(color(0.8, 0.8, 0.8), 0.67);
   auto material_right = make_shared<Metal>(color(0.8, 0.6, 0.2), 0.28);

   world.add(make_shared<Sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
   world.add(make_shared<Sphere>(point3(0.0 ,0.0 , -1.2), 0.5, material_center));
   world.add(make_shared<Sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
   world.add(make_shared<Sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

   Camera cam;

   cam.aspect_ratio = 16.0 / 9.0;
   // UHD
   cam.image_width = 1440;
   cam.samples_per_pixel = 280;
   // TESTING
   // cam.image_width = 800;
   // cam.samples_per_pixel = 10;
   cam.max_depth = 50;

   cam.Render(world);
}
