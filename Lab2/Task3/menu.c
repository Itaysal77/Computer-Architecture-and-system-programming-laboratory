//#include</home/caspl202/Desktop/archi/Lab2/Task2/Task2.c>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct fun_desc {
  char *name;
  char (*fun)(char);
};
char censor(char c) {
  if(c == '!')
    return '.';
  else
    return c;
}
 
char* map(char *array, int array_length, char (*f) (char)){
    getchar();
  char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
   free(mapped_array);
  for (int i=0;i<array_length;i++){
      mapped_array[i]=f(array[i]);
  }
  
  return mapped_array;
}
 char encrypt(char c){/* Gets a char c and returns its encrypted form by adding 3 to its value. If c is not between 0x20 and 0x7E it is returned unchanged */
     if (c>=0x20&&c<=0x7E)
         c=c+3;
         return c;
 } 
char decrypt(char c){ /* Gets a char c and returns its decrypted form by reducing 3 to its value. If c is not between 0x20 and 0x7E it is returned unchanged */
    if (c>=0x20&&c<=0x7E)
         c=c-3;
         return c;
}
char cprt(char c){    /* If c is a number between 0x20 and 0x7E, cprt prints the character of ASCII value c followed  by a new line. Otherwise, cprt prints the dot ('.') character. After printing, cprt returns the value of c unchanged. */
    if (c>=0x20&&c<=0x7e)
         printf("%c\n",c);
    else printf(".\n");
    return c;
}
char my_get(char c){ /* ppIgnores c, reads and returns a character from stdin using fgetc. */
    return fgetc(stdin);
}
int main (int argc, char**argv){
    char*carray=(char*) (malloc(5*sizeof(char)));
    struct fun_desc menu[]={{"Censor",censor},{"Encrypt",encrypt},{"Decrypt", decrypt},{"Print string",cprt},{"Get string",my_get},{NULL,NULL}};
    printf("Please choose a function:\n");
    for (int i=0;i<5;i++)
        printf ("%d) %s\n",i, menu[i].name);
    printf ("Option: ");
    char opt=getc(stdin)-48;
    while (opt>=0&&opt<=4)
    {
       printf("Within bounds\n");
       carray=map(carray,5,menu[opt].fun);
       printf("Done.\n");
       printf("Please choose a function:\n");
       for (int i=0;i<5;i++)
            printf ("%d) %s\n",i, menu[i].name);
        printf ("Option: ");
       opt=getc(stdin)-48;
       
    }
    printf ("Not within bounds\n");
    exit (0);
    return 0;

    

    

}
