#ifndef _MYVECTOR_HPP
#define _MYVECTOR_HPP

#include <iostream>
#include <stdexcept>

template<typename T>
class MyVector {
public:
    MyVector();
    MyVector(T* data, size_t size, size_t capacity);
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    MyVector& operator=(MyVector&& other) noexcept;
    ~MyVector();

    void setVector(T* data, size_t size, size_t capacity);

    const T* getVector() const;
    size_t getVectorSize() const;
    size_t getVectorCapacity() const;

    bool isEmpty() const;
    void clear();
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void pushBack(const T& obj);
    void pushBack(T&& obj);
    T popBack();
    bool contains(const T* element) const;
    bool contains(const T& element) const;
    void remove(const T& element);
	void remove(const T* element);
    void removeAt(size_t index);

private:
    T* data;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity);
    void copyFrom(const MyVector& other);
    void moveFrom(MyVector&& other) noexcept;
    void freeVector();
};


template<typename T>
inline MyVector<T>::MyVector() : data(nullptr), size(0), capacity(0) {}

template<typename T>
inline MyVector<T>::MyVector(T* data, size_t size, size_t capacity) {
    setVector(data, size, capacity);
}

template<typename T>
inline MyVector<T>::MyVector(const MyVector& other) {
    copyFrom(other);
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this != &other) {
        freeVector();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
inline MyVector<T>::MyVector(MyVector&& other) noexcept {
    moveFrom(std::move(other));
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        freeVector();
        moveFrom(std::move(other));
    }
    return *this;
}

template<typename T>
inline MyVector<T>::~MyVector() {
    freeVector();
}

template<typename T>
inline void MyVector<T>::resize(size_t newCapacity) {
    T* resizedData = new T[newCapacity];
    size_t limit = (size < newCapacity) ? size : newCapacity;
    for (size_t i = 0; i < limit; ++i) {
        resizedData[i] = std::move(data[i]);
    }
    delete[] data;
    data = resizedData;
    capacity = newCapacity;
    size = limit;
}

template<typename T>
inline void MyVector<T>::copyFrom(const MyVector& other) {
    if (other.data == nullptr) {
        throw std::invalid_argument("Vector cannot be null!");
    }

    if (other.size > other.capacity) {
        throw std::invalid_argument("Size of vector cannot be more than its capacity!");
    }

    capacity = other.capacity;
    size = other.size;
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

template<typename T>
inline void MyVector<T>::moveFrom(MyVector&& other) noexcept {
    data = other.data;
    size = other.size;
    capacity = other.capacity;

    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<typename T>
inline void MyVector<T>::freeVector() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

template<typename T>
inline void MyVector<T>::setVector(T* inputData, size_t inputSize, size_t inputCapacity) {
    if (inputData == nullptr) {
        throw std::invalid_argument("Vector cannot be null!");
    }

    if (inputSize > inputCapacity) {
        throw std::invalid_argument("Size of vector cannot be more than its capacity!");
    }

    freeVector();
    capacity = inputCapacity;
    size = inputSize;
    data = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        data[i] = inputData[i];
    }
}

template<typename T>
inline const T* MyVector<T>::getVector() const {
    return data;
}

template<typename T>
inline size_t MyVector<T>::getVectorSize() const {
    return size;
}

template<typename T>
inline size_t MyVector<T>::getVectorCapacity() const {
    return capacity;
}

template<typename T>
inline bool MyVector<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
inline void MyVector<T>::clear() {
    size = 0;
}

template<typename T>
inline T& MyVector<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::invalid_argument("Index is out of range!");
    }
    return data[index];
}

template<typename T>
inline const T& MyVector<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::invalid_argument("Index is out of range!");
    }
    return data[index];
}

template<typename T>
inline void MyVector<T>::pushBack(const T& obj) {
    if (size >= capacity) {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resize(newCapacity);
    }
    data[size++] = obj;
}

template<typename T>
inline void MyVector<T>::pushBack(T&& obj) {
    if (size >= capacity) {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        resize(newCapacity);
    }
    data[size++] = std::move(obj);
}

template<typename T>
inline T MyVector<T>::popBack() {
    if (isEmpty()) {
        throw std::length_error("Vector is already empty!");
    }
    return data[--size];
}

template<typename T>
inline bool MyVector<T>::contains(const T* element) const {
    if (element == nullptr) {
        throw std::invalid_argument("Element cannot be null!");
    }

    for (size_t i = 0; i < size; ++i) {
        if (&data[i] == element) {
            return true;
        }
    }
    return false;
}

template<typename T>
inline bool MyVector<T>::contains(const T& element) const {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] == element) {
            return true;
        }
    }
    return false;
}

template<typename T>
inline void MyVector<T>::remove(const T& element) {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] == element) {
            for (size_t j = i; j < size - 1; ++j) {
                data[j] = data[j + 1];
            }
            --size;
            return;
        }
    }

    throw std::invalid_argument("Element not found in vector!");
}

template<typename T>
inline void MyVector<T>::remove(const T* element) {
    if (element == nullptr) {
        throw std::invalid_argument("Element cannot be null!");
    }

    for (size_t i = 0; i < size; ++i) {
        if (&data[i] == element) {
            for (size_t j = i; j < size - 1; ++j) {
                data[j] = data[j + 1];
            }
            --size;
            return;
        }
    }

    throw std::invalid_argument("Element not found in vector!");
}

template<typename T>
inline void MyVector<T>::removeAt(size_t index) {
	if (index >= size) {
		throw std::invalid_argument("Index is out of range!");
	}

	for (size_t i = index; i < size - 1; ++i) {
		data[i] = data[i + 1];
	}
	--size;
}

#endif // !_MYVECTOR_HPP