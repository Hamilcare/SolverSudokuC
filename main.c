#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 9
int recursions;//variable globale permettant de compter le nombre de recursions necessaires a la resolution d'une grille
int facto(int n);
int check_colonne(int val, int grille[9][9], int j);
int check_ligne(int val, int grille[N][N], int i);
int check_carre(int val, int grille[N][N],int i,int j);
int est_valide(int grille[N][N], int position);
void affiche_grille(int grille[N][N]);
void load_grille(int grille[N][N],int n);

int main()
{
    printf("Hello world!\n");


    int grille[N][N];
    int moyenne=0;


    int i;
    for(i=0;i<50;i++){
	recursions=0;
	//On lit la grille de sudoku depuis le fichier texte et on la charge dans grille
	load_grille(grille,i);
	//Resolution de la grille
	est_valide(grille,0);

	moyenne+=recursions;
	affiche_grille(grille);
	printf("Grille %d resolue en %d recursions\n",i,recursions);
    }
    printf("La resolution d'une grille demande en moyenne %d recrusions \n",moyenne/50);





    return 0;
}

void load_grille(int grille[N][N],int n){


    int i=0,j=0;
    FILE* fichier = NULL;
    fichier=fopen("sudoku.txt", "r");

    if (fichier != NULL){

  //      printf("L'ouverture du fichier s'est bien deroulee\n");

        char tmp[20]; //Ce tableau contient les valeurs des cases
        char l1[40];

        for(i=0;i<n*N+n;i++){

            fscanf(fichier,"%s",l1);

        }


        fscanf(fichier,"%s",l1);

		/* On lit ligne par ligne le fichier et on stock les nombres de la ligne dans tmp*/
        i=0;
        for(i=0;i<N;i++){
            j=0;

            fscanf(fichier,"%s",tmp);

            for(j=0;j<N;j++){
		//on extrait les nombres tmp pour les positionner dans la grille
                grille[i][j]=tmp[j]-48;

            }
            printf("\n");
        }



		fclose(fichier);
	}

	else{
        printf("L'ouverture a bidee \n");
	}




}

void affiche_grille(int grille[N][N]){
    int i,j;

    for(i=0;i<N;i++){
            printf("|");
        for(j=0;j<N;j++){
            printf("%d|",grille[i][j]);
        }
        printf("\n");


    }


}

//position = i*N+j
int est_valide(int grille[N][N], int position){
	
	recursions++;

    //Si on a parcouru toute la grille c'est qu'elle est terminee
    if(position==N*N){
        return 1;
    }

    int i= position/N, j=position%N;

    //si la case n'est pas vide on passe a la suivante
    if(grille[i][j]!=0){
        return est_valide(grille,position+1);

    }



    else{



        // énumération des valeurs possibles
        int k;
        for (k=1; k <= 9; k++)
        {
            // Si la valeur est absente, donc autorisée
            if ((check_ligne(k,grille,i)==0) && (check_colonne(k,grille,j)==0) && (check_carre(k,grille,i,j)==0))
            {
                // On enregistre k dans la grille
                grille[i][j] = k;
                // On appelle récursivement la fonction estValide(), pour voir si ce choix est bon par la suite
                if ( est_valide (grille, position+1) )
                    return 1;  // Si le choix est bon, plus la peine de continuer, on renvoie true :)
            }
        }
        // Tous les chiffres ont été testés, aucun n'est bon, on réinitialise la case
        grille[i][j] = 0;
        // Puis on retourne false :(
        return 0;


    }



}

//On verifie si val est present sur la ligne i
int check_ligne(int val, int grille[N][N], int i){

    int j=0;
    int trouve=0;
    while(j<N && trouve==0){
        if(grille[i][j]==val){
            trouve=1;
        }
        j++;
    }

    return trouve;
}

//On verifie si val est present sur la colonne j
int check_colonne(int val, int grille[N][N], int j){

    int i=0;
    int trouve=0;

    while(i<N && trouve==0){
        if(grille[i][j]==val){
            trouve=1;
        }
        i++;
    }

    return trouve;

}


//On verifie si val est present dans le sous carre associer aux coordonnes de val
int check_carre(int val, int grille[N][N],int i,int j){

    int tempoI = i - i%3;
    int tempoJ = j - j%3;
    int trouve=0;

    for(i=tempoI;i<tempoI+3;i++){
            for(j=tempoJ;j<tempoJ+3;j++){
                if(grille[i][j]==val){
                    trouve=1;
                }
            }
    }

    return trouve;
}







//Initiation a la recursivite
int facto (int n){
if(n==1)
    return 1;
else
    return n*facto(n-1);
}
