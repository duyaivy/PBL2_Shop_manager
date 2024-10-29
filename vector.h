
#ifndef VECTOR_H
#define VECTOR_H
#include <stdexcept>

template <typename T>
class vector {
private:
    T* data;          
    size_t size;       //so luong phan tu hien tai cua vector
    size_t capacity;   // dung luong hien tai cua vector

   // resize capacity khi can thiet
    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    // Constructor
    vector() : data(nullptr), size(0), capacity(0) {}

    // Destructor
    ~vector() {
        delete[] data;
    }

   // them phan tu vao cuoi vector
    void push_back(const T& value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }

    // tuy caap theo chi so
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // tra ve so luong hien tai cua vector
    size_t getSize() const {
        return size;
    }
    // xoa element tai vi tri hien tai
      void erase(T* position) {
        if (position < data || position >= data + size) {
            throw std::out_of_range("Iterator out of range");
        }
        size_t index = position - data;
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }
    // empty
    int empty(){
        return (size ==0): 1?0;
    }
    //clear vector
    void clear() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
    }
    // ham thu hep dung luong xuong bằng size hien tai
    void shrink_to_fit(){
        if (size < capacity) {
        // tao mang moi bang kich thuoc hien co
        T* newData = new T[size];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = std::move(data[i]); // dung std:: de chuyen doi gia trij 
        }
        delete[] data; 
        data = newData; 
        capacity = size; 
        }
    }
    // dinh nghia interator de dung ham for each
    using iterator = T*;
    using const_iterator = const T*;

    // tra ve inter toi phan tu dau tien
    iterator begin() {
        return data;
    }

       // tra ve inter toi phan tu cuoi cung
    iterator end() {
        return data + size;
    }

    // tra ve inter toi phan tu dau tien cho doi tuong hang
    const_iterator begin() const {
        return data;
    }

    // tra ve inter toi phan tu cuoi cung cho doi tuong hang
    const_iterator end() const {
        return data + size;
    }
};

#endif // VECTOR_H
