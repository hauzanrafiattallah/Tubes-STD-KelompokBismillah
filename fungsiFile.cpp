#include "header.h"

// Inisialisasi editor teks
void createTeksEditor(TextEditor &editor)
{
    editor.files = nullptr; // Set editor.files ke nullptr
}

// Menambahkan file baru
void addFile(TextEditor &editor, string &fileName)
{
    FileNode *newFile = new FileNode;
    newFile->fileName = fileName;
    newFile->head = nullptr;                  // File kosong di awal
    newFile->cursorPosition = 0;              // Posisi kursor awal
    newFile->clipboard = "";                  // Clipboard kosong
    createStack(newFile->cutBuffer);          // Inisialisasi cutBuffer
    createStack(newFile->undoRedo.undoStack); // Inisialisasi undo stack
    createQueue(newFile->undoRedo.redoQueue); // Inisialisasi redo queue
    newFile->next = editor.files;             // Sambungkan file baru ke linked list
    editor.files = newFile;                   // Update head
}

// Memilih file dari daftar
int selectFile(TextEditor &editor)
{
    if (editor.files == nullptr) // Jika belum ada file
    {
        cout << "Tidak ada file yang tersedia.\n";
        return -1;
    }

    cout << "Daftar file yang tersedia:\n";
    displayFiles(editor); // Menampilkan file

    cout << "Pilih nomor file (0 untuk batal): ";
    int choice;
    cin >> choice;
    cin.ignore(); // Bersihkan buffer input

    if (choice == 0)
    {
        cout << "Pemilihan file dibatalkan.\n";
        return -1;
    }

    FileNode *file = getFileByIndex(editor, choice);
    if (file == nullptr)
    {
        cout << "Error: File tidak valid.\n";
        return -1;
    }

    return choice;
}
// Menampilkan daftar file
void displayFiles(TextEditor &editor)
{
    if (editor.files == nullptr)
    {
        cout << "Tidak ada file yang tersedia.\n";
        return;
    }

    int index = 1;
    FileNode *temp = editor.files;
    while (temp != nullptr)
    {
        cout << index << ". " << temp->fileName << "\n";
        temp = temp->next;
        index++;
    }
}
// Menambahkan karakter ke file tertentu
void addCharacterToFile(TextEditor &editor, string &fileName, char character)
{
    FileNode *file = findFile(editor, fileName);
    if (file != nullptr)
    {
        CharNode *newChar = new CharNode;
        newChar->character = character;
        newChar->next = nullptr;

        // Menambahkan karakter ke linked list file
        if (file->head == nullptr)
        {
            file->head = newChar; // Jika file kosong
        }
        else
        {
            CharNode *temp = file->head;
            while (temp->next != nullptr)
            {
                temp = temp->next; // Menelusuri ke akhir linked list
            }
            temp->next = newChar; // Tambahkan karakter baru di akhir
        }

        // Simpan operasi ke stack undo
        push(file->undoRedo.undoStack, character);

        // Kosongkan redo queue jika ada operasi baru
        while (!isQueueEmpty(file->undoRedo.redoQueue))
        {
            dequeue(file->undoRedo.redoQueue); // Hapus data redo yang tidak relevan
        }

        // Update posisi kursor ke karakter terakhir
        CharNode *temp = file->head;
        int position = 0;
        while (temp->next != nullptr)
        {
            temp = temp->next;
            position++;
        }
        file->cursorPosition = position; // Set kursor ke karakter terakhir
    }
    else
    {
        cout << "Error: File tidak ditemukan.\n";
    }
}

