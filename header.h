#ifndef HEADER_INCLUDED
#define HEADER_INCLUDED

#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

// Struktur Node untuk karakter (linked list karakter)
struct CharNode
{
    char character; // Karakter yang disimpan
    CharNode *next; // Pointer ke node karakter berikutnya
};

struct UndoRedoStack
{
    stack<char> undoStack; // Stack untuk undo
    queue<char> redoQueue; // Queue untuk redo
};

// Struktur Node untuk file (linked list file)
struct FileNode
{
    string fileName;        // Nama file
    CharNode *head;         // Pointer ke linked list karakter
    FileNode *next;         // Pointer ke file berikutnya
    int cursorPosition;     // Posisi kursor dalam file
    string clipboard;       // Menyimpan teks yang disalin
    stack<char> cutBuffer;  // Stack untuk menyimpan teks yang dipotong
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
void displayCursorPosition(FileNode *selectedFile);

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
void addCharacterToFile(FileNode &file, char character);

// Fungsi menu
void displayMainMenu();
void displayFileMenu();

#endif
