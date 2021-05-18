#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
int fd[2];
   pid_t p;
   if (pipe(fd) == -1)
   {
      fprintf(stderr, "Pipe Failed");
      exit(1);
   }
   p = fork();
   if (p < 0)
   {
      fprintf(stderr, "fork Failed");
   }
   char message[] = "hello";
   char buf[100];
   if (p == 0)
   {
      close(fd[0]);
      write(fd[1], message, strlen(message) + 1);
   }
     
   if (p>0){
        close(fd[1]);
      while (read(fd[0], &buf, 1) > 0)
         write(STDOUT_FILENO, &buf, 1);
          write(STDOUT_FILENO, "\n", 1);
      close(fd[0]);
   }
   return 0;
}

