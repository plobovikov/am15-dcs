/*
** These examples use semaphores to ensure that writer and reader
** processes have exclusive, alternating access to the shared-memory region.
*/

/**********  writer.c  ***********/

#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char shm_fn[] = "my_shm";
char sem_fn[] = "my_sem";

/**** WRITER ****/

int main(){
  caddr_t shmptr;
  int shmdes, index, sem_des;
  sem_t *semdes;
  int SHM_SIZE;



  /* Open the shared memory object */

  if ( (shmdes = shm_open(shm_fn,O_CREAT|O_RDWR, 0644)) == -1 ) {
     perror("shm_open failure");
     exit(-1);
   }

  /* Preallocate a shared memory area */

  SHM_SIZE = sysconf(_SC_PAGE_SIZE);

  if(ftruncate(shmdes, SHM_SIZE) == -1){
    perror("ftruncate failure");
    exit(-1);
  }

  if((shmptr = (char*)mmap(0, SHM_SIZE, PROT_WRITE|PROT_READ, MAP_SHARED,
                shmdes,0)) == (caddr_t) -1){
    perror("mmap failure");
    exit(-1);
  }

  /* Create a semaphore in locked state */

//Initial value = 0
 semdes = sem_open(sem_fn, O_CREAT, 0644, 0);

 if(semdes == (void*)-1){
   perror("sem_open failure");
   exit(-1);
 }

    /* Access to the shared memory area */

    for(index = 0; index < 100; index++){
       printf("write %d into the shared memory shmptr[%d]\n", index*2, index);
       shmptr[index]=index*2;
       }

  /* Release the semaphore lock */

  sem_post(semdes);
  munmap(shmptr, SHM_SIZE);

  /* Close the shared memory object */

  close(shmdes);

  /* Close the Semaphore */

  sem_close(semdes);

  /* Delete the shared memory object */

  //shm_unlink(shm_fn);
}