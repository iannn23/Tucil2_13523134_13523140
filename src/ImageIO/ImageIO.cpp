#include <iostream>
#include <vector>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

vector<vector<vector<unsigned char>>> loadImage(const string& path, int& width, int& height) {
    int channels;

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 3);

    if (!data) {
        cerr << "Gagal load gambar: " << path << endl;
        cerr << "Alasan: " << stbi_failure_reason() << endl;
        exit(1);
    }

    vector<vector<vector<unsigned char>>> rgb(height, vector<vector<unsigned char>>(width, vector<unsigned char>(3)));

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * 3;
            rgb[y][x][0] = data[idx + 0];    
            rgb[y][x][1] = data[idx + 1];    
            rgb[y][x][2] = data[idx + 2];    
        }
    }
    
    stbi_image_free(data);
    return rgb;
}
