#include "header.h"

// Fungsi untuk inisialisasi stack
void createStack(CharStack &Stack)
{
    Stack.top = nullptr; // Stack kosong
}

// Fungsi untuk memeriksa apakah stack kosong
bool isStackEmpty(CharStack &Stack)
{
    return Stack.top == nullptr;
}

// Fungsi untuk menambahkan elemen ke stack (push)
void push(CharStack &Stack, char value)
{
    CharNode *newNode = new CharNode;
    newNode->character = value;
    newNode->next = Stack.top; // Node baru menunjuk ke top lama
    Stack.top = newNode;       // Update top menjadi node baru
}

// Fungsi untuk menghapus elemen dari stack (pop)
char pop(CharStack &Stack)
{
    if (isStackEmpty(Stack))
    {
        cout << "Error: Stack kosong, tidak bisa pop.\n";
        return '\0'; // Return default value
    }

    CharNode *temp = Stack.top;
    char value = temp->character;
    Stack.top = Stack.top->next;
    delete temp;
    temp = nullptr; // Pastikan pointer temp tidak lagi menunjuk ke memori yang telah dihapus
    return value;
}

// Fungsi untuk mendapatkan elemen di atas stack tanpa menghapusnya (top)
char top(CharStack &Stack)
{
    if (isStackEmpty(Stack))
    {
        cout << "Error: Stack kosong, tidak ada elemen di atas stack.\n";
        return '\0'; // Return default value jika stack kosong
    }
    return Stack.top->character;
}

// Fungsi untuk inisialisasi queue
void createQueue(CharQueue &Queue)
{
    Queue.front = Queue.rear = nullptr; // Queue kosong
}

// Fungsi untuk memeriksa apakah queue kosong
bool isQueueEmpty(CharQueue &Queue)
{
    return Queue.front == nullptr;
}

// Fungsi untuk menambahkan elemen ke queue (enqueue)
void enqueue(CharQueue &Queue, char value)
{
    CharNode *newNode = new CharNode;
    newNode->character = value;
    newNode->next = nullptr;

    if (isQueueEmpty(Queue))
    {
        Queue.front = Queue.rear = newNode; // Queue kosong, front dan rear menunjuk ke node baru
    }
    else
    {
        Queue.rear->next = newNode; // Rear lama menunjuk ke node baru
        Queue.rear = newNode;       // Update rear ke node baru
    }
}

// Fungsi untuk menghapus elemen dari queue (dequeue)
char dequeue(CharQueue &Queue)
{
    if (isQueueEmpty(Queue))
    {
        cout << "Error: Queue kosong, tidak bisa dequeue.\n";
        return '\0'; // Return karakter kosong jika queue kosong
    }

    CharNode *temp = Queue.front;
    char value = temp->character;
    Queue.front = Queue.front->next; // Update front ke node berikutnya
    if (Queue.front == nullptr)      // Jika queue kosong setelah dequeue
    {
        Queue.rear = nullptr; // Update rear menjadi nullptr
    }
    delete temp;
    temp = nullptr; // Pastikan pointer temp tidak lagi menunjuk ke memori yang telah dihapus
    return value;
}
