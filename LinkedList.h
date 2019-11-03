#ifndef LINKEDLISTCLASS_LINKEDLIST_H
#define LINKEDLISTCLASS_LINKEDLIST_H

class LinkedList {
public:
    struct Node {
        int val;
        Node* ptr;
    };
    LinkedList();
    ~LinkedList();
    explicit LinkedList(int val);
    void printAll();
    void append(int val);
    void appendFront(int val);
    void remove(int index);
    void removeFirst();
    void removeLast();
    int get(int index);
    int count();

private:
    void actuallyRemoveIndex(int index);
    Node* createNewNodeWithVal(int val);
    void deleteAll();
    Node* root;
    Node* tail;
    int size = 0;
};


#endif //LINKEDLISTCLASS_LINKEDLIST_H
