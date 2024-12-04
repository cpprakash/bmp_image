/**
 * @license
 * Copyright Chander Prakash.
 */

#include <iostream>

#include "Image.hpp"

int main(void) {
  BmpImage img;
  std::string file_name = "test.bmp";
  img.create_empty_image(file_name);
  return 0;
}
