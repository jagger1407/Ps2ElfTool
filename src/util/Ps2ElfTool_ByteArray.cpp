#include "Ps2ElfTool_ByteArray.h"

ByteArray::ByteArray()
{
	this->size = 0;
	this->ptr = nullptr;
	this->cur = nullptr;
}
ByteArray::ByteArray(const ByteArray& ba)
{
	this->size = ba.size;
	this->ptr = new u8[this->size];
	this->cur = this->ptr;
	NCopy(this->ptr, ba.ptr, this->size);
}
ByteArray::ByteArray(ByteArray&& ba) noexcept
{
	this->size = ba.size;
	this->ptr = ba.ptr;
	this->cur = ba.cur;
	ba.ptr = nullptr;
	ba.cur = nullptr;
	ba.size = 0;
}
ByteArray::ByteArray(u8* ptr, u64 size)
{
	this->size = size;
	this->ptr = new u8[size];
	this->cur = this->ptr;
	NCopy(this->ptr, ptr, size);
}
ByteArray::ByteArray(u64 size)
{
	this->size = size;
	this->ptr = new u8[size];
	this->cur = this->ptr;
}

ByteArray::~ByteArray()
{
	if (this->ptr) {
		delete[] this->ptr;
		this->ptr = nullptr;
	}
	this->cur = nullptr;
	this->size = 0;
}

ByteArray& ByteArray::operator=(const ByteArray& ba)
{
	if (this != &ba) {
		delete[] this->ptr;

		this->size = ba.size;
		if (ba.ptr && ba.size > 0) {
			this->ptr = new u8[ba.size];
			this->cur = this->ptr;
			NCopy(this->ptr, ba.ptr, this->size);
		}
		else {
			this->ptr = nullptr;
			this->cur = nullptr;
		}
	}
	return *this;
}

ByteArray& ByteArray::operator=(ByteArray&& ba) noexcept
{
	if (this != &ba) {
		if(this->ptr) delete[] this->ptr;

		this->size = ba.size;
		this->ptr = ba.ptr;
		this->cur = ba.cur;

		ba.ptr = nullptr;
		ba.cur = nullptr;
		ba.size = 0;
	}

	return *this;
}

u8& ByteArray::operator[](u64 index)
{
	//if (index >= this->bsize) return ;
	return this->cur[index];
}

u8& ByteArray::operator*()
{
	//if (this->cur < this->ptr || this->cur >= (this->ptr + this->bsize)) return ;
	return *this->cur;
}

ByteArray& ByteArray::operator+=(u64 offset)
{
	this->cur += offset;
	return *this;
}
ByteArray& ByteArray::operator++()
{
	this->cur++;
	return *this;
}

ByteArray& ByteArray::operator-=(u64 offset)
{
	this->cur -= offset;
	return *this;
}
ByteArray& ByteArray::operator--()
{
	this->cur--;
	return *this;
}

u8* ByteArray::Cptr() { return this->cur; }
u64 ByteArray::Size() { return this->size; }

bool ByteArray::AtStart() { return this->cur == this->ptr; }
bool ByteArray::AtEnd() { return this->cur == (this->ptr + this->size); }

void ByteArray::MoveToStart() { this->cur = this->ptr; }
void ByteArray::MoveToEnd() { this->cur = this->ptr + this->size - 1; }

ByteArray ByteArray::Subarray(u64 start, u64 length)
{
	return ByteArray(this->cur + start, length);
}
