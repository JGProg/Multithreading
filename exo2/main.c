#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZETAMPON 2

void * ecrireTampon(int * tampon);
void * lireTampon(int * tampon);

int main ()
{
	pthread_t producteur;
	pthread_t consommateur;
	int valueReturn =0;
	
	int tampon[SIZETAMPON];

	valueReturn = pthread_create(&producteur, NULL,(void *) ecrireTampon,&tampon);
	if(valueReturn)
	{
		printf("ERROR; return code from pthread_create() is %d\n", valueReturn);
		exit(-1);
	}

	pthread_join(producteur,NULL);
	valueReturn = pthread_create(&consommateur,NULL,(void *) lireTampon, &tampon);
	if(valueReturn)
	{
		printf("ERROR; return code from pthread_create() is %d\n", valueReturn);
		exit(-1);
	}

	pthread_join(consommateur,NULL);
	pthread_exit(NULL);
	return 1;

}

void* ecrireTampon(int* tampon)
{
	tampon[0] = 42;
	tampon[1] = 666;
	pthread_exit(NULL);
}

void* lireTampon(int* tampon)
{
	for(int i=0; i<SIZETAMPON;i++)
	{
		printf("Content of table  %d\n",tampon[i]);
	}
	pthread_exit(NULL);
}
