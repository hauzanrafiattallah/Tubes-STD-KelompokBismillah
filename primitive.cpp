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