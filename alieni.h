#ifndef ALIENI_H
#define ALIENI_H

/** Dichiarazione delle librerie usate*/
#include "buffer.h"

/** Dichiarazione delle macro usate*/
//Tempo di attesa per ogni alieno prima di scendere di una casella
#define TEMPO_DISCESA 5

//Si definiscono le specifiche sugli alieni
#define DIM_X_ALIEN 3											//Dimesine x alieno
#define DIM_Y_ALIEN 3											//Dimesine y alieno
#define N_ALIENI 12
#define DIM_X_BABYALIEN 7
#define DIM_Y_BABYALIEN 3
#define N_BABY_ALIENI 4
#define N_ALIEN_RIGA 4
#define N_ALIEN_COL 3
#define PASSO_X 1
#define PASSO_Y 1

//Si definiscono le specifiche sulle bombe
#define DIM_Y_BOMB 2
#define DIM_X_BOMB 1
#define PARTENZA_BOMB 2

/** Dichiarazione delle funzioni e procedure di  gestione delle astronavi aliene*/
void iniz_Alieni();
void iniz_baby(Posizione v[]);
void* alieno();
void controllo_next_prev(int *, int *);
_Bool controlloPasso(Posizione, int);					
void* bomba();
void print_Alien(Posizione, Posizione);
void print_Baby_Alien(Posizione, Posizione, char []);			
void print_Bomb(Posizione, Posizione);	
void delete_Alien(Posizione);
void delete_BabyAlien(Posizione, char []);	
_Bool lvl(int);	

#endif