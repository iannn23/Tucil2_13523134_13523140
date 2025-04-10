#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

// Fungsi untuk menghitung entropi dalam satu blok untuk setiap kanal RGB
double calculateBlockEntropy(const vector<vector<vector<unsigned char>>> &rgb, int startX, int startY, int width, int height)
{
   // Array untuk menghitung frekuensi setiap intensitas (0-255) untuk R, G, B
   vector<int> histR(256, 0), histG(256, 0), histB(256, 0);
   int totalPixels = 0;

   // hitung histogram untuk setiap rgb
   for (int y = startY; y < startY + height && y < (int)rgb.size(); y++)
   {
      for (int x = startX; x < startX + width && x < (int)rgb[y].size(); x++)
      {
         histR[rgb[y][x][0]]++; // R
         histG[rgb[y][x][1]]++; // G
         histB[rgb[y][x][2]]++; // B
         totalPixels++;
      }
   }

   if (totalPixels == 0)
   {
      return 0;
   }

   // hitung entropi untuk setiap kanal
   double entropyR = 0, entropyG = 0, entropyB = 0;
   for (int i = 0; i < 256; i++)
   {
      if (histR[i] > 0)
      {
         double p = static_cast<double>(histR[i]) / totalPixels;
         entropyR -= p * log2(p);
      }
      if (histG[i] > 0)
      {
         double p = static_cast<double>(histG[i]) / totalPixels;
         entropyG -= p * log2(p);
      }
      if (histB[i] > 0)
      {
         double p = static_cast<double>(histB[i]) / totalPixels;
         entropyB -= p * log2(p);
      }
   }

   double entropy = (entropyR + entropyG + entropyB) / 3;
   return entropy;
}