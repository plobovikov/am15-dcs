#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
 
int main()

{

  int fd_fifo; /*descriptor*/

  char buffer[]="Test string to fifo\n";

  char buf[100];

   
  unlink("/tmp/fifo0001.1");

	/*create FIFI to read and write*/
	
  if((mkfifo("/tmp/fifo0001.1", O_RDWR)) == -1)

  {

    fprintf(stderr, "Unable to create FIFO\n");
    _exit(0);

  }

  /*Open FIFO to write and read*/

  if((fd_fifo=open("/tmp/fifo0001.1", O_RDWR)) == - 1)

  {

    fprintf(stderr, "Unable to open FIFO\\n");

    _exit(0);

  }

  write(fd_fifo,buffer,strlen(buffer)) ;

  if(read(fd_fifo, &buf, sizeof(buf)) == -1)

  fprintf(stderr, "Unable to read from FIFO\n");

  else

  printf("String froim fifo : %s\n",buf);

  return 0;

}