#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <chrono>
#include <filesystem>
#include "..\src\Quadtree\Quadtree.cpp"
#include "..\src\ImageIO\ImageIO.cpp"
namespace fs = std::filesystem;
using namespace std;

// input
// 1. input alamat file gambar input ()
// 2. input metode perhitungan error (done)
// 3. input ambang batas (threshold) (done)
// 4. input ukuran blok minimum (done)
// 5. input target presentase kompresi (bonus)
// 6. input alamat absolut file output

// output
// 1. waktu eksekusi (done)
// 2. ukuran gambar sebelum
// 3. ukuran gambar setelah
// 4. presentase kompresi
// 5. kedalaman pohon
// 6. banyak simpul pohon
// 7. gambar hasil kompresi pada alamat yang sudah ditentukan
Node *buildQuadtree(const vector<vector<vector<unsigned char>>> &, int, int, int, int, int, double, string);
void reconstructImage(Node *, vector<vector<vector<unsigned char>>> &);
void deleteTree(Node *);

int main()
{
    string inputPath;
    string outputPath;
    int pilihmetode;
    double threshold;
    int minBlockSize;
    int width, height;

    cout << "    __ __                                                   ______                __               " << endl;
    cout << "   / //_/___  ____ ___  ____  ________  _________  _____   / ____/___ _____ ___  / /_  ____ ______ " << endl;
    cout << "  / ,< / __ \\/ __ `__ \\/ __ \\/ ___/ _ \\/ ___/ __ \\/ ___/  / / __/ __ `/ __ `__ \\/ __ \\/ __ `/ ___/ " << endl;
    cout << " / /| / /_/ / / / / / / /_/ / /  /  __(__  ) /_/ / /     / /_/ / /_/ / / / / / / /_/ / /_/ / /     " << endl;
    cout << "/_/ |_\\____/_/ /_/ /_/ .___/_/   \\___/____/\\____/_/      \\____/\\__,_/_/ /_/ /_/_.___/\\__,_/_/      " << endl;
    cout << "                    /_/                                                                            " << endl;

    while (true)
    {
        cout << "Input alamat absolut file gambar yang ingin dikompresi: ";
        getline(cin, inputPath);
        // auto rgb = loadImage(inputPath, width, height);
        break;
    }

    while (true)
    {
        cout << "Pilih metode perhitungan error" << endl;
        cout << "1. Variance" << endl;
        cout << "2. Mean Absolute Deviation (MAD)" << endl;
        cout << "3. Max Pixel Difference" << endl;
        cout << "4. Entropy" << endl;
        cout << "Pilih metode: ";
        cin >> pilihmetode;

        // error message handling pilihan metode
        if (!(pilihmetode))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Terdapat kesalahan: Masukan harus berupa angka. Silakan coba lagi (gunakan angka)." << endl;
            continue;
        }

        // validasi input metode
        if (pilihmetode < 1 || pilihmetode > 4)
        {
            cout << "Kesalahan pada input: harap masukkan angka antara 1 - 4." << endl;
            continue;
        }

        break;
    }
    // input threshold
    while (true)
    {
        cout << "Masukkan nilai threshold: ";
        cin >> threshold;
        if (!threshold)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Terdapat kesalahan: Masukan harus berupa angka. Silakan coba lagi (gunakan angka)." << endl;
            continue;
        }

        if (threshold < 0)
        {
            cout << "" << endl;
            continue;
        }
        break;
    }

    // input ukuran blok minimum
    while (true)
    {
        cout << "Masukkan ukuran blok minimum: ";
        cin >> minBlockSize;
        if (!minBlockSize)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Masukan harus berupa angka. Silakan coba lagi.\n";
            continue;
        }

        if (minBlockSize < 0)
        {
            cout << "" << endl;
            continue;
        }
        break;
    }

    // waktu eksekusi
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Waktu eksekusi: " << duration.count() << " detik" << endl;
    chrono::duration<double, milli> duration_ms = end - start;
    cout << "Waktu eksekusi: " << duration_ms.count() << " milidetik" << endl;

    // ukuran gambar sebelum kompresi
    cout << "Hasil Kompresi" << endl;
    uintmax_t sizeInBytesBefore = fs::file_size(inputPath);
    double sizeInKBBefore = sizeInBytesBefore / 1024.0;
    double sizeInMBBefore = sizeInKBBefore / 1024.0;
    cout << "Ukuran file sebelum kompresi (dalam KB): " << sizeInKBBefore << " KB" << std::endl;
    cout << "Ukuran file sebelum kompresi (dalam MB): " << sizeInMBBefore << " MB" << std::endl;

    // ukuran gambar sesudah kompresi
    uintmax_t sizeInBytesAfter = fs::file_size(outputPath);
    double sizeInKBAfter = sizeInBytesAfter / 1024.0;
    double sizeInMBAfter = sizeInKBAfter / 1024.0;
    cout << "Ukuran file hasil kompresi (dalam KB): " << sizeInKBBefore << " KB" << std::endl;
    cout << "Ukuran file hasil kompresi (dalam MB): " << sizeInMBBefore << " MB" << std::endl;

    // presentase kompresi
    uintmax_t compressedSize;
    float compressionPrecentage = ((1 - (static_cast<double>(sizeInBytesAfter) / sizeInBytesBefore)) * 100);
    cout << "Persentase kompresi: " << compressionPrecentage << "%" << endl;
    // kedalaman pohon

    // banyak simpul pada pohon

    // gambar hasil kompresi pada alamat yang sudah ditentukan
}