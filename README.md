# Tugas Besar IF 2110 Algoritma dan Struktur Data (Kelompok TB_01_H)
> <div align="justify">Tugas besar ini disusun sebaik-baiknya oleh anggota Kelompok H K-01 untuk memenuhi kebutuhan spesifikasi tugas dalam mata kuliah IF2110 Algoritma dan Struktur Data Semester I 2023/2024. Dalam tugas besar kali ini, kami membuat sebuah program yang merupakan replika atas sebuah aplikasi yang bernama Twitter yang sekarang menjadi X, dengan nama program Tweeter yang mana merupakan program berbasis CLI <i>(Command Line Interface)</i>. Untuk membuat program ini, kami menggunakan struktur data yang bervariasi dan memilih ADT yang paling cocok untuk menyelesaikan sebuah persoalan atau fitur tertentu dalam program ini. </div>

## Komposisi Kelompok dan Dokumentasi
- Zachary Samuel T (13522016)
- Tazkia Nizami (13522032)
- M Athaullah Daffa Kusuma M (13522044)
- Elbert Chailes (13522045)
- Kharris Khisunica (13522051)
  
<img src="https://github.com/ChaiGans/Tubes-Alstrukdat-K01-H/assets/113753352/b39ecd6f-8080-404a-9ab3-1c70c3c89f8d" width="400" height="fit">

## Ringkasan Program
Program Tweeter ini merupakan sebuah program replika sebuah sosial media yang memberikan kesempatan bagi penggunanya untuk berinteraksi dengan pengguna lainnya dan berbasis CLI. Program ini menyediakan fitur-fitur bersosial media layaknya seperti aplikasi aslinya, seperti membuat kicauan, melihat profil teman, melakukan pertambahan pertemanan, membuat tagar, dan fitur-fitur lainnya. Program ini dibangun dengan menggunakan berbagai struktur data atau ADT yang bervariasi sesuai dengan persoalan atau fitur yang dibuat dalam program tersebut. Program ini dikembangkan dengan menggunakan bahasa pemrograman C. 

Fitur-fitur utama yang tersedia program ini adalah sebagai berikut.
- Fitur `Perintah` yang direalisasi dengan menggunakan `ADT Mesin Kata dan ADT Mesin Karakter` untuk membaca setiap perintah atau _command_ yang diberikan oleh pengguna untuk menggunakan fitur-fitur pada program.
- Fitur `Inisialisasi/Pengguna` yang diintegrasikan tanpa menggunakan struktur data melainkan hanya logika pemrograman biasa yang dilakukan pada file `main.c`. 
- Fitur `Pengguna` yang diselesaikan dengan menggunakan struktur data `ADT List dengan Struktur Data Array Statik`
- Fitur `Profil` yang diselesaikan dengan menggunakan struktur data `ADT Matriks` untuk mengatasi permasalahan foto profil dan menggunakan list pengguna statik untuk menyelesaikan persoalan fitur lainnya.
- Fitur `Teman` yang diselesaikan dengan menggunakan struktur data `ADT Graf dengan representasi Adjacency Matrix` untuk mengetahui relasi antara satu pengguna dengan pengguna lainnya.
- Fitur `Permintaan Teman` yang diselesaikan dengan menggunakan `ADT Priority Queue` untuk menyelesaikan permasalah masukan permintaan teman sesuai dengan popularitas atau teman yang dimiliki oleh pengguna yang mengirimkan permintaan pertemanan.
- Fitur `Kicauan` yang diselesaikan dengan membuat list kicauan yang direalisasi dengan menggunakan `ADT List dengan Struktur Data Array Dinamik` untuk mengatasi permasalahan pembuatan atau penyimpanan kicauan yang tidak dibatasi.
- Fitur `Balasan` yang diselesaikan dengan menggunakan `ADT Tree` untuk menyelesaikan permasalahan fitur balasan yang sifatnya bercabang dan saling menyambung antara satu node dengan node lainnya sehingga membentuk struktur yang seperti pohon.
- Fitur `Draf Kicauan` yang diselesaikan dengan menggunakan `ADT Stack` karena pada fitur ini pengguna dapat melihat draf terakhirya dan melakukan aksi lanjutan seperti hapus, simpan, atau bahkan menerbitkannya sehingga mengubah statusnya dari draf kicauan menjadi kicauan yang sebenarnya.
- Fitur `Utas` yang diselesaikan dengan menggunakan `ADT List dengan Struktur Data Berkait` karena sifat utas yang berkaitan antara satu dengan yang lainnya, dapat dibuat kicauan sambungan terhadap utas tersebut. Setiap penghapusan juga menyebabkan indeks utas menjadi menurun sehingga secara tidak langsung menggambar struktur data list linier.
- Fitur `Simpan dan Muat` yang diselesaikan dengan menggunakan `ADT Mesin Kata atau ADT Mesin Karakter` yang telah dimodifikasi untuk membaca teks dari file secara per baris dan sebaliknya.

