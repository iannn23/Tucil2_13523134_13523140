#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Fungsi untuk menghitung Mean Absolute Deviation (MAD) antara dua matriks gambar RGB
double calculateBlockMAD(const vector<vector<vector<unsigned char>>> &rgb, int startX, int startY, int width, int height)
{
    vector<double> valR, valG, valB;

    for (int y = startY; y < startY + (height) && y < (int)rgb.size(); y++)
    {
        for (int x = startX; x < startX + (width) && x < (int)rgb[y].size(); x++)
        {
            valR.push_back(rgb[y][x][0]); // R
            valG.push_back(rgb[y][x][1]); // G
            valB.push_back(rgb[y][x][2]); // B
        }
    }

    int N = height * width;

    // hitung rata-rata RGB
    double avgR = 0, avgG = 0, avgB = 0;
    for (int i = 0; i < N; i++)
    {
        avgR += valR[i];
        avgG += valG[i];
        avgB += valB[i];
    }
    avgR /= N;
    avgG /= N;
    avgB /= N;

    // hitung variansi untuk setiap RGB
    double madR = 0;
    double madG = 0;
    double madB = 0;
    for (int i = 0; i < N; i++)
    {
        madR += abs(valR[i] - avgR);
        madG += abs(valG[i] - avgG);
        madB += abs(valB[i] - avgB);
    }

    madR /= N;
    madG /= N;
    madB /= N;

    // Hitung MAD rata-rata untuk ketiga kanal warna
    double MAD = (madR + madG + madB) / 3;
    return MAD;
}