#include <fstream>
#include <iostream>

/**
 * image of size 5*5
 * colors =
 * [Red Green Blue White Black
 * Green Blue White Black Red
 * Blue White Black Red Green
 * White Black Red Green Blue
 * Black Red Green Blue White]
 *
 */
uint32_t IMG_WIDTH = 5;
uint32_t IMG_HEIGHT = 5;

uint32_t pixel_padding = 4 - ((IMG_WIDTH * 3) % 4);

struct BMP_FILE_HEADER {
  const unsigned char magic1 = 'B';
  const unsigned char magic2 = 'M';
  uint32_t bmp_file_size;
  uint16_t reserved1;
  uint16_t reserved2;
  uint32_t starting_address;
};

struct WINDOWS_BITMAP_INFO_HEADER {
  const uint32_t header_size = 40;
  uint32_t bitmap_width_in_pixel;
  uint32_t bitmap_height_in_pixel;
  const uint16_t number_of_color_panes = 1;
  const uint16_t number_of_bits_per_pixel = 24;
  const uint32_t compression_method = 0;
  uint32_t image_size;
  uint32_t horizontal_resolution_of_image;
  uint32_t vertical_resolution_of_image;
  uint32_t number_of_colors_in_palette;
  uint32_t number_of_important_colors = 0;
};

// void write_bmp_file(void);
void write_bmp_header(void);
void write_dib_info_header(void);
void write_color_data(void);

int main(void) {
  if (pixel_padding == 4)
    pixel_padding = 0;
  std::cout << "Padding = " << pixel_padding << std::endl;
  write_bmp_header();
  write_dib_info_header();
  write_color_data();
  return 0;
}
/***
 * Write the bmp header
 * a bmp header is 14 bytes long
 */
void write_bmp_header(void) {
  std::cout << "Writing bmp header to the file" << std::endl;
  std::cout << "SIze = " << 54 + (IMG_WIDTH * 3 + pixel_padding) * IMG_HEIGHT
            << std::endl;
  BMP_FILE_HEADER bmp_file_header;
  bmp_file_header.bmp_file_size =
      14 + 40 + (IMG_WIDTH * 3 + pixel_padding) * IMG_HEIGHT;
  // 54; // total file size
  bmp_file_header.reserved1 = 0;
  bmp_file_header.reserved2 = 0;
  bmp_file_header.starting_address = 54;

  std::ofstream bmp_file;
  bmp_file.open("demo.bmp", std::ios::binary | std::ios::out);
  if (!bmp_file.is_open()) {
    std::cout << "File could not be opened" << std::endl;
  } else {
    std::cout << "File is opened" << std::endl;
    bmp_file.write((char *)&bmp_file_header.magic1,
                   sizeof(bmp_file_header.magic1)); // B
    bmp_file.write((char *)&bmp_file_header.magic2,
                   sizeof(bmp_file_header.magic2)); // M
    bmp_file.write(
        (char *)&bmp_file_header.bmp_file_size,
        sizeof(bmp_file_header.bmp_file_size)); // total file size, bmp header
                                                // 14 bytes, dib header 40 bytes
    bmp_file.write((char *)&bmp_file_header.reserved1,
                   sizeof(bmp_file_header.reserved1)); // reserverd, should be 0
    bmp_file.write((char *)&bmp_file_header.reserved2,
                   sizeof(bmp_file_header.reserved2)); // reserved, should be 0
    bmp_file.write(
        (char *)&bmp_file_header.starting_address,
        sizeof(bmp_file_header.starting_address)); // starting address of the
                                                   // bmp color data
  }
  bmp_file.close();
}

/***
 * the dib info header
 * the size of this header is 40 bytes
 */
void write_dib_info_header(void) {
  std::cout << "Writing dib info header to the file" << std::endl;
  std::ofstream bmp_file;
  bmp_file.open("demo.bmp", std::ios::app | std::ios::binary);
  WINDOWS_BITMAP_INFO_HEADER dib_info_header;
  if (!bmp_file.is_open()) {
    std::cout << "File could not be opened" << std::endl;
    return;
  } else {
    /*
const uint32_t header_size = 40;
  uint32_t bitmap_width_in_pixel;
  uint32_t bitmap_height_in_pixel;
  const uint16_t number_of_color_panes = 1;
  const uint16_t number_of_bits_per_pixel = 4;
  const uint32_t compression_method;
  uint32_t image_size;
  uint32_t horizontal_resolution_of_image;
  uint32_t vertical_resolution_of_image;
  uint32_t number_of_colors_in_palette;
  uint32_t number_of_important_colors = 0;*/

    dib_info_header.bitmap_height_in_pixel = IMG_HEIGHT;
    dib_info_header.bitmap_width_in_pixel = IMG_WIDTH;
    dib_info_header.image_size = (IMG_WIDTH + pixel_padding) * IMG_HEIGHT;
    dib_info_header.horizontal_resolution_of_image = 2835;
    dib_info_header.vertical_resolution_of_image = 2835;
    dib_info_header.number_of_colors_in_palette = 0;
    dib_info_header.number_of_important_colors = 0;
    std::cout << "File is opened, will write the dib info header." << std::endl;

    bmp_file.write((char *)&dib_info_header.header_size,
                   sizeof(dib_info_header.header_size));
    bmp_file.write((char *)&dib_info_header.bitmap_width_in_pixel,
                   sizeof(dib_info_header.bitmap_width_in_pixel));
    bmp_file.write((char *)&dib_info_header.bitmap_height_in_pixel,
                   sizeof(dib_info_header.bitmap_height_in_pixel));
    bmp_file.write((char *)&dib_info_header.number_of_color_panes,
                   sizeof(dib_info_header.number_of_color_panes));
    bmp_file.write((char *)&dib_info_header.number_of_bits_per_pixel,
                   sizeof(dib_info_header.number_of_bits_per_pixel));
    bmp_file.write((char *)&dib_info_header.compression_method,
                   sizeof(dib_info_header.compression_method));
    bmp_file.write((char *)&dib_info_header.image_size,
                   sizeof(dib_info_header.image_size));
    bmp_file.write((char *)&dib_info_header.horizontal_resolution_of_image,
                   sizeof(dib_info_header.horizontal_resolution_of_image));
    bmp_file.write((char *)&dib_info_header.vertical_resolution_of_image,
                   sizeof(dib_info_header.vertical_resolution_of_image));
    bmp_file.write((char *)&dib_info_header.number_of_colors_in_palette,
                   sizeof(dib_info_header.number_of_colors_in_palette));
    bmp_file.write((char *)&dib_info_header.number_of_important_colors,
                   sizeof(dib_info_header.number_of_important_colors));

    bmp_file.close();
  }
}

void write_color_data(void) {
  std::cout << "Writing color data to the file" << std::endl;
  std::ofstream bmp_file;
  bmp_file.open("demo.bmp", std::ios::app | std::ios::binary);
  if (!bmp_file.is_open()) {
    std::cout << "File could not be opened" << std::endl;
    return;
  } else {
    std::cout << "File is opened, will write the color info." << std::endl;
  }
}