// Fungsi untuk memilih teks berdasarkan posisi awal dan akhir
void selectText(FileNode *selectedFile, int startPos, int endPos)
{
    if (selectedFile == nullptr || selectedFile->head == nullptr)
    {
        cout << "File kosong atau tidak valid.\n";
        return;
    }

    if (startPos < 0 || endPos < startPos)
    {
        cout << "Posisi yang dimasukkan tidak valid.\n";
        return;
    }

    // Memastikan posisi akhir tidak lebih dari panjang file
    int fileLength = 0;
    CharNode *temp = selectedFile->head;
    while (temp != nullptr)
    {
        fileLength++;
        temp = temp->next;
    }

    if (endPos >= fileLength)
    {
        cout << "Posisi akhir melebihi panjang file. Maksimal posisi akhir: " << fileLength - 1 << endl;
        return;
    }

    // Mulai menelusuri karakter dari posisi awal
    temp = selectedFile->head;
    int currentPosition = 0;
    string selectedText;

    // Menemukan posisi awal
    while (temp != nullptr && currentPosition < startPos)
    {
        temp = temp->next;
        currentPosition++;
    }

    // Menyusun teks yang dipilih dari startPos hingga endPos
    while (temp != nullptr && currentPosition <= endPos)
    {
        selectedText += temp->character;
        temp = temp->next;
        currentPosition++;
    }

    // Menyimpan teks yang dipilih ke clipboard
    selectedFile->clipboard = selectedText;
    cout << "Teks berhasil dipilih: \"" << selectedText << "\"\n";
}

// Menyalin teks ke clipboard
void copyText(FileNode *selectedFile)
{
    if (selectedFile == nullptr || selectedFile->clipboard.empty())
    {
        cout << "Tidak ada teks yang dipilih untuk disalin.\n";
        return;
    }

    // Teks yang disalin sudah ada di clipboard
    cout << "Teks berhasil disalin ke clipboard: \"" << selectedFile->clipboard << "\"\n";
}

// Menempelkan teks dari clipboard setelah posisi kursor
void pasteText(FileNode *selectedFile)
{
    if (selectedFile == nullptr || selectedFile->head == nullptr)
    {
        cout << "File kosong atau tidak valid.\n";
        return;
    }

    if (selectedFile->clipboard.empty())
    {
        cout << "Clipboard kosong. Tidak ada teks yang dapat ditempelkan.\n";
        return;
    }

    string textToPaste = selectedFile->clipboard;

    CharNode *temp = selectedFile->head;
    int currentPosition = 0;

    // Menelusuri hingga posisi kursor
    while (temp != nullptr && currentPosition < selectedFile->cursorPosition)
    {
        temp = temp->next;
        currentPosition++;
    }

    CharNode *lastInsertedNode = temp;

    // Menyisipkan setiap karakter dalam teks dari clipboard
    for (int i = 0; i < textToPaste.length(); ++i)
    {
        char c = textToPaste[i]; // Mengakses karakter berdasarkan indeks

        CharNode *newChar = new CharNode;
        newChar->character = c;

        // Hubungkan node baru
        newChar->next = lastInsertedNode->next;
        lastInsertedNode->next = newChar;

        // Perbarui node terakhir
        lastInsertedNode = newChar;
    }

    // Perbarui posisi kursor
    selectedFile->cursorPosition += textToPaste.length();
    cout << "Teks berhasil ditempelkan.\n";

    // Tampilkan file dengan kursor
    displayFileContent(selectedFile);
}

// Memotong teks dari posisi startPos hingga endPos
void cutText(FileNode *selectedFile, int startPos, int endPos)
{
    if (selectedFile == nullptr || selectedFile->head == nullptr)
    {
        cout << "File kosong atau tidak valid.\n";
        return;
    }

    if (startPos < 0 || endPos < startPos)
    {
        cout << "Posisi yang dimasukkan tidak valid.\n";
        return;
    }

    // Pastikan endPos tidak melebihi panjang file
    int fileLength = 0;
    CharNode *temp = selectedFile->head;
    while (temp != nullptr)
    {
        fileLength++;
        temp = temp->next;
    }

    if (endPos >= fileLength)
    {
        cout << "Posisi akhir melebihi panjang file. Maksimal posisi akhir: " << fileLength - 1 << endl;
        return;
    }

    // Salin teks ke clipboard
    string cutText;
    temp = selectedFile->head;
    int currentPosition = 0;

    while (temp != nullptr && currentPosition < startPos)
    {
        temp = temp->next;
        currentPosition++;
    }

    while (temp != nullptr && currentPosition <= endPos)
    {
        cutText += temp->character;
        push(selectedFile->cutBuffer, temp->character);
        temp = temp->next;
        currentPosition++;
    }

    selectedFile->clipboard = cutText;
    deleteTextInRange(selectedFile, startPos, endPos);
    cout << "Teks berhasil dipotong: \"" << cutText << "\"\n";

    // Update posisi kursor
    if (selectedFile->cursorPosition > startPos)
    {
        selectedFile->cursorPosition = startPos;
    }
}

