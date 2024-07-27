#include<stdio.h>
extern func(int glob,int bs,int consvar,int loc);
int globalvar=60;
int bssvar;
const int constvar=10;

int main(){
int localvar=200;
func(globalvar,bssvar,constvar,localvar);

return 0;
}

