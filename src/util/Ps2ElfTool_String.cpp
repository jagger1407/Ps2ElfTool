#include "Ps2ElfTool_String.h"

u32 _ztlen8(const char* str)
{
    if (str == nullptr) return 0;
    const char* start = str;
    while (*str != 0x00) {
        str++;
    }
    return str - start;
}

u32 _ztcnt8(const char* txt, const char* str)
{
    if(txt == nullptr || *txt == 0x00 || str == nullptr || *str == 0x00) return 0;
    u32 occurrences = 0;
    const char* cur = str;
    while(*txt != 0x00) {
        if(*txt == *cur) {
            while(*cur != 0x00) {
                if(*txt != *cur) continue;
                txt++;
                cur++;
            }
            cur = str;
            occurrences++;
            continue;
        }
        txt++;
    }

    return occurrences;
}

bool _ztcmp8(const char* str1, const char* str2)
{
    if(str1 == nullptr) {
        if(str2 == nullptr) return true;
        return false;
    }
    if(str2 == nullptr) return false;

    while(*str1 != 0x00) {
        if(*str1 != *str2) return false;
        str1++;
        str2++;
    }
    if(*str2 != 0x00) return false;
    return true;
}

u32 _ztcopy8(char* dest, const char* src) {
    if (dest == nullptr) return 0;
    if (src == nullptr) {
        *dest = 0x00;
        return 0;
    }
    const char* start = src;
    while (*src != 0x00) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = 0x00;
    return src - start;
}

s8 _nibble(char c) {
    if(c >= 'a' && c <= 'f') {
        return 10 + (c - 'a');
    }
    if(c >= 'A' && c <= 'F') {
        return 10 + (c - 'A');
    }
    if(c >= '0' && c <= '9') {
        return c - '0';
    }
    return -1;
}

u64 _powersDec[] = {
                             1,
                            10,
                           100,
                         1'000,
                        10'000,
                       100'000,
                     1'000'000,
                    10'000'000,
                   100'000'000,
                 1'000'000'000,
                10'000'000'000,
               100'000'000'000,
             1'000'000'000'000,
            10'000'000'000'000,
           100'000'000'000'000,
         1'000'000'000'000'000,
        10'000'000'000'000'000,
       100'000'000'000'000'000,
     1'000'000'000'000'000'000,
    10'000'000'000'000'000'000
};

u64 _powersHex[] = {
                   0x1,
                  0x10,
                 0x100,
                0x1000,
               0x10000,
              0x100000,
             0x1000000,
            0x10000000,
           0x100000000,
          0x1000000000,
         0x10000000000,
        0x100000000000,
       0x1000000000000,
      0x10000000000000,
     0x100000000000000,
    0x1000000000000000
};

String::String()
{
    this->ptr = nullptr;
    this->len = 0;
}

String::String(const char* cstr)
{
    this->len = _ztlen8(cstr);
    this->ptr = new char[this->len+1];
    _ztcopy8(this->ptr, cstr);
}
String::String(const char* cstr, u32 len)
{
    this->len = len;
    this->ptr = new char[this->len+1];
    this->ptr[this->len] = 0x00;
    NCopy(this->ptr, (void*)cstr, this->len);
}
String::String(ByteArray& ba)
{
    if (ba.Cptr() == nullptr) {
        this->ptr = nullptr;
        this->len = 0;
        return;
    }
    this->len = ba.Size();
    this->ptr = new char[this->len + 1];
    this->ptr[this->len] = 0x00;
    NCopy(this->ptr, ba.Cptr(), this->len);
}
String::String(const String& str)
{
    this->len = str.len;
    this->ptr = new char[this->len + 1];
    _ztcopy8(this->ptr, str.ptr);
}


String::~String()
{
    this->len = 0;
    if(this->ptr) {
        delete[] this->ptr;
        this->ptr = nullptr;
    }
}


String& String::operator=(const char* str)
{
    if(this->ptr) {
        delete[] this->ptr;
        this->ptr = nullptr;
        this->len = 0;
    }
    if(str == nullptr || *str == 0x00) return *this;
    this->len = _ztlen8(str);
    this->ptr = new char[this->len+1];
    _ztcopy8(this->ptr, str);

    return *this;
}

String& String::operator=(String&& str)
{
    if(this->ptr) {
        delete[] this->ptr;
        this->ptr = nullptr;
        this->len = 0;
    }
    if(!str.ptr) return *this;
    this->len = str.len;
    this->ptr = new char[this->len + 1];
    _ztcopy8(this->ptr, str.ptr);

    return *this;
}

String& String::operator=(ByteArray ba)
{
    if (this->ptr) {
        delete[] this->ptr;
        this->ptr = nullptr;
        this->len = 0;
    }
    if (!ba.Cptr()) return *this;
    this->len = ba.Size();
    this->ptr = new char[this->len + 1];
    this->ptr[this->len] = 0x00;
    NCopy(this->ptr, ba.Cptr(), this->len);

    return *this;
}

