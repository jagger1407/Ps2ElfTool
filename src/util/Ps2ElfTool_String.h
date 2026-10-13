#ifndef PS2ELFTOOL_STRING_H
#define PS2ELFTOOL_STRING_H

#include "../Ps2ElfTool_Common.h"
#include "Ps2ElfTool_Array.h"
#include "Ps2ElfTool_ByteArray.h"

class String
{
public:
	String();
	String(const char* cstr);
	String(const char* cstr, u32 len);
	String(const String& str);
	String(ByteArray& ba);
	~String();

	String& operator=(const char* str);
	String& operator=(ByteArray ba);
	String& operator=(String&& str);
	String& operator=(const String& str);

	String& operator+=(const char* str);
	String& operator+=(String& str);
	String& operator+=(String&& str);

	bool operator==(const char* str);
	bool operator==(String& str);

	char& operator[](u32 index);

	String Substring(u64 start);
	String Substring(u64 start, u64 len);

	char* Cstr() const;
	u32 Length() const;

	Array<String> Split(const char* separator);
	Array<String> Split(String& separator);

	String ToUpper();
	String ToLower();

	bool IsEmpty();

	bool StartsWith(String str);
	bool EndsWith(String str);

	String Repeat(int count);

	String Replace(String original, String replacement);

	static String Format(const char* fmt, ...);

	u64 ToU64();
	double ToDouble();

private:
	char* ptr;
	u32 len;

};

String operator+(String left, const char* right);
String operator+(const char* left, String right);

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
