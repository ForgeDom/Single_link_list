#include <iostream>
#include <Windows.h>

using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
};

template <typename T>
class SinglyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    SinglyLinkedList() : head(nullptr), tail(nullptr) {}

    void AddToHead(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
    }

    void AddToTail(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void DeleteFromHead() {
        if (!head) {
            cout << "Список порожній!" << endl;
            return;
        }
        Node<T>* temp = head;
        head = head->next;
        if (!head) {
            tail = nullptr;
        }
        delete temp;
    }

    void DeleteFromTail() {
        if (!head) {
            cout << "Список порожній!" << endl;
            return;
        }
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != tail) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
    }

    void DeleteAll() {
        while (head) {
            DeleteFromHead();
        }
    }

    void Show() const {
        if (!head) {
            cout << "Список порожній!" << endl;
            return;
        }
        Node<T>* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~SinglyLinkedList() {
        DeleteAll();
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    SinglyLinkedList<int> list;

    list.AddToHead(10);
    list.AddToHead(20);
    list.AddToTail(30);
    list.Show();

    list.DeleteFromHead();
    list.Show();

    list.DeleteFromTail();
    list.Show();

    list.DeleteAll();
    list.Show();

    return 0;
}
