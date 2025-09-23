L'objectif du projet est de recoder la fonction nm.

-------------------------------------------------------------------------------------
Comment savoir si un fichier est un ELF ?
-------------------------------------------------------------------------------------
Read the first four bytes. If they are equal to \x7fELF, it's an ELF file. 

Comment connaître length du fichier avant de mmap ?

Utiliser fstat, dans la structure ft_size contient la taille en bytes

-------------------------------------------------------------------------------------
A quoi sert offset dans mmap ?
-------------------------------------------------------------------------------------
It lets you map a section of a file that doesn't necessarily start at the beginning.

So

fd = open("/path/to/myfile", O_RDONLY);
ptr = mmap(NULL, 8192, PROT_READ, MAP_PRIVATE, fd, 4096);

would map bytes 4096-12287 of the file into memory, and return a pointer to the address where they are mapped.

This is useful, for instance, if you are loading a shared library. Some parts of the file may be headers or debug info that you don't need to map into memory.

-------------------------------------------------------------------------------------
Comment accéder aux infos du fichier après avoir map ? (header)
-------------------------------------------------------------------------------------
→ pas juste un printf pour afficher l'entièreté du fichier
f6r8s2% ./ft_nm ft_nm   
uid = 109630, size = 16120
FIle = ELF

Je peux le cast en Elf32_Ehdr ou Elf64_Ehdr mais pour ça il faut déterminer si c’est un 32 ou 64 bits.

-------------------------------------------------------------------------------------
Comment déterminer si le fichier est 32 ou 64 bits ?
-------------------------------------------------------------------------------------
Cast le fichier map en unsigned char, étant donné que le début des header, ici la variable unsigned char e_ident, que ce soit 32 ou 64 bits est la même, on peut accéder aux infos en faisant: data[EI_CLASS]. SI == ELFCLASS32 ou ELFCLASS64

-------------------------------------------------------------------------------------
Que contient la structure elfN_Ehdr ?
-------------------------------------------------------------------------------------
typedef struct {
     unsigned char e_ident[EI_NIDENT];
→ array of bytes specifies how to interpret the file (contient 0x7f EFL…)
     uint16_t      e_type;
→ type du fichier (executable, partage, core, relocatable, unknown)
     uint16_t      e_machine;
→ specifie l’architecture requise (Intel, Motorola..)
     uint32_t      e_version;
→ version du fichier
     ElfN_Addr     e_entry;
→ virtual address to which the system first transfers control, thus starting the process
     ElfN_Off      e_phoff;
→ program header table's file offset in bytes. [interessant]
     ElfN_Off      e_shoff;
→ holds the section header table's file offset in bytes. [inter]
     uint32_t      e_flags;
     uint16_t      e_ehsize;
     uint16_t      e_phentsize;
→ holds the size in bytes of one entry in the file's program header table; all entries are the same size. [inter]
     uint16_t      e_phnum;
→ This member holds the number of entries in the program header table. [inter]
     uint16_t      e_shentsize;
→ This member holds a sections header's size in bytes. [inter]
     uint16_t      e_shnum;
→ This member holds the number of entries in the section header table. [inter]
     uint16_t      e_shstrndx;
} ElfN_Ehdr;

-------------------------------------------------------------------------------------
Comment accéder à l’ensemble du fichier ELF ?
-------------------------------------------------------------------------------------
Le fichier peut être scindé en 3 parties qui ont chacune leur structure:
ELF Header (elfN_Ehdr)
Program header (elfN_Phdr)
Section header (elfN_Shdr)

On peut connaître la taille et l’emplacement des 2 derniers headers grâce aux variables contenues dans ELF Header (e_phoff, e_phentsize, e_phnum…)
