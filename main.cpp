#include <fstream>
#include <iostream>

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
  const uint16_t number_of_bits_per_pixel = 4;
  const uint32_t compression_method;
  uint32_t image_size;
  uint32_t horizontal_resolution_of_image;
  uint32_t vertical_resolution_of_image;
  uint32_t number_of_colors_in_palette;
  uint32_t number_of_important_colors = 0;
};

// void write_bmp_file(void);
void write_bmp_header(void);
void write_info_header(void);
void write_color_data(void);

int main(void) {
  write_bmp_header();
  write_info_header();
  write_color_data();
  return 0;
}

void write_bmp_header(void) {
  std::cout << "Writing bmp header to the file" << std::endl;

  BMP_FILE_HEADER bmp_file_header;
  bmp_file_header.bmp_file_size = 70; // total file size
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
        sizeof(bmp_file_header
                   .bmp_file_size)); // total file size, bmp header 14 bytes,
                                     // dib header 40 bytes and 16 bytes data
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

void write_info_header(void) {
  std::cout << "Writing info header to the file" << std::endl;
  std::ofstream bmp_file;
  bmp_file.open("demo.bmp", std::ios::app | std::ios::binary);
  if (!bmp_file.is_open()) {
    std::cout << "File could not be opened" << std::endl;
  } else {
    std::cout << "File is opened" << std::endl;
  }
}

void write_color_data(void) {
  std::cout << "Writing color data to the file" << std::endl;
  std::ofstream bmp_file;
  bmp_file.open("demo.bmp", std::ios::app | std::ios::binary);
  if (!bmp_file.is_open()) {
    std::cout << "File could not be opened" << std::endl;
  } else {
    std::cout << "File is opened" << std::endl;
  }
}