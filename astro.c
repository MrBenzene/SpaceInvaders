#include "astro.h"

// Dichiarazione delle variabili globali
int fine = 0, collision =-1, nRocket = 0;        
char astroPaint[DIM_X_ASTRO + 1] = {"(_/\\_)\0"};	
Posizione posMissiliAttuale[N_MAX_MISSILI * 2];

/*Inizializzazione dei missili a id = -1*/
void iniz_Missili(){
	int i;
	for(i = 0; i < N_MAX_MISSILI * N_MISSILI; i++)	posMissiliAttuale[i].id = -1;
}

/** Processo per il movimento dell'astronave e per lo sparo dei missili e la loro ricarica*/
void* astronave(){
	Posizione posiz = {0, MAXY, "astro", 0};
	char freccia = DESTRA;				
	float partenza, fineT, tempo;
	float rateo = 0.035;
	
	partenza = clock();
	while(fine == 0){
		//Viene inserita la posizione nella coda
		if(freccia != ERR)
			inserimentoInCoda_sicuro(posiz);
		
		if(!lvl(0))
			rateo = 0.030;
		
		freccia = getch();			//Si attende un input dall'utente
		fineT = clock();
		tempo = (fineT - partenza) / CLOCKS_PER_SEC;

		if(freccia == DESTRA && posiz.x < MAXX - DIM_X_ASTRO)	posiz.x += PASSO_X_ASTRO;			//Spostamento dell'astronave a destra
		if(freccia == SINISTRA && posiz.x  > 0)										posiz.x -=  PASSO_X_ASTRO;			//Spostamento dell'astronave a sinistra
		if(freccia == SPAZIO && tempo >= rateo){																								//Si spara un missile ad una frequenza prestabilita		
			info_base_missili(posiz);
			partenza = clock();			
		}			
		if(freccia == 'r' || freccia == 'R')														nRocket = 0;
		usleep(3000);
	}
}

/* Inizializzazione della posizione di partenza dei missili*/
void info_base_missili(Posizione posiz){
	if(nRocket != N_MAX_MISSILI){
		posMissiliAttuale[nRocket].x = posiz.x + 2;
		posMissiliAttuale[nRocket].y = posiz.y - 1;
		posMissiliAttuale[nRocket].id = nRocket;
		
		posMissiliAttuale[nRocket + 1].x = posiz.x + 3;
		posMissiliAttuale[nRocket + 1].y = posiz.y - 1;
		posMissiliAttuale[nRocket + 1].id = nRocket +1;
		nRocket += N_MISSILI;
	}
}

/** Processo per il movimento dei missili in diagonale*/
void* missile(){
	Posizione missil_p;
	int i;
	
	while(fine == 0){
		for (i = 0; i < N_MAX_MISSILI * N_MISSILI; i++){
			if(posMissiliAttuale[i].id != -1){
				strcpy(posMissiliAttuale[i].c, "missl");
				missil_p = posMissiliAttuale[i];
				
				inserimentoInCoda_sicuro(missil_p);		//Inserimento missile 

				if(missil_p.x <= MAXX && missil_p.y >= MINY){
					if(i % 2 == 0){
						missil_p.x -= 1;
						missil_p.y -= 1;
					}else{
						missil_p.x += 1;
						missil_p.y -= 1;
					}
				}
				posMissiliAttuale[i].x = missil_p.x;
				posMissiliAttuale[i].y = missil_p.y;
			}
		}
		usleep(35000);	
	}
}

/* Stampa dell'astronave in base alla posizione precedente*/
void print_Astro(Posizione p, Posizione pos_prec){
	attrset(COLOR_PAIR(2));
	mvprintw(pos_prec.y, pos_prec.x, "______");	
	
	attrset(COLOR_PAIR(7));
	mvprintw(p.y, p.x, astroPaint);
}

/* Stampa del missile in base alla posizione precedente */
void print_Rocket(Posizione p, Posizione *posPrec){
	attrset(COLOR_PAIR(4));
	mvaddch(posPrec->y, posPrec->x, ' ');
	*posPrec = p;								//Aggiorna la posizione del missile
	if(p.x >= 0 && p.x <= MAXX && p.y >= MINY)
		mvaddch(p.y, p.x, '!');
	else
		posPrec->id = -1;
}




