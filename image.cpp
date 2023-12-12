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
    image.m_path = path;

    if(imagefile.is_open()) {
        int count = 0;
        int line_count = 0;
        while (getline(imagefile, line)){
            parse_line(image, line);
            write_data(image, line);
            line_count++;
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
    if (line.at(0) == '#') { return; }  //Skip comments
    std::smatch match;

    //Read out width and height
    if(std::regex_match(line, match, std::regex("(\\d+)\\s+(\\d+)"))) {
        image.m_width = std::stoi(match[1].str());
        image.m_height = std::stoi(match[2].str());
    }

    //Check for Image_Type
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

std::string Image::image_type_string(Image_Type i_type) {
    switch (i_type) {
        case Image_Type::PBM:
            return "Portable BitMap (.pbm)";
        case Image_Type::PGM:
            return "Portable GrayMap (.pgm)";
        case Image_Type::PPM:
            return "Portable PixMap (.ppm)";
        default:
            return "Unknown format";
    }
}

std::string Image::content_type_string(Content_Type c_type) {
    switch (c_type) {
        case Content_Type::ASCII:
            return "ASCII Format";
        case Content_Type::BINARY:
            return "Binary Format";
        default:
            return "Unknown Format";
    }
}

void Image::show_image_details() {
    std::cout << "+--Image Information----------------+" << '\n';
    std::cout << "+ -Path:\t" << get_path() << '\n';
    std::cout << "+ -Type:\t" << get_image_type_string() << '\n';
    std::cout << "+ -Content:\t" << get_content_type_string() << '\n'; 
    std::cout << "+ -Width:\t" << get_width() << '\n';
    std::cout << "+ -Height:\t" << get_height() << '\n';
    std::cout << "+-----------------------------------+" << '\n'; 
}

int Image::get_width(){
    return this->m_width;
}

int Image::get_height(){
    return this->m_height;
}

std::string Image::get_path() {
    return this->m_path;
}

std::vector<Pixel> Image::get_pixeldata() {
    return this->m_pixeldata;
}

std::vector<std::string> Image::get_stringdata() {
    return this->m_stringdata;
}

Image_Type Image::get_image_type() {
    return this->m_image_type;
}

Content_Type Image::get_content_type(){
    return this->m_content_type;
}

std::string Image::get_image_type_string() {
    return image_type_string(this->m_image_type);
}

std::string Image::get_content_type_string() {
    return content_type_string(this->m_content_type);
}