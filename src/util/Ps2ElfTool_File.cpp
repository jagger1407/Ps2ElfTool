#include "Ps2ElfTool_File.h"

const char* _fom[] = {
    "",
    "rb",
    "r+b",
    "w+b",
    "ab"
};

File::File()
{
    this->size = 0;
    this->openmode = FOM_NONE;
    this->fp = nullptr;
    this->isopen = false;
    this->path = "";
    this->name = "";
    this->pos = 0;
}
File::File(String8 path, FileOpenMode mode)
{
    this->Open(path, mode);

}
File::File(const char* path, FileOpenMode mode)
{
    this->Open(String8(path), mode);
}

File::~File()
{
    if(this->isopen) {
        fclose(this->fp);
        this->isopen = false;
        this->fp = nullptr;
        this->pos = 0;
    }
}

s32 File::Open(String8 path, FileOpenMode mode)
{
    this->isopen = false;

    this->fp = fopen(path.Cstr(), _fom[(u32)mode]);
    if(this->fp != nullptr) {
        this->openmode = mode;
        this->isopen = true;
        this->size = ftell(this->fp);
        this->pos = 0;
        fseek(this->fp, 0, SEEK_END);
        this->size = ftell(this->fp) - this->size;
        fseek(this->fp, 0, SEEK_SET);
        this->path = GetAbsolutePath(path);
        Array<String8> parts = this->path.Split(PATH_SEP);
        this->name = parts[parts.Size()-1];
        return 0;
    }
    perror("File::Open failed");
    return -1;
}

ByteArray File::Read(u64 size)
{
    if (this->openmode != FOM_READ && this->openmode != FOM_READWRITE) 
        return ByteArray();

    u64 basize = size;
    if(size == 0) {
        basize = this->size;
    }

    ByteArray ba(basize);

    fread(ba.Cptr(), 1, basize, this->fp);
    this->pos += basize;

    return ba;
}

Array<String8> File::ReadLines()
{
    if (this->openmode != FOM_READ && this->openmode != FOM_READWRITE)
        return Array<String8>();

    u64 len = size;
    char* ptr = new char[len+1];
    ptr[len] = 0x00;
    fseek(this->fp, 0, SEEK_SET);
    fread(ptr, 1, len, this->fp);
    pos = len;
    String8 data(ptr);
    data = data.Replace("\r", "");
    return data.Split("\n");
}

u64 File::Write(ByteArray ba)
{
    if (this->openmode != FOM_WRITE && this->openmode != FOM_READWRITE)
        return 0;

    if (ba.Size() == 0 || !isopen) return 0;

    u64 written = fwrite(ba.Cptr(), 1, ba.Size(), this->fp);
    return written;
}
u64 File::Write(String8 str)
{
    if (this->openmode != FOM_WRITE && this->openmode != FOM_READWRITE)
        return 0;

    if (str.Length() == 0 || !isopen) return 0;

    u64 written = fwrite(str.Cstr(), 1, str.Length(), this->fp);
    return written;
}
u64 File::WriteLine(String8 str)
{
    if (this->openmode != FOM_WRITE && this->openmode != FOM_READWRITE)
        return 0;

    if (!isopen) return 0;
    str += "\n";

    u64 written = fwrite(str.Cstr(), 1, str.Length(), this->fp);
    return written;
}

void File::Seek(u64 offset, u32 whence)
{
    if (!this->isopen) return;
    fseek(this->fp, offset, whence);
    this->pos = ftell(this->fp);
}
u64 File::Tell()
{
    if (!this->isopen) return (u64)-1;
    return ftell(this->fp);
}

String8 File::FileName()
{
    if (!this->isopen) return String8();
    return this->name;
}
String8 File::Path()
{
    if (!this->isopen) return String8();
    return this->path;
}

FileOpenMode File::OpenMode() { return this->openmode; }

String8 File::GetAbsolutePath(const String8& path) {
    char real[PATH_MAXLEN];
    NZero(real, PATH_MAXLEN);
#ifdef _WIN32
    _fullpath(real, path.Cstr(), _MAX_PATH);
#elif __linux__
    realpath(path.Cstr(), real);
#endif
    return String8(real);
}

File& File::operator=(File f)
{
    if (this->fp) {
        this->Close();
    }
    this->size = f.size;
    this->openmode = f.openmode;
    this->fp = f.fp;
    f.fp = nullptr;
    this->isopen = f.isopen;
    f.isopen = false;
    this->path = f.path;
    this->name = f.name;
    this->pos = f.pos;
    return *this;
}

bool File::IsOpen() { return this->isopen; }

void File::Close()
{
    if (this->fp) {
        fclose(this->fp);
        this->fp = nullptr;
    }
    this->path = "";
    this->name = "";
    this->size = 0;
    this->openmode = FOM_NONE;
    this->isopen = false;
}
