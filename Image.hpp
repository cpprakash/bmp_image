#ifndef __HEADER__IMAGE__
#define __HEADER__IMAGE__

#include <array>
#include <fstream>
#include <iostream>
#include <vector>

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
class BmpImage {
public:
  unsigned int IMG_WIDTH = 5;
  unsigned int IMG_HEIGHT = 5;
  const unsigned long pixel_size = 3UL;
  unsigned int local_offset = 0;
  unsigned char padding_byte = 0b0000;

private:
  unsigned int box_size;
  std::string image_file_name;
  unsigned int pixel_padding = 4 - ((IMG_WIDTH * 3) % 4);
  /**
   * Colors are defined in reverser order, so it is not RGB but BGR
   */

  std::vector<std::array<unsigned char, 3UL>> color_palette{
      {255, 255, 255}, // white
      {0, 0, 0},       // black
      {0, 0, 255},     // red
      {0, 255, 0},     // green
      {255, 0, 0}      // blue
  };

  /**
   * chess pattern TODO fix it later
   */
  std::vector<std::array<unsigned char, 3UL>> chess_color_palette{
      {255, 255, 255}, // white
      {0, 0, 0}        // black
  };

  std::vector<unsigned char> pixel_data;

  /**
   * BMP File header
   * 14 bytes long
   */
  struct BMP_FILE_HEADER {
    const unsigned char magic1 = 'B';
    const unsigned char magic2 = 'M';
    unsigned int bmp_file_size;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int starting_address;
  };
  /**
   * BMP File information header
   * 40 bytes long
   */
  struct WINDOWS_BITMAP_INFO_HEADER {
    const unsigned int header_size = 40;
    int32_t bitmap_width_in_pixel;
    int32_t bitmap_height_in_pixel;
    const unsigned short number_of_color_panes = 1;
    const unsigned short number_of_bits_per_pixel = 24;
    const unsigned int compression_method = 0;
    unsigned int image_size;
    int32_t horizontal_resolution_of_image;
    int32_t vertical_resolution_of_image;
    unsigned int number_of_colors_in_palette;
    unsigned int number_of_important_colors = 0;
  };

public:
  BmpImage();
  BmpImage(const std::string &file_name, const unsigned int img_height,
           const unsigned int img_width) noexcept;
  void start_reading_bmp_file(const std::string &file_name) noexcept;
  void create_empty_image(const std::string &file_name);
  void create_chess_pattern(const std::string &file_name,
                            const unsigned int &img_height,
                            const unsigned int &img_width,
                            const unsigned int &box_size) noexcept;

private:
  void read_bmp_file(void);
  void write_bmp_header(void);
  void write_dib_info_header(void);
  void write_color_data(void);
  void write_default_image_data(void) noexcept;
  unsigned int get_padding_for_row(void) noexcept;
  void write_single_pixel_color_data(void) noexcept;
  void write_chess_pattern_data(void) noexcept;
  unsigned int calculate_pixel_data_size(void) noexcept;
  void setup_initial_values(const std::string &file_name,
                            const unsigned int &img_height,
                            const unsigned int &img_width) noexcept;
};

#endif