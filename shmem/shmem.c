#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024 /*make it 1K shared mem segment*/

int main(int argc, char *argv[])
{
	key_t key;
	int shmid;
	char *data;
	int mode;

	if(argc > 2) {
		fprintf(stderr, "usage: shmdemo [data_to_write]\n");
		exit(1);
	}

	/*make the key*/
	if ((key = ftok("hello.txt"), 'R')) == -1) /*Here the file must 
xist*/
	{
		perror("ftok");
		exit(1);
	}

	/*Create segment*/
	if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
		perror("shmget");
		exit(1);
	}

	/*attach to the segment to get a pointer to it*/
	data = shmat(shmid, (void *)0, 0);
	if (data == (char *)(-1)) {
		perror("shmat");
		exit(1);	
	}

	/*read or modify segment, based on CLI*/
	if(argc == 2) {
		printf("writing to segment: \"%s\"\n", argv[1]);
		strncpy(data, argv[1, SHM_SIZE);
	}
	else
		printf("Segment contains: \"%s\"\n", data);

	/*detach from segment*/
	if (shmdt(data) == -1) {
		perror("shmdt");
		exit(1);
	}
	
	return 0;
}
