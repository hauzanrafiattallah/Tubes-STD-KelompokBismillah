#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

#include <iostream>
#include <string>

using namespace std;

// Struktur Node untuk karakter (linked list karakter)
struct CharNode
{
    char character; // Karakter yang disimpan
    CharNode *next; // Pointer ke node karakter berikutnya
};
// Struktur untuk stack (menggunakan linked list)
struct CharStack
{
    CharNode *top; // Pointer ke node paling atas
};

// Struktur untuk queue (menggunakan linked list)
struct CharQueue
{
    CharNode *front; // Pointer ke node paling depan
    CharNode *rear;  // Pointer ke node paling belakang
};

struct UndoRedoStack
{
    CharStack undoStack; // Stack untuk undo
    CharQueue redoQueue; // Queue untuk redo
};

// Struktur Node untuk file (linked list file)
struct FileNode
{
    string fileName;        // Nama file
    CharNode *head;         // Pointer ke linked list karakter
    FileNode *next;         // Pointer ke file berikutnya
    int cursorPosition;     // Posisi kursor dalam file
    string clipboard;       // Menyimpan teks yang disalin
    CharStack cutBuffer;    // Stack untuk menyimpan teks yang dipotong
    UndoRedoStack undoRedo; // Stack undo dan queue redo untuk file ini
};

// Struktur untuk teks editor
struct TextEditor
{
    FileNode *files;  // Linked list untuk menyimpan file-file yang ada
    string clipboard; // menyimpan teks yang disalin
};

// Fungsi inisialisasi
void initializeEditor(TextEditor &editor);

// Fungsi file
int selectFile(TextEditor &editor);
void addFile(TextEditor &editor, string &fileName);
void addCharacterToFile(TextEditor &editor, string &fileName, char character);
void displayFiles(TextEditor &editor);
FileNode *findFile(TextEditor &editor, string &fileName);
FileNode *getFileByIndex(TextEditor &editor, int index);

// Fungsi kursor
void moveCursorLeft(FileNode *selectedFile);
void moveCursorRight(FileNode *selectedFile);

// Fungsi untuk operasi file
void addTextToFile(TextEditor &editor, FileNode *selectedFile);
void displayFileContent(FileNode *selectedFile);
void insertTextAfterCursor(FileNode *selectedFile);
void deleteCharacterAtCursor(FileNode *selectedFile);
void selectText(FileNode *selectFile, int startPos, int endPos);
void copyText(FileNode *selectedFile);
void pasteText(FileNode *selectedFile);
void cutText(FileNode *selectedFile, int startPos, int endPos);
void deleteTextInRange(FileNode *selectedFile, int startPos, int endPos);
void pasteCutText(FileNode *selectedFile);
int findText(FileNode *selectedFile, string &searchText, int startPos);
void replaceText(FileNode *selectedFile, string &searchText, string &replaceText, int startPos);
void undo(FileNode *selectedFile);
void redo(FileNode *selectedFile);
void tambahCharacterWithUndo(FileNode &file, char character);

// Fungsi menu
void displayMainMenu();
void displayFileMenu();

// Fungsi dan prosedur primitive untuk stack dan queue
void createStack(CharStack &stack);
bool isStackEmpty(CharStack &stack);
void push(CharStack &stack, char value);
char pop(CharStack &stack);
void createQueue(CharQueue &queue);
bool isQueueEmpty(CharQueue &queue);
void enqueue(CharQueue &queue, char value);
char dequeue(CharQueue &queue);

#endif
