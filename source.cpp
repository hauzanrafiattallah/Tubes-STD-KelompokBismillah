#include "header.h"

// *** Implementasi Fungsi List ***

// Membuat list kosong
void createList(List &L) {
    L.first = nullptr;
    L.last = nullptr;
}

// Membuat elemen baru untuk list
address createElement(string text) {
    address newElm = new elmList;
    newElm->info = text;
    newElm->prev = nullptr;
    newElm->next = nullptr;
    return newElm;
}

// Menyisipkan baris teks pada posisi tertentu
void insertLine(List &L, string text, int lineNumber) {
    address newElm = createElement(text);

    // Jika list kosong
    if (L.first == nullptr) {
        L.first = newElm;
        L.last = newElm;
        return;
    }

    address current = L.first;
    int count = 1;

    // Navigasi ke posisi yang sesuai
    while (current && count < lineNumber) {
        current = current->next;
        count++;
    }

    if (current == nullptr) { // Sisipkan di akhir
        L.last->next = newElm;
        newElm->prev = L.last;
        L.last = newElm;
    } else { // Sisipkan sebelum current
        newElm->next = current;
        newElm->prev = current->prev;

        if (current->prev) {
            current->prev->next = newElm;
        } else {
            L.first = newElm; // Jika di awal
        }
        current->prev = newElm;
    }
}

// Menghapus baris teks pada posisi tertentu
void deleteLine(List &L, int lineNumber) {
    if (L.first == nullptr) return; // Jika list kosong

    address current = L.first;
    int count = 1;

    // Navigasi ke baris yang sesuai
    while (current && count < lineNumber) {
        current = current->next;
        count++;
    }

    if (!current) return; // Jika baris tidak ditemukan

    // Perbarui pointer sebelum menghapus
    if (current->prev) {
        current->prev->next = current->next;
    } else {
        L.first = current->next; // Jika di awal
    }

    if (current->next) {
        current->next->prev = current->prev;
    } else {
        L.last = current->prev; // Jika di akhir
    }

    delete current;
}

// Menampilkan teks dari awal ke akhir
void displayListFromFront(List L) {
    address current = L.first;
    while (current) {
        cout << current->info << endl;
        current = current->next;
    }
}

// Menampilkan teks dari akhir ke awal
void displayListFromBack(List L) {
    address current = L.last;
    while (current) {
        cout << current->info << endl;
        current = current->prev;
    }
}

// *** Implementasi Fungsi Stack ***

// Membuat stack kosong
void createStack(Stack &S) {
    S.top = nullptr;
}

// Menambahkan elemen ke stack
void pushStack(Stack &S, string action, string data, int lineNumber) {
    addressStack newElm = new elmStack;
    newElm->action = action;
    newElm->data = data;
    newElm->lineNumber = lineNumber;
    newElm->next = S.top;
    S.top = newElm;
}

// Mengambil elemen dari stack
bool popStack(Stack &S, string &action, string &data, int &lineNumber) {
    if (S.top == nullptr) return false;

    addressStack temp = S.top;
    action = temp->action;
    data = temp->data;
    lineNumber = temp->lineNumber;
    S.top = temp->next;

    delete temp;
    return true;
}

// Mengecek apakah stack kosong
bool isStackEmpty(Stack S) {
    return S.top == nullptr;
}

// *** Implementasi Fungsi Queue ***

// Membuat queue kosong
void createQueue(Queue &Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

// Menambahkan data ke clipboard (queue)
void enqueueClipboard(Queue &Q, string data) {
    addressQueue newElm = new elmQueue;
    newElm->clipboardData = data;
    newElm->next = nullptr;

    if (Q.head == nullptr) { // Jika queue kosong
        Q.head = newElm;
        Q.tail = newElm;
        return;
    }

    Q.tail->next = newElm;
    Q.tail = newElm;
}

// Mengambil data dari clipboard (queue)
bool dequeueClipboard(Queue &Q, string &data) {
    if (Q.head == nullptr) return false; // Jika queue kosong

    addressQueue temp = Q.head;
    data = temp->clipboardData;
    Q.head = Q.head->next;

    if (Q.head == nullptr) { // Jika elemen terakhir dihapus
        Q.tail = nullptr;
    }

    delete temp;
    return true;
}

// Mengecek apakah queue kosong
bool isQueueEmpty(Queue Q) {
    return Q.head == nullptr;
}

// *** Implementasi Fungsi Utility ***

// Mengosongkan redo stack
void clearRedo(Stack &redoStack) {
    string action, data;
    int lineNumber;
    while (!isStackEmpty(redoStack)) {
        popStack(redoStack, action, data, lineNumber);
    }
}

// Menghapus baris dengan menyimpan undo
void deleteLineWithUndo(List &L, Stack &undoStack, int lineNumber) {
    address current = L.first;
    int count = 1;

    while (current && count < lineNumber) {
        current = current->next;
        count++;
    }

    if (!current) {
        cout << "Baris tidak ditemukan.\n";
        return;
    }

    string text = current->info;
    pushStack(undoStack, "DELETE", text, lineNumber);
    deleteLine(L, lineNumber);
}

// Melakukan undo
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

// Melakukan redo
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

// Menyalin baris ke clipboard
void copyLine(List &L, Queue &clipboardQueue, int lineNumber) {
    address current = L.first;
    int count = 1;

    while (current && count < lineNumber) {
        current = current->next;
        count++;
    }

    if (!current) {
        cout << "Baris tidak ditemukan untuk disalin.\n";
        return;
    }

    enqueueClipboard(clipboardQueue, current->info);
    cout << "Teks \"" << current->info << "\" telah disalin.\n";
}

// Menempelkan teks dari clipboard ke baris tertentu
void pasteLine(List &L, Queue &clipboardQueue, int lineNumber) {
    string clipboardData;
    if (!dequeueClipboard(clipboardQueue, clipboardData)) {
        cout << "Clipboard kosong, tidak ada teks untuk ditempel.\n";
        return;
    }

    insertLine(L, clipboardData, lineNumber);
    cout << "Teks \"" << clipboardData << "\" telah ditempel di baris " << lineNumber << ".\n";
}
