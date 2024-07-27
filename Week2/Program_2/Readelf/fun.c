#include<stdio.h>
#include</home/ammar/Desktop/st/Readelf/test.h>
void printClass(long int class_val){
printf(" CLASS:                                      ");

switch(class_val)
{
    case ELFNONE:

    break;
    case ELF32:
    printf("ELF32\n");
    break;
    case ELF64:
    printf("ELF64\n");
    break;
}
}



void printData(long int Data_val){
printf(" Data:                                       ");
switch(Data_val)
{
    case ELFDATANONE:
    printf("Invalid data encoding\n");
    break;
    case ELFDATA2LSB:
    printf("2's complement, little endian\n");
    break;
    case ELFDATA2MSB:
    printf("2's complement, big endian\n");
    break;
}
}


void printVersion(long int Version_val){
printf(" Version:                                    ");

switch(Version_val)
{
    case VERSION_1:
    printf("%d (current)\n",VERSION_1); 
    break;
    
    case VERSION_0:
    printf("%d (current)\n",VERSION_0);
    break;
}
}


/**********************OS/ABI***************************/
void printOS_ABI(long int OS_ABO_val){
printf(" OS/ABI:                                     "); 

switch(OS_ABO_val)
{
    case ELFOSABI_NONE:
    printf("UNIX System V ABI\n"); 
    break;

    case ELFOSABI_HPUX:
    printf("HP-UX\n"); 
    break;
    
    case ELFOSABI_NETBSD:
    printf("NetBSD\n");
    break;
    
    case ELFOSABI_GNU:
    printf("UNIX - GNU\n"); 
    break;
    
    case ELFOSABI_SOLARIS:
    printf("Sun Solaris\n");
    break;
    
    case ELFOSABI_AIX:
    printf("IBM AIX.\n"); 
    break;
    
    case ELFOSABI_IRIX:
    printf("SGI Irix\n");
    break;
    
    case ELFOSABI_FREEBSD:
    printf("FreeBSD\n"); 
    break;
    
    case ELFOSABI_TRU64:
    printf("Compaq TRU64 UNIX.\n");
    break;
    
    case ELFOSABI_MODESTO:
    printf("Novell Modesto.\n"); 
    break;
    
    case ELFOSABI_OPENBSD:
    printf("OpenBSD.\n");
    break;

    case ELFOSABI_ARM_AEABI:
    printf("ARM EABI\n");
    break;

    case ELFOSABI_ARM:
    printf("ARM\n");
    break;
    
    case ELFOSABI_STANDALONE:
    printf("Standalone (embedded) application\n");
    break;
}
}
/*****************************TYPE*********************************/
void printf_Type(long int type_val){

printf(" Type:                                       "); 

switch(type_val){
    case ET_NONE:
    printf("No file type\n"); 
    break;

    case ET_REL:
    printf("REL (Relocatable file)\n"); 
    break;
    
    case ET_EXEC:
    printf("EXEC (Executable file)\n");
    break;
    
    case ET_DYN:
    printf("(DYN (Shared object file) \n"); 
    break;
    
    case ET_CORE:
    printf("Core file\n");
    break;
    
}
}
/*************************Machine*****************************************/
void printf_Machine(long int machine_val){
printf(" Machine:                                    "); 
switch(machine_val){
    case EM_NONE:
    printf("No machine\n"); 
    break;

    case EM_386:
    printf("Intel 80386\n"); 
    break;
    
    case EM_IAMCU:
    printf("Intel MCU\n");
    break;
    
    case EM_860:
    printf("Intel 80860 \n"); 
    break;
    
    case EM_960:
    printf("Intel 80960 \n");
    break;

	case EM_ARM:
    printf("ARM \n"); 
    break;

    case EM_IA_64:
    printf("Intel Merced\n"); 
    break;
    
    case EM_ST100:
    printf("STMicroelectronic ST100 processor\n");
    break;
    
    case EM_X86_64:
    printf("Advanced Micro Devices  x86-64\n"); 
    break;
    
    case EM_ST7:
    printf("STmicroelectronics ST7 8 bit mc");
    break;
    
    case EM_ST19:
    printf("STMicroelectronics ST19 8 bit mc\n"); 
    break;
    
    case EM_HUANY:
    printf("Harvard University machine-independent object files\n");
    break;
    
    case EM_AVR:
    printf("Atmel AVR 8-bit microcontroller\n");
    break;
    }
    
}
