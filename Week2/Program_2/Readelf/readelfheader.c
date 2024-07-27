#include<stdio.h>
#include<elf.h>
#include</home/ammar/Desktop/st/Readelf/test.h>

#define File_Path "/home/ammar/Desktop/st/Program/trail"

int main(){

FILE *elfFile=fopen(File_Path,"r");

Elf64_Ehdr elfheader;

fread(&elfheader,sizeof(elfheader),1,elfFile);

/******************magic **************************/
printf(" Magic:     ");
for(int counter=0 ;counter<EI_MAG3;counter++){
printf("%x ",elfheader.e_ident[counter]);
}
for(int counter=4 ;counter<EI_NIDENT;counter++){
printf("0%x ",elfheader.e_ident[counter]);
}
printf("\n");

/**********************class ***********************/
printClass(elfheader.e_ident[EI_CLASS]);

/********************** Data ******************************/
printData(elfheader.e_ident[EI_DATA]);

/**********************Version***************************/

printVersion(elfheader.e_ident[EI_VERSION]);

/**********************OS/ABI***************************/
printOS_ABI(elfheader.e_ident[EI_OSABI]);
/***********************************ABI VERSION *********************/
printf(" ABI VERSION=                                %d\n",0);
/*****************************TYPE*********************************/
printf_Type(elfheader.e_type);

/*************************Machine*****************************************/
printf_Machine(elfheader.e_machine);

/**************************VERSION*****************************/
printf(" VERSION:                                    0x1\n");
/*************************Entery Point Adderss *****************/
printf(" Entery Point Adderss:                       0x%lx\n",elfheader.e_entry);
/*************************Start Of  Program Header*******************/
printf(" Start Of Program Header:                    %ld (bytes into files)\n",elfheader.e_phoff);
/**************************Start Of Section Header****************/
printf(" Start Of Section Header:                    %ld (bytes into files)\n",elfheader.e_shoff);
/**************************Flags***********************************/
printf(" Flags:                                      %ld \n",elfheader.e_flags);


/*************************Size Of  this Header*******************/
printf(" Size Of  this Header:                       %ld (bytes)\n",elfheader.e_ehsize);
/**************************Size Of Program Header****************/
printf(" Size Of Program Header:                     %ld (bytes)\n",elfheader.e_phentsize);
/**************************Number Of Program Header***********************************/
printf(" Number Of Program Header:                   %ld \n",elfheader.e_phnum);

/**************************Size Of Section Header****************/
printf(" Size Of Section Header:                     %ld (bytes)\n",elfheader.e_shentsize);
/**************************Number Of Section Header***********************************/
printf(" Number Of Section Header:                   %ld \n",elfheader.e_shnum);

/**************************Section header string table index *******************/
printf(" Section header string table index:          %ld \n",elfheader.e_shstrndx);
/********************************************************************************/
fclose(elfFile);
return 0;
}

