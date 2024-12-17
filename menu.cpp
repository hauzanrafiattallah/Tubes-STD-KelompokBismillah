#include "header.h"

// Menampilkan menu utama
void displayMainMenu()
{
  cout << "\n=================== TEXT EDITOR ===================\n";
  cout << "1. Tambahkan file baru\n";
  cout << "2. Tampilkan semua file\n";
  cout << "0. Keluar\n";
  cout << "===================================================\n";
  cout << "Pilih opsi: ";
}

// Menampilkan menu file
void displayFileMenu()
{
  cout << "\n================= FILE MENU =================\n";
  cout << "1. Tambahkan teks\n";
  cout << "2. Tampilkan isi file\n";
  cout << "3. Pindah kursor\n";
  cout << "4. Hapus karakter di posisi kursor\n";
  cout << "5. Sisipkan setelah posisi kursor\n";
  cout << "6. Pilih teks\n";
  cout << "7. Salin teks\n";
  cout << "8. Tempelkan teks\n";
  cout << "9. Potong teks\n";
  cout << "10. Cari dan Ganti Teks\n";
  cout << "11. Undo\n";
  cout << "12. Redo\n";
  cout << "0. Kembali ke menu utama\n";
  cout << "=============================================\n";
  cout << "Pilih opsi: ";
}
