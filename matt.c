#include "matt.h"

/* Variabili globali definite in altri filrìe*/
extern int fine, collision, nRocket;
extern Posizione posMissiliAttuale[N_MAX_MISSILI * 2];			
extern Posizione posAlieniAttuale[N_ALIENI];
extern char nome[];
int punteggio = 0;

/** Funzione dove si gestisce la stampa a video e la collisione degli elementi sotto processi */
void matt(){
	Posizione p, pAstro = {1, MAXY}, posAlieniPrec[N_ALIENI], pBomb, posMissiliPrec[N_MAX_MISSILI*N_MISSILI]; // Variabili di supporto
	int i, j, nVite = 2;
	char statoBabyAlieni[N_ALIENI][N_BABY_ALIENI + 1], statoAstro = '2';
	int numBA;
	pthread_t thr_BA;
	int partenza_gioco = 0;
	
	punteggio = 0;
	
	iniz_Alieni(posAlieniPrec);
	
	partenza_gioco = time(NULL);
	attron(COLOR_PAIR(2));
	for(int i = 0; i< MAXX; i++)
		mvaddch(MAXY, i, '_');

	while(fine == 0){
		//Lettura valore dal buffer
		do{
			p = letturaCoda_sicura();
		}while(controllo_input_Matt(p, pAstro, posAlieniPrec, posMissiliPrec, pBomb) && fine == 0);
		
		print_info_Rocket();
		stampa_vita(nVite, partenza_gioco);
		
		/// Stampa dello score
		attrset(COLOR_PAIR(7));
		mvprintw(0, MAXX-13, "     ", punteggio);
		attrset(COLOR_PAIR(2));
		mvprintw(0, MAXX-20, "SCORE: %d", punteggio);

		if(strcmp(p.c, "astro") == 0) {		///AGGIORNAMENTO DELLA POSIZIONE DELL'ASTRONAVE
			print_Astro(p, pAstro);				//Stampa dell'astronave 
			pAstro = p;									//Aggiorna la posizione dell'astronave
		}
		
		
		if(strcmp(p.c, "alien") == 0 && posAlieniAttuale[p.id].id != -1){				///AGGIORNAMENTO DELLA POSIZIONE DELL'ALIENO
			if(posAlieniAttuale[p.id].level == 0){								///ALIENO DI LIVELLO 0
				print_Alien(p, posAlieniPrec[p.id]);								//Stampa dell'alieno 
				posAlieniPrec[p.id] = p;													//Si memorizza l'ultima posizione stampata
				
				if(posAlieniPrec[p.id].y + DIM_Y_ALIEN  > MAXY)	//Controllo della collisione con la base della mappa 
					collisione(ALIEN_BASE, partenza_gioco);
			}else{																													///ALIENO DI LIVELLO 1
				print_Baby_Alien(p, posAlieniPrec[p.id], statoBabyAlieni[p.id]);			//Stampa del gruppo di alieni
				posAlieniPrec[p.id] = p;																					//Si memorizza l'ultima posizione stampata
				
				//Controllo della collisione con la base della mappa 
				if(p.y + DIM_Y_BABYALIEN > MAXY){
					if(statoBabyAlieni[p.id][N_BABY_ALIENI-1] != '0' || statoBabyAlieni[p.id][N_BABY_ALIENI-2] != '0' )		//Controllo dello stato vitale delle navicelle posizionate più in basso
						collisione(ALIEN_BASE, partenza_gioco);
					else if(p.y >= MAXY)																																					//Se le navicelle in basso sono già morte allora si controlla la posizione di quelle in alto
						collisione(ALIEN_BASE, partenza_gioco);		
				}																																										//Almeno una navicella deve essere viva per entrare nel processo di stampa 
			}
		}
		
		
		if(strcmp(p.c, "missl") == 0 && posMissiliAttuale[p.id].id != -1){				///AGGIORNAMENTO DELLA POSIZIONE DEI MISSILI
			print_Rocket(p, &posMissiliPrec[p.id]);
			
			for(i = N_ALIENI - 1; i >= 0 && posMissiliAttuale[p.id].id != -1; i--)
				controllo_hit_alieni(p, statoBabyAlieni[i], i, &posAlieniPrec[i]);
		}
		
		
		if(strcmp(p.c, "bomba") == 0){																			///AGGIORNAMENTO DELLA POSIZIONE DELLA BOMBA
				print_Bomb(p, pBomb);
			
			if(pBomb.y + 1 >= MAXY){
				attrset(COLOR_PAIR(2));
				mvprintw(MAXY, pBomb.x, "_");
			}
			
			pBomb = p;
			
			// Controllo della collisione con l'astronave con aggiunta di gof mode per test
			if(pBomb.y + DIM_Y_BOMB == MAXY &&  pBomb.x >= pAstro.x && pBomb.x < pAstro.x + DIM_X_ASTRO){
				if(GOD_MODE == 0){
					if(statoAstro == '0')
						collisione(HIT_BOMBA, partenza_gioco);
					else{
						statoAstro--;
						nVite--;
					}		
				}
			}
		}
		
		// Contralla se sono morti gli alieni per cambiare il livello o in caso di vincita
		if(alieni_morti()){
			if(posAlieniAttuale[0].level == -1){
				punteggio += PT_FINE_GIOCO;
				collisione(ALIENI_MORTI, partenza_gioco);
				pthread_join(thr_BA, NULL);
			}else{
				iniz_baby(posAlieniAttuale);
				pthread_create(&thr_BA, NULL, &alieno, NULL);
			}
		}
		
		refresh();
		usleep(100);
	}
	return;
}

