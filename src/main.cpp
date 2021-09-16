
#include "common_stuff.h"

#include "color.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"

color ray_color(const ray& r, HittableList world, int depth){
    hit_record rec;
    if(depth <= 0)
        return color(0.1,0.1,0.1);
    
    if(world.hit(r, 0.001, infinity, rec))
    {
        ray scattered;
        color attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);//colot bounces untill max depth is reached, attenuation = material's albedo
        return color(0, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);//-1~1 -> 0~1
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

    //Materials
    auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(color(0.7, 0.3, 0.3));
    auto material_left   = std::make_shared<Metal>(color(0.8, 0.8, 0.8));
    auto material_right  = std::make_shared<Metal>(color(0.8, 0.6, 0.2));

    //World obj
    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5, material_center));
    world.add(std::make_shared<Sphere>(point3(-1, 0, -1), 0.5, material_left));
    world.add(std::make_shared<Sphere>(point3(1, 0, -1), 0.5, material_right));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100, material_ground));

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