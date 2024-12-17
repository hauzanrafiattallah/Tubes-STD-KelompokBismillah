#include "header.h"
int main() {
    TextEditor editor;
    initializeEditor(editor);

    int choice;
    do {
        displayMainMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string fileName;
                cout << "Masukkan nama file baru: ";
                getline(cin, fileName);
                addFile(editor, fileName);
                cout << "File \"" << fileName << "\" berhasil ditambahkan.\n";
                break;
            }
            case 2: {
                int fileIndex = selectFile(editor);
                if (fileIndex == -1) break;

                FileNode* selectedFile = getFileByIndex(editor, fileIndex);

                int fileChoice;
                do {
                    displayFileMenu();
                    cin >> fileChoice;
                    cin.ignore();

                    switch (fileChoice) {
                        case 1:
                            addTextToFile(editor, selectedFile);
                            break;
                        case 2:
                            cout << "Isi file \"" << selectedFile->fileName << "\":\n";
                            displayFileContent(selectedFile);
                            break;
                        case 3:
                            int cursorChoice;
                            cout << "Pindah kursor:\n";
                            cout << "1. Pindah ke kanan\n";
                            cout << "2. Pindah ke kiri\n";
                            cin >> cursorChoice;
                            cin.ignore();
                            if (cursorChoice == 1) {
                                moveCursorRight(selectedFile);
                            } else if (cursorChoice == 2) {
                                moveCursorLeft(selectedFile);
                            } else {
                                cout << "Pilihan tidak valid.\n";
                            }
                            break;
                        case 4: // Hapus karakter di posisi kursor
                            deleteCharacterAtCursor(selectedFile);
                            break;
                        case 5: // Sisipkan teks setelah posisi kursor
                            insertTextAfterCursor(selectedFile);
                            break;
                        case 6: { // Pilih teks
                            int startPos, endPos;
                            cout << "Masukkan posisi awal teks yang ingin dipilih: ";
                            cin >> startPos;
                            cout << "Masukkan posisi akhir teks yang ingin dipilih: ";
                            cin >> endPos;
                            selectText(selectedFile, startPos, endPos);
                            break;
                        }
                        case 7: { // Salin teks
                            copyText(selectedFile);
                            break;
                        }
                        case 8:
                            {// Tempelkan teks
                            pasteText(selectedFile);
                            break;
                        }
                        case 9: {  // Potong teks
                            int startPos, endPos;
                            cout << "Masukkan posisi awal teks yang ingin dipotong: ";
                            cin >> startPos;
                            cout << "Masukkan posisi akhir teks yang ingin dipotong: ";
                            cin >> endPos;
                            cutText(selectedFile,startPos,endPos);
                            break;
                        }
                        case 10: { // Find and Replace
                            std::string searchText, replacementText;
                            int startPos = 0; // Default posisi awal pencarian

                            std::cout << "Masukkan teks yang ingin dicari: ";
                            std::getline(std::cin, searchText);

                            std::cout << "Masukkan teks pengganti: ";
                            std::getline(std::cin, replacementText);

                            replaceText(selectedFile, searchText, replacementText, startPos);
                            break;
                        }
                         case 11: { // Undo
                            undo(selectedFile);
                            cout << "Undo berhasil.\n";
                            break;
                        }
                        case 12: { // Redo
                            redo(selectedFile);
                            cout << "Redo berhasil.\n";
                            break;
                        }
                        case 0:
                            cout << "Kembali ke menu utama.\n";
                            break;
                        default:
                            cout << "Pilihan tidak valid.\n";
                    }
                } while (fileChoice != 0);
                break;
            }
            case 0:
                cout << "Terima kasih telah menggunakan editor teks ini. Sampai jumpa!\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 0);

    return 0;
}
