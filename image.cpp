#include "image.hpp"

Image::Image() {}

Image::Image(std::string path, Image_Type i_type, Content_Type c_type, int width, int height, int color) {
    this->m_path = path;
    this->image_header.img_type = i_type;
    this->image_header.content_type = c_type;
    this->image_header.width = width;
    this->image_header.height = height;
    this->image_header.color_bitrate = color;
    generate_header_string();
}

Image::~Image() {}

void Image::fill_image(std::string input_string){}

void Image::generate_body_string(int arr[], int width, int height, int color) {
    Image* image = this;
    std::string body;
}

void Image::generate_header_string() {
    Image* image = this;
    // if (image.get_content_type() == Content_Type::NONE) {
    //     std::cout << "No content type (ASCII/ Binary) defined." << '\n';
    //     return;
    // }
    if (image->image_header.width == 0) {
        std::cout << "Image width could not be found. Is it defined?" << '\n';
        return;
    }
    if (image->image_header.height == 0) {
        std::cout << "Image height could not be found. Is it defined?" << '\n';
        return;
    }
    if (image->m_path.empty()) {
        std::cout << "No path is defined." << '\n';
        return;
    }
    if (image->image_header.img_type == Image_Type::NO_IMG_TYPE) {
        std::cout << "No image format was defined." << '\n';
        return;
    }
    if (image->image_header.content_type == Content_Type::NO_CONT_TYPE) {
        std::cout << "No image format was defined." << '\n';
        return;
    }
    std::string header;
    //Add Image type identifier
    header.append(get_image_type_identifier_string() + '\n');
    //Add comments if exist
    if (get_comment_vec().size() != 0) {
        for (auto comment : get_comment_vec()) {
            header.append("# ");
            header.append(comment + '\n');
        }
    }
    //Add width and height identifier
    header.append(std::to_string(get_width()) + ' ');
    header.append(std::to_string(get_height()) + '\n');
    //Add color space
    header.append(std::to_string(get_color()) + '\n');

    image->m_header_string = header;
}

void Image::print_header_string() {
    std::cout << get_header_string();
}

Image Image::open(std::string path) {
    Image image;
    std::ifstream imagefile;
    std::string line;
    imagefile.open(path, std::ios::out);
    image.m_path = path;

    if(imagefile.is_open()) {
        int count = 0;
        int line_count = 0;
        bool header = false;
        while (getline(imagefile, line)){
            if (!header){
                if (find_header(image, line)) {
                    //Set header to true if start of header found
                    header = true;
                    continue;
                }
            }
            if (header) {
                header = parse_header(image, line);
            }
            parse_line(image, line);
            //write_data(image, line);
            line_count++;
        }
        imagefile.close();
    }
    else {
        std::cout << "Unable to open file: " << path << '\n';
    }
    return image;
}

bool Image::parse_header(Image& image, std::string line) {
    //Read out comments
    if (line.at(0) == '#') {
        image.image_header.comment_vec.push_back(line);
        image.image_header.comment_count++;
        return true;
    }
    //Read out width and height
    std::smatch match;
    if(std::regex_match(line, match, std::regex("(\\d+)\\s+(\\d+)"))) {
        image.image_header.width = std::stoi(match[1].str());
        image.image_header.height = std::stoi(match[2].str());
        return true;
    }
    //Read out color-spac
    if (image.get_image_type() == Image_Type::PPM || image.get_image_type() == Image_Type::PGM) {
        int color_range = std::stoi(line);
        Color_Type color_type = parse_color_type(color_range);
        image.image_header.color_type = color_type;
        image.image_header.color_range = color_range;
    } else {
        int color_range = std::stoi(line);
        image.image_header.color_type = Color_Type::MONO;
        image.image_header.color_range = color_range;
    }
    return false;
}

Color_Type Image::parse_color_type(int color_range) {
    if (color_range < 255) {
        return Color_Type::GRAY;
    }
    return Color_Type::RGB;
}

void Image::save(const Image& image) {}

void Image::write_data(Image& image, std::string line) {} // image.m_pixeldata.push_back(line);

