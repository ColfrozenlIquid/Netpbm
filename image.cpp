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
            write_data(image, line);
        }
        imagefile.close();
    }
    else {
        std::cout << "Unable to open file: " << path << '\n';
    }

    return image;
}

void Image::save(const Image& image) {}

void Image::write_data(Image& image, std::string line) {
    image.m_stringdata.push_back(line);
}

void Image::parse_line(Image& image, std::string line) {
    if(std::regex_match(line, std::regex("(P[1-6])"))) {
        if(line.size() == 2) {
            char img_type_token = line.at(1);
            switch (img_type_token) {
            case '1':
                image.m_image_type = Image_Type::PBM;
                image.m_content_type = Content_Type::ASCII;
                std::cout << "Opening PBM file" << '\n';
                break;
            case '2':
                image.m_image_type = Image_Type::PGM;
                image.m_content_type = Content_Type::ASCII;
                std::cout << "Opening PGM file" << '\n';
                break;
            case '3':
                image.m_image_type = Image_Type::PPM;
                image.m_content_type = Content_Type::ASCII;
                std::cout << "Opening PPM file" << '\n';
                break;
            case '4':
                image.m_image_type = Image_Type::PBM;
                image.m_content_type = Content_Type::BINARY;
                std::cout << "Opening PBM file" << '\n';
                break;
            case '5':
                image.m_image_type = Image_Type::PGM;
                image.m_content_type = Content_Type::BINARY;
                std::cout << "Opening PGM file" << '\n';
                break;
            case '6':
                image.m_image_type = Image_Type::PPM;
                image.m_content_type = Content_Type::BINARY;
                std::cout << "Opening PPM file" << '\n';
                break;
            default:
                break;
            }
        }
    }
}