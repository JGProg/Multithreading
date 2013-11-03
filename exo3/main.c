#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NBLigne 3

/* methods pour résoudre l'exercice */
void caculMatriciel(void);

void * calculLignematrice(int * tampon);

int **allocateMatrix()
{
    int i;
    int *vals, **temp;
    
    vals = (int *) malloc (matrixSize * matrixSize * sizeof(int));
    temp = (int **) malloc (matrixSize * sizeof(int*));
    
    for(i=0; i < matrixSize; i++)
    {
        temp[i] = &(vals[i * matrixSize]);
    }
    return temp;
}


void printMatrix(int **mat)
{
    int i,j;
    
    printf("Matrice avec une dimension de  %d * %d est \n", matrixSize, matrixSize);
    for(i=0; i < matrixSize; i++)
    {
        for(j=0; j < matrixSize; j++)
            printf("%d ",  mat[i][j]);
        printf("\n");
    }
}

void add(int myId)
{
    int i,j,k;
    int sum;
    
    int activerow = myId;
    
    // matrix mult over the strip of rows for this thread
    for (i = activerow; i <= activerow; i++)
    {
        for (j = 0; j < matrixSize; j++)
        {
            sum = 0.0;
            for (k = 0; k < matrixSize; k++)
            {
                sum = sum + a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
    printf("Calcul thread : ");
    for (i = activerow; i <= activerow; i++)
    {
        for (j = 0; j < matrixSize; j++)
        {
            printf("%d ",c[i][j]);
        }
    }
    printf("\n");
}

void worker(void *arg)
{
    int id = *((int *) arg);
    add(id);
}


int main (int argc, char *argv[])
{
	int i, j;
    int *p;
    pthread_t *threads;
    
    if (argc != 2)
    {
        printf("Information: %s <size> <n>,  représente la taille de la matrice\n", argv[0]);
        exit(1);
    }
    
    matrixSize = atoi(argv[1]);
    numThreads = matrixSize;
    
    a = allocateMatrix();
    b = allocateMatrix();
    c = allocateMatrix();
    
    for (i = 0; i < matrixSize; i++)
    {
        for (j = 0; j < matrixSize; j++)
        {
            a[i][j] = i + j;
            b[i][j] = i + j;
        }
    }
    
    if (matrixSize < 10)
    {
        printMatrix(a);
        printMatrix(b);
    }
    
    // Allocation handles
    threads = (pthread_t *) malloc(matrixSize * sizeof(pthread_t));
    
    // Creation des threads
    for (i = 0; i < numThreads; i++)
    {
        p = (int *) malloc(sizeof(int));
        *p = i;
        pthread_create(&threads[i], NULL,(void *) worker, (void *)(p));
    }
    
    for (i = 0; i < numThreads; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    printf("\nRésultat de l'addition \n");
    printMatrix(c);
}
