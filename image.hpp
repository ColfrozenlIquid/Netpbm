#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <regex>

typedef struct Pixel {
    int red;
    int green;
    int blue;
    int pos_x;
    int pos_y;
} Pixel;

enum Image_Type {
    PBM, PGM, PPM
};

enum Content_Type {
    ASCII, BINARY
};

class Image {
    public:
        Image();
        Image(std::string path, Image_Type type, int width, int height);
        ~Image();
        static Image open(std::string path);
        void save(const Image& image);

    private:
        std::vector<Pixel> m_pixeldata;
        std::string m_path;
        int m_width;
        int m_height;
        Image_Type m_image_type;
        Content_Type m_content_type;

        static void parse_line(Image& image, std::string line);
};