#include "image.hpp"
#include <string>

enum INPUT_ARG {
    VERBOSE, NO_ARGUMENT
};

INPUT_ARG parse_input_args(std::string arg);

int main(int argc, char** argv) {
    Image image("sample_image.ppm", Image_Type::PPM, Content_Type::ASCII, 20, 20, 255);
    image.add_comment("This is a sample comment.");
    image.add_comment("This is another sample comment.");
    image.print_header_string();

    int img[18] = { 255, 0  , 0,
                    0  , 255, 0,
                    0  , 0  , 255,
                    255, 255, 0,
                    255, 255, 255,
                    0  , 0  , 0     };
    int width = 3;
    int height = 2;

    Image new_image("gen_image.ppm", Image_Type::PPM, Content_Type::ASCII, 3, 2, 255);

    


    // if (argc < 2) {
    //     std::cout << "No input arguments detected" << '\n';
    // } else {
    //     INPUT_ARG input_arg = INPUT_ARG::NO_ARGUMENT;
    //     if (argc >= 3 ) {
    //         input_arg = parse_input_args(std::string(argv[2]));
    //     }
    //     Image image = Image::open(argv[1]);
    //     std::cout << "*-------------------------*" << '\n';
    //     switch (input_arg) {
    //     case INPUT_ARG::VERBOSE:
    //         { image.show_image_details_verbose(); }
    //         break;
    //     case INPUT_ARG::NO_ARGUMENT:
    //         { image.show_image_details(); }
    //         break;
    //     default:
    //         break;
    //     }
    //     std::cout << "*-------------------------*" << '\n';
    // }
    return 0;
}

INPUT_ARG parse_input_args(std::string arg) {
    if (arg == "-v") {
        return INPUT_ARG::VERBOSE;
    }
    return NO_ARGUMENT;
}