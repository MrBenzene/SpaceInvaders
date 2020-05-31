#include "menu.h"

extern int collision;
extern char alienPaint[DIM_Y_ALIEN][DIM_X_ALIEN + 1];	
extern char astroPaint[DIM_X_ASTRO + 1];																				
extern char babyAlienPaint[DIM_X_BABYALIEN + 1];
extern char nome[];
extern int punteggio;

/* Funzione per la stampa delle istruzioni*/
void istruzioni(){
	char c = 0;
	char* richiestaInput = "Premere K per chiudere.";
	Posizione p;
	
	clear();
	
	attron(COLOR_PAIR(2));
	for(int i = 0; i< MAXX; i++)
		mvaddch(MAXY, i, '_');
	
	p.x = 10;
	p.y = 3;
	print_Alien(p, p);
	
	p.x = 80;
	p.y = 5;
	print_Baby_Alien(p, p, "2222");
	p.x = 80 + DIM_X_BABYALIEN + 5;
	p.y = 4;
	print_Baby_Alien(p, p, "2122");
	
	p.x = 50;
	p.y = MAXY;
	print_Astro(p, p);
	p.x += 2;
	p.y -= 1;
	print_Rocket(p, &p);
	p.x++;
	print_Rocket(p, &p);
	p.x -= 3;
	p.y -= 2;
	print_Rocket(p, &p);
	p.x += 5;
	print_Rocket(p, &p);
	
	p.x = 11;
	p.y = 9;
	print_Bomb(p, p);
	
	attrset(COLOR_PAIR(7));
	mvprintw(0, MAXX - 7,"HP:");
	attrset(COLOR_PAIR(6));
	mvprintw(0, MAXX - 4,"<3<3");
	
	attrset(COLOR_PAIR(7));
	mvprintw(0, 0, "AMMO:");
	attrset(COLOR_PAIR(4));
	mvprintw(0, 6, "%d  ", N_MAX_MISSILI);
	mvprintw(1, 0, "Premi 'R' per RICARICARE");

	
	attrset(COLOR_PAIR(2));
	mvprintw(4, 15, "Alieno di Primo Livello.");
	mvprintw(6 + DIM_Y_BABYALIEN, 80, "Gruppo di alieni di Secondo Livello.");
	mvprintw(7 + DIM_Y_BABYALIEN, 80, "Quando colpiti si arrabbiano e diventano rossi.");
	mvprintw(8 + DIM_Y_BABYALIEN, 80, "Dovrai colpirli due volte per ucciderli.");
	mvprintw(MAXY - 2, 57, "Questa è la tua astronave.");
	mvprintw(MAXY - 1, 57, "Spara due colpi alla volta in orizzontale.");
	mvprintw(9, 15, "Fai attenzione alle bombe lanciate dalle astronavi aliene!");
	mvprintw(10, 15, "Possono ucciderti!");
	mvprintw(0, MAXX - 9 - strlen("Hai solo tre vite, usale bene."), "Hai solo tre vite, usale bene.");

	attrset(COLOR_PAIR(1));
	mvprintw(MAXY + 2, (MAXX / 2) - (strlen(richiestaInput) / 2), richiestaInput);
	while(c != 'K' && c != 'k')
		c = getch();
}

/* Funzione per l'inizializzazione dei colri per le stampe*/
void iniz_schermo_colori(){
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_RED, COLOR_BLACK);
	init_pair(7, COLOR_GREEN, COLOR_BLACK);
	
	attron(COLOR_PAIR(2));
}

