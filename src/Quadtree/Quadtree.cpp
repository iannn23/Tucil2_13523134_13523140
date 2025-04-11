#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "..\ErrorMeasurement\MAD\MAD.cpp"
#include "..\ErrorMeasurement\MaxPixelDiff\MaxPixelDiff.cpp"
#include "..\ErrorMeasurement\Variance\Variance.cpp"
#include "..\ErrorMeasurement\Entropy\Entropy.cpp"

using namespace std;

struct Node
{
   int x, y;
   int width, height;
   bool isLeaf;

   unsigned char avgR;
   unsigned char avgG;
   unsigned char avgB;

   Node *topLeft;
   Node *topRight;
   Node *bottomLeft;
   Node *bottomRight;
};

void getAverageColor(
    const vector<vector<vector<unsigned char>>> &rgb,
    int x, int y, int width, int height,
    unsigned char &avgR, unsigned char &avgG, unsigned char &avgB)
{
   long long sumR = 0, sumG = 0, sumB = 0;

   int validWidth = min(width, max(0, (int)rgb[0].size() - x));
   int validHeight = min(height, max(0, (int)rgb.size() - y));

   if (validWidth <= 0 || validHeight <= 0 || x < 0 || y < 0)
   {
      avgR = avgG = avgB = 0;
      return;
   }

   for (int i = y; i < y + validHeight; i++)
   {
      for (int j = x; j < x + validWidth; j++)
      {
         sumR += rgb[i][j][0];
         sumG += rgb[i][j][1];
         sumB += rgb[i][j][2];
      }
   }

   int total = validWidth * validHeight;
   avgR = static_cast<unsigned char>(sumR / total);
   avgG = static_cast<unsigned char>(sumG / total);
   avgB = static_cast<unsigned char>(sumB / total);
}

Node *buildQuadtree(
    const vector<vector<vector<unsigned char>>> &rgb,
    int x, int y, int width, int height,
    int minBlockSize, double threshold, string errorMethod)
{
   Node *node = new Node();
   node->x = x;
   node->y = y;
   node->width = width;
   node->height = height;

   if (width * height <= minBlockSize)
   {
      node->isLeaf = true;
      node->topLeft = node->topRight = node->bottomLeft = node->bottomRight = nullptr;
      return node;
   }

   double variance = 0.0;

   if (errorMethod == "Variance")
   {
      variance = calculateBlockVariance(rgb, x, y, width, height);
   }
   else if (errorMethod == "MAD")
   {
      variance = calculateBlockMAD(rgb, x, y, width, height);
   }
   else if (errorMethod == "MaxPixelDifference")
   {
      variance = calculateBlockMaxPixelDifference(rgb, x, y, width, height);
   }
   else if (errorMethod == "Entropy")
   {
      variance = calculateBlockEntropy(rgb, x, y, width, height);
   }

   if (variance <= threshold)
   {
      node->isLeaf = true;
      node->topLeft = node->topRight = node->bottomLeft = node->bottomRight = nullptr;
      return node;
   }

   node->isLeaf = false;

   int halfWidth = (width + 1) / 2;
   int halfHeight = (height + 1) / 2;

   node->topLeft = buildQuadtree(rgb, x, y, halfWidth, halfHeight, minBlockSize, threshold, errorMethod);
   node->topRight = buildQuadtree(rgb, x + halfWidth, y, width - halfWidth, halfHeight, minBlockSize, threshold, errorMethod);
   node->bottomLeft = buildQuadtree(rgb, x, y + halfHeight, halfWidth, height - halfHeight, minBlockSize, threshold, errorMethod);
   node->bottomRight = buildQuadtree(rgb, x + halfWidth, y + halfHeight, width - halfWidth, height - halfHeight, minBlockSize, threshold, errorMethod);

   return node;
}

void deleteTree(Node *root)
{
   if (!root)
      return;

   deleteTree(root->topLeft);
   deleteTree(root->topRight);
   deleteTree(root->bottomLeft);
   deleteTree(root->bottomRight);

   delete root;
}

void fillArea(
    vector<vector<vector<unsigned char>>> &output,
    int x, int y, int width, int height,
    unsigned char r, unsigned char g, unsigned b)
{
   for (int i = y; i < y + height; i++)
   {
      for (int j = x; j < x + width; j++)
      {
         output[i][j][0] = r;
         output[i][j][1] = g;
         output[i][j][2] = b;
      }
   }
}

void reconstructImage(
    Node *root,
    vector<vector<vector<unsigned char>>> &outputImage)
{
   if (!root)
      return;

   if (root->isLeaf)
   {
      fillArea(outputImage, root->x, root->y, root->width, root->height, root->avgR, root->avgG, root->avgB);
   }
   else
   {
      reconstructImage(root->topLeft, outputImage);
      reconstructImage(root->topRight, outputImage);
      reconstructImage(root->bottomLeft, outputImage);
      reconstructImage(root->bottomRight, outputImage);
   }
}

// Fungsi untuk menghitung kedalaman pohon
int calculateTreeDepth(Node *root)
{
   if (!root)
      return 0;
   if (root->isLeaf)
      return 1;

   int depthTL = calculateTreeDepth(root->topLeft);
   int depthTR = calculateTreeDepth(root->topRight);
   int depthBL = calculateTreeDepth(root->bottomLeft);
   int depthBR = calculateTreeDepth(root->bottomRight);

   return 1 + max(max(depthTL, depthTR), max(depthBL, depthBR));
}

// Fungsi untuk menghitung jumlah simpul
int calculateNodeCount(Node *root)
{
   if (!root)
      return 0;
   if (root->isLeaf)
      return 1;

   return 1 + calculateNodeCount(root->topLeft) +
          calculateNodeCount(root->topRight) +
          calculateNodeCount(root->bottomLeft) +
          calculateNodeCount(root->bottomRight);
}
