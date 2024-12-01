#include "header.h"

int main() {
    List editor;
    Stack undoStack, redoStack;
    Queue clipboardQueue;

    createList(editor);
    createStack(undoStack);
    createStack(redoStack);
    createQueue(clipboardQueue);

    int choice;
    do {
        cout << "\n=================== TEXT EDITOR ===================\n";
        cout << "1. Tambahkan teks pada baris tertentu\n";
        cout << "2. Hapus teks pada baris tertentu\n";
        cout << "3. Tampilkan teks dari awal ke akhir\n";
        cout << "4. Tampilkan teks dari akhir ke awal\n";
        cout << "5. Undo aksi terakhir\n";
        cout << "6. Redo aksi terakhir\n";
        cout << "7. Salin baris ke clipboard\n";
        cout << "8. Tempel teks dari clipboard ke baris tertentu\n";
        cout << "9. Hapus redo stack\n";
        cout << "10. Tambah karakter di posisi kursor\n";
        cout << "11. Hapus karakter di posisi kursor\n";
        cout << "12. Gerakkan kursor (kiri/kanan)\n";
        cout << "13. Tampilkan posisi kursor\n";
        cout << "14. Aktifkan kursor\n";
        cout << "0. Keluar\n";
        cout << "===================================================\n";
        cout << "Pilih opsi: ";
        cin >> choice;
        cin.ignore(); // Membersihkan buffer newline

        switch (choice) {
            case 1: {
                string text;
                int lineNumber;
                cout << "Masukkan teks: ";
                getline(cin, text);
                cout << "Masukkan nomor baris: ";
                cin >> lineNumber;
                insertLine(editor, text, lineNumber);
                pushStack(undoStack, "INSERT", text, lineNumber);
                clearRedo(redoStack);
                cout << "Teks berhasil ditambahkan.\n";
                break;
            }
            case 2: {
                int lineNumber;
                cout << "Masukkan nomor baris yang ingin dihapus: ";
                cin >> lineNumber;
                deleteLineWithUndo(editor, undoStack, lineNumber);
                clearRedo(redoStack);
                cout << "Baris berhasil dihapus.\n";
                break;
            }
            case 3:
                cout << "\nTeks dari awal ke akhir:\n";
                displayListFromFront(editor);
                break;
            case 4:
                cout << "\nTeks dari akhir ke awal:\n";
                displayListFromBack(editor);
                break;
            case 5:
                undo(editor, undoStack, redoStack);
                break;
            case 6:
                redo(editor, redoStack, undoStack);
                break;
            case 7: {
                int lineNumber;
                cout << "Masukkan nomor baris yang ingin disalin: ";
                cin >> lineNumber;
                copyLine(editor, clipboardQueue, lineNumber);
                break;
            }
            case 8: {
                int lineNumber;
                cout << "Masukkan nomor baris untuk menempelkan teks: ";
                cin >> lineNumber;
                pasteLine(editor, clipboardQueue, lineNumber);
                break;
            }
            case 9:
                clearRedo(redoStack);
                cout << "Redo stack berhasil dikosongkan.\n";
                break;
            case 10: {
                char karakter;
                cout << "Masukkan karakter untuk ditambahkan: ";
                cin >> karakter;
                insertCharacter(editor, karakter);
                break;
            }
            case 11: {
                deleteCharacterAtCursor(editor);
                break;
            }
            case 12: {
                string direction;
                cout << "Masukkan arah (l untuk kiri, r untuk kanan): ";
                cin >> direction;
                moveCursor(editor, direction);
                break;
            }
            case 13:
                displayCursorPosition(editor);
                break;
            case 14:{
                string position;
                cout << "Pilih posisi kursor ('start' untuk awal, 'end' untuk akhir): ";
                cin >> position;
                activateCursor(editor, position);
                break;
            }
            case 0:
                cout << "Terima kasih telah menggunakan editor teks ini. Sampai jumpa!\n";
                break;
            default:
                cout << "Opsi tidak valid. Silakan coba lagi.\n";
        }
    } while (choice != 0);

    return 0;
}
