/*
 *
 *	Autori : Elia Renzoni e Alessio Biagioli
 *	Programma : verifica delle congetture di Gilbreath, Goldbach e Legendre
 *
 * */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CONG_GILB_SCELTA 0
#define CONG_GOLD_SCELTA 1
#define CONG_LEGE_SCELTA 2
#define MAX_NUMERI_GENE  1000
#define MAX_NUMERI_PRIMI 168
#define MAX_LUNGH_SEQ    10

typedef struct {
	int  numero_sequenze, n_disp_gold, n_cong_lege;
	int  numeri_primi[MAX_NUMERI_PRIMI];
} congetture_t;

typedef struct coda {
	int numero_gen;
	struct coda *succ_p;
} coda_numeri_t;

int  acquisisci_valida(congetture_t);
void sequenza_numeri_primi(congetture_t);
void congettura_gilbreath(congetture_t);
void crea_coda_seq_numeri(coda_numeri_t **, coda_numeri_t **,  int);
void crea_nuova_sequenza(coda_numeri_t *, int differenza[]);
void congettura_goldbach(congetture_t);
void congettura_legendre(congetture_t);

int main(void) {

	congetture_t accesso_struttura;
	int          congettura_scelta;

	printf("********************************\n");
	printf("    Verifica delle Congetture   \n");
	printf("********************************\n");
	printf("       [0] - Gilbreath          \n");
	printf("       [1] - Goldbach           \n");
	printf("       [2] - Legendre           \n");
	printf("********************************\n");

	congettura_scelta = acquisisci_valida(accesso_struttura);
	sequenza_numeri_primi(accesso_struttura);

	switch (congettura_scelta) {
		
		case CONG_GILB_SCELTA:
			congettura_gilbreath(accesso_struttura);
			break;
		case CONG_GOLD_SCELTA:
			congettura_goldbach(accesso_struttura);
			break;
		case CONG_LEGE_SCELTA:
			congettura_legendre(accesso_struttura);
			break;
	}


	return (0);
}

int acquisisci_valida(congetture_t accesso_struttura) {

	int congettura_scelta;
	int acquisizione_errata,
	    esito_lettura,
	    esito_lettura_id,
	    verifica_dispari;

	do {
		printf("Inserisci l'identificativo della congettura da verificare : \n");
		esito_lettura_id = scanf("%d", &congettura_scelta);

		switch (congettura_scelta) {

			case CONG_GILB_SCELTA:
				printf("Inserisci il numero di sequenze da generare ( >= 1 ) : \n");
				esito_lettura = scanf("%d", &accesso_struttura.numero_sequenze);
				acquisizione_errata = esito_lettura_id != 1 || esito_lettura != 1 || accesso_struttura.numero_sequenze < 1;
				break;

			case CONG_GOLD_SCELTA:
				printf("Inserisci un numero dispari e > 5 : \n");
				esito_lettura = scanf("%d", &accesso_struttura.n_disp_gold);
				verifica_dispari = accesso_struttura.n_disp_gold % 2;
				acquisizione_errata = esito_lettura_id != 1 || esito_lettura != 1 || accesso_struttura.numero_sequenze < 5 || verifica_dispari == 0;
				break;
			
			case CONG_LEGE_SCELTA:
				printf("Inserisci un numero >= 1 : \n");
				esito_lettura = scanf("%d", &accesso_struttura.n_cong_lege);
				acquisizione_errata = esito_lettura_id != 1 || esito_lettura != 1 || accesso_struttura.n_cong_lege < 1;
				break;
			
			default:
				acquisizione_errata = 1;
				break;
		}

		if (acquisizione_errata)
			printf("Errore, ripeti l'operazione ! \n");

		while (getchar() != '\n');

	} 
	while (acquisizione_errata);

	return (congettura_scelta);

}

