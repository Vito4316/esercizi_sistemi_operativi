#include <stdio.h>
#include <string.h>

int main() {

    char matricola[4];
    char nome[50];
    double media_voti;

    FILE *f_in;
    FILE *f_temp;


    if((f_in = fopen("studenti","r")) == NULL){
        printf("il file di input non può essere aperto\n");
    }
    else{
        int x;

        f_temp = fopen("temp","w");
        if(f_temp == NULL){
            printf("il file nuovo non può essere aperto\n");
        }
        else{

            fscanf(f_in,"%s %s %lf", matricola,nome,&media_voti);
            fprintf(stdout,"%s| %s| %lf\n", matricola,nome,media_voti);

            do{

                if(strcmp(matricola,"002") == 0){

                    media_voti = 30.0;
                    printf("Sto cambiando la media voti di %s\n",nome);
                }

                fprintf(f_temp,"%s %s %lf\n", matricola,nome,media_voti);
                fscanf(f_in,"%s%s%lf",matricola,nome,&media_voti);

            }while((!feof(f_in)));

        }
        fclose(f_temp);
        fclose(f_in);
    }

    remove("studenti.txt");
    rename("temp.txt","studenti.txt");

    return 0;

}

