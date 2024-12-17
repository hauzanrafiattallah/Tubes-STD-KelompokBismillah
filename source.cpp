#include "header.h"

// Fungsi untuk inisialisasi stack
void createStack(CharStack &stack)
{
    stack.top = nullptr; // Stack kosong
}

// Fungsi untuk memeriksa apakah stack kosong
bool isStackEmpty(CharStack &stack)
{
    return stack.top == nullptr;
}

// Fungsi untuk menambahkan elemen ke stack (push)
void push(CharStack &stack, char value)
{
    CharNode *newNode = new CharNode;
    newNode->character = value;
    newNode->next = stack.top; // Node baru menunjuk ke top lama
    stack.top = newNode;       // Update top menjadi node baru
}

// Fungsi untuk menghapus elemen dari stack (pop)
char pop(CharStack &stack)
{
    if (isStackEmpty(stack))
    {
        cout << "Stack kosong!\n";
        return '\0'; // Return karakter kosong jika stack kosong
    }
    else
    {
        CharNode *temp = stack.top;
        char value = temp->character;
        stack.top = stack.top->next; // Update top ke node berikutnya
        delete temp;                 // Hapus node lama
        return value;
    }
}
char top(CharStack &stack)
{
    if (stack.top != nullptr)
    {
        return stack.top->character; // Mengambil karakter dari node teratas
    }
    return '\0'; // Jika stack kosong, return karakter kosong
}

// Fungsi untuk inisialisasi queue
void createQueue(CharQueue &queue)
{
    queue.front = queue.rear = nullptr; // Queue kosong
}

// Fungsi untuk memeriksa apakah queue kosong
bool isQueueEmpty(CharQueue &queue)
{
    return queue.front == nullptr;
}

// Fungsi untuk menambahkan elemen ke queue (enqueue)
void enqueue(CharQueue &queue, char value)
{
    CharNode *newNode = new CharNode;
    newNode->character = value;
    newNode->next = nullptr;

    if (isQueueEmpty(queue))
    {
        queue.front = queue.rear = newNode; // Queue kosong, front dan rear menunjuk ke node baru
    }
    else
    {
        queue.rear->next = newNode; // Rear lama menunjuk ke node baru
        queue.rear = newNode;       // Update rear ke node baru
    }
}

// Fungsi untuk menghapus elemen dari queue (dequeue)
char dequeue(CharQueue &queue)
{
    if (isQueueEmpty(queue))
    {
        cout << "Queue kosong!\n";
        return '\0'; // Return karakter kosong jika queue kosong
    }
    else
    {
        CharNode *temp = queue.front;
        char value = temp->character;
        queue.front = queue.front->next; // Update front ke node berikutnya
        if (queue.front == nullptr)      // Jika queue kosong setelah dequeue
            queue.rear = nullptr;
        delete temp; // Hapus node lama
        return value;
    }
}

// Inisialisasi editor teks
void initializeEditor(TextEditor &editor)
{
    editor.files = nullptr;
}

// Menambahkan file baru
void addFile(TextEditor &editor, string &fileName)
{
    FileNode *newFile = new FileNode;
    newFile->fileName = fileName;
    newFile->head = nullptr;
    newFile->next = editor.files;
    newFile->cursorPosition = 0; // Kursor dimulai di posisi awal
    editor.files = newFile;
}

// Memilih file dari daftar
int selectFile(TextEditor &editor)
{
    FileNode *temp = editor.files;
    if (temp == nullptr)
    {
        cout << "Tidak ada file yang tersedia.\n";
        return -1; // Tidak ada file
    }

    cout << "\nDaftar file yang tersedia:\n";
    displayFiles(editor);

    cout << "0. Batal\n"; // Tambahkan opsi untuk membatalkan
    cout << "\nPilih nomor file: ";
    int choice;
    cin >> choice;
    cin.ignore(); // Membersihkan buffer input

    if (choice == 0)
    {
        cout << "Pemilihan file dibatalkan.\n";
        return -1; // Return -1 untuk menunjukkan pembatalan
    }

    if (choice < 1 || getFileByIndex(editor, choice) == nullptr)
    {
        cout << "Pilihan tidak valid.\n";
        return -1; // Return -1 untuk pilihan tidak valid
    }

    return choice;
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
            file->head = newChar;
        }
        else
        {
            CharNode *temp = file->head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newChar;
        }

        // Menyimpan karakter yang baru ditambahkan ke dalam undo stack
        push(file->undoRedo.undoStack, character);

        // Reset redo queue jika ada operasi baru setelah undo
        while (!isQueueEmpty(file->undoRedo.redoQueue))
        {
            dequeue(file->undoRedo.redoQueue); // Menggunakan dequeue untuk mengosongkan redoQueue
        }

        // Update posisi kursor ke akhir file
        file->cursorPosition++;
    }
}

