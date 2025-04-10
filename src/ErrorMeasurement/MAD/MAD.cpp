#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// menghitung Mean Absolute Deviation (MAD) antara dua matriks gambar rgb
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

    if (N == 0)
    {
        return 0;
    }

    // hitung rata-rata rgb
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

    // hitung mad untuk setiap rgb
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

    // hitung MAD rata-rata untuk rgb
    double MAD = (madR + madG + madB) / 3;
    return MAD;
