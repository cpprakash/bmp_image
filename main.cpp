/**
 * @license
 * Copyright Chander Prakash.
 */

#include <iostream>

#include "Image.hpp"

void handle_choice_one(void) noexcept;   // Create a 1x1 BMP image file
void handle_choice_two(void) noexcept;   // Read a BMP image file
void handle_choice_three(void) noexcept; // Create a wXy BMP image file
void handle_choice_four(void) noexcept;  // Create chess pattern

/**
 * Creates a menu so that the user can select the option
 * for now the options are
 * create a blank default 1x1 image
 * read a bmp file (only supported types of bmp specification)
 */
void create_menu(void) {
  std::cout << "Welcome to BMP Image Program. Please enter a choice:"
            << std::endl;
  std::cout << "1. Create a 1x1 BMP image file." << std::endl;
  std::cout << "2. Read a BMP image file" << std::endl;
  std::cout << "3. Create a wXy BMP image file." << std::endl;
  std::cout << "4. Create a chess pattern." << std::endl;
  std::cout << "5. Exit the program." << std::endl;
  uint32_t choice;
  std::cin >> choice;
  std::cout << "You have entered " << choice << std::endl;
  // while (true) {
  /* code */
  switch (choice) {
  case 1:
    handle_choice_one();
    break;
  case 2:
    handle_choice_two();
    break;
  case 3:
    handle_choice_three();
    break;
  case 4: {
    handle_choice_four();
  } break;
  case 5: {
    std::cout << "Exiting the program. Thankyou for using it." << std::endl;
    exit(0);
  } break;
  default:
    std::cout << "Exiting for no reason " << choice << std::endl;
    break;
  }
  //}
}

int main(void) {
  create_menu();
  return 0;
}

void handle_choice_one(void) noexcept {
  std::cout << "Please enter the file name to create without extension."
            << std::endl;
  std::string file_name;
  std::cin >> file_name;
  BmpImage img;
  file_name += ".bmp";
  img.create_empty_image(file_name);
}

void handle_choice_two(void) noexcept {
  std::cout << "Please enter a file name to read" << std::endl;
  std::string file_name;
  std::cin >> file_name;
  BmpImage img;
  img.start_reading_bmp_file(file_name + ".bmp");
}

void handle_choice_three(void) noexcept {
  std::cout << "Please enter a file name to create" << std::endl;
  std::string file_name;
  std::cin >> file_name;
  std::cout << "Please enter a height of image" << std::endl;
  uint32_t height;
  std::cin >> height;
  std::cout << "Please enter a width of image" << std::endl;
  uint32_t width;
  std::cin >> width;
  file_name += ".bmp";
  BmpImage img(file_name, height, width);
}

void handle_choice_four(void) noexcept {
  std::cout << "Please enter a file name to create" << std::endl;
  std::string file_name;
  std::cin >> file_name;
  std::cout << "Please enter a height of image" << std::endl;
  uint32_t height;
  std::cin >> height;
  std::cout << "Please enter a width of image" << std::endl;
  uint32_t width;
  std::cin >> width;
  file_name += ".bmp";
  uint32_t box_size;
  std::cout << "Please enter box size (multiple of 8)" << std::endl;
  std::cin >> box_size;
  BmpImage img;
  // TODO, fix me with proper values, for now we just make it fixed size
  // without user input,
  img.create_chess_pattern(file_name, 8, 8, 1);
}