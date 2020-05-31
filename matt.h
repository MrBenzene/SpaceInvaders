#ifndef MATT_H
#define MATT_H

/** Dichiarazione delle librerie usate*/
#include "astro.h"
#include "alieni.h"
#include "menu.h"

/// Dichiarazione delle macro usate 
#define GOD_MODE 0
#define PT_ALIENO_LVL_UNO 25
#define PT_ALIENO_LVL_DUE 50
#define PT_FINE_GIOCO 400

/** Dichiarazione delle funzioni e procedure di  gestione della stampa e collisione */
void matt();				//Funzione che disegna nel prompt 	
void stampa_vita(int , int );
void print_info_Rocket();															
_Bool controllo_input_Matt(Posizione, Posizione, Posizione[], Posizione[], Posizione);						
int controllo_hit_missile(Posizione, Posizione);
void controllo_hit_alieni(Posizione, char [], int , Posizione *);		
void collisione(int, int);
_Bool alieni_morti();

#endif