/******************************************************************************
 * FILE: hello.c
 * DESCRIPTION:
 *   A "hello world" Pthreads program.  Demonstrates thread creation and
 *   termination.
 * AUTHOR: Jessy GIACOMONI
 * LAST REVISED: 08/09/13
 ******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *PrintThread1()
{
    int i;
    for(i=0;i<50;i++)
    {
        printf("1 \n");
    }
    pthread_exit(NULL);
}

void *PrintThread2()
{
    int i;
    for(i=0;i<50;i++)
    {
        printf("2 \n");
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // Pour enlever warning unused
	argc =3;
	argv=NULL;
    
    // Retour d'erreur des fonctions
    int rc;
    
    // Création des theads
    pthread_t id1;
    pthread_t id2;
    
    printf("Début du programme\n");
    
    // Création du premier thread qui appele le Hanler PrintThread1
    rc = pthread_create(&id1, NULL, PrintThread1, NULL);
    if (rc)
    {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }
    
    // Création du premier thread qui appele le Hanler PrintThread2
    rc = pthread_create(&id2, NULL, PrintThread2, NULL);
    if (rc)
    {
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }
    
    pthread_join(id2,NULL);
    pthread_join(id1, NULL);
    printf("programme terminé\n");
    pthread_exit(NULL);
    return -1;
}
