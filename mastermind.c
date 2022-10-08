// author: Stefano Walter Mavilio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



// PROTOTIPI
int RandomInteger(int , int );
void stampaBanner();
void stampaIstruzioni();
void play();
void conta_bianchi(int * c , int * sum, int min, int l, int * cp, int * tentativo, char input[], char code[]);
void sequenza_esatta(int *flag, int, char input[], char code[], int tentativo);  
int conta_neri(int cp, int l, char input[], char code[]);	
int controllo_arreso(char input[], char code[], int, int);
int controllo_input(int, int, int, char input[]);



/* simple helper-function to empty stdin */  
void empty_stdin(void) {   // usiamo questa funzione per pulire il buffer di input
    int c = getchar();
    while (c != '\n' && c != EOF) {
    	c = getchar();
	}
        
}



main() {
	
	// DEFINIZIONI
	int rtn, choice;
	
	// chiamata alla funzione print_banner() 
	stampaBanner();
	
	
	// MENU (scegli tra le opzioni possibili)
	do {
		printf("\nScegli tra le opzioni possibili sottostanti (digita un numero):\n\n");
		
 		printf("1. Istruzioni di gioco\n");
 		
 		printf("2. Gioca\n");
 		
 		printf("3. Exit\n");
 		
 		printf("\nInserisci un numero:");
		
		
		// GESTIONE DEGLI ERRORI DI INPUT
		rtn = scanf (" %d", &choice);    /* save return */
		// se il rtn è 1, vuol dire che va bene, se 0 vuol dire che non è valido

        if (rtn == EOF) {   /* user generates manual EOF */
        	
            fputs("L'utente ha cancellato l'input\n", stderr);
            
            return 1;
        }
        else if (rtn == 0) {    /* matching failure */
        	
            fputs("\n[-]Errore: numero invalido!\n", stderr);
            
            empty_stdin();
        }
        else if (choice < 1 || 3 < choice) {  /* validate range */
        	
            fputs("\n[-]Errore: input fuori dal range [1-3]\n", stderr);
            
            empty_stdin();
        }
        else {
	        switch (choice) {
				case 1:
					stampaIstruzioni();  // stampa a video istruzioni
					break;
				case 2:
					play();  // avvia la partita 
					break;
				case 3:
					// esco
					printf("\nAlla prossima!\n");
					
					exit(0);
					break;
				default:
					
					printf("Input invalido!\n");
					
					break;
			}
	        empty_stdin();	// pulisco buffer di input
		}
	} while (choice != 3);
}



	// BANNER
void stampaBanner() {
	
	int j = 0;  // contatore per i colori fino a 12 (funziona con estensione cpp se aggiunte le linee di codice per i colori)
	int i;
	// prima linea di *
	printf("\t\t\t\t");
	for (i = 0; i < 55; i++) {
		if (j > 12) {
			j = 0;
		}
		
		printf("*");
		j++;
	}
	printf("\n");
	
	// scritta principale
	for (i = 0; i < 6; i++) {
		if (i == 2){
			
			printf("\t\t\t\t*\t\tWELCOME TO MASTERMIND!\t\t      *\n");
		}
		
		printf("\t\t\t\t*  \t\t\t\t\t\t      *\n");
	}
	
	// seconda linea di *
	printf("\t\t\t\t");
	j = 0;
	for (i = 0; i < 55; i++) {
		if (j > 12) {
			j = 0;
		}
		
		printf("*");
		j++;
	}
	printf("\n");
	
}



	// ALGORITMO PER LA GENERAZIONE RANDOMICA DI INTERI IN UN DATO INTERVALLO
int RandomInteger(int low, int high) {	
	int k;
	double d;
	// rand() : returns a pseudo-random integral value between 0 and RAND_MAX (0 and RAND_MAX included).
	// RAND_MAX : 32767
	d = (double)rand()/(1.0 + (double)RAND_MAX); 
  	k = (int) (d*(high - low + 1));
  	return (low + k);
}



	// FUNZIONE DI STAMPA ISTRUZIONI DEL GIOCO
