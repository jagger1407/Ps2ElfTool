#ifndef PS2ELFTOOL_FILE_H
#define PS2ELFTOOL_FILE_H

#include "../Ps2ElfTool_Common.h"
#include "Ps2ElfTool_String.h"
#include "Ps2ElfTool_ByteArray.h"
#include "Ps2ElfTool_Array.h"

typedef enum openmode_e {
	FOM_NONE,
	FOM_READ,
	FOM_READWRITE,
	FOM_WRITE,
	FOM_WRITEREAD,
	FOM_APPEND
} FileOpenMode;

#define READ_ALL 0

#ifdef _WIN32
#define PATH_SEP "\\"
#define PATH_MAXLEN _MAX_PATH
#else
#include <limits.h>
#define PATH_SEP "/"
#define PATH_MAXLEN PATH_MAX
#endif

class File
{
public:
	File();
	File(String8 path, FileOpenMode mode);
	File(const char* path, FileOpenMode mode);

	~File();

	s32 Open(String8 path, FileOpenMode mode);

	ByteArray Read(u64 size);
	Array<String8> ReadLines();

	u64 Write(ByteArray ba);
	u64 Write(String8 str);
	u64 WriteLine(String8 str);

	void Seek(u64 offset, u32 whence);
	u64 Tell();

	String8 FileName();
	String8 Path();
	FileOpenMode OpenMode();

	bool IsOpen();

	void Close();

	static String8 GetAbsolutePath(const String8& path);

	File& operator=(File f);

private:
	String8 path;
	String8 name;
	u64 size;
	u8* buffer;
	FileOpenMode openmode;

	u64 pos;

	FILE* fp;
	bool isopen;
};

#endif
