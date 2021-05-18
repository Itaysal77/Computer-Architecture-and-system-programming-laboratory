#include <stdio.h>
#include <stdlib.h>
#define BUF 1000000

void PrintHex( unsigned char buffer[], int length){
    for (int i=0; i<length;i++)
        printf( "%02X ", buffer[i]);
    printf("\n");
}

int main (int argc , char **argv){
    size_t length;
    char *buffer[BUF];
    FILE *input = fopen(argv[1],"rb");
    if(input==NULL)
       fprintf(stderr, "error while trying reading the file\n");

    length=fread(buffer,sizeof (char),BUF,input);
     fclose(input);
    PrintHex(buffer,length);
    if (input!=stdin)
        return 0;
    
}