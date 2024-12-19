#include "header.h"

int main()
{
    TextEditor editor;
    createTeksEditor(editor);

    int choice = -1;

    // Menu utama
    while (choice != 0)
    {
        displayMainMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            string fileName;
            cout << "Masukkan nama file baru: ";
            getline(cin, fileName);
            addFile(editor, fileName);
            cout << "File \"" << fileName << "\" berhasil ditambahkan.\n";
        }
        else if (choice == 2)
        {
            int fileIndex = selectFile(editor);

            if (fileIndex != -1)
            { // Jika pemilihan file tidak dibatalkan
                FileNode *selectedFile = getFileByIndex(editor, fileIndex);

                int fileChoice = -1;
                while (fileChoice != 0)
                {
                    displayFileMenu();
                    cin >> fileChoice;
                    cin.ignore();

                    if (fileChoice == 1)
                    {
                        addTextToFile(editor, selectedFile);
                    }
                    else if (fileChoice == 2)
                    {
                        cout << "Isi file \"" << selectedFile->fileName << "\":\n";
                        displayFileContent(selectedFile);
                    }
                    else if (fileChoice == 3)
                    {
                        int cursorChoice;
                        cout << "Pindah kursor:\n";
                        cout << "1. Pindah ke kanan\n";
                        cout << "2. Pindah ke kiri\n";
                        cin >> cursorChoice;
                        cin.ignore();

                        if (cursorChoice == 1)
                        {
                            moveCursorRight(selectedFile);
                        }
                        else if (cursorChoice == 2)
                        {
                            moveCursorLeft(selectedFile);
                        }
                        else
                        {
                            cout << "Pilihan tidak valid.\n";
                        }
                    }
                    else if (fileChoice == 4)
                    {
                        deleteCharacterAtCursor(selectedFile);
                    }
                    else if (fileChoice == 5)
                    {
                        insertTextAfterCursor(selectedFile);
                    }
                    else if (fileChoice == 6)
                    {
                        int startPos, endPos;
                        cout << "Masukkan posisi awal teks yang ingin dipilih: ";
                        cin >> startPos;
                        cout << "Masukkan posisi akhir teks yang ingin dipilih: ";
                        cin >> endPos;
                        selectText(selectedFile, startPos, endPos);
                    }
                    else if (fileChoice == 7)
                    {
                        copyText(selectedFile);
                    }
                    else if (fileChoice == 8)
                    {
                        pasteText(selectedFile);
                    }
                    else if (fileChoice == 9)
                    {
                        int startPos, endPos;
                        cout << "Masukkan posisi awal teks yang ingin dipotong: ";
                        cin >> startPos;
                        cout << "Masukkan posisi akhir teks yang ingin dipotong: ";
                        cin >> endPos;
                        cutText(selectedFile, startPos, endPos);
                    }
                    else if (fileChoice == 10)
                    {
                        string searchText, replacementText;
                        int startPos = 0;

                        cout << "Masukkan teks yang ingin dicari: ";
                        getline(cin, searchText);

                        cout << "Masukkan teks pengganti: ";
                        getline(cin, replacementText);

                        replaceText(selectedFile, searchText, replacementText, startPos);
                    }
                    else if (fileChoice == 11)
                    {
                        undo(selectedFile);
                        cout << "Undo berhasil.\n";
                    }
                    else if (fileChoice == 12)
                    {
                        redo(selectedFile);
                        cout << "Redo berhasil.\n";
                    }
                    else if (fileChoice == 0)
                    {
                        cout << "Kembali ke menu utama.\n";
                    }
                    else
                    {
                        cout << "Pilihan tidak valid.\n";
                    }
                }
            }
            else
            {
                cout << "Pemilihan file dibatalkan atau tidak valid.\n";
            }
        }
        else if (choice == 0)
        {
            cout << "Terima kasih telah menggunakan editor teks ini. Sampai jumpa!\n";
        }
        else
        {
            cout << "Pilihan tidak valid.\n";
        }
    }

    return 0;
}
