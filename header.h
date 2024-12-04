#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

#include <iostream>
#include <string>

using namespace std;

// Struktur Node untuk Doubly Linked List
struct elmList {
    string info;          // Data teks yang disimpan
    elmList* prev;        // Pointer ke elemen sebelumnya
    elmList* next;        // Pointer ke elemen berikutnya
};

typedef elmList* address;

// Struktur Node untuk Stack
struct elmStack {
    string action;        // Aksi (INSERT/DELETE)
    string data;          // Data teks terkait aksi
    int lineNumber;       // Nomor baris terkait aksi
    elmStack* next;       // Pointer ke elemen berikutnya dalam stack
};

typedef elmStack* addressStack;

// Struktur untuk List
struct List {
    address first;        // Pointer ke elemen pertama dalam list
    address last;         // Pointer ke elemen terakhir dalam list
    address cursor;       // Pointer ke posisi kursor
};

// Struktur untuk Stack
struct Stack {
    addressStack top;     // Pointer ke elemen teratas dalam stack
};

// Struktur Node dan Queue untuk Clipboard
struct elmQueue {
    string clipboardData; // Data teks dalam clipboard
    elmQueue* next;       // Pointer ke elemen berikutnya dalam queue
};

typedef elmQueue* addressQueue;

struct Queue {
    addressQueue head;    // Pointer ke elemen pertama dalam queue
    addressQueue tail;    // Pointer ke elemen terakhir dalam queue
};

// Primitive Functions
void createList(List &L);                      // Menginisialisasi list kosong
address createElement(string text);            // Membuat elemen baru untuk list
void insertLine(List &L, string text, int lineNumber); // Menyisipkan teks di posisi tertentu
void deleteLine(List &L, int lineNumber);      // Menghapus baris teks tertentu
void tampilkanTeks(List L);         // Menampilkan teks 

void createStack(Stack &S);                    // Menginisialisasi stack kosong
void pushStack(Stack &S, string action, string data, int lineNumber); // Menambahkan data ke stack
bool popStack(Stack &S, string &action, string &data, int &lineNumber); // Mengambil elemen dari stack
bool isStackEmpty(Stack S);                    // Mengecek apakah stack kosong

// Fitur Utama
void undo(List &L, Stack &undoStack, Stack &redoStack); // Membatalkan aksi terakhir
void redo(List &L, Stack &redoStack, Stack &undoStack); // Mengulangi aksi terakhir yang dibatalkan
void deleteLineWithUndo(List &L, Stack &undoStack, int lineNumber); // Menghapus baris dengan undo

// Fitur Tambahan
void createQueue(Queue &Q);                    // Menginisialisasi queue kosong
void enqueueClipboard(Queue &Q, string data);  // Menambahkan data ke clipboard
bool dequeueClipboard(Queue &Q, string &data); // Mengambil data dari clipboard
bool isQueueEmpty(Queue Q);                    // Mengecek apakah clipboard kosong
void clearRedo(Stack &redoStack);              // Menghapus semua data di redo stack
void copyLine(List &L, Queue &clipboardQueue, int lineNumber); // Menyalin baris ke clipboard
void pasteLine(List &L, Queue &clipboardQueue, int lineNumber); // Menempelkan data clipboard ke baris tertentu

// Fitur tambahan
void activateCursor(List &L, const string &position);
void insertCharacter(List &L, char c);
void deleteCharacterAtCursor(List &L);
void moveCursor(List &L, const string &direction);
void displayCursorPosition(List L);


#endif
