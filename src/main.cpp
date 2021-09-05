
#include <vec3.h>
#include <color.h>
#include <ray.h>
#include <iostream>
int main()
{
    const int img_height = 256;
    const int img_width = 256;

    std::cout << "P3 \n" << img_width << " " << img_height << std::endl << "255 \n";
    color pixel_color;
    for(int j = img_height-1; j >= 0; j--){
        for(int i = 0; i < img_width; i++){
            pixel_color = color((double)j/img_height, (double)i/img_width, (double)0.1);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\n Done! \n";
    return 0;
}