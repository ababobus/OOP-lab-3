#include <iostream>

template<typename T>
class MyBase {
public:
    T data;
    MyBase<T> *next = nullptr;
    MyBase<T> *prev = nullptr;

    MyBase() {} 

    MyBase(T value) {
        data = value;
    }

    ~MyBase() {}
};

template <typename T>
class MyStorage {
private:
    MyBase<T> *front = nullptr;
    MyBase<T> *back = nullptr;
    MyBase<T> *current = nullptr;
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

    int get_size() {
        return size;
    }
    void get_next() {
        if (current == nullptr) {
            return;
        }
        if (current->next != nullptr) {
            current = current->next;
            return;
        }
        return;
    }

    void get_prev() {
        if (current == nullptr) {
            return;
        }
        if (current->prev != nullptr) {
            current = current->prev;
            return;
        }
        return;
    }

    T take_front() { 
        if (size == 0) {
            return 0;
        }
        else {
            return front->data;
        }
    }

    T pop_front() {//получнеие и удаление первого элемента списка

        T value = front->data;

        if (size == 0) {
            throw std::out_of_range("empty list");
            return 0;
        }

        if (size == 1) {
            delete front;
            front = nullptr;
            back = nullptr;
            size--;
            return value;
        }

        front = front->next;
        delete front->prev;
        front->prev = nullptr;
        size--;
        return value;
    }

    T take_back() {//получение последнего элемента списка
        if (size == 0) {
            return 0;
        }
        else {
            return back->data;
        }
    }

    T pop_back() {//получение и удаление последнего элемента списка
        T value = back->data;

        if (size == 0) {
            throw std::out_of_range("empty list");
            return 0;
        }

        if (size == 1) {
            delete back;
            front = nullptr;
            back = nullptr;
            size--;
            return value;
        }

        back = back->prev;
        delete back->next;
        back->next = nullptr;
        size--;
        return value;
    }

    MyBase<T> *position(int index) { //получение указателя на объект,  по индексу 
        MyBase<T> *buf = front;
        for (int i = 0; i < size; i++) {
            if (i == index) {
                return buf;
            }
            else {
                buf = buf->next;
            }
        }
        return nullptr;
    }

    T get_value(int index) { //получение значения элемента по индексу
        return position(index)->data;
    }

    void push_front(T object) {//вставка элемента в начало 
        MyBase<T> *buf = new MyBase<T>(object);
        buf->data = object;
        buf->prev = nullptr;
        buf->next = front; 

        if (size > 0) {
            front->prev = buf;
            front = buf;
        }
        else {
            back = buf;
            front = buf;
        }
        size++;
    }

    void push_back(T object) {//вставка элемента в конец
        MyBase<T>* buf = new MyBase<T>;
        buf->data = object;
        buf->prev = back;
        buf->next = nullptr;

        if (size) {
            back->next = buf;
            back = buf;
        }
        else {
            front = buf;
            back = buf;
        }
        size++;
    }

    void insert(int index, T object) {//вставка элемента по индексу
        if (index == 0) {
            push_front(object);
            return;
        }
        if (index == size) {
            push_back(object);
            return;
        }
        if (index < 0 || index > size) {
            throw std::out_of_range("wrong index");
            return;
        }

        MyBase<T>* buf = front;

        for (int i = 0; i < index; i++) {
            buf = buf->next;
        }

        MyBase<T>* old = buf; //принимает значение элемента с заданным индексом
        buf = new MyBase<T>(object);
        buf->prev = old->prev; 
        buf->next = old; //односторонняя связь

        (old->prev)->next = buf;//двусторонняя связь
        old->prev = buf;
        
        size++;
    }




    T remove(int index) { //удаление элем по индексу
        if (index == 0) {
            return pop_front();
        }
        if (index == size - 1) {
            return pop_back();
        }
        if (index < 0 || index > size) {
            throw std::out_of_range("wrong index");
            return 0;
        }

        MyBase<T>* buf = position(index);
        T value = buf->data;
        (buf->prev)->next = buf->next;
        (buf->next)->prev = buf->prev;

        delete buf;
        size--;
        return value;
    }

    
};

int main()
{
    MyStorage <int> a;


    for (int i = 0; i < 10; i++) {
        a.push_back(i);
    }
    a.insert(3, 32);
    
    a.remove(7);

    std::cout<<a.take_back() << std::endl;
   
    std::cout<< a.get_value(7) << std::endl;
    
    //std::cout << a.take_front();

    std::cout << "Hello World!\n";
    return 0;
}
