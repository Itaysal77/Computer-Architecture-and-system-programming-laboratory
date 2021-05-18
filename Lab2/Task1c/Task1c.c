#include <stdio.h>
int main(){
//int iarray[3];

//printf("iarray %p \t iarray+1 %p\n", iarray ,iarray+1);
float farray[3];
printf("farray %p \t farray+1 %p\n", farray ,farray+1);
double darray[3];
printf("darray %p \t darray+1 %p\n", darray ,darray+1);
//char carray[3];
//printf("carray %p \t carray+1 %p\n", carray ,carray+1);
int* iptrarray[3];
printf("iptrarray %p \t iptrarray+1 %p\n", iptrarray ,iptrarray+1);
char* cptrarray[3];
printf("cptrarray %p \t cptrarray+1 %p\n", cptrarray ,cptrarray+1);
int iarray[] = {1,2,3};
char carray[] = {'a','b','c'};
int* iarrayPtr=iarray;
char* carrayPtr=carray;
printf("iarray[1] %i iarray[2] %i iarray[3] %i\n", *iarrayPtr,*(iarrayPtr+1),*(iarrayPtr+2));
printf("carray[1] %c carray[2] %c carray[3] %c\n", *carrayPtr,*(carrayPtr+1),*(carrayPtr+2));
int* p;
printf("%p\n" ,p);

}