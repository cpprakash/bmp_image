#include "Image.hpp"

BmpImage::BmpImage() {}

BmpImage::BmpImage(const std::string &file_name, const uint32_t img_height,
                   const uint32_t img_widht) noexcept {
  this->IMG_WIDTH = img_widht;
  this->IMG_HEIGHT = img_height;
  this->pixel_padding = this->get_padding_for_row();
  this->write_default_image_data();
}

void BmpImage::start_reading_bmp_file(void) {
  if (this->pixel_padding == 4)
    this->pixel_padding = 0;
  read_bmp_file();
}

/**
 * Creates an empty image with default values
 * only one pixel by one pixel image
 * with default white color
 */
void BmpImage::create_empty_image(const std::string &file_name) {
  this->image_file_name = file_name;
  this->IMG_HEIGHT = 1;
  this->IMG_WIDTH = 1;

  this->write_bmp_header();
  this->write_dib_info_header();
  this->write_default_image_data();
  this->write_color_data();
}

void BmpImage::read_bmp_file(void) {
  std::ifstream bmp_file_input;
  bmp_file_input.open("demo.bmp", std::ios::binary | std::ios::in);
  // file could not be opened or file doesnt exists
  if (!bmp_file_input) {
    std::cout << "Could not open the file." << std::endl;
    return;
  }
  // create a variable to hold bmp file data
  unsigned char bmp_temp[14];
  // std::cout << sizeof(unsigned short);
  bmp_file_input.read(reinterpret_cast<char *>(bmp_temp), sizeof(bmp_temp));
  // check the magic number to make sure it is BMP file
  if (bmp_temp[0] != 'B' && bmp_temp[1] != 'M') {
    std::cout << "Not a BMP file. Will Exit." << std::endl;
    return;
  }
  uint32_t file_size = *(reinterpret_cast<int *>(bmp_temp + 2));
  uint32_t starting_offset = *(reinterpret_cast<int *>(bmp_temp + 10));
  // print BMP file header
  std::cout << "Magic Number =" << bmp_temp[0] << "" << bmp_temp[1]
            << std::endl;
  std::cout << "File size =" << file_size << " bytes." << std::endl;
  std::cout << "File offset to pixel array =" << (starting_offset) << " bytes."
            << std::endl;
  bmp_file_input.close();

  std::ifstream complete_bmp_file;
  complete_bmp_file.open("demo.bmp", std::ios::binary | std::ios::in);
  if (!complete_bmp_file)
    return; // TODO handle with grace here later
  unsigned char bmp_file_array[file_size];
  complete_bmp_file.read(reinterpret_cast<char *>(bmp_file_array),
                         sizeof(bmp_file_array));
  complete_bmp_file.close();

  /// Windows BITMAPINFOHEADER information
  std::cout << "Size of this header ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 14))
            << std::endl;
  std::cout << "Image width ="
            << *(reinterpret_cast<int32_t *>(bmp_file_array + 18)) << std::endl;
  std::cout << "Image height ="
            << *(reinterpret_cast<int32_t *>(bmp_file_array + 22)) << std::endl;
  std::cout << "Num of Color planes ="
            << *(reinterpret_cast<uint16_t *>(bmp_file_array + 26))
            << std::endl;
  std::cout << "Num of bits per pixel ="
            << *(reinterpret_cast<uint16_t *>(bmp_file_array + 28))
            << std::endl;
  std::cout << "Compression method ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 30))
            << std::endl;
  std::cout << "Image size ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 34))
            << std::endl;
  std::cout << "Horizntal Resolution ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 38))
            << std::endl;
  std::cout << "Vertical Resolution ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 42))
            << std::endl;
  std::cout << "Num of colors in color palette ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 46))
            << std::endl;
  std::cout << "Num of imp colors used ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 50))
            << std::endl;
}
/***
 * Write the bmp header
 * a bmp header is 14 bytes long
 */
