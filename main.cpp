/**
 * @license
 * Copyright Chander Prakash.
 */

#include <iostream>

#include "Image.hpp"

void handle_choice_one(void);   // Create a 1x1 BMP image file
void handle_choice_two(void);   // Read a BMP image file
void handle_choice_three(void); // Create a wXy BMP image file

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
  std::cout << "4. Exit the program." << std::endl;
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

void handle_choice_one(void) {
  std::cout << "Please enter the file name to create without extension."
            << std::endl;
  std::string file_name;
  std::cin >> file_name;
  BmpImage img;
  file_name += file_name + ".bmp";
  img.create_empty_image(file_name);
}

void handle_choice_two(void) {
  std::cout << "Please enter a file name to read" << std::endl;
  std::string file_name;
  std::cin >> file_name;
  BmpImage img;
  img.start_reading_bmp_file(file_name + ".bmp");
}

void handle_choice_three(void) {
  std::cout << "Please enter a file name to create" << std::endl;
  std::string file_name;
  std::cin >> file_name;
  std::cout << "Please enter a height of image" << std::endl;
  uint32_t height;
  std::cin >> height;
  std::cout << "Please enter a width of image" << std::endl;
  uint32_t width;
  std::cin >> width;
  file_name += file_name + ".bmp";
  BmpImage img(file_name, height, width);
}