#include "matt.h"

// Inizializzazionedel mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;		

// Variabili globali passate dalle altre funzioni
extern Posizione posAlieniAttuale[N_ALIENI];					
extern int fine, collision, nRocket;			
extern Queue queue;
char nome[DIM_STRING_NAME];

// Funzione per la richiesta del nome
void richiesta_nome(char []);

int main(){
	pthread_t thr_Astro, thr_Alien, thr_Rocket, thr_Bomb;
	int scelta = 0;
	Posizione posAux = {};
	int partenza_gioco = 0, fine_gioco = 0, tempo_gioco = 0;
	
	// Inizializzazione dei semafori
	sem_init(&presenti, 0, 0);
	sem_init(&disponibili, 0, DIM_CODA);
	
	/*Inizializzazione coda*/
	queue.front = NULL;
	queue.back = NULL;
	queue.cont = 0;
	
	initscr();					//Si inizializza lo schermo 
	richiesta_nome(nome);
	noecho();					//Non saranno visualizzati i caratteri inseriti
	srand((int)time(NULL));
	curs_set(0);				//Si nasconde il cursore
	nodelay(stdscr, true);
	
	start_color();
	iniz_schermo_colori();
	
	while(scelta != ESCI){
		scelta = menu(nome);						// Si chiama la funzione del menù
		clear();
		
		if(scelta == TUTORIAL)						// Viene stampato il tutorial
			istruzioni();
		
		if(scelta == MENUSKIN){					// Viene stampato il menu per la scelta si quale skin modificare
			scelta = menuSkin();
			
			if(scelta != ESCI){							// Scelta effettiva della skin
				clear();
				skin(scelta);
			}
			scelta = 10;
		}
		if(scelta == STATISTICHE){
			Lett_Statistiche();
		}
		if(scelta == GIOCA){							// Partenza del gioco
			fine = 0;
			collision =-1;
			nRocket = 0;
			iniz_Alieni(posAlieniAttuale);			//Si definiscono le posizioni iniziali degli alieni
			iniz_Missili();										//Si inizializza lo stato dei missili
			
			pthread_create(&thr_Astro, NULL, &astronave, NULL);
			pthread_create(&thr_Rocket, NULL, &missile, NULL);		
			pthread_create(&thr_Alien, NULL, &alieno, NULL);
			pthread_create(&thr_Bomb, NULL, &bomba, NULL);
			
			matt();						//Viene chiamata la funzione di disegno
			
			while(!isEmptyQueue(&queue))
				posAux = letturaCoda_sicura();
			
			pthread_join(thr_Astro, NULL);	
			pthread_join(thr_Rocket, NULL);	
			pthread_join(thr_Alien, NULL);
			pthread_join(thr_Bomb, NULL);
		}
		
	}
	
	endwin();
	return 0;
}

// Funzione per la richiesta del nome
void richiesta_nome(char nome[]){
	char* frase1 = "Ciao.\n", *frase2 = "Come ti chiami?\n";
	
	mvprintw(MAXY / 2 -1, (MAXX/2) - (strlen(frase1)/ 2), frase1);
	mvprintw(MAXY / 2, (MAXX/2) - (strlen(frase2)/ 2), frase2);
	mvaddch(MAXY / 2+ 2, (MAXX/2) - 5, ' ');
	getstr(nome);
}
