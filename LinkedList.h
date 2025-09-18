#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <functional>

// Node class template
template<typename T>
class Node {
private:
    T data;
    Node<T>* next;

    // Grant LinkedList access to private members
    template<typename> friend class LinkedList;

public:
    Node(T val) : data(val), next(nullptr) {}
};

template<typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    void append(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head)
            head = newNode;
        else {
            Node<T>* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
    }

    // Store current head, if it is not null. Set head to newNode. Set head->next to stored node or null if
    // it doesn't exist.
    void addFirst(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = newNode;
            head->next = nullptr;
        } else {
            Node<T>* temp = head;
            head = newNode;
            head->next = temp;
        }
    }

    // If the list is empty, return. Otherwise, store current head as curr, make head->next = head,
    // delete curr.
    void deleteFirst() {
        if (head == nullptr)
            return;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }

    // If list is empty, return. Otherwise, if there is only one element, delete it and make the head null.
    // If there is more than one element, continuously check that the next, next element is not null.
    // If it is null, delete the next element and set next to null.
    void deleteLast() {
        if (!head)
            return;
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
        } else {
            Node<T>* temp = head;
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
    }

    // Loop through the list until temp->next is at the target index. Delete head->next and set head->next
    // to head->next->next if it is not null. Otherwise, set head->next->next to null. If the target index
    // is out of bounds, return.
    void deleteAtIndex(int index) {
        if (!head)
            return;
        if (index == 0) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        else if (index > 0) {
            Node<T>* temp = head;
            for (int i = 0; i < index - 1; i++) {
                if (temp->next != nullptr)
                    temp = temp->next;
                else
                    return;
            }
            if (temp->next == nullptr)
                return;
            Node<T>* tNext = temp->next;
            temp->next = temp->next->next;
            delete tNext;
        }
    }
    void forEach(std::function<void(const T&, bool)> callback) {
        Node<T>* current = head;
        while (current) {
            bool isLast = (current->next == nullptr);
            callback(current->data, isLast);
            current = current->next;
        }
    }

    // Destructor to delete each element once the program is done, releasing memory space
    ~LinkedList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

#endif // LINKEDLIST_H