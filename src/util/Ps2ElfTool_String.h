#ifndef PS2ELFTOOL_STRING_H
#define PS2ELFTOOL_STRING_H

#include "../Ps2ElfTool_Common.h"
#include "Ps2ElfTool_Array.h"
#include "Ps2ElfTool_ByteArray.h"

class String8
{
public:
	String8();
	String8(const char* cstr);
	String8(const char* cstr, u32 len);
	String8(const String8& str);
	String8(ByteArray& ba);
	~String8();

	String8& operator=(const char* str);
	String8& operator=(ByteArray ba);
	String8& operator=(String8&& str);
	String8& operator=(const String8& str);

	String8& operator+=(const char* str);
	String8& operator+=(String8& str);
	String8& operator+=(String8&& str);

	bool operator==(const char* str);
	bool operator==(String8& str);

	char& operator[](u32 index);

	String8 Substring(u64 start);
	String8 Substring(u64 start, u64 len);

	char* Cstr() const;
	u32 Length() const;

	Array<String8> Split(const char* separator);
	Array<String8> Split(String8& separator);

	String8 ToUpper();
	String8 ToLower();

	bool IsEmpty();

	bool StartsWith(String8 str);
	bool EndsWith(String8 str);

	String8 Repeat(int count);

	String8 Replace(String8 original, String8 replacement);

	static String8 Format(const char* fmt, ...);

	u64 ToU64();
	double ToDouble();

private:
	char* ptr;
	u32 len;

};

String8 operator+(String8 left, const char* right);
String8 operator+(const char* left, String8 right);

/*
class String16
{
public:
	String16();
	String16(char16* cstr);

private:
	char16* ptr;
	u32 len;
};
*/

#endif // PS2ELFTOOL_STRING_H
