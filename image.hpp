#pragma once 

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include "pixelData.hpp"

enum Image_Type {
    PBM,
    PGM,
    PPM,
    NO_IMG_TYPE
};

enum Content_Type {
    ASCII,
    BINARY,
    NO_CONT_TYPE
};

typedef struct Header {
    Image_Type img_type;
    Content_Type content_type;
    int comment_count;
    std::vector<std::string> comment_vec;
    int width, height;
    Color_Type color_type;
} Header;

class Image : Pixel_Data {
    public:
        Image();
        Image(std::string path, Image_Type i_type, Content_Type c_type, Color_Type col_type, int width, int height);
        ~Image();
        static Image open(std::string path);
        void save(const Image& image);
        void read_image(const Image& image);
        void print_header_string();
        void add_comment(std::string comment);
        void show_image_details();
        void show_image_details_verbose();
        void print_image_data();
        void fill_image(std::string input_string);

    private:
        Header image_header;
        Pixel_Data image_body;
        std::vector<char> m_pixeldata;
        std::vector<std::string> m_stringdata;
        std::string m_header_string;
        std::string m_body_string;
        std::string m_path;

        static bool find_header(Image& image, std::string line);
        static bool parse_header(Image& image, std::string line);
        static void parse_line(Image& image, std::string line);
        static void write_data(Image& image, std::string line);
        std::string image_type_string(Image_Type i_type);
        std::string content_type_string(Content_Type c_type);
        std::string image_type_identifier_string(Image_Type i_type, Content_Type c_type);

        void generate_header_string();
        void generate_body_string(int arr[], int width, int height, int color);

        std::vector<char> get_pixeldata();
        std::vector<std::string> get_stringdata();
        std::string get_path();
        std::string get_header_string();
        std::vector<std::string> get_comment_vec();
        int get_width();
        int get_height();
        int get_color();
        Image_Type get_image_type();
        std::string get_image_type_string();
        std::string get_image_type_identifier_string();
        Content_Type get_content_type();
        std::string get_content_type_string();
};