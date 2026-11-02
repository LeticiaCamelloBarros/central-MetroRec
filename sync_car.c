#include "sync_car.h"

void station_init(struct station *station)
{
	pthread_mutex_init(&station->lock, NULL);
	pthread_cond_init(&station->car_arrived, NULL);
	pthread_cond_init(&station->all_boarded, NULL);

	station->waiting = 0;
	station->free_seats = 0;
	station->boarding = 0;
}

void station_load_car(struct station *station, int count)
{
	pthread_mutex_lock(&station->lock);

	/* Sem assentos ou sem passageiros esperando: retorna na hora */
	if (count <= 0 || station->waiting == 0) {
		pthread_mutex_unlock(&station->lock);
		return;
	}

	/* Anuncia os assentos livres e acorda os passageiros */
	station->free_seats = count;
	pthread_cond_broadcast(&station->car_arrived);

	/*
	 * Espera até que:
	 *  - o carro esteja cheio (free_seats == 0) ou a fila tenha acabado
	 *    (waiting == 0), e
	 *  - todos que entraram já tenham chamado station_on_board().
	 */
	while ((station->waiting > 0 && station->free_seats > 0) ||
	       station->boarding > 0)
		pthread_cond_wait(&station->all_boarded, &station->lock);

	/* O carro parte: zera os assentos para ninguém mais entrar */
	station->free_seats = 0;

	pthread_mutex_unlock(&station->lock);
}

void station_wait_for_car(struct station *station)
{
	pthread_mutex_lock(&station->lock);

	/* Chegou na estação: entra na fila de espera */
	station->waiting++;

	/* Dorme até haver um carro na estação com assento livre */
	while (station->free_seats == 0)
		pthread_cond_wait(&station->car_arrived, &station->lock);

	/* Acordou com assento disponível: ocupa um lugar */
	station->free_seats--;
	station->waiting--;
	station->boarding++;   /* liberado para embarcar, mas ainda não sentou */

	pthread_mutex_unlock(&station->lock);
}