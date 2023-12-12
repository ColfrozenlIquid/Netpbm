#include "image.hpp"

int main() {
    std::cout << "*-------------------------*" << '\n';
    Image image1 = Image::open("image.ppm");
    Image image2 = Image::open("image.pbm");
    std::cout << "*-------------------------*" << '\n';
    return 0;
}