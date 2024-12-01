#include "header.h"

// Fungsi untuk membuat list kosong
void createList(List &L) {
    L.first = nullptr;
    L.last = nullptr;
    L.cursor = nullptr; // Inisialisasi cursor
}


// Fungsi untuk membuat elemen baru pada list
address createElement(string text) {
    address newElm = new elmList;
    newElm->info = text;
    newElm->prev = nullptr;
    newElm->next = nullptr;
    return newElm;
}

// Fungsi untuk menyisipkan baris teks pada posisi tertentu
void insertLine(List &L, string text, int lineNumber) {
    address newElm = createElement(text);

    if (L.first == nullptr) {
        // Jika list kosong
        L.first = newElm;
        L.last = newElm;
        L.cursor = newElm;
    } else {
        address current = L.first;
        int count = 1;

        // Navigasi ke posisi tertentu
        while (current != nullptr && count < lineNumber) {
            current = current->next;
            count++;
        }

        if (current == nullptr) {
            // Sisipkan di akhir
            L.last->next = newElm;
            newElm->prev = L.last;
            L.last = newElm;
        } else {
            // Sisipkan sebelum current
            newElm->next = current;
            newElm->prev = current->prev;

            if (current->prev != nullptr) {
                current->prev->next = newElm;
            } else {
                L.first = newElm;
            }
            current->prev = newElm;
        }
    }
}

// Fungsi untuk menghapus baris teks pada posisi tertentu
void deleteLine(List &L, int lineNumber) {
    if (L.first == nullptr) {
        // Jika list kosong
        return;
    }

    address current = L.first;
    int count = 1;

    // Navigasi ke baris tertentu
    while (current != nullptr && count < lineNumber) {
        current = current->next;
        count++;
    }

    if (current == nullptr) {
        // Jika baris tidak ditemukan
        return;
    }

    if (current->prev != nullptr) {
        current->prev->next = current->next;
    } else {
        L.first = current->next;
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    } else {
        L.last = current->prev;
    }

    delete current;
}

// Fungsi untuk menampilkan teks dari awal ke akhir
void displayListFromFront(List L) {
    address current = L.first;
    while (current != nullptr) {
        cout << current->info << endl;
        current = current->next;
    }
}

// Fungsi untuk menampilkan teks dari akhir ke awal
void displayListFromBack(List L) {
    address current = L.last;
    while (current != nullptr) {
        cout << current->info << endl;
        current = current->prev;
    }
}

// Fungsi untuk membuat stack kosong
void createStack(Stack &S) {
    S.top = nullptr;
}

// Fungsi untuk menambahkan elemen ke stack
void pushStack(Stack &S, string action, string data, int lineNumber) {
    addressStack newElm = new elmStack;
    newElm->action = action;
    newElm->data = data;
    newElm->lineNumber = lineNumber;
    newElm->next = S.top;
    S.top = newElm;
}

// Fungsi untuk mengambil elemen dari stack
bool popStack(Stack &S, string &action, string &data, int &lineNumber) {
    if (S.top == nullptr) {
        return false;
    }

    addressStack temp = S.top;
    action = temp->action;
    data = temp->data;
    lineNumber = temp->lineNumber;
    S.top = temp->next;

    delete temp;
    return true;
}

// Fungsi untuk mengecek apakah stack kosong
bool isStackEmpty(Stack S) {
    return S.top == nullptr;
}

