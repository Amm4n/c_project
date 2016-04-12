#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHSIZE 100

int main(int argc, char *argv[])
{
	int shmid;
	key_t key;
	char *shm;
	char *s;

	key = 9876;

	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666);
	if(shmid < 0)
	{
		perror("shmget");
		exit(1);
	}

	shm = shmat(shmid, NULL, 0);
	
	if(shm == (char *) -1)
	{
		perror("shmat");
		exit(1);
	}

	memcpy(shm, "Assalamualaikum Dunia", 21);
	s = shm;
	s += 21;
	*s = 0;

	while(*shm != '*')
		sleep(1);
	
	return 0;
}
