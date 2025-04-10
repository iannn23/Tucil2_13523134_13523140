#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// Fungsi untuk menghitung variansi dalam satu blok
double calculateBlockVariance(const vector<vector<vector<unsigned char>>>& image, 
    int startX, int startY, int blockSize) {
vector<double> rValues, gValues, bValues;

// Kumpulkan nilai RGB dari blok
for (int y = startY; y < startY + blockSize && y < (int)image.size(); y++) {
for (int x = startX; x < startX + blockSize && x < (int)image[0].size(); x++) {
rValues.push_back(image[y][x][0]);
gValues.push_back(image[y][x][1]);
bValues.push_back(image[y][x][2]);
}
}

int N = rValues.size();
if (N == 0) return 0;

// Hitung rata-rata RGB
double avgR = 0, avgG = 0, avgB = 0;
for (int i = 0; i < N; i++) {
avgR += rValues[i];
avgG += gValues[i];
avgB += bValues[i];
}
avgR /= N;
avgG /= N;
avgB /= N;

// Hitung variansi
double variance = 0;
for (int i = 0; i < N; i++) {
variance += pow(rValues[i] - avgR, 2) + pow(gValues[i] - avgG, 2) + pow(bValues[i] - avgB, 2);
}
return variance / N;
}

// Struktur untuk menyimpan info blok (koordinat dan ukuran)
struct Block {
    int x, y, size;
    Block(int x, int y, int size) : x(x), y(y), size(size) {}
};

// Fungsi rekursif untuk membagi blok berdasarkan variansi
void divideBlocks(const vector<vector<vector<unsigned char>>>& image, 
                  vector<Block>& blocks, int startX, int startY, int blockSize, 
                  double threshold, int minBlockSize) {
    double variance = calculateBlockVariance(image, startX, startY, blockSize);

    // Jika variansi > threshold dan ukuran blok > minimum, bagi menjadi 4
    if (variance > threshold && blockSize > minBlockSize) {
        int newSize = blockSize / 2;
        divideBlocks(image, blocks, startX, startY, newSize, threshold, minBlockSize);              // Kiri atas
        divideBlocks(image, blocks, startX + newSize, startY, newSize, threshold, minBlockSize);    // Kanan atas
        divideBlocks(image, blocks, startX, startY + newSize, newSize, threshold, minBlockSize);    // Kiri bawah
        divideBlocks(image, blocks, startX + newSize, startY + newSize, newSize, threshold, minBlockSize); // Kanan bawah
    } else {
        blocks.emplace_back(startX, startY, blockSize); // Simpan blok jika tidak perlu dibagi lagi
    }
}