// Fungsi untuk membuat queue kosong
void createQueue(Queue &Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

// Fungsi untuk menambahkan data ke clipboard (queue)
void enqueueClipboard(Queue &Q, string data) {
    addressQueue newElm = new elmQueue;
    newElm->clipboardData = data;
    newElm->next = nullptr;

    if (Q.head == nullptr) {
        Q.head = newElm;
        Q.tail = newElm;
    } else {
        Q.tail->next = newElm;
        Q.tail = newElm;
    }
}

// Fungsi untuk mengambil data dari clipboard (queue)
bool dequeueClipboard(Queue &Q, string &data) {
    if (Q.head == nullptr) {
        return false;
    }

    addressQueue temp = Q.head;
    data = temp->clipboardData;
    Q.head = Q.head->next;

    if (Q.head == nullptr) {
        Q.tail = nullptr;
    }

    delete temp;
    return true;
}

// Fungsi untuk mengecek apakah queue kosong
bool isQueueEmpty(Queue Q) {
    return Q.head == nullptr;
}

// Fungsi untuk mengosongkan redo stack
void clearRedo(Stack &redoStack) {
    string action, data;
    int lineNumber;

    while (!isStackEmpty(redoStack)) {
        popStack(redoStack, action, data, lineNumber);
    }
}

// Fungsi untuk menghapus baris dengan menyimpan undo
void deleteLineWithUndo(List &L, Stack &undoStack, int lineNumber) {
    address current = L.first;
    int count = 1;

    while (current != nullptr && count < lineNumber) {
        current = current->next;
        count++;
    }

    if (current == nullptr) {
        cout << "Baris tidak ditemukan.\n";
        return;
    }

    string text = current->info;
    pushStack(undoStack, "DELETE", text, lineNumber);
    deleteLine(L, lineNumber);
}

// Fungsi untuk melakukan undo
void undo(List &L, Stack &undoStack, Stack &redoStack) {
    if (isStackEmpty(undoStack)) {
        cout << "Tidak ada aksi untuk di-undo.\n";
        return;
    }

    string action, data;
    int lineNumber;
    popStack(undoStack, action, data, lineNumber);

    if (action == "INSERT") {
        deleteLine(L, lineNumber);
        pushStack(redoStack, "INSERT", data, lineNumber);
    } else if (action == "DELETE") {
        insertLine(L, data, lineNumber);
        pushStack(redoStack, "DELETE", data, lineNumber);
    }
    cout << "Undo berhasil.\n";
}

// Fungsi untuk melakukan redo
void redo(List &L, Stack &redoStack, Stack &undoStack) {
    if (isStackEmpty(redoStack)) {
        cout << "Tidak ada aksi untuk di-redo.\n";
        return;
    }

    string action, data;
    int lineNumber;
    popStack(redoStack, action, data, lineNumber);

    if (action == "INSERT") {
        insertLine(L, data, lineNumber);
        pushStack(undoStack, "INSERT", data, lineNumber);
    } else if (action == "DELETE") {
        deleteLine(L, lineNumber);
        pushStack(undoStack, "DELETE", data, lineNumber);
    }
    cout << "Redo berhasil.\n";
}

// Fungsi untuk menyalin baris ke clipboard
void copyLine(List &L, Queue &clipboardQueue, int lineNumber) {
    address current = L.first;
    int count = 1;

    while (current != nullptr && count < lineNumber) {
        current = current->next;
        count++;
    }

    if (current == nullptr) {
        cout << "Baris tidak ditemukan untuk disalin.\n";
        return;
    }

    enqueueClipboard(clipboardQueue, current->info);
    cout << "Teks \"" << current->info << "\" telah disalin.\n";
}

// Fungsi untuk menempelkan teks dari clipboard ke baris tertentu
void pasteLine(List &L, Queue &clipboardQueue, int lineNumber) {
    string clipboardData;
    if (!dequeueClipboard(clipboardQueue, clipboardData)) {
        cout << "Clipboard kosong, tidak ada teks untuk ditempel.\n";
        return;
    }

    insertLine(L, clipboardData, lineNumber);
    cout << "Teks \"" << clipboardData << "\" telah ditempel di baris " << lineNumber << ".\n";
}

void activateCursor(List &L, const string &position) {
    if (L.first == nullptr) {
        cout << "List kosong, kursor tidak dapat diaktifkan.\n";
        return;
    }

    if (position == "start") {
        L.cursor = L.first; // Aktifkan kursor di elemen pertama
        cout << "Kursor diaktifkan di awal list.\n";
    } else if (position == "end") {
        L.cursor = L.last; // Aktifkan kursor di elemen terakhir
        cout << "Kursor diaktifkan di akhir list.\n";
    } else {
        cout << "Posisi tidak valid. Gunakan 'start' atau 'end'.\n";
    }
}


void insertCharacter(List &L, char c) {
    address newElm = createElement(string(1, c)); // Buat elemen untuk karakter baru

    if (L.first == nullptr) {
        // Jika list kosong
        L.first = newElm;
        L.last = newElm;
        L.cursor = newElm;
    } else if (L.cursor == nullptr) {
        // Jika kursor belum diatur, tambahkan di awal
        newElm->next = L.first;
        L.first->prev = newElm;
        L.first = newElm;
        L.cursor = newElm;
    } else {
        // Sisipkan setelah kursor
        newElm->next = L.cursor->next;
        newElm->prev = L.cursor;

        if (L.cursor->next != nullptr) {
            L.cursor->next->prev = newElm;
        } else {
            L.last = newElm; // Jika di akhir, atur last
        }

        L.cursor->next = newElm;
        L.cursor = newElm; // Pindahkan kursor ke elemen baru
    }
}


void deleteCharacterAtCursor(List &L) {
    if (L.cursor == nullptr) {
        cout << "Tidak ada karakter untuk dihapus.\n";
        return;
    }

    address target = L.cursor;

    if (target->prev != nullptr) {
        target->prev->next = target->next;
    } else {
        L.first = target->next;
    }

    if (target->next != nullptr) {
        target->next->prev = target->prev;
    } else {
        L.last = target->prev;
    }

    L.cursor = target->next ? target->next : target->prev;
    delete target;

    cout << "Karakter berhasil dihapus.\n";
}

void moveCursor(List &L, const string &direction) {
    if (L.first == nullptr) {
        cout << "Teks kosong, kursor tidak bisa dipindahkan.\n";
        return;
    }

    if (direction == "r") {
        if (L.cursor != nullptr && L.cursor->next != nullptr) {
            L.cursor = L.cursor->next;
        } else {
            cout << "Kursor sudah di posisi paling kanan.\n";
        }
    } else if (direction == "l") {
        if (L.cursor != nullptr && L.cursor->prev != nullptr) {
            L.cursor = L.cursor->prev;
        } else {
            cout << "Kursor sudah di posisi paling kiri.\n";
        }
    } else {
        cout << "Perintah tidak valid. Gunakan 'r' atau 'l'.\n";
    }
}

void displayCursorPosition(List L) {
    if (L.cursor == nullptr) {
        cout << "[Kursor tidak aktif]\n";
    } else {
        cout << "[Kursor pada: \"" << L.cursor->info << "\"]\n";
    }
}