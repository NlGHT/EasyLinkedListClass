#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
    LinkedList<int> linkedList(200);
    linkedList.append(59999);
    linkedList.printAll();
    linkedList.append(10);
    linkedList.printAll();
    linkedList.remove(0);
    linkedList.printAll();
    linkedList.append(5);
    linkedList.append(69);
    linkedList.append(134);
    cout << "Just appended 5, 69 and 134" << endl;
    linkedList.get(5);
    cout << "Hey!  That value at index 3 is: " << linkedList.get(3) << endl;
    linkedList.printAll();
    linkedList.removeLast();
    linkedList.printAll();
    linkedList.remove(1); // This doesn't work :(
    linkedList.printAll();
    linkedList.remove(-1);
    cout << "Negative remove!" <<  endl;
    linkedList.printAll();
    linkedList.appendFront(5);
    linkedList.printAll();
    linkedList.appendFront(10);
    linkedList.printAll();
    linkedList.append(420);
    linkedList.printAll();
    linkedList.remove(2);
    linkedList.printAll();
    cout << "Getting -2 value: " << linkedList.get(-2) << endl;
    linkedList.removeFirst();
    linkedList.removeFirst();
    linkedList.removeFirst();
    linkedList.removeFirst();
    linkedList.removeFirst();
    linkedList.removeFirst();
    linkedList.append(0);
    linkedList.append(5);
    cout << linkedList.get(0) << endl;
    return 0;
}