void stampa_vita(int nVite, int t_partenza){
	int i;
	char *hp = "<3\0";
	int t_fine = time(NULL), t_attuale = t_fine - t_partenza;
	
	attrset(COLOR_PAIR(7));
	mvprintw(0, MAXX/2 - 4,"HP:");
	mvprintw(0, MAXX/2 - 1 , "    ");
	mvprintw(1, MAXX/2 - 6,"TIME:");
	mvprintw(1, MAXX/2 - 1 , "    ");
	for(i = 0; i < nVite; i++){
		/** Stampa dei dati visibili al giocatore(vita)*/
		attrset(COLOR_PAIR(6));
		mvprintw(0, MAXX/2 - 1 + (2*i) , hp);
	}
	attrset(COLOR_PAIR(2));
	mvprintw(1, MAXX/2 - 1, "%d", t_attuale);
}

/* Funzione che stampa a video le munizioni dell'asronave*/
void print_info_Rocket(){
	attrset(COLOR_PAIR(7));
	mvprintw(0, 0, "AMMO: %d  ", N_MAX_MISSILI - nRocket);
	attrset(COLOR_PAIR(4));
	mvprintw(0, 6, "%d  ", N_MAX_MISSILI - nRocket);
	if(nRocket == N_MAX_MISSILI)
		mvprintw(MAXY + 2, (MAXX/2) - 9, "Premi 'R' per RICARICARE");
	else
		mvprintw(MAXY + 2, (MAXX/2) - 9, "                         ");
}

/* Funzione di controllo dell'input del Matt */
_Bool controllo_input_Matt(Posizione p, Posizione pAstro, Posizione pAlien[], Posizione pM[], Posizione pB){
	Posizione pPrev;
	
	if(strcmp(p.c, "astro") == 0)
		pPrev = pAstro;
	else if(strcmp(p.c, "alien") == 0)
		pPrev = pAlien[p.id];
	else if(strcmp(p.c, "missl") == 0)
		pPrev = pM[p.id];
	else if(strcmp(p.c, "bomba") == 0)
		pPrev = pB;
	
	if(p.x != pPrev.x || p.y != pPrev.y)
		return false;
	else 
		return true;
}

