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
void detect_virus(char *buffer, unsigned int size, link *virus_list,FILE* output){
    int ind = 0;
    int cmp=0;
    while (virus_list!=NULL) {
        while (ind <= size - virus_list->vir->SigSize) {
            
            cmp=memcmp(virus_list->vir->sig, buffer+ind, virus_list->vir->SigSize);
            if (cmp==0)
              {
                printf("The starting byte location in the suspected file: %d\nThe virus name: %s\nThe size of virus signature: %d",ind,
                    virus_list->vir->virusName,virus_list->vir->SigSize);
                printf("\n");
                break;
            }
            ind =ind+1;
        }
        ind = 0;
        virus_list = virus_list -> nextVirus;
    }
}
void kill_virus(char *fileName, int signatureOffset, int signatureSize){
    char killArray[signatureSize];
    for (int i=0; i<signatureSize;i++){
        killArray[i]=0x90;
    }
    FILE * file=fopen(fileName,"rb+");
    fseek(file,signatureOffset,SEEK_SET);
    fwrite(killArray,1,signatureSize,file);
    fclose(file);

}
int main(int argc, char **argv)
{
    int bounds = 0;
    int opt = 0;
    link *virusList = NULL;
    char* buffer;
    struct fun_desc menu[] = {{"Load signatures", loadSignatures}, {"Print signatures", list_print},{ "Detect viruses", detect_virus },{"Fix file", kill_virus}, {NULL, NULL}};
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
        if (opt < 5 && opt > 0)
        {
            if (opt == 1)
            {
                menu[opt - 1].fun(&virusList);
            }
        else if (opt == 2)
            {
                menu[opt - 1].fun(virusList, stdout);
            }
        else if (opt == 3){
            int fileS;
             buffer = malloc(10000);
            FILE*f = fopen(argv[1], "rb");
            fseek(f, 0, 2); 
            fileS = ftell(f);
            rewind(f);
            fread (buffer,1,fileS, f);
            int min;
            if (fileS>=10000){
                min=10000;
            }
            else min=fileS;
            menu[opt - 1].fun(buffer, min , virusList, stdout);
            fclose(f);
            
        }
        else
         if (opt == 4){
            int start=0;
            int vSize=0;
            printf("\nindex of beginning of virus: ");
            scanf("%d", &start);
            printf("\nsize of virus: ");
            scanf("%d", &vSize);
            menu[opt - 1].fun(argv[1], start, vSize);
        }
        printf("Done\n");
        }
        else
                break;

    }
    free(buffer);
    list_free(virusList);
    return 0;
}

