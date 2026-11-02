/* SPDX-License-Identifier: GPL-3.0 */
#ifndef SYNC_CAR_H
#define SYNC_CAR_H

#include <pthread.h>

/*
 * Estado compartilhado da estação.
 * A struct precisa estar completa aqui porque o runner declara
 * `struct station station;` na pilha.
 */
struct station {
	pthread_mutex_t lock;        /* protege todos os campos abaixo */
	pthread_cond_t  car_arrived; /* passageiros esperam o carro com assentos livres */
	pthread_cond_t  all_boarded; /* o carro espera todos terminarem de embarcar */

	int waiting;     /* passageiros esperando na estação */
	int free_seats;  /* assentos livres do carro que está na estação */
	int boarding;    /* passageiros liberados que ainda não chamaram on_board */
};

/* Inicializa a estação (mutex, variáveis de condição e contadores). */
void station_init(struct station *station);

/*
 * Chamada pelo carro ao chegar na estação com `count` assentos livres.
 * Retorna imediatamente se count == 0 ou se não há passageiros esperando.
 * Caso contrário, só retorna quando o carro estiver cheio ou não houver mais
 * passageiros esperando, e todos os que entraram tiverem chamado
 * station_on_board().
 */
void station_load_car(struct station *station, int count);

/*
 * Chamada por cada passageiro ao chegar na estação.
 * Bloqueia até que um carro esteja na estação com assento livre para ele.
 */
void station_wait_for_car(struct station *station);

/*
 * Chamada pelo passageiro depois de se acomodar no assento,
 * avisando o carro de que o embarque dele terminou.
 */
void station_on_board(struct station *station);

#endif /* SYNC_CAR_H */