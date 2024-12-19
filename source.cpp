#include "header.h"

// Mendapatkan file berdasarkan index
FileNode *getFileByIndex(TextEditor &editor, int index)
{
    if (index <= 0)
        return nullptr;

    FileNode *current = editor.files;
    int currentIndex = 1;
    while (current != nullptr)
    {
        if (currentIndex == index)
        {
            return current;
        }
        current = current->next;
        currentIndex++;
    }
    return nullptr;
}

// Menemukan file berdasarkan nama
FileNode *findFile(TextEditor &editor, string &fileName)
{
    FileNode *temp = editor.files;
    while (temp != nullptr)
    {
        if (temp->fileName == fileName)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr; // Jika file tidak ditemukan
}

// Menambahkan teks ke dalam file setelah posisi kursor
void addTextToFile(TextEditor &editor, FileNode *selectedFile)
{
    cout << "Masukkan paragraf (akhiri dengan ENTER dua kali):\n";

    string paragraph, line;
    bool firstEmptyLine = false;

    while (true)
    {
        getline(cin, line);

        // Jika pengguna menekan Enter tanpa teks
        if (line.empty())
        {
            if (firstEmptyLine)
            {
                // Jika ini adalah Enter kedua, keluar dari loop
                break;
            }
            // Tandai bahwa ini adalah Enter pertama
            firstEmptyLine = true;
        }
        else
        {
            // Jika input bukan kosong, tambahkan ke paragraf
            firstEmptyLine = false;   // Reset jika ada teks setelah Enter pertama
            paragraph += line + '\n'; // Tambahkan teks dan newline
        }
    }

    // Hapus newline terakhir di paragraf (karena Enter kedua tidak diinginkan)
    if (!paragraph.empty() && paragraph.back() == '\n')
    {
        paragraph.pop_back(); // Menghapus newline terakhir
    }

    // Menambahkan karakter satu per satu ke file
    for (size_t i = 0; i < paragraph.length(); ++i)
    {
        addCharacterToFile(editor, selectedFile->fileName, paragraph[i]);
    }

    // Pindahkan kursor ke akhir file setelah menambahkan teks
    CharNode *temp = selectedFile->head;
    int currentPosition = 0;
    while (temp != nullptr)
    {
        temp = temp->next;
        currentPosition++;
    }

    // Setel posisi kursor ke posisi akhir
    selectedFile->cursorPosition = currentPosition;

    // Pindahkan kursor ke kiri satu kali (jika memungkinkan)
    if (selectedFile->cursorPosition > 0)
    {
        selectedFile->cursorPosition--;
    }

    cout << "Paragraf berhasil ditambahkan ke file \"" << selectedFile->fileName << "\".\n";
}

// Fungsi untuk menambah karakter dan menyimpan operasi untuk undo
void tambahCharacterWithUndo(FileNode &file, char character)
{
    // Alokasi memori baru untuk node karakter
    CharNode *newNode = new CharNode;
    if (newNode == nullptr) // Cek apakah alokasi berhasil
    {
        cout << "Error: Gagal mengalokasikan memori.\n";
        return;
    }

    newNode->character = character;
    newNode->next = nullptr;

    if (file.head == nullptr) // Jika file kosong
    {
        file.head = newNode;     // Node pertama menjadi head
        file.cursorPosition = 0; // Set kursor ke posisi awal
    }
    else
    {
        // Cari node terakhir dalam linked list
        CharNode *current = file.head;
        int currentPosition = 0; // Hitung posisi kursor

        while (current->next != nullptr)
        {
            current = current->next;
            currentPosition++;
        }

        current->next = newNode;                   // Tambahkan node di akhir
        file.cursorPosition = currentPosition + 1; // Update kursor ke posisi terakhir
    }

    // Simpan karakter ke undo stack
    push(file.undoRedo.undoStack, character);

    // Kosongkan redo queue karena operasi baru terjadi
    while (!isQueueEmpty(file.undoRedo.redoQueue))
    {
        dequeue(file.undoRedo.redoQueue);
    }

    cout << "Karakter '" << character << "' berhasil ditambahkan.\n";
}

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
    cout << "5. Sisipkan teks setelah posisi kursor\n";
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
