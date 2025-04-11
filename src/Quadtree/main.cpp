#include <iostream>
#include <vector>
#include <string>
#include "../ImageIO/ImageIO.cpp"
#include "Quadtree.cpp"
using namespace std;

// Tambahin deklarasi semua fungsi yang lo udah punya:
Node *buildQuadtree(const vector<vector<vector<unsigned char>>> &, int, int, int, int, int, double, string);
void reconstructImage(Node *, vector<vector<vector<unsigned char>>> &);
void deleteTree(Node *);

// Fungsi main untuk uji coba
int main()
{
   // string path = "C:\\Users\\ASUS\\Downloads\\Burpy.jpeg";
   // string path = "C:\\Users\\ASUS\\Downloads\\1b8d2abf-87ed-4ce7-be50-e24ac3719e32.jpeg";
   string path = "";
   string outputPath = "";

   // ...

   int width, height;
   auto rgb = loadImage(path, width, height);

   cout << "✅ Gambar berhasil dibaca: " << width << "x" << height << endl;

   // Build quadtree
   int minBlockSize = 10;
   double threshold = 5; // bisa dicoba ubah
   // string errorMethod = "Entropy";
   string errorMethod = "Variance";
   // string errorMethod = "MaxPixelDifference";
   // string errorMethod = "MAD";

   Node *root = buildQuadtree(rgb, 0, 0, width, height, minBlockSize, threshold, errorMethod);

   // Siapkan buffer output
   vector<vector<vector<unsigned char>>> output(height, vector<vector<unsigned char>>(width, vector<unsigned char>(3)));

   // Rekonstruksi dari quadtree
   reconstructImage(root, output);

   // Simpan hasilnya
   saveImage(outputPath, output, width, height);

   cout << "✅ Gambar hasil disimpan sebagai 'hasil.png'" << endl;

   // Bebaskan memori
   deleteTree(root);

   return 0;
}