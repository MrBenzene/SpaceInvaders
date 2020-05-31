#ifndef MENU_H
#define MENU_H

/** Dichiarazione delle librerie usate*/
#include "astro.h"
#include "alieni.h"

/** Dichiarazione delle macro usate*/
/*Specifiche del menù*/
#define EL_MENU 5		//Numero di elementi nel menù
#define GIOCA 0
#define TUTORIAL 1
#define MENUSKIN 2
#define ESCI 3
#define STATISTICHE 4
#define SKINALIENO_UNO 0
#define SKINALIENO_DUE 1
#define SKINASTRONAVE 2

#define DIM_STRING_FILE 30
#define NUM_EL_FILE 10
#define DIM_STRING_NAME 20

//Tipo di collisione
#define ALIEN_BASE 0		//L'alieno tocca la base dello schermo 
#define ALIENI_MORTI 1	//Tutti li alieni sono morti
#define HIT_BOMBA 2

typedef struct{
	int Time_g;
	int Punteggi;
	char Nome_pl[20];
} Statistica;

/** Dichiarazione delle funzioni e procedure di  gestione dell'astronave */
int menu(char*);
void endgame();
void iniz_schermo_colori();
void istruzioni();
int menuSkin();
void skin(int scelta);
void salvataggio_stampa(FILE *, int , int, int);
void scorrimentoListaSkin(FILE *fp, int dimX, int dimY, int elementi_menu);
int scorrimento_menu(int elementi_menu);
void Salv_statistiche(int );
void Lett_Statistiche();
void ordinamentoFile(Statistica Risultati[]);
void selectionSort(Statistica *array, int dim);
void swap(Statistica* max, Statistica* j);
#endif