Fitur-fitur tambahan juga dibuat, yaitu :
- Fitur `Tagar` yang diintegrasikan bersama dengan fitur kicauan dengan menggunakan `ADT HashTable` sehingga pengguna dapat mencari kicauan dengan tagar tertentu.
- Fitur `Nomor HP` yang dimodifikasi sehingga pengguna dapat melakukan modifikasi informasi nomor HP pada profilnya dengan jumlah angka yang tak terhingga. Fitur ini tidak menggunakan ADT khusus, namun hanya melakukan modifikasi dengan fungsi `realloc`, `calloc`, dan `malloc`.

 Perintah-perintah yang tersedia pada program ini, sebagai berikut:
 - `MASUK` merupakan _command_ yang bertujuan untuk masuk pada akun pengguna tertentu yang telah terdaftar dan tersimpan pada list pengguna.
 - `DAFTAR` merupakan _command_ yang memberikan kesempatan bagi pengguna program untuk melakukan pendaftaran akun baru.
 - `TUTUP_PROGRAM` merupakan _command_ yang dapat digunakan untuk melakukan terminasi program jika penggunaan program dirasa sudah cukup oleh pengguna.
 - `UBAH_FOTO_PROFI`L merupakan _command_ yang bertujuan untuk mengubah foto profil yang dimiliki oleh seorang pengguna. Sebelum melakukan modifikasi, fitur ini akan terlebih dahulu menampilkan foto profil dari pengguna tersebut sebelum diubah. Fitur ini hanya dapat melakukan modifikasi foto profil akun sendiri dan tidak melakukan modifikasi pada akun pengguna lain. Fitur ini menerima masukan berupa matriks 10x10 yang berisi warna sebelum simbol, berupa kode “R”/”G”/”B” untuk menentukan warna simbol setelahnya merupakan warna merah, hijau, ataupun biru.
 - `GANTI_PROFIL` merupakan _command_ yang bertujuan untuk melakukan modifikasi informasi yang disimpan pada profil seorang pengguna, seperti bio akun, nomor HP, Weton. Sebelum melakukan modifikasi pada informasi profil, fitur ini akan menampilkan informasi profil pengguna saat ini.
 -` LIHAT_PROFIL [NAMA]` merupakan _command_  yang menerima satu parameter tambahan yaitu nama pengguna yang dituju untuk diberlakukan pada fitur ini. Fitur ini akan menampilkan informasi profil yang dimiliki oleh pengguna dengan nama yang dituju, dengan syarat bahwa jika pengguna yang dituju merupakan pengguna dengan jenis akun PUBLIK ataupun jika PRIVAT harus merupakan teman yang ingin melakukan aksi ini.
 - `ATUR_JENIS_AKUN` merupakan _command_ yang bertujuan untuk melakukan modifikasi jenis akun dari PUBLIK menjadi PRIVAT ataupun sebaliknya.
 - `DAFTAR_TEMAN` merupakan _command_ yang bertujuan untuk menampilkan teman-teman yang dimiliki oleh pengguna yang melakukan aksi ini.
 - HAPUS_TEMAN merupakan command untuk melakukan penghapusan teman dengan nama masukan spesifik pengguna yang hendak dihapus status pertemanannya.
 - `KICAU` merupakan _command_ untuk mengunggah sebuah kicauan. Perintah ini hanya bisa diakses ketika pengguna sudah masuk ke dalam sebuah akun. Kicauan ini mempunyai panjang maksimal 280 karakter, yang nantinya diunggah akan dimasukkan ke dalam sebuah list kicau, ID nya sesuai ID terakhir dari list kicau, datetime nya sesuai dengan waktu unggah, dan jumlah disukai dimulai dari nol. Selain itu, pengguna juga dimintai untuk memasukkan tagar dari kicauan tersebut, jika pengguna tidak memasukkan tagar, maka kicauan dianggap tidak memiliki tagar.
 - `KICAUAN` merupakan _command_ untuk melihat kicauan milik teman dan diri sendiri. Perintah ini cukup sederhana, cukup mengecek setiap kicauan di list kicau, apakah pengguna saat ini dan author dari kicauan berteman, jika mereka berteman, maka kicauan tersebut akan ditampilkan.
 - `SUKA_KICAUAN [IDKicau]` merupakan _command_ yang berfungsi untuk menyukai kicauan dengan ID IDKicau. Jika author dari kicauan yang hendak disukai privat namun belum berteman dengan pengguna saat ini, perintah tersebut akan ditolak. Akan tetapi jika author dari kicauan yang hendak disukai publik atau privat dan sudah berteman dengan pengguna saat ini, jumlah disukai dari kicauan tersebut bertambah 1.
 - `UBAH_KICAUAN [IDKicau]` merupakan command yang berfungsi untuk merubah sebuah kicauan dengan ID IDKicau. Adapun kicauan yang bisa diubah hanyalah kicauan milik pribadi, yaitu kicauan dengan author yang sama dengan pengguna saat ini.
 - `BALAS [IDKicau] [IDBalasan]` merupakan _command_ untuk melakukan balasan pada IDKicau tertentu dan dengan IDBalasan tertentu yang terdapat pada IDkicau tersebut. Balasan hanya dapat dibalas jika balasan yang hendak dibalas dibuat oleh akun yang bersifat publik atau memiliki teman dengan pengguna yang hendak membalas.
 - `BALASAN [IDKicau]` merupakan _command_ untuk menampilkan seluruh balasan yang terdapat pada IDKicau tertentu.
 - `HAPUS_BALASAN [IDKicau] [IDBalasan]` merupakan _command_ untuk melakukan aksi penghapusan sebuah balasan yang spesifik pada IDBalasan tertentu yang terdapat pada IDKicauan tertentu.
 - `BUAT_DRAF` merupakan _command_ untuk melakukan aksi pembuatan draf kicauan yang kemudian pengguna mendapatkan tiga pilihan, yaitu untuk melakukan SIMPAN untuk menyimpan draf tersebut, HAPUS untuk melakukan penghapus draf tersebut, dan TERBIT untuk melakukan penerbitan dan pengubahan status draf tersebut menjadi kicauan.
 - `LIHAT_DRAF` merupakan _command_ untuk melakukan aksi melihat draf terakhir yang dibuat oleh pengguna yang melakukan aksi tersebut. Kemudian, akan diberikan pilihan terhadap pengguna untuk melakukan aksi HAPUS jika ingin menghapus draf terakhir yang ditampilkan, UBAH jika ingin melakukan pengubahan terhadap konten dari draf tersebut, TERBIT untuk melakukan pengubahan status draf terakhir tersebut menjadi kicauan, dan KEMBALI untuk kembali ke menu pilihan lainnya tanpa melakukan aksi apapun terhadap draf terakhir yang ditampilkan.
 - `SIMPAN` merupakan _command_ untuk melakukan penyimpanan progress saat ini di sebuah folder yang berisi file config. Program akan meminta input dari user berupa folder yang nantinya akan digunakan untuk menyimpan progress saat ini. Jika folder belum ada, maka program akan otomatis membuat folder terlebih dahulu lalu melakukan penyimpanan.
 - `MUAT` merupakan _command_ untuk memuat kondisi dari folder yang berisi file config. Proses memuat ini akan mengganti seluruh data progress saat ini menjadi data sesuai file config yang dimuat. Command ini hanya bisa dipanggil ketika pengguna belum masuk ke dalam akun.
 - `CARI_KICAUAN [Tagar]` adalah _command_ yang digunakan ketika pengguna ingin mencari semua kicauan yang memiliki tagar berupa Tagar. Program nantinya akan membuat seluruh karakter di Tagar menjadi lowercase untuk alfabet, dan nantinya diproses di fungsi hash yang nantinya akan digunakan menjadi indeks dari tagar tersebut ditempatkan. Program akan menampilkan semua kicauan yang memiliki tagar Tagar, tanpa perlu memperhatikan apakah pengguna telah berteman dengan author dari kicauan tersebut.