// Menampilkan semua file yang ada
void displayFiles(TextEditor &editor)
{
    FileNode *temp = editor.files;
    if (temp == nullptr)
    {
        cout << "Tidak ada file untuk ditampilkan.\n";
        return;
    }

    int index = 1;
    while (temp != nullptr)
    {
        cout << index << ". " << temp->fileName << "\n";
        temp = temp->next;
        index++;
    }
}

// Mencari file berdasarkan nama
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
    return nullptr;
}

// Mendapatkan file berdasarkan indeks
FileNode *getFileByIndex(TextEditor &editor, int index)
{
    FileNode *temp = editor.files;
    int currentIndex = 1;
    while (temp != nullptr && currentIndex < index)
    {
        temp = temp->next;
        currentIndex++;
    }
    return temp;
}

// Fungsi untuk pindah kursor ke kanan
void moveCursorRight(FileNode *selectedFile)
{
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
        cout << "Kursor dipindahkan ke kanan.\n";
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
    if (selectedFile->cursorPosition == 0)
    {
        cout << "Kursor sudah di posisi paling kiri.\n";
        return;
    }

    selectedFile->cursorPosition--;
    cout << "Kursor dipindahkan ke kiri.\n";

    // Tampilkan teks dengan kursor setelah berpindah
    displayFileContent(selectedFile);
}

// Menghapus karakter di posisi kursor
void deleteCharacterAtCursor(FileNode *selectedFile)
{
    if (selectedFile->head == nullptr)
    {
        cout << "File kosong. Tidak ada karakter untuk dihapus.\n";
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

    // Bebaskan memori
    delete temp;

    // Update posisi kursor (tetap di posisi yang sama, jika memungkinkan)
    if (selectedFile->cursorPosition > 0)
    {
        selectedFile->cursorPosition--;
    }

    cout << "Karakter berhasil dihapus.\n";
}

// Menambahkan teks ke file tertentu
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
    cout << "Kursor dipindahkan ke kiri satu kali.\n";
}

// Menampilkan isi file tertentu dengan tampilan kursor menyatu dengan teks
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

    // Menampilkan isi file dengan kursor menyatu di dalam teks
    while (temp != nullptr)
    {
        if (currentPosition == selectedFile->cursorPosition)
        {
            // Jika kursor berada di posisi ini, tampilkan karakter dengan tanda kurung
            cout << "(" << temp->character << ")";
        }
        else
        {
            // Jika bukan posisi kursor, tampilkan karakter biasa
            cout << temp->character;
        }
        temp = temp->next;
        currentPosition++;
    }

    // Jika kursor berada setelah karakter terakhir
    if (currentPosition == selectedFile->cursorPosition)
    {
        cout << "()"; // Tampilkan tanda kursor di akhir teks
    }

    cout << "\n";
}

