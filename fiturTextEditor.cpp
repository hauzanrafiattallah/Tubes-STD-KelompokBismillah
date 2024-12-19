#include "header.h"

// fitur Cursor

// Fungsi untuk pindah kursor ke kanan
void moveCursorRight(FileNode *selectedFile)
{
    // Pastikan file tidak kosong
    if (selectedFile->head == nullptr)
    {
        cout << "File kosong. Tidak ada karakter untuk dipindahkan.\n";
        return;
    }

    CharNode *temp = selectedFile->head;
    int currentPosition = 0;

    // Menelusuri linked list untuk mencapai posisi kursor saat ini
    while (temp != nullptr && currentPosition < selectedFile->cursorPosition)
    {
        temp = temp->next;
        currentPosition++;
    }

    // Pindah kursor ke kanan jika memungkinkan
    if (temp != nullptr && temp->next != nullptr)
    {
        selectedFile->cursorPosition++;
        cout << "Kursor dipindahkan ke kanan. Posisi saat ini: " << selectedFile->cursorPosition << "\n";
    }
    else
    {
        cout << "Kursor sudah di posisi paling kanan.\n";
    }

    // Tampilkan teks dengan kursor setelah berpindah
    displayFileContent(selectedFile);
}

// Fungsi untuk pindah kursor ke kiri
void moveCursorLeft(FileNode *selectedFile)
{
    if (selectedFile == nullptr || selectedFile->head == nullptr)
    {
        cout << "File kosong atau tidak valid.\n";
        return;
    }

    // Pastikan kursor tidak berada di posisi paling kiri
    if (selectedFile->cursorPosition == 0)
    {
        cout << "Kursor sudah di posisi paling kiri.\n";
        return;
    }

    selectedFile->cursorPosition--;
    cout << "Kursor dipindahkan ke kiri. Posisi saat ini: " << selectedFile->cursorPosition << "\n";

    // Tampilkan teks dengan kursor setelah berpindah
    displayFileContent(selectedFile);
}

// Menampilkan isi file dengan tanda kursor
void displayFileContent(FileNode *selectedFile)
{
    if (selectedFile->head == nullptr)
    {
        cout << "File kosong.\n";
        return;
    }

    CharNode *temp = selectedFile->head;
    int currentPosition = 0;

    cout << "Isi file:\n";

    // Tampilkan setiap karakter dengan tanda kursor
    while (temp != nullptr)
    {
        if (currentPosition == selectedFile->cursorPosition)
        {
            cout << "[" << temp->character << "]"; // Tampilkan kursor tepat di karakter terakhir
        }
        else
        {
            cout << temp->character; // Tampilkan karakter biasa
        }

        temp = temp->next;
        currentPosition++;
    }

    cout << "\n";
}


// Menghapus karakter di posisi kursor
void deleteCharacterAtCursor(FileNode *selectedFile)
{
    if (selectedFile == nullptr || selectedFile->head == nullptr)
    {
        cout << "File kosong atau tidak valid. Tidak ada karakter untuk dihapus.\n";
        return;
    }

    CharNode *temp = selectedFile->head;
    CharNode *prev = nullptr;
    int currentPosition = 0;

    // Menelusuri linked list untuk mencapai posisi kursor
    while (temp != nullptr && currentPosition < selectedFile->cursorPosition)
    {
        prev = temp;
        temp = temp->next;
        currentPosition++;
    }

    // Jika kursor berada di luar batas atau tidak ada karakter yang cocok
    if (temp == nullptr)
    {
        cout << "Tidak ada karakter di posisi kursor.\n";
        return;
    }

    // Menghapus node di posisi kursor
    if (prev == nullptr)
    {
        // Menghapus karakter pertama
        selectedFile->head = temp->next;
    }
    else
    {
        // Menghapus karakter di posisi lainnya
        prev->next = temp->next;
    }

    delete temp;
    temp = nullptr; // Pastikan pointer tidak lagi menunjuk ke memori yang telah dihapus

    // Update posisi kursor
    if (selectedFile->cursorPosition > 0)
    {
        selectedFile->cursorPosition--;
    }

    cout << "Karakter berhasil dihapus. Posisi kursor saat ini: " << selectedFile->cursorPosition << "\n";

    // Tampilkan teks dengan kursor setelah karakter dihapus
    displayFileContent(selectedFile);
}


// Menyisipkan teks setelah posisi kursor
void insertTextAfterCursor(FileNode *selectedFile)
{
    if (selectedFile == nullptr || selectedFile->head == nullptr)
    {
        cout << "File kosong atau tidak valid. Tidak ada tempat untuk menyisipkan teks.\n";
        return;
    }

    cout << "Masukkan teks untuk disisipkan setelah posisi kursor:\n";
    string textToInsert;
    getline(cin, textToInsert);

    CharNode *temp = selectedFile->head;
    int currentPosition = 0;

    // Menelusuri linked list hingga posisi kursor
    while (temp != nullptr && currentPosition < selectedFile->cursorPosition)
    {
        temp = temp->next;
        currentPosition++;
    }

    // Menambahkan setiap karakter dalam teks ke linked list
    CharNode *lastInsertedNode = temp;
    for (int i = 0; i < textToInsert.length(); ++i)
    {
        char c = textToInsert[i]; // Mengambil karakter berdasarkan indeks

        CharNode *newChar = new CharNode;
        newChar->character = c;

        // Menyisipkan setelah node saat ini
        newChar->next = lastInsertedNode->next;
        lastInsertedNode->next = newChar;

        lastInsertedNode = newChar; // Pindahkan ke node baru
    }

    // Perbarui posisi kursor setelah teks yang disisipkan
    selectedFile->cursorPosition += textToInsert.length();

    cout << "Teks berhasil disisipkan. Posisi kursor saat ini: " << selectedFile->cursorPosition << "\n";

    // Tampilkan isi file dengan kursor
    displayFileContent(selectedFile);
}