...
   
## Panduan Penggunaan Program
Pertama, pastikan sudah melakukan _unzip_ folder dan kemudian buka terminal atas repository tersebut. Jika anda merupakan pengguna Windows, harap mengetik **wsl** pada terminal. Jika bukan, maka abaikan perintah sebelumnya. Jika anda sudah berada pada parent folder IF2110_TB_01_H, jalankan perintah sebagai berikut.
```shell
make
./main
```
Perintah `./main` untuk menjalankan program utama, sedangkan untuk menjalankan driver dapat disesuaikan dengan nama file .exe dari setiap driver. Contoh format: ./[nama file .exe]

## Pembagian Tugas
- Zachary Samuel T (13522016) : ADT listutas, Konfigurasi Utas, Fitur Utas
- Tazkia Nizami (13522032) : ADT Mesin Karakter, ADT Mesin Kata, ADT Graf Pertemanan, Fitur teman, Konfigurasi Pengguna
- M Athaullah Daffa Kusuma M (13522044) : ADT listkicauan, Konfigurasi Kicauan, Fitur Kicauan, Fitur Simpan dan Muat
- Elbert Chailes (13522045) : ADT listpengguna, ADT treebalasan, ADT stackdraf, ADT datetime, Fitur Pengguna, Fitur Balasan, Fitur Draf Kicauan, Fitur Profil, Konfigurasi Balasan, Konfigurasi Draf
- Kharris Khisunica (13522051) : -
  
## Daftar Fitur
- Fitur `Perintah` **SELESAI**
- Fitur `Inisialisasi/Pengguna` **SELESAI**
- Fitur `Pengguna` **SELESAI**
- Fitur `Profil` **SELESAI**
- Fitur `Teman` **SELESAI**
- Fitur `Permintaan Teman` **SELESAI**
- Fitur `Kicauan` **SELESAI**
- Fitur `Balasan` **SELESAI**
- Fitur `Draf Kicauan` **SELESAI**
- Fitur `Utas` **SELESAI**
- Fitur `Simpan dan Muat` **SELESAI**
- Fitur `Tagar` **SELESAI**
- Fitur `Nomor HP` **SELESAI**
