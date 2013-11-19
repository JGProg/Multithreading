#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

float minIntervalle,maxIntervalle, nbTranches;
float resultPremierePartie, resultatSecondePartie, resultatTroisiemepartie, resultatParenthese;

//Quotient
void calculPremierePartie(void *arg)
{
    resultPremierePartie = (maxIntervalle - minIntervalle) / nbTranches;
}

//Quotient de la fonction
void calculSecondePartie(void *arg)
{
    resultatSecondePartie = ((minIntervalle*minIntervalle*minIntervalle)+(maxIntervalle*maxIntervalle*maxIntervalle))/2;
}

//Somme
void calculTroisiemePartie(void *arg)
{
    float i;
    for (i = 0; i<nbTranches;i++)
    {
        resultatTroisiemepartie += i*i*i;
    }
}

//Calcul de la parenthèse
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
    
    //On regarde si les 3 paramètres on bien été rentrés
    if(argc != 4)
    {
        printf("Information : intervalle min,max et le nombre de tranche\n");
        exit(-1);
    }
    
    //Conversion des entrées saisie par l'utilisateur en "float"
    minIntervalle = atof(argv[1]);
    maxIntervalle = atof(argv[2]);
    nbTranches = atof(argv[3]);

    //On calcul le quotient
    valueReturn = pthread_create(&firstCalcul, NULL,(void *) calculPremierePartie,NULL);
	if(valueReturn)
	{
		printf("ERROR; return code from pthread_create() is %d\n", valueReturn);
		exit(-1);
	}
    
    //On calcul le quotient de la fonction
    valueReturn = pthread_create(&secondCalcul, NULL,(void *) calculSecondePartie,NULL);
	if(valueReturn)
	{
		printf("ERROR; return code from pthread_create() is %d\n", valueReturn);
		exit(-1);
	}
    
    //Le calcul la somme
    valueReturn = pthread_create(&thirdCalcul, NULL,(void *) calculTroisiemePartie,NULL);
	if(valueReturn)
	{
		printf("ERROR; return code from pthread_create() is %d\n", valueReturn);
		exit(-1);
	}
    
    // On attend que le calcul à l'intérieur de la parenthèse
    pthread_join(secondCalcul, NULL);
    pthread_join(thirdCalcul, NULL);
    
    //Calcul de la parenthèse
    valueReturn = pthread_create(&bracketCalcul, NULL,(void *) calculParenthese,NULL);
	if(valueReturn)
	{
		printf("ERROR; return code from pthread_create() is %d\n", valueReturn);
		exit(-1);
	}

    //On attend que le quotient et le calcul de la parenthèse soit calculé
    pthread_join(bracketCalcul, NULL);
    pthread_join(firstCalcul, NULL);
    
    //On fait le produit des deux
    float result = resultatParenthese * resultPremierePartie;
    
    //On affiche le résultat
    printf("%.2f\n",result);
}
