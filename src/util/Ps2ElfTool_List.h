#ifndef PS2ELFTOOL_LIST_H
#define PS2ELFTOOL_LIST_H

#include "../Ps2ElfTool_Common.h"
#include "Ps2ElfTool_Array.h"

#define DEFAULT_CAPACITY 16

template<typename T>
class List
{
public:
    List<T>()
    {
        this->capacity = DEFAULT_CAPACITY;
        this->ptr = new T[this->capacity];
        this->size = 0;
    }
    List<T>(u64 startCapacity)
    {
        this->capacity = startCapacity;
        this->ptr = new T[this->capacity];
        this->size = 0;
    }
    List<T>(Array<T> arr)
    {
        this->capacity = arr.Size();
        this->size = this->capacity;
        this->ptr = new T[this->capacity];
        for(int i=0;i<this->size;i++) {
            this->ptr[i] = arr[i];
        }
    }
    List<T>(List<T>& list)
    {
        this->capacity = list.capacity;
        this->ptr = new T[this->capacity];
        this->size = list.size;
        for(int i=0;i<list.size;i++) {
            this->ptr[i] = list.ptr[i];
        }
    }
    ~List()
    {
        if(this->ptr) {
            delete[] this->ptr;
            this->ptr = nullptr;
            this->size = 0;
            this->capacity = 0;
        }
    }

    T& operator[](u64 index)
    {
        return this->ptr[index];
    }

    List<T>& operator+=(T item)
    {
        Add(item);
        return *this;
    }
    List<T>& operator+=(List<T> list)
    {
        for (T item : list) {
            Add(item);
        }
    }
    List<T>& operator+=(Array<T> list)
    {
        for (T item : list) {
            Add(item);
        }
    }

    List<T>& operator=(List<T> list)
    {
        if(this->ptr) {
            delete[] this->ptr;
        }
        this->ptr = new T[list.capacity];
        this->capacity = list.capacity;
        for(int i=0;i<list.size;i++) {
            this->ptr[i] = list.ptr[i];
        }
        this->size = list.size;
        return *this;
    }

    bool operator==(List<T>& list)
    {
        if(this->size != list.size) return false;

        for(int i=0;i<this->size;i++) {
            if(this->ptr[i] != list.ptr[i]) return false;
        }
        return true;
    }

    void Add(T item)
    {
        if(this->size == this->capacity) {
            this->enlarge();
        }
        this->ptr[this->size++] = item;
    }

    T Get(u64 index) const
    {
        return this->ptr[index];
    }

    u64 Size() { return this->size; }
    u64 Capacity() { return this->capacity; }

    T* Cptr() { return this->ptr; }

private:
    T* ptr;
    u64 size;
    u64 capacity;

    void enlarge() {
        this->capacity *= 2;
        T* newptr = new T[this->capacity];
        for(int i=0;i<this->size;i++) {
            newptr[i] = this->ptr[i];
        }
        delete[] this->ptr;
        this->ptr = newptr;
    }
};

#endif // PS2ELFTOOL_LIST_H

