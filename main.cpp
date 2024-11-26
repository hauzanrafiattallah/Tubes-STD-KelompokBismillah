#include "header.h"

int main() {
    List L;
    Stack undoStack, redoStack;
    Queue clipboardQueue;

    createList(L);
    createStack(undoStack);
    createStack(redoStack);
    createQueue(clipboardQueue);

    int pilihan, nomorBaris;
    string teks;

    do {
        cout << "\nMenu Editor Teks:\n";
        cout << "1. Tambahkan Baris\n";
        cout << "2. Hapus Baris\n";
        cout << "3. Tampilkan dari Awal\n";
        cout << "4. Tampilkan dari Akhir\n";
        cout << "5. Undo\n";
        cout << "6. Redo\n";
        cout << "7. Salin Baris\n";
        cout << "8. Tempel Baris\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan nomor baris: ";
                cin >> nomorBaris;
                cin.ignore();
                cout << "Masukkan teks: ";
                getline(cin, teks);
                insertLine(L, teks, nomorBaris);
                pushStack(undoStack, "INSERT", teks, nomorBaris);
                kosongkanRedo(redoStack); // Kosongkan redo setelah aksi baru
                break;

            case 2:
                cout << "Masukkan nomor baris untuk dihapus: ";
                cin >> nomorBaris;
                deleteBarisDenganUndo(L, undoStack, nomorBaris);
                kosongkanRedo(redoStack); // Kosongkan redo setelah aksi baru
                break;

            case 3:
                cout << "Teks dari awal:\n";
                displayListFromFront(L);
                break;

            case 4:
                cout << "Teks dari akhir:\n";
                displayListFromBack(L);
                break;

            case 5:
                undo(L, undoStack, redoStack);
                break;

            case 6:
                redo(L, redoStack, undoStack);
                break;

            case 7:
                cout << "Masukkan nomor baris untuk disalin: ";
                cin >> nomorBaris;
                copyLine(L, clipboardQueue, nomorBaris);
                break;

            case 8:
                cout << "Masukkan nomor baris untuk menempelkan teks: ";
                cin >> nomorBaris;
                pasteLine(L, clipboardQueue, nomorBaris);
                break;

            case 0:
                cout << "Keluar dari program...\n";
                break;

            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}
