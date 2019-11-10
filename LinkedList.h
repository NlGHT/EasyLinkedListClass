#ifndef LINKEDLISTCLASS_LINKEDLIST_H
#define LINKEDLISTCLASS_LINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <cassert>
#include <string>

using namespace std;

template<typename T> class LinkedList {
public:
    struct Node {
        T val;
        Node* ptr;
    };
    LinkedList();
    ~LinkedList();
    explicit LinkedList(T val);
    void printAll();
    void append(T val);
    void appendFront(T val);
    void remove(int index);
    void removeFirst();
    void removeLast();
    T get(int index);
    int count();
    void insertAtIndex(T val, int index);

private:
    void actuallyRemoveIndex(int index);
    Node* createNewNodeWithVal(T val);
    void deleteAll();
    void throwOOBException(int indexRequested);
    Node* root;
    Node* tail;
    int size = 0;
};
#endif //LINKEDLISTCLASS_LINKEDLIST_H


// ----Start class implementation----
template<typename T>
LinkedList<T>::LinkedList() {
    root = nullptr;
    tail = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    deleteAll();
}

template<typename T>
LinkedList<T>::LinkedList(T val) {
    root = nullptr;
    tail = nullptr;
    append(val);
}

template<typename T>
void LinkedList<T>::printAll() {
    assert(size > 0);
    cout << "List at current time:" << endl;
    for (Node *walk = root; walk != nullptr; walk = walk->ptr) {
        cout << walk->val << endl;
    }
}

template<typename T>
int LinkedList<T>::count() {
    return size;
}

template<typename T>
void LinkedList<T>::appendFront(T val) {
    Node* newHead = createNewNodeWithVal(val);
    if (size == 0) {
        newHead->val = val;
        newHead->ptr = nullptr;
        tail = nullptr;
    } else if (size == 1) {
        newHead->val = val;
        newHead->ptr = root;
        root->ptr = nullptr;
        tail = root;
    } else {
        newHead->val = val;
        newHead->ptr = root;
    }
    root = newHead;
    size++;
}

template<typename T>
void LinkedList<T>::append(T val) {
    Node* newTail = createNewNodeWithVal(val);
    if (size == 0) {
        root = newTail;
        tail = nullptr;
    } else if (size == 1) {
        tail = newTail;
        root->ptr = tail;
    } else {
        tail->ptr = newTail;
        tail = newTail;
    }
    size++;
}

template<typename T>
void LinkedList<T>::remove(int index) {
    assert(size > 0);
    if (index == 0) {
        removeFirst();
    } else {
        index = (index < 0) ? size + index : index; // Fix negative index so it counts back from end
        if (index > size - 1) {
            throwOOBException(index);
        } else if (index == size - 1) {
            removeLast();
        } else {
            actuallyRemoveIndex(index);
        }
    }
}

template<typename T>
void LinkedList<T>::removeFirst() {
    assert(size > 0);
    if (size == 1) {
        free(root);
        root = nullptr;
        tail = nullptr;
        size = 0;
    } else if (size == 2) {
        Node* temp = root;
        root = root->ptr;
        free(temp);
        tail = nullptr;
        size = 1;
    } else {
        Node* temp = root;
        root = root->ptr;
        free(temp);
        size--;
    }
}

template<typename T>
void LinkedList<T>::removeLast() {
    assert(size > 0);
    if (size == 1) {
        free(root);
        root = nullptr;
        tail = nullptr;
        size = 0;
    } else if (size == 2) {
        root->ptr = nullptr;
        free(tail);
        tail = nullptr;
        size = 1;
    } else {
        for (Node *walk = root; walk; walk = walk->ptr) {
            if (walk->ptr == tail) {
                Node* temp = walk->ptr;
                tail = walk;
                tail->ptr = nullptr;
                free(temp);
                size--;
            }
        }
    }
}

template<typename T>
void LinkedList<T>::actuallyRemoveIndex(int index) {
    signed int i = 0;
    for (Node* walk = root; walk; walk = walk->ptr, i++) {
        if (i == index-1) {
            Node* beforeDeletion = walk;
            walk = walk->ptr;
            beforeDeletion->ptr = walk->ptr;
            free(walk);
            size--;
            break;
        }
    }
}

template<typename T>
typename LinkedList<T>::Node *LinkedList<T>::createNewNodeWithVal(T val) {
    Node *newTail;
    newTail = static_cast<Node *>(malloc(sizeof(Node)));
    newTail->val = val;
    newTail->ptr = nullptr;
    return newTail;
}

template<typename T>
void LinkedList<T>::deleteAll() {
    if (size > 0) {
        Node* walk = root;
        while (true) {
            if (walk->ptr == nullptr) {
                free(walk);
                root = nullptr;
                tail = nullptr;
                delete root;
                delete tail;
                break;
            } else {
                Node* temp = walk;
                walk = walk->ptr;
                free(temp);
            }
        }
    }
}

template<typename T>
T LinkedList<T>::get(int index) {
    index = (index < 0) ? size + index : index; // Fix negative index so it counts back from end
    if (index > size-1) {
        throwOOBException(index);
        return -1;
    } else {
        signed int i = 0;
        for (Node *walk = root; walk; walk = walk->ptr, i++) {
            if (i == index) {
                return walk->val;
            }
        }
    }
    return 0;
}

template<typename T>
void LinkedList<T>::insertAtIndex(T val, int index) {
    index = (index < 0) ? size + index : index; // Fix negative index so it counts back from end
    if (index > size) {
        throwOOBException(index);
    } else {
        if (index == size) {
            append(val);
        } else if (index == 0) {
            appendFront(val);
        } else {
            signed int i = 0;
            for (Node *walk = root; walk; walk = walk->ptr, i++) {
                if (i == index - 1) {
                    Node *newNode = createNewNodeWithVal(val);
                    Node *tempWalk = walk;
                    walk = walk->ptr;
                    tempWalk->ptr = newNode;
                    newNode->ptr = walk;
                    break;
                }
            }
        }
    }
}

template<typename T>
void LinkedList<T>::throwOOBException(int indexRequested) {
    string errorBuilder;
    if (indexRequested >= size) {
        errorBuilder.append("Index ");
        errorBuilder.append(to_string(indexRequested));
        errorBuilder.append(" requested is out of bounds.  Range: -");
        errorBuilder.append(to_string(size - 1));
        errorBuilder.append(" to ");
        errorBuilder.append(to_string(size - 1));
        errorBuilder.append(".");
        deleteAll();
        throw out_of_range(errorBuilder);
    } else if (size == 0) {
        errorBuilder.append("Attempted to access list when there was no items.");
    }
}
