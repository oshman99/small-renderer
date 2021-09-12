
#include <common_stuff.h>

#include <color.h>
#include <sphere.h>
#include <hittable_list.h>

color ray_color(const ray& r, HittableList world){
    hit_record rec;
    if(world.hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0 - t)*color(1.0, 1.0, 1.0) + t*(color(0.5, 0.7, 1.0));

}

int main()
{
    //Image data
    const auto aspect_ratio = 16.0/9.0;
    const int img_width = 400;
    const int img_height = static_cast<int>(img_width * aspect_ratio);

    //World obj
    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    //Camera
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * aspect_ratio;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    //Render
    std::cout << "P3 \n" << img_width << " " << img_height << std::endl << "255 \n";
    color pixel_color;
    for(int j = img_height-1; j >= 0; j--){
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < img_width; i++){
            auto u = double(i)/(img_width-1);
            auto v = double(j)/(img_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\n Done! \n";
    return 0;
}