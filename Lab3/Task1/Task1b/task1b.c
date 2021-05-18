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
typedef struct link link;
 
struct link {
    link *nextVirus;
    virus *vir;
};
void list_print(link *virus_list, FILE* f){
    while (virus_list!=NULL){
    printVirus(virus_list->vir,f);
    virus_list=virus_list->nextVirus;
    }
}
link* list_append(link* virus_list, virus* data){
    if (virus_list==NULL){
        virus_list=malloc(sizeof (link));
        virus_list->vir=data;
        virus_list->nextVirus=NULL;
        return virus_list;
    }
    link* newHead=malloc(sizeof(link));
    newHead->vir=data;
    newHead->nextVirus=virus_list;
    return newHead;
} 
void list_free(link *virus_list){
    while(virus_list->nextVirus!=NULL){
        free(virus_list->vir->sig);
        free(virus_list->vir);
        free(virus_list);
        virus_list=virus_list->nextVirus;
    }
}
struct fun_desc
{
    char *name;
    char (*fun)();
};
void loadSignatures (link** virusList){
    char fileName[256];
    fgets(fileName, sizeof(fileName), stdin);
    fileName[strcspn(fileName, "\n")] = 0;
    FILE* f=fopen(fileName,"rb");
    for (int i=0;i<4;i++)
    fgetc(f);
    virus* v = readVirus(f);
    
    while (v!=NULL)
    {
        *virusList = list_append (*virusList, v);
        v = readVirus(f);
        
    }
    fclose(f);
    
}
int main(int argc, char **argv)
{
    int bounds = 0;
    int opt = 0;
    link *virusList = NULL;
    struct fun_desc menu[] = {{"Load signatures", loadSignatures}, {"Print signatures", list_print}, {NULL, NULL}};
    while (1)
    {
        printf("Please choose a function:\n");
        for (int i = 0; menu[i].name != NULL; i++)
        {
            printf("%d) %s\n", i + 1, menu[i].name);
            bounds++;
        }
        printf("Option: ");
        opt = fgetc(stdin) - '0';
        getchar();
        if (opt < bounds && opt > 0)
        {
            if (opt == 1)
            {
                menu[opt - 1].fun(&virusList);
            }
        else if (opt == 2)
            {
                menu[opt - 1].fun(virusList, stdout);
            }
            else
                break;
            printf("Done\n");
        }

    }
    list_free(virusList);
    return 0;
}
