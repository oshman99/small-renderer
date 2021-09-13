
#include "common_stuff.h"

#include "color.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"

color ray_color(const ray& r, HittableList world, int depth){
    hit_record rec;
    if(depth <= 0)
        return color(0.1,0.1,0.1);
    
    if(world.hit(r, 0.001, infinity, rec))
    {
        //point3 target = rec.p + rec.normal + random_unit_vector();
        point3 target = rec.p + rec.normal + random_in_hemisphere(rec.normal);
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth - 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t)*color(1.0, 1.0, 1.0) + t*(color(0.5, 0.7, 1.0));

}

int main()
{
    //Image data
    const auto aspect_ratio = 16.0/9.0;
    const int img_width = 500;
    const int img_height = static_cast<int>(img_width / aspect_ratio);
    const int sampels_per_pixel = 25;
    const int max_depth = 50;
    //World obj
    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    //Camera
    Camera cam;

    //Render
    std::cout << "P3 \n" << img_width << " " << img_height << std::endl << "255 \n";
    
    for(int j = img_height-1; j >= 0; j--){
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < img_width; i++){
            color pixel_color(0, 0, 0);
            for(int s = 0; s < sampels_per_pixel; s++)
            {
                auto u = (i + random_double())/(img_width-1);
                auto v = (j + random_double())/(img_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, sampels_per_pixel);
        }
    }

    std::cerr << "\n Done! \n";
    return 0;
}