#include "header.h"

int main() {
    List editor;
    Stack undoStack, redoStack;
    Queue clipboardQueue;

    // Inisialisasi editor, undo stack, redo stack, dan clipboard queue
    createList(editor);
    createStack(undoStack);
    createStack(redoStack);
    createQueue(clipboardQueue);

    int choice;
    do {
        // Menampilkan menu editor yang lebih terstruktur
        cout << "\n=================== TEXT EDITOR ===================\n";
        cout << "Pilih aksi yang ingin Anda lakukan:\n";
        cout << "\n--- Pengeditan Teks ---\n";
        cout << "1. Tambahkan teks pada baris tertentu\n";
        cout << "2. Hapus teks pada baris tertentu\n";
        cout << "3. Tampilkan teks\n";
        
        cout << "\n--- Undo/Redo ---\n";
        cout << "5. Undo aksi terakhir\n";
        cout << "6. Redo aksi terakhir\n";
        
        cout << "\n--- Clipboard ---\n";
        cout << "7. Salin baris ke clipboard\n";
        cout << "8. Tempel teks dari clipboard ke baris tertentu\n";
        
        cout << "\n--- Kursor ---\n";
        cout << "9. Tambah karakter di posisi kursor\n";
        cout << "10. Hapus karakter di posisi kursor\n";
        cout << "11. Gerakkan kursor (kiri/kanan)\n";
        cout << "12. Tampilkan posisi kursor\n";
        cout << "13. Aktifkan kursor\n";
        
        cout << "\n--- Keluar ---\n";
        cout << "0. Keluar\n";
        cout << "===================================================\n";
        cout << "Pilih opsi (masukkan angka sesuai pilihan): ";
        cin >> choice;
        cin.ignore(); // Membersihkan buffer newline setelah membaca angka

        switch (choice) {
            case 1: {
                string text;
                int lineNumber;
                cout << "Masukkan teks yang ingin ditambahkan: ";
                getline(cin, text);
                cout << "Masukkan nomor baris di mana teks akan ditambahkan: ";
                cin >> lineNumber;
                insertLine(editor, text, lineNumber);  // Menambahkan teks
                pushStack(undoStack, "INSERT", text, lineNumber);  // Simpan aksi untuk undo
                clearRedo(redoStack);  // Kosongkan redo stack setelah aksi baru
                cout << "Teks berhasil ditambahkan pada baris " << lineNumber << ".\n";
                break;
            }
            case 2: {
                int lineNumber;
                cout << "Masukkan nomor baris yang ingin dihapus: ";
                cin >> lineNumber;
                deleteLineWithUndo(editor, undoStack, lineNumber);  // Hapus baris dengan undo
                clearRedo(redoStack);  // Kosongkan redo stack
                cout << "Baris " << lineNumber << " berhasil dihapus.\n";
                break;
            }
            case 3:
                cout << "\nTeks:\n";
                tampilkanTeks(editor);  // Menampilkan teks
                break;
            case 5:
                undo(editor, undoStack, redoStack);  // Melakukan undo
                break;
            case 6:
                redo(editor, redoStack, undoStack);  // Melakukan redo
                break;
            case 7: {
                int lineNumber;
                cout << "Masukkan nomor baris yang ingin disalin: ";
                cin >> lineNumber;
                copyLine(editor, clipboardQueue, lineNumber);  // Menyalin baris ke clipboard
                cout << "Baris " << lineNumber << " berhasil disalin ke clipboard.\n";
                break;
            }
            case 8: {
                int lineNumber;
                cout << "Masukkan nomor baris untuk menempelkan teks: ";
                cin >> lineNumber;
                pasteLine(editor, clipboardQueue, lineNumber);  // Menempelkan teks dari clipboard
                cout << "Teks berhasil ditempelkan pada baris " << lineNumber << ".\n";
                break;
            }
            case 9: {
                char karakter;
                cout << "Masukkan karakter untuk ditambahkan di posisi kursor: ";
                cin >> karakter;
                insertCharacter(editor, karakter);  // Menambah karakter pada posisi kursor
                cout << "Karakter '" << karakter << "' berhasil ditambahkan.\n";
                break;
            }
            case 10:
                deleteCharacterAtCursor(editor);  // Menghapus karakter pada posisi kursor
                cout << "Karakter di posisi kursor berhasil dihapus.\n";
                break;
            case 11: {
                string direction;
                cout << "Masukkan arah gerakan kursor ('k' untuk kiri, 'r' untuk kanan): ";
                cin >> direction;
                if (direction == "k" || direction == "r") {
                    moveCursor(editor, direction);  // Menggerakkan kursor
                    cout << "Kursor berhasil digerakkan ke " << (direction == "k" ? "kiri" : "kanan") << ".\n";
                } else {
                    cout << "Arah tidak valid. Gunakan 'k' untuk kiri atau 'r' untuk kanan.\n";
                }
                break;
            }
            case 12:
                displayCursorPosition(editor);  // Menampilkan posisi kursor
                break;
            case 13: {
                string position;
                cout << "Pilih posisi kursor ('start' untuk awal, 'end' untuk akhir): ";
                cin >> position;
                if (position == "start" || position == "end") {
                    activateCursor(editor, position);  // Mengaktifkan kursor di posisi tertentu
                    cout << "Kursor berhasil dipindahkan ke " << position << ".\n";
                } else {
                    cout << "Posisi tidak valid. Gunakan 'start' atau 'end'.\n";
                }
                break;
            }
            case 0:
                cout << "Terima kasih telah menggunakan editor teks ini. Sampai jumpa!\n";
                break;
            default:
                cout << "Opsi tidak valid. Silakan coba lagi.\n";
        }
    } while (choice != 0);  // Loop hingga pengguna memilih untuk keluar

    return 0;
}