// Menyisipkan teks setelah posisi kursor
void insertTextAfterCursor(FileNode *selectedFile)
{
    if (selectedFile->head == nullptr)
    {
        cout << "File kosong. Tidak ada tempat untuk menyisipkan teks.\n";
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
    for (int i = 0; i < textToInsert.length(); i++)
    {
        char c = textToInsert[i];
        CharNode *newChar = new CharNode;
        newChar->character = c;

        // Menyisipkan setelah node saat ini
        newChar->next = lastInsertedNode->next;
        lastInsertedNode->next = newChar;

        lastInsertedNode = newChar; // Pindahkan ke node baru
    }

    // Perbarui posisi kursor setelah teks yang disisipkan
    selectedFile->cursorPosition += textToInsert.length();

    cout << "Teks berhasil disisipkan.\n";

    // Tampilkan isi file dengan kursor
    displayFileContent(selectedFile);
}

// select text
void selectText(FileNode *selectedFile, int startPos, int endPos)
{
    if (selectedFile == nullptr || startPos < 0 || endPos < startPos)
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

// copy text
void copyText(FileNode *selectedFile)
{
    if (selectedFile->clipboard.empty())
    {
        cout << "Tidak ada teks yang dipilih untuk disalin.\n";
        return;
    }

    // Teks yang disalin sudah ada di clipboard
    cout << "Teks berhasil disalin ke clipboard: \"" << selectedFile->clipboard << "\"\n";
}

// Fungsi untuk menempelkan teks dari clipboard setelah posisi kursor dengan spasi setelah kursor
void pasteText(FileNode *selectedFile)
{
    // Memastikan clipboard tidak kosong
    if (selectedFile->clipboard.empty())
    {
        cout << "Tidak ada teks yang dapat ditempelkan. Clipboard kosong.\n";
        return;
    }

    // Teks yang akan dipaste adalah teks yang ada di clipboard
    string textToPaste = selectedFile->clipboard;

    // Menambahkan spasi setelah posisi kursor untuk memberikan jarak sebelum menempelkan teks
    CharNode *temp = selectedFile->head;
    int currentPosition = 0;

    // Menelusuri file hingga mencapai posisi kursor
    while (temp != nullptr && currentPosition < selectedFile->cursorPosition)
    {
        temp = temp->next;
        currentPosition++;
    }

    // Jika posisi kursor valid, sisipkan spasi setelah posisi kursor terlebih dahulu
    CharNode *lastInsertedNode = temp; // Node sebelum posisi kursor

    // Menyisipkan spasi pertama setelah kursor
    CharNode *newSpace = new CharNode;
    newSpace->character = ' '; // Spasi
    newSpace->next = lastInsertedNode->next;
    lastInsertedNode->next = newSpace;
    lastInsertedNode = newSpace; // Update lastInsertedNode ke spasi yang baru disisipkan

    // Menyisipkan setiap karakter dalam teks dari clipboard
    for (int i = 0; i < textToPaste.length(); i++)
    {
        char c = textToPaste[i];
        CharNode *newChar = new CharNode;
        newChar->character = c;
        newChar->next = lastInsertedNode->next;
        lastInsertedNode->next = newChar;
        lastInsertedNode = newChar; // Update lastInsertedNode ke node baru
    }

    // Update posisi kursor setelah teks yang dipaste
    selectedFile->cursorPosition++;                       // Posisi kursor setelah spasi yang baru disisipkan
    selectedFile->cursorPosition += textToPaste.length(); // Update kursor setelah teks yang dipaste
    cout << "Teks berhasil ditempelkan.\n";

    // Tampilkan file dengan kursor setelah operasi paste
    displayFileContent(selectedFile);
}
// Fungsi untuk memotong teks
void cutText(FileNode *selectedFile, int startPos, int endPos)
{
    if (selectedFile == nullptr || startPos < 0 || endPos < startPos)
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
    string cutText;

    // Menemukan posisi awal
    while (temp != nullptr && currentPosition < startPos)
    {
        temp = temp->next;
        currentPosition++;
    }

    // Menyusun teks yang dipilih dari startPos hingga endPos
    while (temp != nullptr && currentPosition <= endPos)
    {
        cutText += temp->character;
        push(selectedFile->cutBuffer, temp->character);
        // Push ke stack cutBuffer
        temp = temp->next;
        currentPosition++;
    }

    // Menyimpan teks yang dipilih ke clipboard (cutBuffer sudah berisi teks yang dipotong)
    cout << "Teks berhasil dipotong: \"" << cutText << "\"\n";

    // Hapus teks yang dipilih dari dokumen
    deleteTextInRange(selectedFile, startPos, endPos);

    // Perbarui posisi kursor setelah teks dipotong
    if (startPos <= selectedFile->cursorPosition)
    {
        // Jika kursor berada sebelum atau tepat pada teks yang dipotong,
        // kita harus mengurangi posisi kursor setelah penghapusan teks
        if (selectedFile->cursorPosition >= endPos)
        {
            // Geser kursor mundur berdasarkan panjang teks yang dipotong
            selectedFile->cursorPosition = selectedFile->cursorPosition - (endPos - startPos + 1);
        }
        else
        {
            // Jika kursor berada di posisi setelah teks yang dipotong, set posisi kursor ke startPos
            selectedFile->cursorPosition = startPos;
        }
    }

    cout << "Posisi kursor telah diperbarui: " << selectedFile->cursorPosition << endl;
}
// Fungsi untuk menghapus teks dalam rentang posisi (startPos - endPos)
void deleteTextInRange(FileNode *selectedFile, int startPos, int endPos)
{
    if (selectedFile->head == nullptr)
    {
        cout << "File kosong. Tidak ada teks untuk dihapus.\n";
        return;
    }

    CharNode *temp = selectedFile->head;
    CharNode *prev = nullptr;
    int currentPosition = 0;

    // Menelusuri hingga posisi awal
    while (temp != nullptr && currentPosition < startPos)
    {
        prev = temp;
        temp = temp->next;
        currentPosition++;
    }

    // Hapus karakter dari startPos hingga endPos
    while (temp != nullptr && currentPosition <= endPos)
    {
        CharNode *toDelete = temp;
        if (prev == nullptr)
        {
            // Hapus karakter pertama
            selectedFile->head = temp->next;
        }
        else
        {
            // Hapus karakter berikutnya
            prev->next = temp->next;
        }
        temp = temp->next;
        delete toDelete; // Bebaskan memori
        currentPosition++;
    }

    cout << "Teks berhasil dihapus dari file.\n";
}

// Fungsi untuk menempelkan teks dari cutBuffer setelah posisi kursor
void pasteCutText(FileNode *selectedFile)
{
    if (isStackEmpty(selectedFile->cutBuffer))
    {
        cout << "Tidak ada teks yang dipotong untuk ditempelkan.\n";
        return;
    }

    // Mengambil teks yang dipotong dari cutBuffer
    string textToPaste;
    while (!isStackEmpty(selectedFile->cutBuffer))
    {
        textToPaste = top(selectedFile->cutBuffer) + textToPaste; // Membalik urutan stack
        pop(selectedFile->cutBuffer);                             // Menghapus elemen teratas dari stack
    }

    // Menambahkan spasi setelah posisi kursor untuk memberikan jarak sebelum menempelkan teks
    CharNode *temp = selectedFile->head;
    int currentPosition = 0;

    // Menelusuri file hingga mencapai posisi kursor
    while (temp != nullptr && currentPosition < selectedFile->cursorPosition)
    {
        temp = temp->next;
        currentPosition++;
    }

    // Menyisipkan spasi pertama setelah kursor terlebih dahulu
    CharNode *lastInsertedNode = temp; // Node sebelum posisi kursor

    // Menyisipkan setiap karakter dalam teks dari cutBuffer
    for (int i = 0; i < textToPaste.length(); i++)
    {
        char c = textToPaste[i];
        CharNode *newChar = new CharNode;
        newChar->character = c;
        newChar->next = lastInsertedNode->next;
        lastInsertedNode->next = newChar;
        lastInsertedNode = newChar; // Update lastInsertedNode ke node baru
    }

    // Update posisi kursor setelah teks yang dipaste
    selectedFile->cursorPosition += textToPaste.length();
    cout << "Teks berhasil ditempelkan.\n";

    // Tampilkan file dengan kursor setelah operasi paste
    displayFileContent(selectedFile);
}

// Fungsi untuk mencari teks dalam file mulai dari posisi tertentu
int findText(FileNode *selectedFile, string &searchText, int startPos)
{
    if (selectedFile == nullptr || searchText.empty())
    {
        cout << "File tidak ditemukan atau teks pencarian kosong.\n";
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
    CharNode *matchStart = temp;

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
            matchStart = matchStart->next;
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
    if (selectedFile == nullptr || searchText.empty())
    {
        cout << "File tidak ditemukan atau teks pencarian kosong.\n";
        return;
    }

    int pos = findText(selectedFile, searchText, startPos);
    if (pos == -1)
    {
        cout << "Teks tidak ditemukan, tidak ada yang diganti.\n";
        return;
    }

    // Temukan posisi awal teks yang ditemukan
    CharNode *temp = selectedFile->head;
    CharNode *prev = nullptr;
    int currentPos = 0;

    while (temp != nullptr && currentPos < pos)
    {
        prev = temp;
        temp = temp->next;
        currentPos++;
    }

    // Simpan panjang teks lama dan baru
    int oldLength = searchText.size();
    int newLength = replaceText.size();

    // Periksa apakah posisi kursor berada di akhir dokumen sebelum penggantian
    bool cursorAtEnd = (selectedFile->cursorPosition == currentPos + oldLength);

    // Hapus teks lama
    CharNode *matchStart = temp;
    for (int i = 0; i < oldLength; ++i)
    {
        if (temp != nullptr)
        {
            CharNode *toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }

    // Hubungkan ulang linked list
    if (prev != nullptr)
    {
        prev->next = temp; // Hubungkan node sebelum teks yang diganti dengan node setelahnya
    }
    else
    {
        selectedFile->head = temp; // Jika teks yang diganti ada di awal file
    }

    // Sisipkan teks baru
    CharNode *insertPos = prev;
    for (int i = 0; i < replaceText.length(); i++)
    {
        char c = replaceText[i];
        CharNode *newChar = new CharNode;
        newChar->character = c;
        newChar->next = nullptr;

        if (insertPos == nullptr)
        {
            // Jika mengganti di awal file
            newChar->next = selectedFile->head;
            selectedFile->head = newChar;
            insertPos = newChar;
        }
        else
        {
            // Sisipkan setelah posisi sebelumnya
            newChar->next = insertPos->next;
            insertPos->next = newChar;
            insertPos = newChar;
        }
    }

    // Perbarui posisi kursor
    if (cursorAtEnd)
    {
        // Jika kursor berada di akhir dokumen, set ulang ke posisi akhir dokumen baru
        selectedFile->cursorPosition = pos + newLength;
    }
    else if (selectedFile->cursorPosition > pos)
    {
        // Jika kursor berada setelah teks yang diganti, sesuaikan posisi kursor
        selectedFile->cursorPosition += (newLength - oldLength);
    }

    cout << "Teks berhasil diganti.\n";
}

// procedure melakukan undo
void undo(FileNode *selectedFile)
{
    if (!isStackEmpty(selectedFile->undoRedo.undoStack))
    {
        // Ambil karakter terakhir dari undo stack
        char lastChar = top(selectedFile->undoRedo.undoStack);
        pop(selectedFile->undoRedo.undoStack);

        // Simpan karakter yang di-undo ke redo queue
        enqueue(selectedFile->undoRedo.redoQueue, lastChar);

        // Hapus karakter terakhir dari file
        CharNode *current = selectedFile->head;
        CharNode *prev = nullptr;
        while (current && current->character != lastChar)
        {
            prev = current;
            current = current->next;
        }

        if (current)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                selectedFile->head = current->next;
            }
            delete current;
        }

        // Update posisi kursor
        selectedFile->cursorPosition--;
    }
    else
    {
        cout << "Tidak ada operasi untuk di-undo!" << endl;
    }
}

// Fungsi untuk melakukan redo
void redo(FileNode *selectedFile)
{
    if (!isQueueEmpty(selectedFile->undoRedo.redoQueue))
    {
        char lastChar = dequeue(selectedFile->undoRedo.redoQueue); // Mengambil karakter dari front
        // Tambahkan karakter ke file dengan versi ketiga
        addCharacterToFile(*selectedFile, lastChar);

        // Masukkan karakter ke undo stack
        push(selectedFile->undoRedo.undoStack, lastChar);

        // Update posisi kursor
        selectedFile->cursorPosition++;
    }
    else
    {
        cout << "Tidak ada operasi untuk di-redo!" << endl;
    }
}

// Fungsi untuk menambah karakter dan menyimpan operasi untuk undo
void addCharacterToFile(FileNode &file, char character)
{
    // Tambahkan karakter ke dalam linked list
    CharNode *newNode = new CharNode; // Alokasi memori untuk CharNode
    newNode->character = character;   // Inisialisasi anggota character
    newNode->next = nullptr;          // Inisialisasi pointer next ke nullptr

    if (file.head == nullptr)
    {
        file.head = newNode;
    }
    else
    {
        CharNode *current = file.head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    // Menyimpan perubahan ke dalam undo stack
    push(file.undoRedo.undoStack, character);
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
