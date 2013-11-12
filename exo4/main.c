#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

float minIntervalle,maxIntervalle, nbTranches;
float resultPremierePartie, resultatSecondePartie, resultatTroisiemepartie, resultatParenthese;


void calculPremierePartie(void *arg)
{
    resultPremierePartie = (maxIntervalle - minIntervalle) / nbTranches;
}

void calculSecondePartie(void *arg)
{
    resultatSecondePartie = ((minIntervalle*minIntervalle)+(maxIntervalle*maxIntervalle))/2;
}

void calculTroisiemePartie(void *arg)
{
    int i;
    for (i =0; i<nbTranches;i++)
    {
        resultatTroisiemepartie += i*i;
    }
}

void calculParenthese(void *arg)
{
    resultatParenthese = resultatSecondePartie +resultatTroisiemepartie;
}

int main(int argc, char *argv[])
{
    pthread_t firstCalcul;
    pthread_t secondCalcul;
    pthread_t thirdCalcul;
    pthread_t bracketCalcul;
    
    int valueReturn;
    
    if(argc != 4)
    {
        printf("Information : intervalle min,max et le nombre de tranche\n");
        exit(-1);
    }
    
    minIntervalle = atof(argv[1]);
    maxIntervalle = atof(argv[2]);
    nbTranches = atof(argv[3]);

    
    valueReturn = pthread_create(&firstCalcul, NULL,(void *) calculPremierePartie,NULL);
	if(valueReturn)
	{
		printf("ERROR; return code from pthread_create() is %d\n", valueReturn);
		exit(-1);
	}
    
    valueReturn = pthread_create(&secondCalcul, NULL,(void *) calculSecondePartie,NULL);
	if(valueReturn)
	{
		printf("ERROR; return code from pthread_create() is %d\n", valueReturn);
		exit(-1);
	}
    
    valueReturn = pthread_create(&thirdCalcul, NULL,(void *) calculTroisiemePartie,NULL);
	if(valueReturn)
	{
		printf("ERROR; return code from pthread_create() is %d\n", valueReturn);
		exit(-1);
	}
    
    pthread_join(secondCalcul, NULL);
    pthread_join(thirdCalcul, NULL);
    
    valueReturn = pthread_create(&bracketCalcul, NULL,(void *) calculParenthese,NULL);
	if(valueReturn)
	{
		printf("ERROR; return code from pthread_create() is %d\n", valueReturn);
		exit(-1);
	}

    pthread_join(bracketCalcul, NULL);
    pthread_join(firstCalcul, NULL);
    
   float result = resultatParenthese * resultPremierePartie;
    printf("%.2f\n",result);
}
