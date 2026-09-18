# Ps2ElfTool

**Ps2ElfTool** is a command-line utility designed for inspecting, exporting, and disassembling PlayStation 2 (PS2) ELF binaries.

This project was created to generate assembly that can be assembled with the [PS2DEV](https://github.com/ps2dev/ps2dev) SDK. 
The end goal is to be able to generate a full disassembly project directory that a decompilation can be started upon.

## Features

* **Section Listing**: Quickly list all sections within a PS2 ELF file, including their names, loaded memory addresses, and sizes.

* **Section Inspection**: View detailed metadata for specific sections. 

  * Current Information: Name, RAM Address, ELF File Offset, Size, Alignment, Section Type

* **Binary Export**: Dump raw section binary data to disk.

* **Disassembly Output**: Disassemble sections into MIPS assembly formatted specifically to be reassembled using the PS2DEV assembler.

## Usage

```bash
# List all sections in an ELF file (Name, Loaded Address, Size)
Ps2ElfTool section list <ELF>

# View detailed metadata for a specific section
Ps2ElfTool section info <ELF> <section>

# Export section data as raw binary
Ps2ElfTool section export <ELF> <section> -o [output_file]

# Export section disassembly compatible with PS2DEV
Ps2ElfTool section disasm <ELF> <section> -o [output_file]

```

## Roadmap & Planned Features

- [ ] **`ldgen` Command**: Automatically generate linker scripts matching the memory layout of a target PS2 ELF.

- [ ] **Full ELF Disassembly Workflow**: A command to disassemble all executable and data sections while producing a matching linker script, allowing full reassembly back into a functional ELF file.

- [ ] **DWARF / STABS Debug Symbol Support:** Support the ability to load debug symbols into the generated disassembly.

- [ ] **`match` Command:** Take a compiled object file and match a given assembly. Inspired by [decomp.me](https://decomp.me/).

## License

This project is open-source. See the [LICENSE](LICENSE) file for details.
