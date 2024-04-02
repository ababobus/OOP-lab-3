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

    int get_size() {//размер списка
        return size;
    }
    


    T take_front() { //получение первого элемент списка
        if (size != 0) {
            return front->data;
        }
        else {
            return 0;
        }
    }

    T pop_front() {//удаление первого элемента списка
        T value = front->data;

        if (size == 1) {
            delete front;
            front = nullptr;
            back = nullptr;
            size--;
            return value;
        }

        if (size == 0) {
            throw std::out_of_range("empty list");
            return 0;
        }

        front = front->next;
        delete front->prev;
        front->prev = nullptr;
        size--;
        return value;
    }

    T take_back() {//получение последнего элемента списка
        if (size != 0) {
            return back->data;
        }
        else {
            return 0;
        }
    }

    T pop_back() {//удаление последнего элемента списка
        T value = back->data;

        if (size == 1) {
            delete back;
            front = nullptr;
            back = nullptr;
            size--;
            return value;
        }

        if (size == 0) {
            throw std::out_of_range("empty list");
            return 0;
        }

        back = back->prev;
        delete back->next;
        back->next = nullptr;
        size--;
        return value;
    }

    T *position(int index) { //получение указателя на объект по индексу (для получения объекта по индексу)
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

    T get_value(int index) { //получение объекта по индексу
        return position(index)->data;
    }

    void first() {
    };
    void last() {
    };
    void get_next() {
    };
    void get_prev() {
    };
    bool not_end() {
    };

    void push_front(T object) {//вставка элемента в начало 
        MyBase<T> *buf = new MyBase<T>(object);
        buf->data = object;
        buf->prev = nullptr;
        buf->next = front; //одностороння связь буф и фронта (0 и 1 элем)

        if (size > 0) {
            
            front = buf; //двусторонняя связь, перетаскиваем фронт
            front->next = front;
            front->prev = nullptr;
        }
        else {
            back = buf;
        }
        size++;
    }

    void push_back(T object) {//вставка элемента в конец
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

    void insert(int index, T object) {//вставка элемента по индексу
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index == size) {
            push_back(value);
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
            return popFront();
        }
        if (index == size - 1) {
            return popBack();
        }
        if (index < 0 || index > size) {
            throw std::out_of_range("wrong index");
            return;
        }

        MyBase<T> * buf = position(index);
        T value = buf->data;
        (buf->prev)->next = buf->next;
        (buf>next)->prev = buf->prev;

        delete buf;
        size--;
        return value;
    }

    T remove(MyBase<T> *object) { //удаление обджекта из списка
        if (object == front) {
            pop_front();
            return;
        }
        if (object == back) {
            pop_back();
            return;
        }
        T value = object->data;
        (object->prev)->next = object->next;
        (object->next)->prev = object->prev;

        delete object;
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
    std::cout << "Hello World!\n";
}