/* Funzione per la stampa a fine gioco*/
void endgame(){
	char c = 0;
	char* richiestaInput = "Premere K per chiudere.";
	char *winString0={"____    ____  ______    __    __     ____    __    ____  __  .__   __. \0"};
	char *winString1={"\\   \\  /   / /  __  \\  |  |  |  |    \\   \\  /  \\  /   / |  | |  \\ |  | \0"};
	char *winString2={" \\   \\/   / |  |  |  | |  |  |  |     \\   \\/    \\/   /  |  | |   \\|  | \0"};
	char *winString3={"  \\_    _/  |  |  |  | |  |  |  |      \\            /   |  | |  . `  | \0"};
	char *winString4={"    |  |    |  `--'  | |  `--'  |       \\    /\\    /    |  | |  |\\   | \0"};
	char *winString5={"    |__|     \\______/   \\______/         \\__/  \\__/     |__| |__| \\__| \0"};
                    
	char *loseString0 = {"  _______      ___      .___  ___.  _______      ______   ____    ____  _______ .______      \0"};
	char *loseString1 = {" /  _____|    /   \\     |   \\/   | |   ____|    /  __  \\  \\   \\  /   / |   ____||   _  \\     \0"};
	char *loseString2 = {"|  |  __     /  ^  \\    |  \\  /  | |  |__      |  |  |  |  \\   \\/   /  |  |__   |  |_)  |    \0"};
	char *loseString3 = {"|  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|     |  |  |  |   \\      /   |   __|  |      /     \0"};
	char *loseString4 = {"|  |__| |  /  _____  \\  |  |  |  | |  |____    |  `--'  |    \\    /    |  |____ |  |\\  \\----.\0"};
	char *loseString5 = {" \\______| /__/     \\__\\ |__|  |__| |_______|    \\______/      \\__/     |_______|| _| `._____|\0"};
	
	attrset(COLOR_PAIR(5));
	
	if(collision == ALIENI_MORTI){
		mvprintw((MAXY / 2) -3, (MAXX / 2) - (strlen(winString0) / 2), winString0);	
		mvprintw((MAXY / 2) -2, (MAXX / 2) - (strlen(winString0) / 2), winString1);
		mvprintw((MAXY / 2) -1, (MAXX / 2) - (strlen(winString0) / 2), winString2);
		mvprintw((MAXY / 2), (MAXX / 2) - (strlen(winString0) / 2), winString3);
		mvprintw((MAXY / 2) +1, (MAXX / 2) - (strlen(winString0) / 2), winString4);
		mvprintw((MAXY / 2) +2, (MAXX / 2) - (strlen(winString0) / 2), winString5);
	}
	if(collision == ALIEN_BASE || collision == HIT_BOMBA){
		mvprintw((MAXY / 2) -3, (MAXX / 2) - (strlen(loseString0) / 2), loseString0);
		mvprintw((MAXY / 2) -2, (MAXX / 2) - (strlen(loseString0) / 2), loseString1);		
		mvprintw((MAXY / 2) -1, (MAXX / 2) - (strlen(loseString0) / 2), loseString2);		
		mvprintw((MAXY / 2), (MAXX / 2) - (strlen(loseString0) / 2), loseString3);		
		mvprintw((MAXY / 2) +1, (MAXX / 2) - (strlen(loseString0) / 2), loseString4);		
		mvprintw((MAXY / 2) +2, (MAXX / 2) - (strlen(loseString0) / 2), loseString5);	
	}
	mvprintw((MAXY / 2) +4, (MAXX / 2) - (strlen(richiestaInput) / 2), richiestaInput);
	
	while(c != 'K' && c != 'k')
		c = getch();
}

/* Funzione per la gestione del menu*/
int menu(char *nome){
	attrset(COLOR_PAIR(7));
	clear();
	
	mvprintw((MAXY / 2) - 7, MAXX / 2, "Ciao");
	mvprintw((MAXY / 2) - 6, MAXX / 2, "%s.", nome);
	mvprintw((MAXY / 2) - 2, MAXX / 2, "MENU'");
	mvaddch((MAXY / 2), (MAXX / 2) -1, '>');
	mvprintw((MAXY / 2), (MAXX / 2), "GIOCA");
	mvprintw((MAXY / 2) + 1, (MAXX / 2), "TUTORIAL");
	mvprintw((MAXY / 2) + 2, (MAXX / 2), "SKIN");
	mvprintw((MAXY / 2) + 3, (MAXX / 2), "ESCI");
	mvprintw((MAXY / 2) + 4, (MAXX / 2), "STATISTICHE");
	mvprintw((MAXY / 2) + 6, (MAXX / 2) - (strlen("Premere K per continuare") / 2) + 2, "Premere K per continuare");


	//Scorrimento nel menù per la scelta dell'azione
	return scorrimento_menu(EL_MENU);
}

//Funzione per lo scorrimento del menù 
int scorrimento_menu(int elementi_menu){
	int posMenu = 0;		//Intero che indica la posizione nel menù e la scelta dell'utente
	char c = 0;
	
	while(c != 'k' && c != 'K'){	

		switch(c=getch()){	//Alla pressione dei tasti freccia su e giù il puntatore viene spostato
			case SU:
				if(posMenu > 0){
					mvaddch((MAXY / 2) + posMenu, (MAXX / 2) - 1, ' ');
					posMenu--;
					mvaddch((MAXY / 2) + posMenu, (MAXX / 2) - 1, '>');
				}
				break;

			case GIU:
				if(posMenu < EL_MENU - 1){
					mvaddch((MAXY / 2) + posMenu, (MAXX / 2) - 1, ' ');
					posMenu++;
					mvaddch((MAXY / 2) + posMenu, (MAXX / 2) - 1, '>');
				}			
				break;
		}
	}
	return posMenu;	//Si ritorna la posizione del cursore al momento della scelta
}

