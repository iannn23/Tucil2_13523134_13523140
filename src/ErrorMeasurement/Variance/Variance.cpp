#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// Fungsi untuk menghitung variansi dalam satu blok
double calculateBlockVariance(const vector<vector<vector<unsigned char>>> &rgb, int startX, int startY, int width, int height)
{
    vector<double> valR, valG, valB;
    // Kumpulkan nilai RGB dari blok
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

    // Hitung rata-rata RGB
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

    double varR = 0;
    double varG = 0;
    double varB = 0;

    // Hitung variansi untuk setiap kanal warna
    double varR = 0, varG = 0, varB = 0;
    for (int i = 0; i < N; i++)
    {
        varR += (pow(valR[i] - avgR, 2));
        varG += (pow(valG[i] - avgG, 2));
        varB += (pow(valB[i] - avgB, 2));
    }

    varR /= N;
    varG /= N;
    varB /= N;

    // Hitung variansi
    double variance = (varR + varG + varB) / 3;
}
