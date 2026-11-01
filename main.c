#include <stdlib.h>
#include <stdio.h> 

int main (int argc , char *argv[]){
    if( argc < 3 || argc > 3) {
       printf("Uso: %s <num_passageiros> <assentos_por_carro>\n", argv);
       return 1;
      }
    else {      
    int num_passengers = atoi(argv[4]); // Converte o 1º parâmetro
    int car_seats = atoi(argv[5]);      // Converte o 2º parâmetro
    }

}
