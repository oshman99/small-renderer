#include <iostream>

int main()
{
    const int img_height = 256;
    const int img_width = 256;

    std::cout << "P3 \n" << img_width << " " << img_height << std::endl << "255 \n";

    for(int j = img_height-1; j >= 0; j--){
        for(int i = 0; i < img_width; i++){
            auto r = (double)j/img_height;
            auto g = (double)i/img_width;
            auto b = (double)0.1;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << " " << ig << " " << ib << std::endl;
        }
    }

    std::cerr << "\n Done! \n";
    return 0;
}