/* Funzione menu per la scelta delle skin*/
int menuSkin(){
	int elementi_menu= EL_MENU;
	
	attrset(COLOR_PAIR(7));

	mvaddch((MAXY / 2), (MAXX / 2) -1, '>');
	mvprintw((MAXY / 2), (MAXX / 2), "ALIENO 1° LVL");
	mvprintw((MAXY / 2) + 1, (MAXX / 2), "ALIENO 2° LVL");
	mvprintw((MAXY / 2) + 2, (MAXX / 2), "ASTRONAVE");
	mvprintw((MAXY / 2) + 3, (MAXX / 2), "ESCI");
	mvprintw((MAXY / 2) + 5, (MAXX / 2) - (strlen("Premere K per continuare") / 2) + 2, "Premere K per continuare");

	//Scorrimento nel menù per la scelta dell'azione
	return scorrimento_menu(elementi_menu);
}

/* Funzione per la modifica della skin*/
void skin(int scelta){
	FILE *fp = NULL;
	int i, dimY, dimX;
	int elementi_menu;
	char nome[DIM_STRING_FILE];

	switch(scelta){			//Viene aperto il file corrispondente alla scelta dell'utente
		case SKINALIENO_UNO:
			fp = fopen("skinAlien1", "r");
			if(fp == NULL){
				printf("Il file 'skinAlien1' non è presente nella directory");
				return;
			}
			dimY = DIM_Y_ALIEN;		//Si impostano le dimensioni delle figure presenti nel file
			dimX = DIM_X_ALIEN;
			break;
		case SKINALIENO_DUE:
			fp = fopen("skinAlien2", "r");
			if(fp == NULL){
				printf("Il file 'skinAlien2' non è presente nella directory");
				return;
			}
			dimY = 1;
			dimX = 3;
			break;
		case SKINASTRONAVE:
			fp = fopen("skinAstro", "r");
			if(fp == NULL){
				printf("Il file 'skinAstro' non è presente nella directory");
				return;
			}
			dimY = DIM_Y_ASTRO;
			dimX = DIM_X_ASTRO;
			break;
	}
	
	clear();
	refresh();
	
	//Stampa dei nomi delle skin aggiuntive
	attrset(COLOR_PAIR(7));
	fscanf(fp, "%d", &elementi_menu);
	fscanf(fp, "\n");
	for(i = 0; i < elementi_menu; i++){
		fscanf(fp, "%[^\n]s", nome);
		fscanf(fp, "\n");
		mvprintw(10 + i, 21, nome);
	}
	mvprintw(MAXY - 5, (MAXX / 2) - (strlen("Premere K per continuare") / 2) + 2, "Premere K per continuare");
	mvaddch(10, 20, '>');	
	
	scorrimentoListaSkin(fp, dimX, dimY, elementi_menu);
	
	salvataggio_stampa(fp, dimY, dimX, scelta);  //Si salva la stampa nella variabile globale
	
	fclose(fp);
}

//Funzione che salvala stampa all'interno della variabile globale
void salvataggio_stampa(FILE *fp, int dimY, int dimX, int scelta){
	char skin[DIM_X_ASTRO + 1];
	int i;
	
	//Viene copiata la figura scelta dal file alla variabile globale
	for(i = 0; i < dimY; i++){
		fscanf(fp, "%[^\n]s", skin);
		fscanf(fp, "\n");
		
		if(scelta == SKINALIENO_UNO){		
			strcpy(alienPaint[i], skin);
			alienPaint[i][dimX] = '\0';					
		}
		
		if(scelta == SKINALIENO_DUE){
			strcpy(babyAlienPaint, skin);
			babyAlienPaint[dimX] = '\0';
		}
		
		if(scelta == SKINASTRONAVE){
			strcpy(astroPaint, skin);
			astroPaint[dimX] = '\0';
		}
	}
}

/* Funzione per lo scorrimento del file e la scelta della skin */
void scorrimentoListaSkin(FILE *fp, int dimX, int dimY, int elementi_menu){
	char c = SU, skin[DIM_X_ASTRO + 1];
	int posMenu = 0;
	int i;
	
	while(c != 'k' && c != 'K'){
		if(c == SU || c == GIU){
			attrset(COLOR_PAIR(3));
			for(i = 0; i < dimY; i++){
				fscanf(fp, "%[^\n]s", skin);					//Si legge e stampa la figura corrispondente all'elemento puntato nel menù
				fscanf(fp, "\n");
				mvprintw(10 + i, 55, skin);
			}	
			fseek(fp, -((dimX + 2) * dimY), SEEK_CUR);		//Viene riportato il puntatore all'inizio della figura
		}
		
		attrset(COLOR_PAIR(7));
		switch(c=getch()){
			case SU:
				if(posMenu > 0){
					mvaddch(10 + posMenu, 20, ' ');
					posMenu--;
					mvaddch(10 + posMenu, 20, '>');		
					fseek(fp, -((dimX + 2) * dimY), SEEK_CUR);	//Viene spostato il puntatore all'interno del file
				}
				break;

			case GIU:
				if(posMenu < elementi_menu - 1){
					mvaddch(10 + posMenu, 20, ' ');
					posMenu++;
					mvaddch(10 + posMenu, 20, '>');
					fseek(fp, (dimX + 2) * dimY, SEEK_CUR);
			}			
			break;
		}	
	}
}

