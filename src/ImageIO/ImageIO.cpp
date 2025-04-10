#include <iostream>
#include <vector>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

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

void saveImage(const string&path, const vector<vector<vector<unsigned char>>>& rgb, int width, int height) {
    vector<unsigned char> data(width * height * 3);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int idx = (y * width + x) * 3;
            data[idx + 0] = rgb[y][x][0]; // R
            data[idx + 1] = rgb[y][x][1]; // G
            data[idx + 2] = rgb[y][x][2]; // B
        }
    }
    
    int success = stbi_write_png(path.c_str(), width, height, 3, data.data(), width * 3);

    if (!success) {
        cerr << "Gagal menyimpan gambar ke: " << path << endl;
    } else {
        cout << "Gambar berhasil disimpan ke: " << path << endl;
    }
}