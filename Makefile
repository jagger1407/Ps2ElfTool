BINDIR  = build
TARGET  = Ps2ElfTool
CXX     = g++

# Disable built-in implicit rules to prevent "cc -o .o" fallbacks
.SUFFIXES:

# C++ Source Files
SRCS = \
    src/Ps2ElfTool_Common.cpp \
    src/Ps2ElfTool_Main.cpp \
    src/Ps2ElfTool_ArgReader.cpp \
    src/util/Ps2ElfTool_String.cpp \
    src/util/Ps2ElfTool_ByteArray.cpp \
    src/util/Ps2ElfTool_File.cpp \
    src/util/Ps2ElfTool_Console.cpp \
    src/ps2/Ps2ElfTool_Elf.cpp \
    src/ps2/Ps2ElfTool_Registers.cpp \
    src/ps2/Ps2ElfTool_MipsDecoder.cpp \
    src/ps2/Ps2ElfTool_Instructions.cpp

# Compiler Flags
FLAGS         = -Wall -Wextra -std=c++17
FLAGS_DEBUG   = $(FLAGS) -g -O0 -D_DEBUG
FLAGS_RELEASE = $(FLAGS) -O2

# Output Directories
DIR_DEBUG   = $(BINDIR)/debug
DIR_RELEASE = $(BINDIR)/release

OBJ_DEBUG   = $(DIR_DEBUG)/obj
OBJ_RELEASE = $(DIR_RELEASE)/obj

BIN_DEBUG   = $(DIR_DEBUG)/$(TARGET)
BIN_RELEASE = $(DIR_RELEASE)/$(TARGET)

# Object file lists automatically mirrored from SRCS
OBJS_DEBUG   = $(patsubst %.cpp, $(OBJ_DEBUG)/%.o, $(SRCS))
OBJS_RELEASE = $(patsubst %.cpp, $(OBJ_RELEASE)/%.o, $(SRCS))

# Default Target
all: debug release

debug: $(BIN_DEBUG)

release: $(BIN_RELEASE)

# Link Targets
$(BIN_DEBUG): $(OBJS_DEBUG)
	@mkdir -p $(DIR_DEBUG)
	$(CXX) $(FLAGS_DEBUG) -o $@ $^

$(BIN_RELEASE): $(OBJS_RELEASE)
	@mkdir -p $(DIR_RELEASE)
	$(CXX) $(FLAGS_RELEASE) -o $@ $^

# Dynamic Compilation Rules (Creates subdirectories on the fly)
$(OBJ_DEBUG)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(FLAGS_DEBUG) -c $< -o $@

$(OBJ_RELEASE)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(FLAGS_RELEASE) -c $< -o $@

# Clean Rule
clean:
	rm -rf $(BINDIR)

.PHONY: all debug release clean
