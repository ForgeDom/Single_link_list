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

    void InsertAtPosition(T val, int pos) {
        if (pos < 1) {
            cout << "Неможлива позицыя!" << endl;
            return;
        }
        Node<T>* newNode = new Node<T>(val);
        if (pos == 1) {
            AddToHead(val);
            return;
        }
        Node<T>* temp = head;
        for (int i = 1; i < pos - 1 && temp; ++i) {
            temp = temp->next;
        }
        if (!temp) {
            cout << "Позиція виходить за межі списку!" << endl;
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        if (newNode->next == nullptr) {
            tail = newNode;
        }
    }

    void DeleteAtPosition(int pos) {
        if (pos < 1 || !head) {
            cout << "Неможлива позиція або список порожній!" << endl;
            return;
        }
        if (pos == 1) {
            DeleteFromHead();
            return;
        }
        Node<T>* temp = head;
        for (int i = 1; i < pos - 1 && temp->next; ++i) {
            temp = temp->next;
        }
        if (!temp->next) {
            cout << "Позиція виходить за межі списку!" << endl;
            return;
        }
        Node<T>* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        if (!temp->next) {
            tail = temp;
        }
        delete nodeToDelete;
    }

    int Search(T val) {
        Node<T>* temp = head;
        int pos = 1;
        while (temp) {
            if (temp->data == val) {
                return pos;
            }
            temp = temp->next;
            ++pos;
        }
        return 0; 
    }

    int SearchAndReplace(T oldVal, T newVal) {
        Node<T>* temp = head;
        int count = 0;
        while (temp) {
            if (temp->data == oldVal) {
                temp->data = newVal;
                ++count;
            }
            temp = temp->next;
        }
        return count > 0 ? count : -1; 
    }

    void Reverse() {
        if (!head || !head->next) {
            return;
        }
        Node<T>* prev = nullptr;
        Node<T>* curr = head;
        tail = head;
        while (curr) {
            Node<T>* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
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

    list.InsertAtPosition(25, 3);
    list.Show();

    list.DeleteAtPosition(2);
    list.Show();

    int pos = list.Search(30);
    if (pos) {
        cout << "Елемент 30 знайдено на позиції: " << pos << endl;
    }
    else {
        cout << "Елемент 30 не знайдено!" << endl;
    }

    int replacedCount = list.SearchAndReplace(25, 50);
    if (replacedCount != -1) {
        cout << "Кількість замінених елементів: " << replacedCount << endl;
    }
    else {
        cout << "Елемент для заміни не знайдено!" << endl;
    }

    list.Show();

    list.Reverse();
    cout << "Список після перевертання: ";
    list.Show();

    return 0;
}