/* Funzione di controllo per l hit del missile con un determitao alieno e se è vivo*/
int controllo_hit_missile(Posizione pos_Alieno, Posizione pos_Missile){
	int i, j;
	
	if(pos_Alieno.id != -1){
		if(pos_Alieno.level == 0){
			if(pos_Missile.y < pos_Alieno.y + DIM_Y_ALIEN && pos_Missile.y >= pos_Alieno.y)
				if(pos_Missile.x < pos_Alieno.x + DIM_X_ALIEN && pos_Missile.x >= pos_Alieno.x)
					return 0;
		}else{
			if(pos_Missile.x < pos_Alieno.x + (DIM_X_BABYALIEN / 2) && pos_Missile.x >= pos_Alieno.x){
				if(pos_Missile.y == pos_Alieno.y)
					return 0;
				else if(pos_Missile.y == pos_Alieno.y + DIM_Y_BABYALIEN -1)
					return 2;
			}else if(pos_Missile.x < pos_Alieno.x + DIM_X_BABYALIEN && pos_Missile.x >= pos_Alieno.x + (DIM_X_BABYALIEN / 2)){
				if(pos_Missile.y == pos_Alieno.y)
					return 1;
				else if(pos_Missile.y == pos_Alieno.y + DIM_Y_BABYALIEN -1)
					return 3;			
			}
		}
	}
	return -1;
}

/* Funzione per il controllo dell'hit del misile eaggiornamento degli stati sia per gli alieni di 1 e 2 livello*/
void controllo_hit_alieni(Posizione pM, char stato[], int  i, Posizione *posAlPr){
	int controllo;
	
	controllo = controllo_hit_missile(*posAlPr, pM);		//Si controlla se il missile ha colpito l'alieno e se l'alieno che si sta controllando è vivo o morto 
	
	if(controllo != -1){
		if(posAlieniAttuale[i].level == 1){						//Controllo alieni di livello 1
			if(stato[controllo] != '0'){
				delete_BabyAlien(*posAlPr, stato);
				stato[controllo]--;														//Viene decrementato lo stato dell'alieno di secondo livello. Indica il numero di volte che può essere colpito
				posMissiliAttuale[pM.id].id = -1;							//Il missile viene eliminato
				
				if(strcmp(stato, "0000\0") == 0){							//Se tutti i baby-alieni sono morti allora l'alieno viene eliminato
					posAlieniAttuale[i].id = -1; 								//La sua posizione non sarà più valida
					posAlieniAttuale[i].level = -1;
					posAlPr->id = -1;
				}
				mvaddch(pM.y, pM.x, ' ');
				punteggio += PT_ALIENO_LVL_DUE;
			}
		}else if(posAlieniAttuale[i].level == 0){				//Controllo alieni di livello 0
			posMissiliAttuale[pM.id].id = -1;						//Il missile viene eliminato
			posAlieniAttuale[i].id = -1;									//L'alieno viene eliminato
			posAlieniAttuale[i].level++;
			posAlPr->id = -1;
			strcpy(stato, "2222\0"); 										//Viene settato lo stato degli alieni di secondo livello
			delete_Alien(*posAlPr);
			punteggio += PT_ALIENO_LVL_UNO;
		}
	}
}

/* Funzione che controlla se ci sono ancora alieni vivi*/
_Bool alieni_morti(){
	int i; 
	for(i=0; i< N_ALIENI; i++)
		if(posAlieniAttuale[i].id != -1)
			return false;
	return true;
}

/* Funzione che modifica la collisione e termina i gioco e i processi*/
void collisione(int tipoCollisione, int partenza_gioco){
	int fine_gioco = time(NULL);
	int tempo_gioco = fine_gioco - partenza_gioco;
	
	clear();
	attrset(COLOR_PAIR(5));
	mvprintw(25, 5, "%s	%d Pt.		%d Secondi", nome, punteggio, tempo_gioco);
	
	Salv_statistiche(tempo_gioco);
	
	
	switch(tipoCollisione){
		case ALIEN_BASE:
			collision= ALIEN_BASE;
			break;
		case ALIENI_MORTI:
			collision= ALIENI_MORTI;
			break;
		case HIT_BOMBA:
			collision= HIT_BOMBA;
			break;
	}
	endgame();
	fine--;
}



