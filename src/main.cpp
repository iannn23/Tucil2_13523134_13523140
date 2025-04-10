#include <iostream>
#include <limits>
#include <string>

using namespace std;

// input
// 1. input alamat file gambar input
// 2. input metode perhitungan error
// 3. input ambang batas (threshold)
// 4. input ukuran blok minimum
// 5. input target presentase kompresi (bonus)
// 6. input alamat absolut file output

// output
// 1. waktu eksekusi
// 2. ukuran gambar sebelum
// 3. ukuran gambar setelah
// 4. presentase kompresi
// 5. kedalaman pohon
// 6. banyak simpul pohon
// 7. gambar hasil kompresi pada alamat yang sudah ditentukan

int main()
{
    string inputPath;
    string outputPath;
    int pilihmetode;
    double threshold;
    int minBlockSize;

    cout << "Kompresi Gambar dengan Quadtree" << endl;

    while (true)
    {
        cout << "input file gambar: ";
        getline(cin, inputPath);
        break;
    }

    while (true)
    {

        cout << "1. Variance" << endl;
        cout << "2. Mean Absolute Deviation (MAD)" << endl;
        cout << "3. Max Pixel Difference" << endl;
        cout << "4. Entropy" << endl;
        cout << "pilih metode: ";
        cin >> pilihmetode;

        // error message handling pilihan metode
        if (!(pilihmetode))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Masukan harus berupa angka. Silakan coba lagi.\n";
            continue;
        }

        // validasi input metode
        if (pilihmetode < 1 || pilihmetode > 4)
        {
            cout << "Kesalahan pada input: harap masukkan angka antara 1 - 4" << endl;
            continue;
        }

        break;
    }
    // input threshold
    while (true)
    {
        cout << "masukkan nilai threshold" << endl;
        cin >> threshold;
        if (!threshold)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Masukan harus berupa angka. Silakan coba lagi.\n";
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
        cout << "masukkan ukuran blok minimum" << endl;
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

    // input alamat file output
}