String& String::operator=(const String& str)
{
    if (this->ptr) {
        delete[] this->ptr;
        this->ptr = nullptr;
        this->len = 0;
    }
    if (!str.ptr) return *this;
    this->len = str.len;
    this->ptr = new char[this->len + 1];
    _ztcopy8(this->ptr, str.ptr);

    return *this;
}

String& String::operator+=(const char* str)
{
    if(!str) return *this;

    if(!this->ptr) {
        *this = str;
    }

    u32 len = _ztlen8(str);
    char* newptr = new char[this->len + len + 1];
    _ztcopy8(newptr, this->ptr);
    _ztcopy8(newptr + this->len, str);
    this->len += len;
    delete[] this->ptr;
    this->ptr = newptr;
    return *this;
}

String& String::operator+=(String& str)
{
    *this += str.ptr;

    return *this;
}


String& String::operator+=(String&& str)
{
    *this += str.ptr;

    return *this;
}

bool String::operator==(const char* str)
{
    return _ztcmp8(this->ptr, str);
}
bool String::operator==(String& str)
{
    return _ztcmp8(this->ptr, str.ptr);
}

char& String::operator[](u32 index)
{
    return this->ptr[index];
}

String operator+(String left, const char* right)
{
    left += right;
    return left;
}
String operator+(const char* left, String right)
{
    String result(left);
    result += right;
    return result;
}

String String::Substring(u64 start)
{
    return String(this->ptr + start);
}

String String::Substring(u64 start, u64 len)
{
    return String(this->ptr + start, len);
}

char* String::Cstr() const { return this->ptr; }
u32 String::Length() const { return this->len; }

Array<String> String::Split(const char* separator)
{
    u32 size = _ztcnt8(this->ptr, separator) + 1;
    Array<String> result(size);

    u64 idx = 0;

    u32 seplen = _ztlen8(separator);

    const char* cur = this->ptr;
    const char* start = cur;
    while(*cur != 0x00) {
        if(*cur == *separator && NCompare((u8*)cur, (u8*)separator, seplen)) {
            result[idx++] = String(start, cur - start);
            start = cur + seplen;
        }
        cur++;
    }
    result[idx] = String(start, cur - start);

    return result;
}
Array<String> String::Split(String& separator)
{
    return this->Split(separator.ptr);
}

String String::ToUpper()
{
    String result(*this);
    for (int i = 0; i < result.len; i++) {
        if (result.ptr[i] >= 'a' && result.ptr[i] <= 'z') {
            result.ptr[i] = 'A' + (result.ptr[i] - 'a');
        }
    }
    return result;
}
String String::ToLower()
{
    String result(*this);
    for (int i = 0; i < result.len; i++) {
        if (result.ptr[i] >= 'A' && result.ptr[i] <= 'Z') {
            result.ptr[i] = 'a' + (result.ptr[i] - 'A');
        }
    }
    return result;
}

bool String::StartsWith(String str)
{
    if (this->len < str.len || str.len == 0) return false;
    if (this->ptr == nullptr || str.ptr == nullptr) return false;

    for (int i = 0; i < str.len; i++) {
        if (this->ptr[i] != str.ptr[i]) return false;
    }
    return true;
}
bool String::EndsWith(String str)
{
    if (this->len < str.len || str.len == 0) return false;
    if (this->ptr == nullptr || str.ptr == nullptr) return false;

    for (int i = 0; i < str.len; i++) {
        if (this->ptr[this->len-1-i] != str.ptr[str.len-1-i]) return false;
    }
    return true;
}

bool String::IsEmpty()
{
    if (this->ptr == nullptr || this->len == 0) return true;
    return false;
}

String String::Replace(String original, String replacement)
{
    if(original.len == 0) return String(this->ptr);
    Array<String> parts = this->Split(original);
    if(parts.Size() <= 1) return String(this->ptr);
    String result(parts[0]);
    for(int i=1;i<parts.Size();i++) {
        result += replacement;
        result += parts[i];
    }
    return result;
}

String String::Repeat(int count)
{
    if (count == 0) return "";

    ByteArray ba(this->len * count);
    char* dest = (char*)ba.Cptr();
    char* src = this->ptr;
    for (int i = 0; i < count; i++) {
        NCopy(dest + (i * this->len), src, this->len);
    }
    return String(ba);
}

u64 String::ToU64()
{
    u64 val = 0;
    if(StartsWith("0x")) {
        String hexval = Substring(2);
        for(int i=0;i<hexval.len;i++) {
            val += _nibble(hexval[hexval.len - 1 - i]) << (i * 4);
        }
        return val;
    }

    for(int i=0;i<len;i++) {
        char c = ptr[len-1-i];
        if(c < '0' || c > '9') return 0;
        val += (c - '0') * _powersDec[i];
    }

    return val;
}


String String::Format(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    va_list args_copy;
    va_copy(args_copy, args);

    int len = vsnprintf(nullptr, 0, fmt, args);
    va_end(args);

    if (len < 0) {
        va_end(args_copy);
        return "";
    }

    String result;
    result.len = len;
    result.ptr = new char[result.len + 1];

    vsnprintf(result.ptr, result.len + 1, fmt, args_copy);
    va_end(args_copy);

    return result;
}



