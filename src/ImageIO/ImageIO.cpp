#include <iostream>
#include <vector>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

vector<vector<vector<unsigned char>>> loadImage(const string& path, int& width, int& height) {
    int channels;

    unsigned char* data = stbi_load
}