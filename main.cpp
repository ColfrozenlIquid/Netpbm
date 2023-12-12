#include "image.hpp"

int main() {
    std::cout << "*-------------------------*" << '\n';
    Image image1 = Image::open("image.ppm");
    Image image2 = Image::open("image.pbm");
    Image tux = Image::open("Tux(2).ppm");
    image1.show_image_details();
    image2.show_image_details();
    tux.show_image_details();
    std::cout << "*-------------------------*" << '\n';
    return 0;
}