#pragma once

#include <string>
#include <vector>

enum Color_Type {
    MONO,
    GRAY,
    RGB,
    NO_COLOR
};

class Pixel_Data {
    public:
        Pixel_Data();
        Pixel_Data(std::vector<int> pixels, Color_Type col_type, int width, int height);
        ~Pixel_Data();
    protected:
        Color_Type get_color_type();
    private:
        std::vector<int> m_pixels;
        Color_Type m_color_type;
        int m_width;
        int m_height;
};