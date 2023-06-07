#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 20

/*
    COMMENTI INIZIALI

    Il programma utilizza un vettore di record per immagazzinare le date.
    Nonostante non sia utilizzata ho lasciato la funzione prntList() 
    per ccontrollare che vengano letti correttamente i dati su pc diversi dal mio.

    Le funzioni utilizzate ed il main sono commentati sotto.

*/


struct date{
    
    int d1,d2,      
        m1,m2,          
        y1,y2;          

}lista[N];      //lista degli intervalli

int mat[N][N];  //matrice di incidenza

void get_date(struct date t[N]);
void prntList();
bool is_overlapped(int ind1, int ind2);
void prtMat(int mat[N][N]);
bool mat_ha_zeri(int mat[N][N]);
struct date intervallo_Max(struct date l[N]);

int main(){

    get_date(lista);

    
    for(int i=0; i<N; i++){     //inserisco le entrate della matrice con la funzione is_overlapped()
        
        for(int j=0; j<N; j++){

            if(is_overlapped(i,j) || is_overlapped(j,i)){       //considero arco a prescindere da quale intervallo è contenuto e quale contiene
                
                mat[i][j] = 1;
            
            }else{
                
                mat[i][j] = 0;

            }
        }
    }

    prtMat(mat);
    
    if(mat_ha_zeri(mat)){

        printf("\nImpossibile soddisfafre tutte le esigenze.\n");
    
    }else{ 
        
        struct date int_max = intervallo_Max(lista);
        printf("\nIntervallo più ampio:\t%d/%d/2024 - %d/%d/2024\n", int_max.d1,int_max.m1,int_max.d2,int_max.m2 );

    }
}


void get_date(struct date t[N]){

    for(int i=0; i<N; i++){
        
        scanf("%d/%d/%d %d/%d/%d\n", &(t[i].d1), &(t[i].m1), &(t[i].y1), &(t[i].d2), &(t[i].m2), &(t[i].y2));

    }

}


void prntList(){

    for(int i=0; i<N; i++){
        printf("%d/%d/%d  %d/%d/%d\n", lista[i].d1,lista[i].m1,lista[i].y1,lista[i].d2,lista[i].m2,lista[i].y2);
    }
}

//La funzione controlla se l'intervallo ind1-esimo si sovrappone all'intervallo ind2-esimio
bool is_overlapped(int ind1, int ind2){

    if(lista[ind1].m1 > lista[ind2].m1 && lista[ind1].m1 < lista[ind2].m2){
    
        // printf("M1 indice: %d, %d\t<>\n",ind1,ind2);

        return true;

    }
    if(lista[ind1].m1 == lista[ind2].m1 && lista[ind1].m1 == lista[ind2].m2){

        if(lista[ind1].d1 >= lista[ind2].d1 && lista[ind1].d1 <= lista[ind2].d2){
            
            // printf("M1 indice: %d, %d\t==\t%d/%d,%d/%d\n",ind1,ind2,lista[ind1].d1,lista[ind1].m1,lista[ind2].d1,lista[ind2].m2);
        
            return true;

        }

    }

    if(lista[ind1].m1 == lista[ind2].m1 && lista[ind1].m1 != lista[ind2].m2){

        if(lista[ind1].d1 >= lista[ind2].d1 ){
            
            // printf("M1 indice: %d, %d\t>=\t%d,%d\n",ind1,ind2,lista[ind1].d1,lista[ind2].d1);
        
            return true;

        }

    }
    if(lista[ind1].m1 == lista[ind2].m2 && lista[ind1].m1 != lista[ind2].m1){
        
        if(lista[ind1].d1 <= lista[ind2].d2){
            
            // printf("M1 indice: %d, %d\t<=\n",ind1,ind2);
        
            return true;

        }  
    }
    ///////
    if(lista[ind1].m2 > lista[ind2].m1 && lista[ind1].m2 < lista[ind2].m2){

        // printf("M2 indice: %d, %d\t<>\n",ind1,ind2);

        return true;

    }
    if(lista[ind1].m2 == lista[ind2].m1 && lista[ind1].m2 == lista[ind2].m2){

        if(lista[ind1].d2 >= lista[ind2].d1 && lista[ind1].d2 <= lista[ind2].d2){
            
            // printf("M2 indice: %d, %d\t==\t%d,%d\n",ind1,ind2,lista[ind1].d1,lista[ind2].d1);
        
            return true;

        }

    }
    if(lista[ind1].m2 == lista[ind2].m1 && lista[ind1].m2 != lista[ind2].m2){

        if(lista[ind1].d2 >= lista[ind2].d1){

            // printf("M2 indice: %d, %d\t>=\n",ind1,ind2);

            return true;
            
        }

    }
    if(lista[ind1].m2 == lista[ind2].m2 && lista[ind1].m2 != lista[ind2].m1){
        
        if(lista[ind1].d2 <= lista[ind2].d2){
            
            // printf("M2 indice: %d, %d\t<=\n",ind1,ind2);
            return true;

        }  
    }

    return false;

}


void prtMat(int mat[N][N]){

    for(int i=0; i<N; i++){

        for(int j=0; j<N; j++){

            printf("%d ", mat[i][j]);

        }
        printf("\n");
    }

}


bool mat_ha_zeri(int mat[N][N]){

    for(int i=0; i<N; i++){

        for(int j=0; j<N; j++){

            if(!mat[i][j]) return true;
            else continue;
        }
    }
    return false;
}

struct date intervallo_Max(struct date l[N]){

    struct date tmp;

    int min_Mese    = 12;
    int min_Giorno  = 31;
    int max_Mese    = 0;
    int max_Giorno  = 0;

    //trovo il mese minimo
    for(int i=0; i<N; i++){
        
        if(l[i].m1 <= min_Mese){

            min_Mese = l[i].m1;

        }
    }
    //trovo il giorno minimo
    for(int i=0; i<N; i++){
        
        if(l[i].m1 == min_Mese){

            if(l[i].d1 <= min_Giorno){

                min_Giorno = l[i].d1;

            }

        }
    }

    for(int i=0; i<N; i++){
        
        if(l[i].m2 >= max_Mese){

            max_Mese = l[i].m2;

        }
    }
    //trovo il giorno minimo
    for(int i=0; i<N; i++){
        
        if(l[i].m2 == max_Mese){

            if(l[i].d2 >= max_Giorno){

                max_Giorno = l[i].d2;

            }

        }
    }

    tmp.m1 = min_Mese;
    tmp.d1 = min_Giorno;
    tmp.m2 = max_Mese;
    tmp.d2 = max_Giorno;

    return tmp;

}
