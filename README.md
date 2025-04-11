# **Kompresi Gambar Dengan Metode Quadtree**

Tugas Kecil 2 Strategi Algoritma kali ini kami menggunakan Algoritma Divide and Conduer untuk membuat sistem kompresi gambar dengan Quadtree. Gambar yang dimasukkan akan dikompresi dan diolah dalam format matriks piksel dengan nilai intensitas berdasrakan sistem warna RGB. Quadtree membagi gambar menjadi blok-blok kecil berdasarkan keseragaman warna atau intensitas piksel. Prosesnya dimulai dengan membagi gambar menjadi empat bagian, lalu memeriksa apakah setiap bagian memiliki nilai yang seragam berdasarkan analisis sistem warna RGB, yaitu dengan membandingkan komposisi nilai merah (R), hijau (G), dan biru (B) pada piksel-piksel di dalamnya.

Input berupa alamat gambar, nilai minimum blok, threshold, dan alamat untuk output gambar disimpan. Parameter yang digunakan adalah Metode Pengukuran Error yaitu Variance, Mean Absolut Deviation, Max Pixel Difference, dan Entropy

## Cara Menjalankan Program 

# Compile Program
asumsi kalian berada pada folder Tucil2_13523134_13523140
```shell
jalankan:
cd src
g++ -o program main.cpp
./program
```
setelah itu kalian akan diminta untuk melakukan hal hal berikut:
1. Input alamat absolut gamabar yang ingin dikompresi
2. Pilih metode perhitungan error (Variance, Mean Absolut Deviation, Max Pixel Difference, dan Entropy)
3. Masukkan nilai threshold
4. Masukkan ukuran blok minimum'
5. Input alamat absolut gambar hasil kompresi

Setelah kalian memasukkan input yang diminta oleh program, maka program akan melakukan kompresi.

