#ifndef PS2ELFTOOL_ARRAY_H
#define PS2ELFTOOL_ARRAY_H

#include "../Ps2ElfTool_Common.h"

template<typename T>
class Array
{
public:
	Array<T>()
	{
		this->ptr = nullptr;
		this->cur = this->ptr;
		this->size = 0;
	}
	Array<T>(u64 size)
	{
		this->ptr = new T[size];
		this->cur = this->ptr;
		this->size = size;
	}
	Array<T>(Array<T>& arr)
	{
		this->size = arr.size;
		this->ptr = new T[this->size];
		this->cur = this->ptr;
		for (u64 i = 0; i < this->size; ++i) {
			this->ptr[i] = arr.ptr[i];
		}
	}
	~Array()
	{
		if(this->ptr) {
			delete[] this->ptr;
			this->ptr = nullptr;
			this->size = 0;
		}
	}

	Array<T>& operator=(const Array<T>& arr)
	{
		if (this->ptr) delete[] this->ptr;
		this->size = arr.size;
		this->ptr = new T[this->size];
		this->cur = this->ptr;
		for (u64 i = 0; i < this->size; ++i) {
			this->ptr[i] = arr.ptr[i];
		}
		return *this;
	}

	Array<T>& operator=(Array<T>&& arr)
	{
		if (this->ptr) delete[] this->ptr;
		this->size = arr.size;
		this->ptr = new T[this->size];
		this->cur = this->ptr;
		for (u64 i = 0; i < this->size; ++i) {
			this->ptr[i] = arr.ptr[i];
		}
		return *this;
	}

	T& operator[](u64 index)
	{
		return this->cur[index];
	}
	T& operator*()
	{
		return *this->cur;
	}

	Array<T>& operator+=(u64 offset)
	{
		this->cur += offset;
		return *this;
	}
	Array<T>& operator++()
	{
		this->cur++;
		return *this;
	}
	Array<T>& operator-=(u64 offset)
	{
		this->cur -= offset;
		return *this;
	}
	Array<T>& operator--()
	{
		this->cur--;
		return *this;
	}

	T* Cptr()
	{
		return this->cur;
	}
	u64 Size()
	{
		return this->size;
	}

	void ResetPtr()
	{
		this->cur = this->ptr;
	}

private:
	T* ptr;
	T* cur;
	u64 size;
};

#endif // PS2ELFTOOL_ARRAY_H