void stampaIstruzioni() {
	printf("========================================================================================================================\n");
	printf("Ecco le regole di ");
	
	printf("MASTERMIND\n");
	
	printf("All'inizio della partita viene generata una sequenza di 4 colori non visibile al giocatore, usando una qualsiasi combinazione dei 6 colori disponibili:\n\n");
	
	printf("-R (red)\n");
	
	printf("-B (blue)\n");
	
	printf("-G (green)\n");
	
	printf("-Y (yellow)\n");
	
	printf("-P (pink)\n");
	
	printf("-W (white)\n\n");
	printf("Il tuo obbiettivo, dunque, sara' quello di comporre e indovinare la giusta sequenza dei colori del codice nascosto.\n");
	printf("Ogniqualvolta viene fatto un tentativo da parte del giocatore, viene restituito:\n");
	printf("- un pallino bianco: indica che un colore, inserito dal giocatore nella sequenza composta, risulta esatto, ma nella posizione sbagliata rispetto alla sequenza nascosta da indovinare.\n");
	printf("- un pallino nero: indica che un colore, inserito dal giocatore nella sequenza composta, risulta esatto e nella posizione corretta rispetto alla sequenza nascosta.\n");
	printf("Hai a disposizione 9 tentativi, i colori accettati sono quelli sopra riportati (quelli utilizzati per la creazione della combinazione segreta)\n");
	printf("Buona fortuna!!!\n");
	printf("========================================================================================================================\n");
}



	// FUNZIONE PER INIZIARE LA PARTITA
void play() {
	
	system("cls");	// clear screen function
	
	// DEFINIZIONI
	int l,min,sum,ret;  // sum (contatore per la somma)    -    min (contatore del minimo)    -    l (contatore per la lunghezza)
	
	printf("\n");
	// colori possibili e definizione lunghezza del codice segreto da generare
	printf("\n=====================================================================================================\n");
	printf("Questi sono i colori che e' possibile scegliere:\n\n");
	
	printf("-R (red)\n");
	
	printf("-B (blue)\n");
	
	printf("-G (green)\n");
	
	printf("-Y (yellow)\n");
	
	printf("-P (pink)\n");
	
	printf("-W (white)\n");
	printf("\nE', inoltre, possibile definire la lunghezza del codice segreto! (di solito e' di 4)\n");
	
	int err = 1;
	do {
		
		printf("\nDefinisci la lunghezza(max:100): ");
		ret = scanf(" %d", &l);  /* save return */
		
		
		
		// GESTIONE DEGLI ERRORI DI INPUT
		if (ret == EOF) {   /* user generates manual EOF */
			
            fputs("\nL'utente ha cancellato l'input\n", stderr);
            
        }
        else if (ret == 0) {    /* matching failure */
        	
            fputs("\n[-]Errore: numero invalido!\n\n", stderr);
            
            empty_stdin();
        }
        else if (l < 1 || 100 < l) {  /* validate range */
        	
            fputs("\n[-]Errore: input fuori dal range [1-100]\n\n", stderr);
            
            empty_stdin();
        } else {
        	err = 0;
        	printf("\n");
        	empty_stdin();
		}
	} while (err == 1);
	
	
	printf("E' stata correttamente generata una sequenza segreta di dimensione %d\n\n", l);
	

	// INIZIO
	
	// ALGORITMO PER LA GENERAZIONE DEL CODICE SEGRETO
	
	srand((int)time(NULL));  // randomize seed function to prevent sequence repetition between runs
	// makes use of the computer's internal clock to control the choice of the seed. Since time is continually changing, the seed is forever changing
	int i;
	int table[l];	//creo array di interi di dimensione l (passata dall'utente)
	for (i = 0; i <= (l-1); i++) {		// utilizzo un ciclo for per inserire dei numeri random nell'array (intervallo di numeri tra 1 e 6)
		table[i] = RandomInteger(1,6);
	}
	char code[l];	//creo array di char di dimensione l (passata dall'utente) che mi serve per contenere la combinazione segreta di colori
	
	/* riempio l'array di char "code" (che conterrà il codice segreto), 
	associando ad ogni numero (dell'array di interi "table") una lettera diversa (che corrisponde ad un colore diverso)
	in questo modo creo anche una sequenza randomica */
	for (i = 0; i <= (l-1); i++) {   
		if (table[i]==1) {		//se table[i] = 1 ==> 'R'
			code[i]='R';
		}		
		if (table[i]==2) {		//se table[i] = 2 ==> 'B'
			code[i]='B';
		}
		if (table[i]==3) {		//se table[i] = 3 ==> 'G'
			code[i]='G';
		} 
		if (table[i]==4) {		//se table[i] = 4 ==> 'Y'
			code[i]='Y';
		}
		if (table[i]==5) {		//se table[i] = 5 ==> 'P'
			code[i]='P';
		} 
		if (table[i]==6) {		//se table[i] = 6 ==> 'W'
			code[i]='W';	
		}
	}
	
	for (i = 0; i <= (l-1); i++) {
		printf("%d \n", table[i]);
	}
	
	
	char input[100];	// creo un array di char di dimensione 100 che conterrà l'input dell'utente
 	int tentativo = 1, cp = 0, c = 0, flag = 0;  // cp (contatore per "neri")    -    c (contatore per "bianchi")    -    flag (contatore per vittoria)
	printf("Questo e' un esempio di inserimento della sequenza: RBGW\n");
	printf("Ora tocca a te!!!\n");
	printf("\nHai a disposizione 9 tentativi!\n");
	printf("Nel caso vorresti arrenderti, basta digitare la parola: ARRESO\n\n");
	int error;		//  per controllo errori nell'input dell'utente
	int interrompi;		// per controllo ARRESO
	
	// ciclo per i 9 tentativi
	while (flag == 0 && tentativo <= 9) {
		
		// chiedo input all'utente
		do {
			
			printf("\nTentativo %d:", tentativo);
			
			scanf("%99s", input);  // accetto soltanto 100 caratteri in input per evitare l'overflow
			int length = strlen(input);
			
			
			// GESTIONE DI "ARRESO"
			interrompi = controllo_arreso(input, code, interrompi, l);
			if (interrompi == 1) {
				break;
			}
	
	
			// GESTIONE DEGLI ERRORI DI INPUT
			error = controllo_input(error, l, length, input);
		
			
		} while (error == 1);  // chiedi nuovamente input se ci sono stati degli errori (di lunghezza o di lettere o entrambi)
		
		
		
		// controlla ARRESO (esci dal ciclo, vai a GAME OVER)
		if (interrompi == 1) {
			break;
		}
		
		// CHIAMATA A FUNZIONE SEQUENZA ESATTA
		sequenza_esatta(&flag, l, input, code, tentativo);  // passaggio per indirizzo di "flag", "input" e "code"
		if (flag == 1) {   // se flag è uguale a 1 usciamo dal ciclo, visto che abbiamo vinto
			break;
		}
	
		
		// CHIAMATA ALLA FUNZIONE CONTA NERI
		cp = conta_neri(cp, l, input, code);	 // passaggio per indirizzo di "input" e "code"
		printf("\tNero (colore e posizione corretti): %d\n", cp);
		
		
		// CHIAMATA ALLA FUNZIONE CONTA BIANCHI
		conta_bianchi(&c, &sum, min, l, &cp, &tentativo, input, code);	// passaggio per indirizzo di c, sum, cp, tentativo, input, code
		
		// FINE (si riparte dall'inizio del ciclo)
		
	}
	
	
	// tentativi finiti: GAME OVER (faccio vedere qual era il codice segreto)
	if (flag == 0 && tentativo > 9) {
		
		int k;
		printf("\n\nGAME OVER! Il codice era: ");
		for (k = 0; k < l; k++) {
			printf("%c", code[k]);
		}
		
		printf("\n========================================================\n");
		printf("\n");
	} 
}



	// ALGORITMO PER LA RICERCA DEI "NERI"
