#include <pthread.h>
#include "sync_car.h"

void station_init(struct station *station) {
    station->arrived = 0;
    station->maxCapacity = 0;

    station->passengersOutside = 0;
    station->passengersEntering = 0;
    station->passengersInside = 0;

    pthread_mutex_init(&(station->mutex), NULL);
    pthread_cond_init(&(station->arrival), NULL);
    pthread_cond_init(&(station->onboard), NULL);
}

void station_load_car(struct station *station, int count) {
    if (count <= 0) return;
        
    pthread_mutex_lock(&(station->mutex));

    station->arrived = 1;
    station->maxCapacity = 0;

    station->passengersEntering = 0;
    station->passengersInside = 0;

    pthread_cond_broadcast(&(station->arrival));

    while (!(station->passengersEntering) && (station->passengersOutside || !(station->maxCapacity))) {
        pthread_cond_wait(&(station->onboard), &(station->mutex));
        if (station->passengersInside == count) {
            station->maxCapacity = 1;
        }
    }
    station->arrived = 0;

    pthread_mutex_unlock(&(station->mutex));
}

void station_wait_for_car(struct station *station) {
    pthread_mutex_lock(&(station->mutex));

    station->passengersOutside++;

    while (!(station->arrived) || station->maxCapacity) {
        pthread_cond_wait(&(station->arrival), &(station->mutex));
    }

    station->passengersOutside--;
    station->passengersEntering++;

    pthread_mutex_unlock(&(station->mutex));
}

void station_on_board(struct station *station) {
    pthread_mutex_lock(&(station->mutex));

	station->passengersEntering--;
	station->passengersInside++;
    pthread_cond_signal(&(station->onboard));

    pthread_mutex_unlock(&(station->mutex));
}