bool Image::find_header(Image& image, std::string line) {
    //Check for Image_Type
    if(std::regex_match(line, std::regex("(P[1-6])"))) {
        if(line.size() == 2) {
            char img_type_token = line.at(1);
            switch (img_type_token) {
            case '1':
                image.image_header.img_type = Image_Type::PBM;
                image.image_header.content_type = Content_Type::ASCII;
                std::cout << "Opening PBM file" << '\n';
                return true;
            case '2':
                image.image_header.img_type = Image_Type::PGM;
                image.image_header.content_type = Content_Type::ASCII;
                std::cout << "Opening PGM file" << '\n';
                return true;
            case '3':
                image.image_header.img_type = Image_Type::PPM;
                image.image_header.content_type = Content_Type::ASCII;
                std::cout << "Opening PPM file" << '\n';
                return true;
            case '4':
                image.image_header.img_type = Image_Type::PBM;
                image.image_header.content_type = Content_Type::BINARY;
                std::cout << "Opening PBM file" << '\n';
                return true;
            case '5':
                image.image_header.img_type = Image_Type::PGM;
                image.image_header.content_type = Content_Type::BINARY;
                std::cout << "Opening PGM file" << '\n';
                return true;
                break;
            case '6':
                image.image_header.img_type = Image_Type::PPM;
                image.image_header.content_type = Content_Type::BINARY;
                std::cout << "Opening PPM file" << '\n';
                return true;
            default:
                break;
            }
        }
        return true;
    }
    return false;
}

void Image::parse_line(Image& image, std::string line) {
    //Parse body lines
    image.m_stringdata.push_back(line); 
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

void Image::add_comment(std::string comment) {
    this->image_header.comment_vec.push_back(comment);
    generate_header_string();
}

std::string Image::image_type_identifier_string(Image_Type i_type, Content_Type c_type) {
    if (c_type == Content_Type::ASCII) {
        switch (i_type) {
            case Image_Type::PBM:
                return "P1";
            case Image_Type::PGM:
                return "P2";
            case Image_Type::PPM:
                return "P3";
            case Image_Type::NO_IMG_TYPE:
                std::cout << "No image type selected" << '\n';
                return "";
        }
    }
    if (c_type == Content_Type::BINARY) {
        switch (i_type) {
            case Image_Type::PBM:
                return "P4";
            case Image_Type::PGM:
                return "P5";
            case Image_Type::PPM:
                return "P6";
            case Image_Type::NO_IMG_TYPE:
                std::cout << "No image type selected" << '\n';
                return "";
        }
    }
    return "";  
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
    std::cout << "+ -Color:\t" << get_color() << '\n';
    std::cout << "+-----------------------------------+" << '\n'; 
}

void Image::show_image_details_verbose() {
    std::cout << "+--Image Information----------------+" << '\n';
    std::cout << "+ -Path:\t" << get_path() << '\n';
    std::cout << "+ -Type:\t" << get_image_type_string() << '\n';
    std::cout << "+ -Content:\t" << get_content_type_string() << '\n'; 
    std::cout << "+ -Width:\t" << get_width() << '\n';
    std::cout << "+ -Height:\t" << get_height() << '\n';
    std::cout << "+ -Color:\t" << get_color() << '\n';
    std::cout << "+ -Comments:\n";
    for (auto comment : get_comment_vec()) {
        std::cout << "+ " << comment << '\n';
    }
    std::cout << "+-----------------------------------+" << '\n'; 
}

void Image::print_image_data() {
    if (get_content_type() == Content_Type::BINARY) {
        std::cout << "Cannot print Binary data as string" << '\n';
    } 
    else {
        for (auto str : get_stringdata()) {
            std::cout << str << '\n';
        }
    }
}

Color_Type Image::get_color() {
    return this->image_body;
}

int Image::get_width(){
    return this->image_header.width;
}

int Image::get_height(){
    return this->image_header.height;
}

std::vector<std::string> Image::get_comment_vec() {
    return this->image_header.comment_vec;
}

std::string Image::get_path() {
    return this->m_path;
}

std::vector<char> Image::get_pixeldata() {
    return this->m_pixeldata;
}

std::vector<std::string> Image::get_stringdata() {
    return this->m_stringdata;
}

Image_Type Image::get_image_type() {
    return this->image_header.img_type;
}

Content_Type Image::get_content_type(){
    return this->image_header.content_type;
}

std::string Image::get_image_type_string() {
    return image_type_string(this->image_header.img_type);
}

std::string Image::get_image_type_identifier_string() {
        return image_type_identifier_string(this->image_header.img_type, this->image_header.content_type);
}

std::string Image::get_content_type_string() {
    return content_type_string(this->image_header.content_type);
}

std::string Image::get_header_string() {
    return this->m_header_string;
}