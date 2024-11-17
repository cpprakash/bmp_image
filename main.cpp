#include <iostream>

struct BMP_FILE_HEADER {
  unsigned char magic1 = 'B';
  unsigned char magic2 = 'M';
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

void write_bmp_file(void);
void write_bmp_header(void);
void write_infor_header(void);
void write_color_data(void);

int main(void) { return 0; }