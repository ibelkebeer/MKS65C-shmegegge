#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(){
  int shmid = shmget(525600, 201, 0666 | IPC_CREAT);
  char* data = shmat(shmid, 0, 0);
  if(data == (char*)(-1)){
    printf("Error, %s\n", strerror(errno));
    exit(0);
  }
  if(!(strcmp(data, ""))){
    printf("New shared memory segment created\n");
  }else{
    printf("Current contents of shared memory segment: %s\n", data);
  }
  printf("Would you like to change the data in the segment?\n");
  char input[256];
  scanf("%s", input);
  getchar();
  if(!(strcmp(input, "yes")) || !(strcmp(input, "Yes"))){
    printf("Input new data for shared memory segment\n");
    scanf("%s", data);
    getchar();
    printf("Shared memory segment updated\n");
  }
  if(shmdt(data) == -1){
    printf("Error, %s\n", strerror(errno));
    exit(0);
  }
  printf("Would you like to delete the memory segment?\n");
  scanf("%s", input);
  getchar();
  if(!(strcmp(input, "yes")) || !(strcmp(input, "Yes"))){
    if(shmctl(shmid, IPC_RMID, NULL) == -1){
      printf("Error, %s\n", strerror(errno));
      exit(0);
    }
    printf("Shared memory segment deleted\n");
  }
  return 0;
}
