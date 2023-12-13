#include "pixelData.hpp"

Pixel_Data::Pixel_Data(std::vector<int> pixels, Color_Type col_type, int width, int height) {
    this->m_pixels = pixels;
    this->m_color_type = col_type;
    this->m_width = width;
    this->m_height = height;
}

Pixel_Data::Pixel_Data() {}

Pixel_Data::~Pixel_Data() {}

Color_Type Pixel_Data::get_color_type() {
    return this->m_color_type;
}