void sequenza_numeri_primi(congetture_t accesso_struttura) {

	int contatore, 
	    primo, 
	    valore_generato,
	    i;

	for (valore_generato = 2, contatore = 0; (valore_generato < MAX_NUMERI_GEN); valore_generato++) {
        for (i = 2, primo = 1; i < sqrt(valore_generato) && primo != 0; i++) {
   	        if(valore_generato % i == 0)
   	            primo = 0;
        }   
        if (primo == 1) {
            accesso_struttura.numeri_primi[contatore] = valore_generato;
            contatore++;
        }
   }

}

void congettura_gilbreath(congetture_t accesso_struttura) {

	coda_numeri_t *uscita = NULL, *ingresso = NULL;
	int contatore;
	int valore, indice, differenza[MAX_LUNGH_SEQ];
	int numero_stampe = MAX_LUNGH_SEQ;

	printf("Sequenze > \n");
	for (contatore = 0; (contatore < accesso_struttura.numero_sequenze); contatore++) {
	    if (contatore < 1) {
			for (indice = 0; (indice < numero_stampe); indice++) {
				valore = accesso_struttura.numeri_primi[contatore + 1] - accesso_struttura.numeri_primi[contatore];
				printf("%d\t", accesso_struttura.numeri_primi[contatore]);
				crea_coda_seq_numeri(&uscita, &ingresso, valore);
			}		
	    }
	    else {
	    	printf("\n");
	    	crea_nuova_sequenza(uscita, differenza);
	    	for (indice = 0; (indice < numero_stampe--); indice++) {
	    		crea_coda_seq_numeri(&uscita, &ingresso, differenza[indice]);
				printf("%d\t", differenza[indice]);
	    	}
	    }
	}
}

void crea_coda_seq_numeri(coda_numeri_t **uscita, coda_numeri_t **ingresso, int val_inserire) {

	coda_numeri_t *nuovo_elem = (coda_numeri_t *)malloc(sizeof(coda_numeri_t));
	nuovo_elem->numero_gen = val_inserire;
	nuovo_elem->succ_p = NULL;
	if (*ingresso != NULL)
		(*ingresso)->succ_p = nuovo_elem;
	else
		*uscita = nuovo_elem;
	*ingresso = nuovo_elem;

}

void crea_nuova_sequenza(coda_numeri_t *uscita, int differenza[]) {

	coda_numeri_t *elemento;
	int contatore;

	for (elemento = uscita, contatore = 0; 
			(elemento != NULL || contatore < 10); 
		contatore++, elemento = elemento->succ_p) {
		differenza[contatore] = elemento->numero_gen - elemento->succ_p->numero_gen;
	}

}

void congettura_goldbach(congetture_t accesso_struttura) {

	int tmp_somma = 0, indice, riconoscimento = 0, contatore;

	for (indice = 0; (indice < MAX_NUMERI_PRIMI); indice++) {
		for (contatore = indice; (contatore < indice + 2); contatore++) 
			tmp_somma += accesso_struttura.numeri_primi[contatore];
		if (tmp_somma == accesso_struttura.n_disp_gold) {
			printf("Numeri la cui somma e' uguale a %d : %d, %d, %d\n", accesso_struttura.n_disp_gold,
										    accesso_struttura.numeri_primi[indice],
										    accesso_struttura.numeri_primi[contatore],
										    accesso_struttura.numeri_primi[contatore + 1]);
			riconoscimento++;
		}
	}

	if (riconoscimento == 0)
	       printf("Congettura non verificata ! \n");	

}

void congettura_legendre(congetture_t accesso_struttura) {

	int primo_vincolo   = pow(accesso_struttura.n_cong_lege, 2),
	    secondo_vincolo = pow(accesso_struttura.n_cong_lege + 1, 2), 
	    indice;

	for (indice = 0; (indice < MAX_NUMERI_PRIMI); indice++) 
		if (primo_vincolo <= accesso_struttura.numeri_primi[indice] && accesso_struttura.numeri_primi[indice] <= secondo_vincolo) 
			printf("Valore Incluso : %d \n", accesso_struttura.numeri_primi[indice]);

}
