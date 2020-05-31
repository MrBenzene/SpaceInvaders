#ifndef ASTRO_H
#define ASTRO_H

/** Dichiarazione delle librerie usate*/
#include "buffer.h"
#include "alieni.h"

/** Dichiarazione delle macro usate*/
#define DIM_X_ASTRO 6						//Dimesine x astronave
#define DIM_Y_ASTRO 1						//Dimesine y astronave
#define PASSO_X_ASTRO 3

#define SU 65										//Caratteri Freccia in ASCII
#define GIU 66
#define DESTRA 67
#define SINISTRA 68
#define SPAZIO 32

#define N_MAX_MISSILI 50			//Si definiscono le specifiche sui missili
#define N_MISSILI 2

/** Dichiarazione delle funzioni e procedure di  gestione dell'astronave */
void iniz_Missili();
void* astronave();
void* missile();
void info_base_missili(Posizione);	
void print_Astro(Posizione, Posizione);
void print_Rocket(Posizione, Posizione *);	

#endif