void BmpImage::write_bmp_header(void) {
  std::cout << "Writing bmp header to the file" << std::endl;
  BMP_FILE_HEADER bmp_file_header;
  bmp_file_header.bmp_file_size =
      14 + 40 + (IMG_WIDTH * 3 + pixel_padding) * IMG_HEIGHT;
  // 54; // total file size
  bmp_file_header.reserved1 = 0;
  bmp_file_header.reserved2 = 0;
  bmp_file_header.starting_address = 54;

  std::ofstream bmp_file;
  bmp_file.open(this->image_file_name, std::ios::binary | std::ios::out);
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
void BmpImage::write_dib_info_header(void) {
  std::cout << "Writing dib info header to the file" << std::endl;
  std::ofstream bmp_file;
  bmp_file.open("demo.bmp", std::ios::app | std::ios::binary);
  WINDOWS_BITMAP_INFO_HEADER dib_info_header;
  if (!bmp_file.is_open()) {
    std::cout << "File could not be opened" << std::endl;
    return;
  } else {
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

void write_single_pixel_color_data(
    const std::ofstream &file, const std::string &file_name,
    const std::vector<std::array<unsigned char, 3UL>> &color_palette,
    const int color) {
  std::ofstream bmp_file(file_name, std::ios_base::binary | std::ios_base::out);
  if (!bmp_file) {
    std::cout << "Error opening file" << std::endl;
    return;
  }
  bmp_file.write((char *)&(color_palette[color]), sizeof(color_palette[color]));
}

/**
 * image of size 5*5
 * colors =
 * [Red Green Blue White Black
 * Green Blue White Black Red
 * Blue White Black Red Green
 * White Black Red Green Blue
 * Black Red Green Blue White]
 *  the colors are defined as
 * 0 = White
 * 1 = black
 * 2 = Red
 * 3 = Green
 * 4 = Blue
 */

void BmpImage::write_color_data(void) {
  std::cout << "Writing color data to the file" << std::endl;
  std::ofstream bmp_file;
  unsigned char bit_pattern = 0;
  bmp_file.open("demo.bmp", std::ios::app | std::ios::binary);
  if (!bmp_file.is_open()) {
    std::cout << "File could not be opened" << std::endl;
    return;
  } else {
    std::cout << "File is opened, will write the color info." << std::endl;
    for (uint32_t i = 0; i < IMG_HEIGHT; i++) {
      for (uint32_t j = 0; j < IMG_WIDTH; j++) {
        bit_pattern++;
        pixel_data.push_back(color_palette[(bit_pattern + 1) % 5][0]);

        pixel_data.push_back(color_palette[(bit_pattern + 1) % 5][1]);

        pixel_data.push_back(color_palette[(bit_pattern + 1) % 5][2]);
        // bmp_file.write((char *)&color_palette[(bit_pattern + 1) % 5],
        //              sizeof(color_palette[j]));
      }
      bit_pattern++; // increment it again to get the pattern
      // add appropriate amount of padding
      if (pixel_padding != 0) {
        for (uint32_t k = 0; k < pixel_padding; k++) {

          pixel_data.push_back(padding_byte);
          // bmp_file.write((char *)&padding_byte, 1);
        }
      }
    }

    bmp_file.write((char *)(&pixel_data), sizeof(pixel_data));

    bmp_file.close();
  }
}

void read_bmp_file(void) {
  std::ifstream bmp_file_input;
  bmp_file_input.open("demo.bmp", std::ios::binary | std::ios::in);
  // file could not be opened or file doesnt exists
  if (!bmp_file_input) {
    std::cout << "Could not open the file." << std::endl;
    return;
  }
  // create a variable to hold bmp file data
  unsigned char bmp_temp[14];
  // std::cout << sizeof(unsigned short);
  bmp_file_input.read(reinterpret_cast<char *>(bmp_temp), sizeof(bmp_temp));
  // check the magic number to make sure it is BMP file
  if (bmp_temp[0] != 'B' && bmp_temp[1] != 'M') {
    std::cout << "Not a BMP file. Will Exit." << std::endl;
    return;
  }
  uint32_t file_size = *(reinterpret_cast<int *>(bmp_temp + 2));
  uint32_t starting_offset = *(reinterpret_cast<int *>(bmp_temp + 10));
  // print BMP file header
  std::cout << "Magic Number =" << bmp_temp[0] << "" << bmp_temp[1]
            << std::endl;
  std::cout << "File size =" << file_size << " bytes." << std::endl;
  std::cout << "File offset to pixel array =" << (starting_offset) << " bytes."
            << std::endl;
  bmp_file_input.close();

  std::ifstream complete_bmp_file;
  complete_bmp_file.open("demo.bmp", std::ios::binary | std::ios::in);
  if (!complete_bmp_file)
    return; // TODO handle with grace here later
  unsigned char bmp_file_array[file_size];
  complete_bmp_file.read(reinterpret_cast<char *>(bmp_file_array),
                         sizeof(bmp_file_array));

  /// Windows BITMAPINFOHEADER information
  std::cout << "Size of this header ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 14))
            << std::endl;
  std::cout << "Image width ="
            << *(reinterpret_cast<int32_t *>(bmp_file_array + 18)) << std::endl;
  std::cout << "Image height ="
            << *(reinterpret_cast<int32_t *>(bmp_file_array + 22)) << std::endl;
  std::cout << "Num of Color planes ="
            << *(reinterpret_cast<uint16_t *>(bmp_file_array + 26))
            << std::endl;
  std::cout << "Num of bits per pixel ="
            << *(reinterpret_cast<uint16_t *>(bmp_file_array + 28))
            << std::endl;
  std::cout << "Compression method ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 30))
            << std::endl;
  std::cout << "Image size ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 34))
            << std::endl;
  std::cout << "Horizntal Resolution ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 38))
            << std::endl;
  std::cout << "Vertical Resolution ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 42))
            << std::endl;
  std::cout << "Num of colors in color palette ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 46))
            << std::endl;
  std::cout << "Num of imp colors used ="
            << *(reinterpret_cast<uint32_t *>(bmp_file_array + 50))
            << std::endl;

  complete_bmp_file.close();
}

void BmpImage::write_default_image_data(void) noexcept {}

uint32_t BmpImage::get_padding_for_row(void) noexcept {
  return 4 - ((IMG_WIDTH * 3) % 4);
}

// void BmpImage::ReadFile(void) {}