# **Kompresi Gambar Dengan Metode Quadtree**

Tugas Kecil 2 Strategi Algoritma kali ini kami menggunakan Algoritma Divide and Conduer untuk membuat sistem kompresi gambar dengan Quadtree. Gambar yang dimasukkan akan dikompresi dan diolah dalam format matriks piksel dengan nilai intensitas berdasrakan sistem warna RGB. Quadtree membagi gambar menjadi blok-blok kecil berdasarkan keseragaman warna atau intensitas piksel. Prosesnya dimulai dengan membagi gambar menjadi empat bagian, lalu memeriksa apakah setiap bagian memiliki nilai yang seragam berdasarkan analisis sistem warna RGB, yaitu dengan membandingkan komposisi nilai merah (R), hijau (G), dan biru (B) pada piksel-piksel di dalamnya.

Input berupa alamat gambar, nilai minimum blok, threshold, dan alamat untuk output gambar disimpan.

## Cara Menjalankan Program 

# Compile Program

```shell
cd src
g++ -o program main.cpp
./program
```
