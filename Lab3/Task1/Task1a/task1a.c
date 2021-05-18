#include<stdio.h>
#include<stdlib.h>

typedef struct virus {
    unsigned short SigSize;
    char virusName[16];
    unsigned char* sig;
} virus;

void PrintHex( unsigned char buffer[], int length){
    for (int i=0; i<length;i++)
        printf( "%02X ", buffer[i]);
    printf("\n");
}

virus* readVirus(FILE* virFile){
    virus* newVirus= malloc (sizeof(virus));
    if (fread(newVirus,1,18,virFile)!=18) //if I could not read the 18 bytes I need
    {
        free(newVirus);
        return NULL;
    }
    newVirus->sig=malloc(newVirus->SigSize);
    fread(newVirus->sig,1,newVirus->SigSize,virFile);
    return newVirus;
}

void printVirus (virus* virus, FILE* output){
    fprintf(output, "Virus name: %s \n", virus->virusName);
    fprintf(output, "Virus size: %d \n", virus->SigSize);
    fprintf(output, "signatue: ");
    PrintHex(virus -> sig, virus->SigSize);
    fprintf(output, "\n");
}


int main (int argc, char** argv){
    FILE* input=fopen(argv[1],"rb");
    FILE* output=stdout;
    for (int i=0;i<4;i++)
        fgetc(input);
    virus* newV= readVirus(input);
    while (newV!=NULL)
    {
       printVirus(newV,output);
       free(newV->sig);
       free(newV);
       newV=readVirus(input);
    }
    fclose(input);
    return 0;
}