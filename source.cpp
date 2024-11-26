#include "header.h" 

void createList(List &L) {
    L.first = nullptr;
    L.last = nullptr;
}

address createElement(string text) {
    address newElm = new elmList;
    newElm->info = text;
    newElm->prev = nullptr;
    newElm->next = nullptr;
    return newElm;
}

void insertLine(List &L, string text, int lineNumber) {
    address newElm = createElement(text);
    if (L.first == nullptr) {
        L.first = L.last = newElm;
    } else {
        address current = L.first;
        int count = 1;

        while (current && count < lineNumber) {
            current = current->next;
            count++;
        }

        if (current == nullptr) { // Append at the end
            L.last->next = newElm;
            newElm->prev = L.last;
            L.last = newElm;
        } else { // Insert before current
            newElm->next = current;
            newElm->prev = current->prev;

            if (current->prev) current->prev->next = newElm;
            else L.first = newElm;

            current->prev = newElm;
        }
    }
}

void deleteLine(List &L, int lineNumber) {
    if (L.first == nullptr) return;

    address current = L.first;
    int count = 1;

    while (current && count < lineNumber) {
        current = current->next;
        count++;
    }

    if (current == nullptr) {
        return;
    } 

    if (current->prev) current->prev->next = current->next;
    else L.first = current->next;

    if (current->next) current->next->prev = current->prev;
    else L.last = current->prev;

    delete current;
}

void displayListFromFront(List L) {
    address current = L.first;
    while (current) {
        cout << current->info << endl;
        current = current->next;
    }
}

void displayListFromBack(List L) {
    address current = L.last;
    while (current) {
        cout << current->info << endl;
        current = current->prev;
    }
}

void createStack(Stack &S) {
    S.top = nullptr;
}

void pushStack(Stack &S, string action, string data, int lineNumber) {
    addressStack newElm = new elmStack;
    newElm->action = action;
    newElm->data = data;
    newElm->lineNumber = lineNumber;
    newElm->next = S.top;
    S.top = newElm;
}

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

bool isStackEmpty(Stack S) {
    return S.top == nullptr;
}

void createQueue(Queue &Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

void enqueueClipboard(Queue &Q, string data) {
    addressQueue newElm = new elmQueue;
    newElm->clipboardData = data;
    newElm->next = nullptr;

    // Jika queue kosong
    if (Q.head == nullptr) {
        Q.head = newElm;
        Q.tail = newElm;
        return;
    }

    // Jika queue tidak kosong
    Q.tail->next = newElm;
    Q.tail = newElm;
}

bool dequeueClipboard(Queue &Q, string &data) {
    // Jika queue kosong
    if (Q.head == nullptr) {
        return false;
    }

    // Jika queue tidak kosong
    addressQueue temp = Q.head;
    data = temp->clipboardData;

    Q.head = Q.head->next;

    // Jika elemen terakhir dihapus
    if (Q.head == nullptr) {
        Q.tail = nullptr;
    }

    delete temp;
    return true;
}

bool isQueueEmpty(Queue Q) {
    return Q.head == nullptr;
}

void kosongkanRedo(Stack &redoStack) {
    string action, data;
    int lineNumber;
    while (!isStackEmpty(redoStack)) {
        popStack(redoStack, action, data, lineNumber);
    }
}

void deleteBarisDenganUndo(List &L, Stack &undoStack, int nomorBaris) {
    address current = L.first;
    int count = 1;

    while (current && count < nomorBaris) {
        current = current->next;
        count++;
    }

    if (!current) {
        cout << "Baris tidak ditemukan.\n";
        return;
    }

    string teks = current->info;
    pushStack(undoStack, "DELETE", teks, nomorBaris);
    deleteLine(L, nomorBaris);
}

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

void pasteLine(List &L, Queue &clipboardQueue, int lineNumber) {
    string clipboardData;
    if (!dequeueClipboard(clipboardQueue, clipboardData)) {
        cout << "Clipboard kosong, tidak ada teks untuk ditempel.\n";
        return;
    }

    insertLine(L, clipboardData, lineNumber);
    cout << "Teks \"" << clipboardData << "\" telah ditempel di baris " << lineNumber << ".\n";
}

