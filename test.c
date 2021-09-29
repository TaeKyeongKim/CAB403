#include <stdint.h> 
#include <stdio.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#include "shm_struct.h"

#define SHARE_NAME "/PARKING"
#define SHM_SIZE 2920



bool create_shared_object( PARKING_t* shm ) {
    int fd;
    // Remove any previous instance of the shared memory object, if it exists.
    shm_unlink(SHARE_NAME);
    
    // Create the shared memory object, allowing read-write access, and saving the
    // resulting file descriptor in shm->fd. If creation failed, ensure 
    // that shm->data is NULL and return false.
    if((fd = shm_open( SHARE_NAME, O_RDWR | O_CREAT, 0666)) == -1 ){
        shm = NULL;
        return false;
    }
   
    // Set the capacity of the shared memory object via ftruncate. If the 
    // operation fails, ensure that shm->data is NULL and return false. 
    // INSERT SOLUTION HERE
     if(ftruncate(fd, SHM_SIZE)==-1){
         shm = NULL;
         return false;
     }

    // Otherwise, attempt to map the shared memory via mmap, and save the address
    // in shm->data. If mapping fails, return false.
    // INSERT SOLUTION HERE
    if((shm = mmap(NULL, SHM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED,fd,0)) == MAP_FAILED){
        return false;

    }
  
    // // Do not alter the following semaphore initialisation code.
    // sem_init( &shm->data->controller_semaphore, 1, 0 );
    // sem_init( &shm->data->worker_semaphore, 1, 0 );


// * \returns Returns true if and only if shm->fd >= 0 and shm->data != MAP_FAILED.
//  *          Even if false is returned, shm->fd should contain the value returned
//  *          by shm_open, and shm->data should contain the value returned by mmap.
//  */
    // If we reach this point we should return true.
    if(fd >= 0 && shm != MAP_FAILED)
        return true;
    
    return false;
}


void simulator() {
    PARKING_t PARKING;

    if(create_shared_object(&PARKING)){
        
        printf("Simulator created shared memory ! \n");

    }else{
        printf( "Shared memory creation failed.\n" );

    }
    
   
}
    

void main(){
    
    pid_t pid1, pid2; 
    
    printf( "process starts \n");

    pid1 = fork();
    
    if(pid1 == 0 ){
        sleep(2);
        //sleep 1s for simulator to create shm, etc.. 
        printf("I am a manager with %d\n ",getpid());
        // manager();
       
    }else{
        pid2 = fork();
        if (pid2 == 0){
            sleep(1);
            printf("I am a fire Alarm with %d \n", getpid());
            // fire_alarm();
        } else{
            printf("I am a simulator with %d \n", getpid());
            simulator();
        }
    }

    if(pid1  == -1){
        printf("ERROR \n");
        exit(1);
    }


    

}