void Salv_statistiche(int tempo){
	FILE *fp = NULL;
	Statistica Risultati[NUM_EL_FILE + 1]={};
	
	/**Apre un file bin in accodamento e salva lo score, nel caso non esista lo apre in scrittura da zero*/
	fp = fopen("statistiche.sav", "ab");
	if(fp == NULL){
		fp = fopen("statistiche.sav", "wb");
		if(fp == NULL){
			printf("\nErrore di apertura del file...");
			exit(-1);
		}
	}
	fwrite(&tempo, sizeof(int), 1, fp);
	fwrite(nome, sizeof(char), DIM_STRING_NAME, fp);
	fwrite(&punteggio, sizeof(int), 1, fp); 

	fclose(fp);
	
	ordinamentoFile(Risultati);
}


void Lett_Statistiche(){
	FILE *fp = NULL;
	Statistica Risultati[NUM_EL_FILE + 1]={}, aux;
	int i = 0, j, k;
	char c = 0;
	char* richiestaInput = "Premere K per chiudere.";
	
	/**Apre un file bin in lettura e salva statistiche in delle variabili ausliari e i dati verranno poi stampati a video*/
	fp = fopen("statistiche.sav", "rb");
	if(fp == NULL){
		printf("\nNessuna partita giocata");
		return;
	}
	//Vengono salvate le informazioni del file all'interno di un vettore 
	for(i = 0; i < NUM_EL_FILE + 1 && !feof(fp); i++){
		fread(&Risultati[i].Time_g, sizeof(int), 1, fp);
		fread(Risultati[i].Nome_pl, sizeof(char), DIM_STRING_NAME, fp);
		fread(&Risultati[i].Punteggi, sizeof(int), 1, fp);
	}

	clear();
	
	for(i=0; i < NUM_EL_FILE; i++)
		mvprintw(3 + i +1, 40, "%20s   %4d   %3d sec", Risultati[i].Nome_pl, Risultati[i].Punteggi, Risultati[i].Time_g );
	
	mvprintw((MAXY / 2) +4, (MAXX / 2) - (strlen(richiestaInput) / 2), richiestaInput);
		
	while(c != 'K' && c != 'k')
		c = getch();
}

void ordinamentoFile(Statistica Risultati[]){
	FILE *fp = NULL;
	int i;
	
	fp = fopen("statistiche.sav", "rb");
	if(fp == NULL){
		printf("\nNessuna partita giocata");
		return;
	}

	//Vengono salvate le informazioni del file all'interno di un vettore 
	for(i = 0; i < NUM_EL_FILE + 1 && !feof(fp); i++){
		fread(&Risultati[i].Time_g, sizeof(int), 1, fp);
		fread(Risultati[i].Nome_pl, sizeof(char), DIM_STRING_NAME, fp);
		fread(&Risultati[i].Punteggi, sizeof(int), 1, fp);
	}
	
	selectionSort(Risultati, i);	//Il vettore viene ordinato
	fclose(fp);							//Si chiude il file
	
	fp = fopen("statistiche.sav", "wb");	//Viene riordinato il file per tenere il numero di elementi costante
	if(fp != NULL){	
		for(i = 0; i < NUM_EL_FILE; i++){
			fwrite(&Risultati[i].Time_g, sizeof(int), 1, fp);
			fwrite(Risultati[i].Nome_pl, sizeof(char), DIM_STRING_NAME, fp);
			fwrite(&Risultati[i].Punteggi, sizeof(int), 1, fp); 
		}
		fclose(fp);
	}
	else
		printf("Errore apertura file.");
}

/* La funzione Selectionsort ordina un array in ordine decrescente prendendo un indice min e controlla scorrendo da min
* all'ultimo elemento e nel caso trovi un elemento maggiore scambia l'indice e scambia gli elementi*/
void selectionSort(Statistica *array, int dim){
	int max, j, i;

	for (i = 0; i < dim - 1; ++i) {
		max = i;

		for (j = i + 1; j < dim; ++j) {
			if(array[j].Punteggi > array[max].Punteggi)
				max = j;
			if(array[j].Punteggi == array[max].Punteggi && array[j].Time_g < array[max].Time_g)
				max = j;
		}
		swap(&array[max], &array[i]);
	}
}

void swap(Statistica* max, Statistica* j){
	Statistica aux;

	aux = *max;
	*max = *j;
	*j = aux;
}