int conta_neri(int cp, int l, char input[], char code[]) {
	// controlla uno per uno
	int i;
	for (i = 0; i <= (l-1); i++) {
			if (input[i] == code[i]) {   // se coincidono i caratteri (che quindi si trovano anche nella stessa posizione)
				cp++;					  // incrementa contatore
			}
		}
		return cp;
}



	// ALGORITMO PER LA RICERCA DEI "BIANCHI"
void conta_bianchi(int * c, int * sum, int min, int l, int * cp, int * tentativo, char input[], char code[]) {
	// contiamo le occorrenze di ciascuna lettera negli array "input" e "code"
	// RS: contatore della lettera R nell'array "input"
	// RC: contatore della lettera R nell'array "code"
	// e così via per tutti gli altri
	// per contare i caratteri (colori) sia in "input" che in "code" li mettiamo inizialmente tutti a zero
	int RS=0, RC=0, BS=0, BC=0, GS=0, GC=0, YS=0, YC=0, PS=0, PC=0, WS=0, WC=0;
	*sum = 0;  // inizializzo una somma uguale a zero (come punto di partenza)
	
	// scorriamo entrambi gli array "input" e "code" nello stesso momento (tanto la lunghezza è la stessa)
	int i;
	for (i = 0; i <= (l-1); i++) {
		if (input[i] == 'R') RS++;
		if (input[i] == 'B') BS++;
		if (input[i] == 'G') GS++;
		if (input[i] == 'Y') YS++;
		if (input[i] == 'P') PS++;
		if (input[i] == 'W') WS++;
		if (code[i] == 'R') RC++;
		if (code[i] == 'B') BC++;
		if (code[i] == 'G') GC++;
		if (code[i] == 'Y') YC++;
		if (code[i] == 'P') PC++;
		if (code[i] == 'W') WC++;
	}
		
	// inserisco nella somma il numero minimo delle occorrenze dei caratteri uguali tra array l'array "input" e quello "code" (quindi le coincidenze di caratteri)
	min = RS;	// considero sempre il numero minimo di ripetizioni (coincidenze dei caratteri tra quelli dell'array "input" e quelli di "code")
	if (RC < min) min = RC;	
	*sum = *sum + min;
	min = BS;
	if (BC < min) min = BC;	
	*sum = *sum + min;
	min = GS;
	if (GC < min) min = GC;
	*sum = *sum + min;
	min = YS;
	if (YC < min) min = YC;
	*sum = *sum + min;
	min = PS;
	if (PC < min) min = PC;
	*sum = *sum + min;
	min = WS;
	if (WC < min) min = WC;
	*sum = *sum + min;
	// adesso otteniamo tutti i "bianchi", quindi i colori corretti che si trovano negli array (colori corretti ma posizione sbagliata)
	(*c) = ((*sum) - (*cp));  // sottraggo alla sommma il numero di "neri" (colori corretti e in posizione esatta) per ottenere infine i "bianchi"
	printf("\tBianco (solo il colore corretto): %d\n", *c);
	*c = 0;   // bianchi azzerati
	*cp = 0;	 // neri azzerati
	(*tentativo)++;  // tentativo incrementato di 1, si riparte dall'inizio

}



	// ALGORITMO PER IL CONTROLLO DELLA SEQUENZA E DEI CARATTERI IN GIUSTA POSIZIONE
