#include "alieni.h"

// Variabili globali per la stampa degli alieni e bombe
char alienPaint[DIM_Y_ALIEN][DIM_X_ALIEN + 1] ={	{"/X\\\0"},
																				{"X X\0"},
																				{"\\X/\0"}};	
																				
char babyAlienPaint[DIM_X_BABYALIEN + 1]={"<O>\0"};

char bombPaint[DIM_Y_BOMB][DIM_X_BOMB + 1]={{"_\0"},
																			{"0\0"}};
																			
// Dichiarazione dell'array globale contenente la posizione degli alieni
Posizione posAlieniAttuale[N_ALIENI];
extern int fine;
														
/* Inizializzazione delle posizioni iniziali delle Navicelle di primo livello*/														
void iniz_Alieni(Posizione v[]){
	int i, j = -1;
	int dist_alieni = MAXX / N_ALIEN_RIGA;
	
	for(i = 0; i < N_ALIENI; i++){
		if(i % N_ALIEN_RIGA == 0)                   
			j++;
		v[i].x = (i % N_ALIEN_RIGA) * dist_alieni;
		v[i].y = (j * (DIM_Y_ALIEN + 1)) + MINY;
		v[i].id = i;
		if(i % N_ALIEN_RIGA != N_ALIEN_RIGA -1 && i != N_ALIENI - 1)    //Controlla se non è l'ultimo della riga
			v[i].next = i + 1;
		else
			v[i].next = -1;
		if(i % N_ALIEN_RIGA != 0)
			v[i].prev = i - 1;
		else 
			v[i].prev = -1;
		strcpy(v[i].c, "alien");	
		v[i].level = 0;
	}
}

/* Inizializzazione delle posizioni iniziali delle navicelle di secondo livello*/
void iniz_baby(Posizione v[]){
	int i, j = -1;
	int dist_alieni = MAXX / N_ALIEN_RIGA;
	
	for(i = 0; i < N_ALIENI; i++){
		if(i % N_ALIEN_RIGA == 0)
			j++;
		v[i].x = (i % N_ALIEN_RIGA) * dist_alieni;
		v[i].y = (j * (DIM_Y_BABYALIEN + 1)) + MINY;
		v[i].id = i;
		if(i % N_ALIEN_RIGA != N_ALIEN_RIGA -1 && i != N_ALIENI - 1)    //Controlla se non è l'ultimo della riga
			v[i].next = i + 1;
		else
			v[i].next = -1;
		if(i % N_ALIEN_RIGA != 0)
			v[i].prev = i - 1;
		else 
			v[i].prev = -1;
		strcpy(v[i].c, "alien");	
		v[i].level = 1;
	}
}

/** Processo per il movimento degli alieni in maniera temporizzata*/
void* alieno(){
	Posizione posiz;
	int passo[N_ALIENI] = {}, i, j = 0, contatore = 0;
	int start = 0, end = 0, tempo = 0;
	int livelloAtt = posAlieniAttuale[0].level;
	
	start = time(NULL);
	while( lvl(livelloAtt) && fine == 0){			// Termina a fine gioco o fino a che tutti gli alieni cambiano livello
		for(i = 0; i < N_ALIENI && fine == 0; i++){
			while(passo[i] == 0 && j==0)
				passo[i] = -1 + rand()%3;
			
			posiz = posAlieniAttuale[i];			//Si assegna la posizione attuale dell'alieno i-esimo
			
			end = time(NULL);
			tempo = end - start;
			if(tempo > TEMPO_DISCESA){			//Ogni n secondi gli alieni scendono di una casella
				posiz.y += PASSO_Y;
				contatore++;
			}
			if(contatore == N_ALIENI){
				start = time(NULL);
				contatore = 0;
			}	
			
			if(posAlieniAttuale[i].id != -1){									//Viene controllato se gli alieni che precedono o succedono l'alieno attuale sono ancora vivi, altrimenti si controlla se esiste un altro alieno affianco
				controllo_next_prev(&posiz.next, &posiz.prev);				
				
				//Se l'elemento non si trova ai bordi della mappa si può muovere liberamente altrimenti 
				//deve cambiare la sua direzione e controllare che non vi siano altri alieni dove deve andare
				if(controlloPasso(posiz, passo[i]))
					posiz.x = posiz.x + (PASSO_X * passo[i]);
				else
					passo[i] *= -1;								//Cambio di direzione 
				
				posAlieniAttuale[i].x = posiz.x;
				posAlieniAttuale[i].y = posiz.y;
				
				inserimentoInCoda_sicuro(posAlieniAttuale[i]);
			}
			usleep(2700);
		}
	
		if(j == 0)
			j++;
	}
}

/* Funzione per il controllo gli elementi adiacenti*/
void controllo_next_prev(int *next, int *prev){
	while(posAlieniAttuale[*next].id == -1 && *next != -1)		//Si controlla se l'elemento next è ancora in vita (id != -1) e se il next che identifica l'alieno più a destra è stato raggiunto (next == -1)
		*next = posAlieniAttuale[*next].next;
	
	while(posAlieniAttuale[*prev].id == -1 && *prev != -1)		//Si controlla se l'elemento prev è ancora in vita (id != -1) e se il prev che identifica l'alieno più a destra è stato raggiunto (prev == -1)
		*prev = posAlieniAttuale[*prev].prev;								
}

