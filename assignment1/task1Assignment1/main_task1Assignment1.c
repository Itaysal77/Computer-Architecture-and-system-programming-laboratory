#include <stdio.h>

char c_checkValidity(int x){
    if (x%2==0)
        return '1';
    return '0';
}
extern int assFunc(int);
int main (int argc, char** argv){
    int x;
    char* c;
    scanf("%d",&x);
    assFunc(x);
}
