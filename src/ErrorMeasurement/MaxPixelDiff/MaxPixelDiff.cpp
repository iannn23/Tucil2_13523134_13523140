#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

// menghitung Max Pixel Difference dalam satu blok untuk rgb
double calculateBlockMaxPixelDifference(const vector<vector<vector<unsigned char>>> &rgb, int startX, int startY, int width, int height)
{
   unsigned char maxR = 0, maxG = 0, maxB = 0;
   unsigned char minR = 255, minG = 255, minB = 255;
   bool DataExist = false;

   for (int y = startY; y < startY + height && y < (int)rgb.size(); y++)
   {
      for (int x = startX; x < startX + width && x < (int)rgb[y].size(); x++)
      {
         DataExist = true;
         maxR = max(maxR, rgb[y][x][0]); // R max
         maxG = max(maxG, rgb[y][x][1]); // G max
         maxB = max(maxB, rgb[y][x][2]); // B max
         minR = min(minR, rgb[y][x][0]); // R min
         minG = min(minG, rgb[y][x][1]); // G min
         minB = min(minB, rgb[y][x][2]); // B min
      }
   }

   if (!DataExist)
   {
      return 0;
   }

   // hitung Max Pixel Difference rgb
   double diffR = maxR - minR;
   double diffG = maxG - minG;
   double diffB = maxB - minB;

   // hitung Max Pixel Difference
   double maxPixelDiff = (diffR + diffG + diffB) / 3;
   return maxPixelDiff;
}
