#ifndef STACK_H
#define STACK_H

#include <stdexcept>

template <typename T>
class Stack {
private:
    T* data;
    int top;
    int capacity;

public:

    Stack() : top(-1), capacity(1) {
        data = new T[capacity];
    }


    Stack(int capacity) : top(-1), capacity(capacity) {
        data = new T[capacity];
    }


    ~Stack() {
        delete[] data;
    }


    bool isEmpty() const {
        return top < 0;
    }


    int getTop() const {
        return top;
    }


    T* getData() const {
        return data;
    }


    void push(const T& val) {
        if (top + 1 >= capacity) {

            capacity *= 2;
            T* newData = new T[capacity];
            for (int i = 0; i <= top; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[++top] = val;
    }


    T pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack underflow");
        }
        return data[top--];
    }


    void freeStack() {
        delete[] data;
        data = nullptr;
        top = -1;
        capacity = 0;
    }
};

#endif // STACK_H