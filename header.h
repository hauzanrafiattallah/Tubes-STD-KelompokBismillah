#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

#include <iostream>
#include <string>

using namespace std;

// *** Struktur Node untuk Doubly Linked List ***
struct elmList {
    string info;          // Data teks
    elmList* prev;        // Pointer ke elemen sebelumnya
    elmList* next;        // Pointer ke elemen berikutnya
};

typedef elmList* address;

// *** Struktur Node untuk Stack ***
struct elmStack {
    string action;        // Tindakan (INSERT atau DELETE)
    string data;          // Data yang dimanipulasi
    int lineNumber;       // Nomor baris tempat tindakan dilakukan
    elmStack* next;       // Pointer ke elemen berikutnya dalam stack
};

typedef elmStack* addressStack;

// *** Struktur Node untuk Queue ***
struct elmQueue {
    string clipboardData; // Data teks dalam clipboard
    elmQueue* next;       // Pointer ke elemen berikutnya dalam queue
};

typedef elmQueue* addressQueue;

// *** Struktur untuk List (Doubly Linked List) ***
struct List {
    address first;        // Pointer ke elemen pertama
    address last;         // Pointer ke elemen terakhir
};

// *** Struktur untuk Stack ***
struct Stack {
    addressStack top;     // Pointer ke elemen teratas dalam stack
};

// *** Struktur untuk Queue ***
struct Queue {
    addressQueue head;    // Pointer ke elemen pertama dalam queue
    addressQueue tail;    // Pointer ke elemen terakhir dalam queue
};

// *** Fungsi Primitive untuk List ***
void createList(List &L);                      // Membuat list baru
address createElement(string text);            // Membuat elemen baru dalam list
void insertLine(List &L, string text, int lineNumber); // Menyisipkan baris teks
void deleteLine(List &L, int lineNumber);      // Menghapus baris teks
void displayListFromFront(List L);             // Menampilkan teks dari awal ke akhir
void displayListFromBack(List L);              // Menampilkan teks dari akhir ke awal

// *** Fungsi Primitive untuk Stack ***
void createStack(Stack &S);                    // Membuat stack baru
void pushStack(Stack &S, string action, string data, int lineNumber); // Menambahkan data ke stack
bool popStack(Stack &S, string &action, string &data, int &lineNumber); // Mengambil data dari stack
bool isStackEmpty(Stack S);                    // Mengecek apakah stack kosong

// *** Fungsi Primitive untuk Queue ***
void createQueue(Queue &Q);                    // Membuat queue baru
void enqueueClipboard(Queue &Q, string data);  // Menambahkan data ke clipboard (queue)
bool dequeueClipboard(Queue &Q, string &data); // Mengambil data dari clipboard (queue)
bool isQueueEmpty(Queue Q);                    // Mengecek apakah queue kosong

// *** Fungsi Utility ***
void clearRedo(Stack &redoStack);              // Mengosongkan redo stack
void deleteLineWithUndo(List &L, Stack &undoStack, int lineNumber); // Menghapus baris dengan undo
void undo(List &L, Stack &undoStack, Stack &redoStack); // Melakukan undo
void redo(List &L, Stack &redoStack, Stack &undoStack); // Melakukan redo
void copyLine(List &L, Queue &clipboardQueue, int lineNumber); // Menyalin baris ke clipboard
void pasteLine(List &L, Queue &clipboardQueue, int lineNumber); // Menempelkan teks dari clipboard ke baris tertentu

#endif // HEADER_INCLUDED
