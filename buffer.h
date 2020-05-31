#ifndef BUFFER_H
#define BUFFER_H

/** Dichiarazione delle librerie standard usate*/
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <ncurses.h>
#include <semaphore.h>

/** Dichiarazione delle macro e delle strutture/tipi usate nel buffer*/
#define DIM_CODA 11
#define MAXX 126	//Definizione dimensione schermo
#define MAXY 28
#define MINY 3

/* Struttura della possizione con i rispettivi campi*/
typedef struct{
	int x;									//Coordinate personaggio
	int y;
	char c[5];							//identificazione personaggio
	int id;
	int next;
	int prev;
	int level;
} Posizione;

/* Struttura Nodo contenente la posizione passata e il link al Nodo sucessivo*/
struct node {
    Posizione data;
    struct node* link;
};

typedef struct node Node;

/* Struttura della Coda utilizzata come buffer*/
typedef struct {
    Node* front;
    Node* back;
    int cont;
}Queue;

// Dichiarazione semafori
sem_t presenti, disponibili; 
pthread_mutex_t mutex;

/** Dichiarazione delle funzioni e procedure di  gestione della coda come buffer*/
_Bool isEmptyQueue(Queue *C);
_Bool isFullQueue(Queue *C);
void pushQueue (Queue *C, Posizione val);
Posizione popQueue (Queue *C);
void inserimentoInCoda_sicuro(Posizione);
Posizione letturaCoda_sicura();	

#endif
