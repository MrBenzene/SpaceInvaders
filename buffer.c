#include "buffer.h"

 //Dichiarazione e inizializzazione della Coda
Queue queue;

/* Funzione che controlla se la coda è vuota o no*/
_Bool isEmptyQueue(Queue *C){
    if(C->cont == 0)
        return true;
    else
        return false;
}

/* Funzione che controlla se la coda è piena o no*/
_Bool isFullQueue(Queue *C){
    if(C->cont == DIM_CODA)
        return true;
    else
        return false;
}

/* Funzione che aggiunge un nodo alla coda, che secondo la sua proprieta FIFO l'elemento viene sempre inserito in coda*/
void pushQueue (Queue *C, Posizione val){
    Node *new_node = NULL;

    if(isFullQueue(C) != true) {
        new_node = (Node *) malloc(sizeof(Node));
        new_node->data = val;
        new_node->link = NULL;

        if(isEmptyQueue(C) == true){
            C->front = new_node;
            C->back  = new_node;
        } else {
            C->back->link = new_node;
            C->back = new_node;
        }
        C->cont = C->cont + 1;
    }
}

/* Funzione che elimina un elemento dalla coda, secondo la proprieta FIFO elimina sempre il primo elemento in testa*/
Posizione popQueue (Queue *C){
    Posizione val;
    Node *temp = NULL;

    if(isEmptyQueue(C) == true){
        val.x = -1;
		val.y = -1;
		strcpy(val.c, " ");
    } else {
        temp = C->front;
        val = C->front->data;

        if(C->cont == 1){
            C->front = NULL;
            C->back = NULL;
        } else {
            C->front = C->front->link;
        }
        C->cont = C->cont - 1;
        free(temp);
    }
    return val;
}

// Inserimento nel buffer secondo il metodo produttore-consumatore
void inserimentoInCoda_sicuro(Posizione pos){
	sem_wait(&disponibili);							//Semaforo sulle posizioni disponibili
	pthread_mutex_lock(&mutex);
	
	pushQueue(&queue, pos);						//Inserimento in coda della posizione
	
	pthread_mutex_unlock(&mutex);
	sem_post(&presenti);								//Semaforo sulle posizioni occupate
}

// Estrazione dal buffer secondo il metoso produttore-consumatore
Posizione letturaCoda_sicura(){
	Posizione p;
	
	sem_wait(&presenti);								//Semaforo sulle posizioni occupate
	pthread_mutex_lock(&mutex);
	
	p = popQueue(&queue);							// Estrazione dalla coda della posizione
	
	pthread_mutex_unlock(&mutex);
	sem_post(&disponibili);							//Semaforo sulle posizioni disponibili
	
	return p;
}




