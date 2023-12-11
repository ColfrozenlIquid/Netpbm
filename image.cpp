#include "image.hpp"

Image::Image() {}

Image::Image(std::string path, Image_Type i_type, Content_Type c_type, int width, int height) 
    : m_path(path), m_image_type(i_type), m_content_type(c_type), m_width(width), m_height(height) {}

Image::~Image() {}

Image Image::open(std::string path) {
    Image image;
    std::ifstream imagefile;
    std::string line; 
    imagefile.open(path, std::ios::out);

    if(imagefile.is_open()) {
        int count = 0;
        int line_count = 0;
        while (getline(imagefile, line)){
            parse_line(image, line);
        }
        std::cout << "Pixel count is: " << (count - 4) / 3 << '\n';
        std::cout << "Line count is: " << line_count << '\n'; 
        imagefile.close();
    }
    else {
        std::cout << "Unable to open file: " << path << '\n';
    }

    return image;
}

void Image::save(const Image& image) {}

void Image::parse_line(Image& image, std::string line) {
    std::basic_regex<char> rgx = std::regex("[P{1,2,3,4,5,6}]");
    std::string str1 = "P6\n";
    std::cout << "String size is: " << str1.size() << '\n';
    if(std::regex_match(line, rgx)) {
        if(line.size() == 3) {
            char img_type_token = line.at(2);
            switch (img_type_token) {
            case '1':
                image.m_image_type = Image_Type::PBM;
                image.m_content_type = Content_Type::ASCII;
                break;
            case '2':
                image.m_image_type = Image_Type::PGM;
                image.m_content_type = Content_Type::ASCII;
                break;
            case '3':
                image.m_image_type = Image_Type::PPM;
                image.m_content_type = Content_Type::ASCII;
                break;
            case '4':
                image.m_image_type = Image_Type::PBM;
                image.m_content_type = Content_Type::BINARY;
                break;
            case '5':
                image.m_image_type = Image_Type::PGM;
                image.m_content_type = Content_Type::BINARY;
                break;
            case '6':
                image.m_image_type = Image_Type::PPM;
                image.m_content_type = Content_Type::BINARY;
                break;
            default:
                break;
            }
        }
    }
}