/* Controllo della collisione del passo degli alieni*/
_Bool controlloPasso(Posizione p, int passo){
	int dim;
	
	if(p.level == 0)
		dim = DIM_X_ALIEN;
	else
		dim = DIM_X_BABYALIEN;

	if(passo == 1){					// Controllo passo a destra 
		if(p.x + dim > MAXX)
			return false;
		if(p.next != -1 && p.x + dim + PASSO_X > posAlieniAttuale[p.next].x)
			return false;
	}else{		                        // Controllopasso a sinistra
		if(p.x <= 0)
			return false;
		if(p.prev != -1 && p.x - PASSO_X < posAlieniAttuale[p.prev].x  + dim)
			return false;
	}	
	return true;
}

/** Processo  lo spostamento delle bombe degli alieni*/
void* bomba(){
	Posizione bomba;
	int i;
	int y_rateo_const = MAXY - 10, dist_agg = 0;

	usleep(2000000);
	
	while(fine == 0){                                // Continua fino al termine della partita
		
		// Scelta casuale dell'alieno ancora vivo
		do{
			i = rand()%N_ALIENI;
		}while(posAlieniAttuale[i].id == -1);
		
		bomba = posAlieniAttuale[i];
		strcpy(bomba.c, "bomba");
		
		if(posAlieniAttuale[i].level == 0){		// Scelta del punto di partenza della bomba in base al lv
			bomba.x += 1;
			bomba.y = bomba.y + DIM_Y_ALIEN - 1;
		}else{
			bomba.x += 2;
			bomba.y += 1;
		}
		
		if(bomba.y - y_rateo_const > 0)		// Rallentamento del rateo di fuoco
			dist_agg = bomba.y - y_rateo_const;
		else 
			dist_agg = 0;
		
		while(bomba.y + 1 != MAXY + dist_agg){
			bomba.y += PASSO_Y;
			inserimentoInCoda_sicuro(bomba);
			usleep(55000);
		}
	}
}

/* Funzione per la stampa degli alieni di primo livello*/
void print_Alien(Posizione p, Posizione posPrec){
	int i;
	attrset(COLOR_PAIR(3));
	
	delete_Alien(posPrec);
					
	for(i = 0; i< DIM_Y_ALIEN; i++)
		mvprintw(p.y + i, p.x, alienPaint[i]);
}

/* Funzione per la stampa degli alieni si secondo livello*/
void print_Baby_Alien(Posizione p, Posizione posPrec, char stato[]){
	int i, j;

	delete_BabyAlien(posPrec, stato);
	for(i = 0; i < N_BABY_ALIENI; i++) {
		attrset(COLOR_PAIR(2));
		if(stato[i] == '1')
			attrset(COLOR_PAIR(6));
		if(i == 0 && stato[i] != '0')
			mvprintw(p.y, p.x, babyAlienPaint);
		if(i == 1 && stato[i] != '0')
			mvprintw(p.y, p.x + (DIM_X_BABYALIEN / 2) + 1, babyAlienPaint);	
		if(i == 2 && stato[i] != '0')
			mvprintw(p.y + DIM_Y_BABYALIEN -1, p.x, babyAlienPaint);
		if(i == 3 && stato[i] != '0')
			mvprintw(p.y + DIM_Y_BABYALIEN -1, p.x + (DIM_X_BABYALIEN / 2) + 1, babyAlienPaint);
	}
}

/* Funzione per la stampa delle bombe*/
void print_Bomb(Posizione p, Posizione posPrec){
	attrset(COLOR_PAIR(5));
	mvprintw(posPrec.y, posPrec.x, " ");
	mvprintw(posPrec.y + DIM_Y_BOMB -1, posPrec.x, " ");
	if(p.y < MAXY){
		mvprintw(p.y, p.x, bombPaint[0]);
		mvprintw(p.y + DIM_Y_BOMB -1, p.x, bombPaint[1]);
	}
}

/* Funzione per l'eliminazione della stampa precedente degli alieni di primo livello*/
void delete_Alien(Posizione posPrec){
	int i;
	
	for(i = 0; i< DIM_Y_ALIEN; i++)
		mvprintw(posPrec.y + i, posPrec.x, "   ");
}

/* Funzione per l'eliminazione della stampa precedente degli alieni di secondo livello*/
void delete_BabyAlien(Posizione posPrec, char stato[]){
	if(stato[0] != '0')
		mvprintw(posPrec.y, posPrec.x, "   ");
	if(stato[1] != '0')
		mvprintw(posPrec.y, posPrec.x + (DIM_X_BABYALIEN / 2)+1, "   ");	
	if(stato[2] != '0')
		mvprintw(posPrec.y + DIM_Y_BABYALIEN - 1, posPrec.x, "   ");
	if(stato[3] != '0')
		mvprintw(posPrec.y + DIM_Y_BABYALIEN - 1, posPrec.x + (DIM_X_BABYALIEN / 2)+1, "   ");
}

/* Funzione per il riconoscimento del livello delle navicelle aliene*/
_Bool lvl(int lev){
	int i; 
	for(i=0; i< N_ALIENI; i++)
		if(posAlieniAttuale[i].level == lev)
			return true;
	return false;
}