void sequenza_esatta(int *flag, int l, char input[], char code[], int tentativo) {
	// controllo tutti i caratteri della sequenza
		*flag = 1;
		int i;
		for (i = 0; i <= (l-1); i++) {
			if (input[i] != code[i]) {
				*flag = 0;  // non sono tutti uguali
			}
		}
		// i caratteri tra "input" e "code" sono tutti uguali e nella stessa sequenza: HAI VINTO!
		if (*flag == 1) {
			
			printf("\nCongratulazioni! Hai vinto il gioco dopo %d tentativi\n", tentativo);
			
			printf("======================================================\n");
		}	
}



	// ALGORITMO PER CONTROLLO SE L'UTENTE SI E' ARRESO
int controllo_arreso(char input[], char code[], int interrompi, int l) {
	// controllo della parola "ARRESO"
	interrompi = 0;
	if (input[0]=='A' && input[1]=='R' && input[2]=='R'
	&& input[3]=='E' && input[4]=='S' && input[5]=='O'){
		
		printf("\nGAME OVER! Il codice era: ");
		int k;
		for (k = 0; k < l; k++) {
			printf("%c", code[k]);
		}
		
		printf("\n");
		printf("========================================================\n");
		interrompi = 1;
	}
	return interrompi;
}



	// ALGORITMO PER CONTROLLO INPUT DELL'UTENTE
int controllo_input(int error, int l, int length, char input[]) {
	// controllo della lunghezza
	error = 0;
	if (length != l) {
		
		printf("\n[-]Errore: la lunghezza della sequenza del codice deve essere di %d colori!\n", l);
		
		error = 1;
		}
	if (error == 1) {
		return error;  // se ci sono stati dei problemi di lunghezza ritorniamo subito error, quindi ignorando le istruzioni che seguono (controllo lettere)
	}
	// se non ci sono stati problemi di lunghezza della input allora passiamo avanti a controllare le lettere se sono giuste o meno
	// controllo delle lettere
	int i;
	for (i = 0; i <= (l-1); i++) {
		if (input[i]!='R' && input[i]!='B' && input[i]!='G' &&
		input[i]!='Y' && input[i]!='P' && input[i]!='W') {
			
			printf("\n[-]Errore: lettere non corrette, riprova\n");
			
			error = 1;
		}
		if (error == 1) {
			break;
		}
	}
	return error;
}



