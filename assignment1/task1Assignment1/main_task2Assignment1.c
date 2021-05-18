#include <stdio.h>
#define	MAX_LEN 34			/* maximal input string size */
					/* enough to get 32-bit string + '\n' + null terminator */
extern int convertor(char* buf);

int main(int argc, char** argv)
{
  int Q=1;
  char buf[MAX_LEN ];
  
  while (Q==1) 
  {
    fgets(buf, MAX_LEN, stdin);		/* get user input string */
    Q= convertor(buf);
    
  }

  return 0;
}