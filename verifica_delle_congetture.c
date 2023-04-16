/*
 *
 *
 *	Autori : Elia Renzoni e Alessio Biagioli
 *	Programma : verifica delle congetture di Gilbreath, Goldbach e Legendre
 *
 *
 *
 * */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define CONG_GILB_SCELTA 0
#define CONG_GOLD_SCELTA 1
#define CONG_LEGE_SCELTA 2
#define MAX_NUMERI_GENE  1000


typedef struct {

	int  numero_sequenze, 
	     n_disp_gold, 
	     n_cong_lege;
	int *numeri_primi,
	     numero_elementi;

} congetture_t;


int  acquisisci_valida(congetture_t);
void sequenza_numeri_primi(congetture_t);
void congettura_gilbreath(congetture_t);
void congettura_goldbach(congetture_t);
void conettura_legendre(congetture_t);

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
	    esito_lettura_id;
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
	    indice;

	for (valore_generato = 2, accesso_struttura.numero_elementi = indice = 0; (valore_generato <= MAX_NUMERI_GENE); valore_generato++) {

		for (contatore = 2, primo = 1; (contatore < sqrt(valore_generato)); contatore++) 
			if (valore_generato % contatore == 0)
				primo = 0;
		if (primo == 1) {
			accesso_struttura.numero_elementi++;
			accesso_struttura.numeri_primi = (int *)calloc(numero_elementi, sizeof(int));
			accesso_struttura.numeri_primi[indice] = valore_generato;
			++indice;
		}
			
	}

}



void congettura_goldbach(congetture_t accesso_struttura){

	int tmp_somma, 
	    tmp_v, 
	    indice, 
	    riconoscimento, 
            contatore;

    for (indice = 0; (indice < accesso_struttura.numero_elementi); indice++) {
		
		tmp_somma = accesso_struttura.numeri_primi[indice];
		contatore = indice + 1;

		while (contatore <= indice + 3) {
			tmp_somma += accesso_struttura.numeri_primi[contatore];
			contatore ++;
		}

		if (tmp_somma == accesso_struttura.n_disp_gold) {
			printf("numeri la cui somma è uguale a %d: %d,%d,%d \n", tmp_somma, accesso_struttura.numero_elementi[indice], accesso_struttura.numero_elementi[contatore - 1], accesso_struttura.numero_elementi[contatore]);
			riconoscimento++;
		} 
	} 
	
	if (riconoscimento == 0)
	printf("congettura non verificata.");
	
}



void congettura_legendre(congetture_t accesso_struttura) {

	int primo_vincolo   = pow(accesso_struttura.n_cong_lege, 2),
	    secondo_vincolo = pow(accesso_struttura.n_cong_lege + 1, 2), 
	    indice;

	for (indice = 0; (indice < accesso_struttura.numero_elementi); indice++) 

		if (primo_vincolo <= accesso_struttura.numeri_primi[indice] && accesso_struttura.numeri_primi[indice] <= secondo_vinolo) 
			printf("Valore Incluso : %d \n", accesso_struttura.numeri_primi[indice]);

}