// Menghapus teks dalam rentang posisi (startPos - endPos)
void deleteTextInRange(FileNode *selectedFile, int startPos, int endPos)
{
    if (selectedFile == nullptr || selectedFile->head == nullptr)
    {
        cout << "File kosong atau tidak valid.\n";
        return;
    }

    CharNode *temp = selectedFile->head;
    CharNode *prev = nullptr;
    int currentPosition = 0;

    while (temp != nullptr && currentPosition < startPos)
    {
        prev = temp;
        temp = temp->next;
        currentPosition++;
    }

    while (temp != nullptr && currentPosition <= endPos)
    {
        CharNode *toDelete = temp;
        temp = temp->next;

        if (prev == nullptr)
        {
            selectedFile->head = temp;
        }
        else
        {
            prev->next = temp;
        }

        delete toDelete;
        currentPosition++;
    }

    cout << "Teks berhasil dihapus dari file.\n";
}

// Menempelkan teks dari cutBuffer setelah posisi kursor
void pasteCutText(FileNode *selectedFile)
{
    if (selectedFile == nullptr || selectedFile->head == nullptr)
    {
        cout << "File kosong atau tidak valid.\n";
        return;
    }

    if (isStackEmpty(selectedFile->cutBuffer))
    {
        cout << "Tidak ada teks yang dipotong untuk ditempelkan.\n";
        return;
    }

    string textToPaste;
    while (!isStackEmpty(selectedFile->cutBuffer))
    {
        textToPaste = top(selectedFile->cutBuffer) + textToPaste;
        pop(selectedFile->cutBuffer);
    }

    CharNode *temp = selectedFile->head;
    int currentPosition = 0;

    while (temp != nullptr && currentPosition < selectedFile->cursorPosition)
    {
        temp = temp->next;
        currentPosition++;
    }

    CharNode *lastInsertedNode = temp;

    for (int i = 0; i < textToPaste.length(); ++i)
    {
        char c = textToPaste[i]; // Mengakses karakter berdasarkan indeks

        CharNode *newChar = new CharNode;
        newChar->character = c;

        newChar->next = lastInsertedNode->next; // Hubungkan node baru dengan node berikutnya
        lastInsertedNode->next = newChar;       // Sambungkan node baru ke node terakhir yang ada

        lastInsertedNode = newChar; // Perbarui lastInsertedNode untuk menunjuk ke node baru
    }

    selectedFile->cursorPosition += textToPaste.length();
    cout << "Teks berhasil ditempelkan dari cut buffer.\n";

    displayFileContent(selectedFile);
}
// Fungsi untuk mencari teks dalam file mulai dari posisi tertentu
int findText(FileNode *selectedFile, string &searchText, int startPos)
{
    if (selectedFile == nullptr || selectedFile->head == nullptr)
    {
        cout << "File kosong atau tidak valid.\n";
        return -1; // Tidak ditemukan
    }

    if (searchText.empty())
    {
        cout << "Teks pencarian kosong.\n";
        return -1; // Tidak ditemukan
    }

    CharNode *temp = selectedFile->head;
    int currentPos = 0;

    // Menelusuri hingga mencapai posisi awal
    while (temp != nullptr && currentPos < startPos)
    {
        temp = temp->next;
        currentPos++;
    }

    // Buffer untuk mencocokkan kata
    string buffer;

    // Menelusuri dokumen untuk mencari kata
    while (temp != nullptr)
    {
        buffer += temp->character;

        // Jika panjang buffer sama dengan panjang teks pencarian
        if (buffer.size() == searchText.size())
        {
            if (buffer == searchText)
            {
                return currentPos - searchText.size() + 1; // Posisi awal kata ditemukan
            }

            // Geser buffer ke depan (hapus karakter pertama)
            buffer.erase(0, 1);
        }

        temp = temp->next;
        currentPos++;
    }

    cout << "Teks tidak ditemukan.\n";
    return -1; // Tidak ditemukan
}

