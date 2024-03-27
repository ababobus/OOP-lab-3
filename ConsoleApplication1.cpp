#include <iostream>

template<typename T>
class MyBase {
public:
    T data;
    MyBase<T> *next = nullptr;
    MyBase<T> *prev = nullptr;

    MyBase() {} 

    MyBase(T value) {
        data(value);
        empty_check = false;
    }

    ~MyBase() {}
};

template <typename T>
class MyStorage {
private:
    MyBase<T> *front = nullptr;
    MyBase<T> *back = nullptr;
    int size = 0;
public:
    MyStorage() {
        std::cout << "MyStorage\n";
    }
    ~MyStorage() {
        while (front) {
            back = front->next;
            delete front;
            front = back;
        }
        std::cout << "~MyStorage\n";
    }


    void push_front(T object) {
        MyBase<T> * buf = new MyBase<T>(object);
        buf->data = object;
        buf->front = nullptr;
        buf->back = front; //одностороння связь буф и фронта (0 и 1 элем)

        if (size > 0) {
            front->prev = nullptr; //двсторонняя связь
            front = buf; //перетаскиваем фронт
        }
        else {
            back = buf;
        }
        size++;
    }

    void push_back(T object) {
        MyBase<T>* buf = new MyBase<T>;
        buf->data = object;
        buf->front = back;
        buf->back = nullptr;

        if (size > 0) {
            back->next = buf;
            back = buf;
        }
        else {
            front = buf;
        }
        size++;
    }

    void insert(int index, T object) {
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index == size) {
            push_back(value);
            return;
        }
        if (index < 0 || index > size) {
            cout << "out of range";
            return;
        }

        MyBase<T>* buf = front;

        for (int i = 0; i < index; i++) {
            buf = buf->next;
        }

        MyBase<T>* old = buf; //принимает значение элемента с заданным индексом
        buf = new MyBase<T>(object);
        buf->prev = old->prev;
        buf->next = old;




    }

    
    
};

int main()
{
    MyStorage <int> a;

    for (int i = 0; i < 10; i++) {
        a.push_back(i);
    }
    std::cout << "Hello World!\n";
}
