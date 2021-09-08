
#include <vec3.h>
#include <color.h>
#include <ray.h>
#include <iostream>
#include <math.h>

double is_sphere_hit(const point3& center, const double& radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    //square equasin with a = dot(direction, direction) and b=2h
    auto a = r.direction().length_squared();
    auto half_b = dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;
    auto discr = half_b*half_b - a*c;
    if(discr < 0)
    {
        return -1;
    }
    else
    {
        return (-half_b - sqrt(discr)) / a;
    }
    
}

color ray_color(const ray& r){
    //sphere
    auto t = is_sphere_hit(point3(0, 0, -1), 0.5, r);
    if(t > 0)
    {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        //convert to 0-1 range
        return 0.5*color(N.x() + 1, N.y() + 1, N.z() + 1);
    } 
    //gradient background
    //scale to (-1.0 1.0)
    vec3 unit_direction = unit_vector(r.direction());
    //scale to (0.0 1.0)
    t = 0.5*(unit_direction.y() + 1);
    //lerp between white and blue
    return color((1-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.0, 0.0, 1.0));
}

int main()
{
    //Image data
    const auto aspect_ratio = 16.0/9.0;
    const int img_width = 400;
    const int img_height = static_cast<int>(img_width * aspect_ratio);

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
            pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\n Done! \n";
    return 0;
}