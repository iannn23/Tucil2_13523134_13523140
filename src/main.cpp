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
        cout << "Input alamat absolut file gambar yang ingin dikompresi (inputPath): ";
        getline(cin, inputPath);
        if (inputPath.empty())
        {
            cout << "Error: Alamat file tidak boleh kosong. Silakan coba lagi.\n";
            continue;
        }
        // Hapus tanda kutip di awal dan akhir jika ada
        if (inputPath.front() == '"' && inputPath.back() == '"')
        {
            inputPath = inputPath.substr(1, inputPath.length() - 2);
        }
        cout << "Mencoba mengakses: " << inputPath << endl;
        if (!fs::exists(inputPath))
        {
            cout << "Error: File tidak ditemukan. Silakan masukkan alamat file yang valid.\n";
            // Tambahkan informasi tambahan
            fs::path pathObj(inputPath);
            cout << "Direktori: " << pathObj.parent_path().string() << endl;
            cout << "Nama file: " << pathObj.filename().string() << endl;
            if (!fs::exists(pathObj.parent_path()))
            {
                cout << "Direktori tidak ditemukan!\n";
            }
            else
            {
                cout << "Direktori ditemukan, tetapi file tidak ada.\n";
            }
            continue;
        }
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
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Terdapat kesalahan: Masukan harus berupa angka. Silakan coba lagi (gunakan angka)." << endl;
            continue;
        }

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
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Terdapat kesalahan: Masukan harus berupa angka. Silakan coba lagi (gunakan angka)." << endl;
            continue;
        }

        if (threshold < 0)
        {
            cout << "Kesalahan pada input: Threshold tidak boleh negatif. Silakan masukkan nilai yang valid.\n";
            continue;
        }
        break;
    }

    // input ukuran blok minimum
    while (true)
    {
        cout << "Masukkan ukuran blok minimum: ";
        cin >> minBlockSize;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Masukan harus berupa angka. Silakan coba lagi.\n";
            continue;
        }

        if (minBlockSize < 0)
        {
            cout << "Error: Ukuran blok minimum tidak boleh negatif. Silakan masukkan nilai yang valid.\n";
            continue;
        }
        break;
    }

    // input alamat output gambar
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bersihkan buffer
    while (true)
    {
        cout << "Input alamat absolut untuk file gambar yang sudah dikompresi (outputPath): ";
        getline(cin, outputPath);
        if (outputPath.empty())
        {
            cout << "Error: Alamat file tidak boleh kosong. Silakan coba lagi.\n";
            continue;
        }
        // Hapus tanda kutip di awal dan akhir jika ada
        if (outputPath.front() == '"' && outputPath.back() == '"')
        {
            outputPath = inputPath.substr(1, inputPath.length() - 2);
        }
        // Cek apakah direktori output valid
        fs::path outputPathObj = fs::path(outputPath);
        fs::path outputDir = outputPathObj.parent_path();
        if (!outputDir.empty() && !fs::exists(outputDir))
        {
            cout << "Error: Direktori output tidak ditemukan. Silakan masukkan alamat yang valid.\n";
            continue;
        }
        // Hapus tanda kutip di awal dan akhir jika ada
        if (outputPath.front() == '"' && outputPath.back() == '"')
        {
            outputPath = outputPath.substr(1, outputPath.length() - 2);
        }
        // Cek apakah outputPath adalah direktori
        if (fs::exists(outputPathObj) && fs::is_directory(outputPathObj))
        {
            // Jika direktori, tambahkan nama file default
            outputPath = outputPathObj.string() + "\\hasil.png";
            cout << "Peringatan: Anda memasukkan direktori. Output akan disimpan sebagai: " << outputPath << endl;
        }
        break;
    }

    // kompresi domulai
    auto start = chrono::high_resolution_clock::now(); // menghitung waktu

    // Muat gambar
    vector<vector<vector<unsigned char>>> rgb;
    try
    {
        rgb = loadImage(inputPath, width, height);
    }
    catch (const exception &e)
    {
        cout << "Gagal memuat gambar: " << e.what() << endl;
        return 1;
    }
    vector<vector<vector<unsigned char>>> output(height, vector<vector<unsigned char>>(width, vector<unsigned char>(3)));

    unsigned char avgR, avgG, avgB;

    string errorMethod;
    switch (pilihmetode)
    {
    case 1:
        errorMethod = "Variance";
        break;
    case 2:
        errorMethod = "MAD";
        break;
    case 3:
        errorMethod = "MaxPixelDifference";
        break;
    case 4:
        errorMethod = "Entropy";
        break;
    default:
        cout << "Kesalahan pada input: harap masukkan angka antara 1 - 4" << endl;
        return 1;
    }

    Node *root = buildQuadtree(rgb, 0, 0, width, height, minBlockSize, threshold, errorMethod);
    try
    {
        reconstructImage(root, output);
        saveImage(outputPath, output, width, height);
    }
    catch (const exception &e)
    {
        cout << "Terjadi kesalahan: " << e.what() << endl;
        deleteTree(root);
        return 1;
    }


    // waktu eksekusi
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Waktu eksekusi: " << duration.count() << " detik" << endl;
    chrono::duration<double, milli> duration_ms = end - start;
    cout << "Waktu eksekusi: " << duration_ms.count() << " milidetik" << endl;

    // ukuran gambar sebelum kompresi
    cout << "Hasil Kompresi" << endl;
    uintmax_t sizeInBytesBefore;
    try
    {
        sizeInBytesBefore = fs::file_size(inputPath);
        double sizeInKBBefore = sizeInBytesBefore / 1024.0;
        double sizeInMBBefore = sizeInKBBefore / 1024.0;
        cout << "\nUkuran file sebelum kompresi (dalam KB): " << sizeInKBBefore << " KB" << endl;
        cout << "Ukuran file sebelum kompresi (dalam MB): " << sizeInMBBefore << " MB" << endl;
    }
    catch (const fs::filesystem_error &e)
    {
        cout << "Gagal membaca ukuran file asli: " << e.what() << endl;
        return 1;
    }


    // ukuran gambar sesudah kompresi
    uintmax_t sizeInBytesAfter = fs::file_size(outputPath);
    double sizeInKBAfter = sizeInBytesAfter / 1024.0;
    double sizeInMBAfter = sizeInKBAfter / 1024.0;
    cout << "Ukuran file hasil kompresi (dalam KB): " << sizeInKBAfter << " KB" << std::endl;
    cout << "Ukuran file hasil kompresi (dalam MB): " << sizeInMBAfter << " MB" << std::endl;

    // presentase kompresi
    uintmax_t compressedSize;
    float compressionPrecentage = ((1 - (static_cast<double>(sizeInBytesAfter) / sizeInBytesBefore)) * 100);
    cout << "Persentase kompresi: " << compressionPrecentage << "%" << endl;
    // kedalaman pohon

    // banyak simpul pada pohon
    int nodes =  calculateNodeCount(root);
    cout <<"Banyak daun: " << nodes << endl;

    // kedalaman
    int depth = calculateTreeDepth(root);
    cout <<"Kedalaman: " << depth << endl;

    // gambar hasil kompresi pada alamat yang sudah ditentukan
    cout << "Gambar hasil disimpan sebagai 'hasil.png' pada " << outputPath << endl;
    deleteTree(root);
}