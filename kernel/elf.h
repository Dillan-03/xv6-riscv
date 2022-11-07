// Format of an ELF executable file
// The  header  file  <elf.h>  defines the format of ELF executable binary files.  Amongst these files are normal  executable  files,  relocatable object files, core files and shared libraries.

 //An executable file using the ELF file format consists of an ELF header, followed by a program header table or a section header table, or  both.
//The  ELF  header  is  always  at  offset zero of the file.  The program header table and the section header table's  offset  in  the  file  are defined  in  the  ELF  header.  The two tables describe the rest of the particularities of the file. 
#define ELF_MAGIC 0x464C457FU  // "\x7FELF" in little endian

// File header
struct elfhdr {
  uint magic;  // must equal ELF_MAGIC
  uchar elf[12];
  ushort type;
  ushort machine;
  uint version;
  uint64 entry;
  uint64 phoff;
  uint64 shoff;
  uint flags;
  ushort ehsize;
  ushort phentsize;
  ushort phnum;
  ushort shentsize;
  ushort shnum;
  ushort shstrndx;
};

// Program section header
struct proghdr {
  uint32 type;
  uint32 flags;
  uint64 off;
  uint64 vaddr;
  uint64 paddr;
  uint64 filesz;
  uint64 memsz;
  uint64 align;
};

// Values for Proghdr type
#define ELF_PROG_LOAD           1

// Flag bits for Proghdr flags
#define ELF_PROG_FLAG_EXEC      1
#define ELF_PROG_FLAG_WRITE     2
#define ELF_PROG_FLAG_READ      4
