#include <iostream>
#include <vector>
#include <string>
#include "ImageIO/ImageIO.cpp"  

using namespace std;

int main() {
    string path;
    cout << "Masukkan path gambar (jpg/png): ";
    cin >> path;

    int width, height;
    auto rgb = loadImage(path, width, height);

    cout << "✅ Gambar berhasil dibaca!\n";
    cout << "Ukuran gambar: " << width << " x " << height << endl;

    // Cek beberapa piksel awal
    cout << "\nSample warna piksel:\n";
    for (int y = 0; y < min(height, 3); y++) {
        for (int x = 0; x < min(width, 3); x++) {
            cout << "Pixel (" << y << "," << x << ") = "
                 << "R: " << (int)rgb[y][x][0] << ", "
                 << "G: " << (int)rgb[y][x][1] << ", "
                 << "B: " << (int)rgb[y][x][2] << endl;
        }
    }

    return 0;
}