// Fungsi untuk mengganti teks dalam file
void replaceText(FileNode *selectedFile, string &searchText, string &replaceText, int startPos)
{
    if (selectedFile == nullptr || selectedFile->head == nullptr)
    {
        cout << "File kosong atau tidak valid.\n";
        return;
    }

    if (searchText.empty())
    {
        cout << "Teks pencarian kosong.\n";
        return;
    }

    int pos = findText(selectedFile, searchText, startPos);
    if (pos == -1)
    {
        cout << "Teks tidak ditemukan, tidak ada yang diganti.\n";
        return;
    }

    CharNode *temp = selectedFile->head;
    CharNode *prev = nullptr;
    int currentPos = 0;

    // Menelusuri hingga menemukan posisi teks yang akan diganti
    while (temp != nullptr && currentPos < pos)
    {
        prev = temp;
        temp = temp->next;
        currentPos++;
    }

    // Hapus teks lama
    for (int i = 0; i < searchText.size(); ++i)
    {
        if (temp != nullptr)
        {
            CharNode *toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }

    // Hubungkan ulang linked list setelah penghapusan
    if (prev != nullptr)
    {
        prev->next = temp;
    }
    else
    {
        selectedFile->head = temp;
    }

    // Sisipkan teks baru
    CharNode *insertPos = prev;
    for (int i = 0; i < replaceText.length(); ++i)
    {
        char c = replaceText[i]; // Mengakses karakter berdasarkan indeks

        CharNode *newChar = new CharNode;
        newChar->character = c;
        newChar->next = nullptr;

        if (insertPos == nullptr)
        {
            newChar->next = selectedFile->head;
            selectedFile->head = newChar;
            insertPos = newChar;
        }
        else
        {
            newChar->next = insertPos->next;
            insertPos->next = newChar;
            insertPos = newChar;
        }
    }

    cout << "Teks berhasil diganti.\n";
}

// undo
void undo(FileNode *selectedFile)
{
    // Pastikan file valid
    if (selectedFile == nullptr)
    {
        cout << "Error: File tidak valid.\n";
        return;
    }

    // Pastikan undo stack tidak kosong
    if (isStackEmpty(selectedFile->undoRedo.undoStack))
    {
        cout << "Tidak ada operasi untuk di-undo.\n";
        return;
    }

    // Ambil karakter terakhir dari undo stack
    char lastChar = pop(selectedFile->undoRedo.undoStack);

    // Tambahkan karakter ke redo queue
    enqueue(selectedFile->undoRedo.redoQueue, lastChar);

    // Hapus karakter terakhir di linked list
    CharNode *temp = selectedFile->head;

    if (temp == nullptr)
    {
        cout << "File kosong.\n";
        return;
    }

    if (temp->next == nullptr)
    {
        delete temp;
        selectedFile->head = nullptr;
    }
    else
    {
        CharNode *prev = nullptr;
        while (temp->next != nullptr)
        {
            prev = temp;
            temp = temp->next;
        }
        delete temp;
        prev->next = nullptr;
    }

    // Update posisi kursor
    int position = 0;
    CharNode *cursor = selectedFile->head;
    while (cursor != nullptr)
    {
        cursor = cursor->next;
        position++;
    }

    if (position > 0)
    {
        selectedFile->cursorPosition = position - 1;
    }
    else
    {
        selectedFile->cursorPosition = 0;
    }
}

// redo
void redo(FileNode *selectedFile)
{
    if (selectedFile == nullptr)
    {
        cout << "File tidak valid atau kosong, tidak ada yang bisa di-redo.\n";
        return;
    }

    if (isQueueEmpty(selectedFile->undoRedo.redoQueue))
    {
        cout << "Tidak ada operasi untuk di-redo.\n";
        return;
    }

    char lastChar = dequeue(selectedFile->undoRedo.redoQueue);

    CharNode *newNode = new CharNode;
    newNode->character = lastChar;
    newNode->next = nullptr;

    if (selectedFile->head == nullptr)
    {
        selectedFile->head = newNode;
    }
    else
    {
        CharNode *temp = selectedFile->head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    selectedFile->cursorPosition++;
}
