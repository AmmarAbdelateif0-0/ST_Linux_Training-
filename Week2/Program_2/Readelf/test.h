#ifndef _TEST_H_
#define _TEST_H_

/*************** prototype section ***********************/
void printClass(long int class_val);

void printData(long int Data_val);

void printVersion(long int Version_val);

void printOS_ABI(long int OS_ABO_val);

void printf_Type(long int type_val);

void printf_Machine(long int machine_val);

#define EI_MAG3         3               /* File identification byte 3 index */
#define EI_NIDENT      (16)

/*************** CLASS SECTION ****************/
#define EI_CLASS 4

#define ELFNONE  0    /* Invalid class */  
#define ELF32    1    /* 32-bit objects */
#define ELF64    2    /* 64-bit objects */
/************** DATA SECTIONS ****************/
#define EI_DATA  5

#define ELFDATANONE     0               /* Invalid data encoding */
#define ELFDATA2LSB     1               /* 2's complement, little endian */
#define ELFDATA2MSB     2               /* 2's complement, big endian */

/************** VERSION SECTIONS ***************/
#define EI_VERSION              6               /* File version byte index */
#define VERSION_1               1
#define VERSION_0               0

/************** OS/ABI SECTIONS ****************/
#define EI_OSABI                7               /* OS ABI identification */
#define ELFOSABI_NONE           0       /* UNIX System V ABI */
#define ELFOSABI_SYSV           0       /* Alias.  */
#define ELFOSABI_HPUX           1       /* HP-UX */
#define ELFOSABI_NETBSD         2       /* NetBSD.  */
#define ELFOSABI_GNU            3       /* UNIX - GNU  */
#define ELFOSABI_SOLARIS        6       /* Sun Solaris.  */
#define ELFOSABI_AIX            7       /* IBM AIX.  */
#define ELFOSABI_IRIX           8       /* SGI Irix.  */
#define ELFOSABI_FREEBSD        9       /* FreeBSD.  */
#define ELFOSABI_TRU64          10      /* Compaq TRU64 UNIX.  */
#define ELFOSABI_MODESTO        11      /* Novell Modesto.  */
#define ELFOSABI_OPENBSD        12      /* OpenBSD.  */
#define ELFOSABI_ARM_AEABI      64      /* ARM EABI */
#define ELFOSABI_ARM            97      /* ARM */
#define ELFOSABI_STANDALONE     255     /* Standalone (embedded) application */

/************** ABI VERSION SEC ***********************/
#define EI_ABIVERSION   8               /* ABI version */

/************** E_TYPE SECTION *************************/
#define ET_NONE         0               /* No file type */
#define ET_REL          1               /* Relocatable file */
#define ET_EXEC         2               /* Executable file */
#define ET_DYN          3               /* Shared object file */
#define ET_CORE         4               /* Core file */
#define ET_NUM          5               /* Number of defined types */
#define ET_LOOS         0xfe00          /* OS-specific range start */
#define ET_HIOS         0xfeff          /* OS-specific range end */
#define ET_LOPROC       0xff00          /* Processor-specific range start */
#define ET_HIPROC       0xffff          /* Processor-specific range end */

/************** E_MACHINE SECTIONS ***************************/
#define EM_NONE          0      /* No machine */
#define EM_M32           1      /* AT&T WE 32100 */
#define EM_386           3      /* Intel 80386 */
#define EM_68K           4      /* Motorola m68k family */
#define EM_88K           5      /* Motorola m88k family */
#define EM_IAMCU         6      /* Intel MCU */
#define EM_860           7      /* Intel 80860 */
#define EM_960          19      /* Intel 80960 */
#define EM_ARM          40      /* ARM */
#define EM_IA_64        50      /* Intel Merced */
#define EM_COLDFIRE     52      /* Motorola Coldfire */
#define EM_68HC12       53      /* Motorola M68HC12 */
#define EM_ST100        60      /* STMicroelectronic ST100 processor */
#define EM_TINYJ        61      /* Advanced Logic Corp. Tinyj emb.fam */
#define EM_X86_64       62      /* AMD(Advanced Micro Devices  x86-64 architecture */
#define EM_FX66         66      /* Siemens FX66 microcontroller */
#define EM_ST9PLUS      67      /* STMicroelectronics ST9+ 8/16 mc */
#define EM_ST7          68      /* STmicroelectronics ST7 8 bit mc */
#define EM_PCP          55      /* Siemens PCP */
#define EM_TRICORE      44      /* Siemens Tricore */
#define EM_ST19         74      /* STMicroelectronics ST19 8 bit mc */
#define EM_HUANY        81      /* Harvard University machine-independent object files */
#define EM_AVR          83      /* Atmel AVR 8-bit microcontroller */
#define EM_MMDSP_PLUS   160     /* STMicroelectronics 64bit VLIW DSP */
#define EM_8051         165     /* Intel 8051 and variants */
#define EM_STXP7X       166     /* STMicroelectronics STxP7x */
#define EM_L10M         180     /* Intel L10M */
#define EM_K10M         181     /* Intel K10M */
#define EM_AARCH64      183     /* ARM AARCH64 */
#define EM_AVR32        185     /* Amtel 32-bit microprocessor */
#define EM_STM8         186     /* STMicroelectronics STM8 */
#define EM_CUDA         190     /* NVIDIA CUDA */
#define EM_MCHP_PIC     204     /* Microchip 8-bit PIC(r) */
#define EM_INTELGT      205     /* Intel Graphics Technology */
#define EM_BPF          247     /* Linux BPF -- in-kernel virtual machine */









#endif
