#include<stdio.h>
int Globvar=6;
int bssVar;
const int Constvar=9;
int main(){
	int Localvar=7;
	printf("Globvar= %d ,bssVar=%d,constvar=%d,Localvar=%d\n",Globvar ,bssVar,Constvar,Localvar);

	return 0;
}
