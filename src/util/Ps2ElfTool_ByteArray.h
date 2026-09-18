#ifndef PS2ELFTOOL_BYTEARRAY_H
#define PS2ELFTOOL_BYTEARRAY_H

#include "../Ps2ElfTool_Common.h"

class ByteArray
{
public:
	ByteArray();
	ByteArray(const ByteArray& bytearray);
	ByteArray(ByteArray&& bytearray) noexcept;
	ByteArray(u8* ptr, u64 size);
	ByteArray(u64 size);

	~ByteArray();

	ByteArray& operator=(const ByteArray& ba);
	ByteArray& operator=(ByteArray&& ba) noexcept;

	u8& operator[](u64 index);
	u8& operator*();

	ByteArray& operator+=(u64 offset);
	ByteArray& operator++();

	ByteArray& operator-=(u64 offset);
	ByteArray& operator--();

	u8* Cptr();
	u64 Size();

	bool AtStart();
	bool AtEnd();

	void MoveToStart();
	void MoveToEnd();

	ByteArray Subarray(u64 start, u64 length);

private:
	u8* ptr;
	u8* cur;

	u64 size;
};

#endif // PS2ELFTOOL_BYTEARRAY_H
