/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                                                     *
 *    -------------------------------------------------------------------------------------------------------------    *
 *    |														  |    *
 *    |	Autori : Alessio Biagioli - Elia Renzoni								  |    *
 *    |														  |    *
 *    |	Programma : verifica delle congetture di Goldbach, Gilbreath, Legendre					  |    *
 *    |														  |    *
 *    |	Programmazione Procedurale - Universita' Degli Studi di Urbino Carlo Bo' - Informatica Applicata L-31     |    *
 *    |														  |    *
 *    -------------------------------------------------------------------------------------------------------------    *
 *                                                                                                                     *
 *														       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  CONG_GILB_SCELTA  0
#define  CONG_GOLD_SCELTA  1
#define  CONG_LEGE_SCELTA  2
#define  MAX_NUMERO_PRIMO  997
#define  MAX_NPRIMI_GEN    1000

typedef struct {

	int  numero_sequenze,
	     numero_cong_gold,
	     numero_cong_lege;

} congetture_t;

typedef struct seq_numeri_p {

	int                  numero_primo;
	struct seq_numeri_p *successivo,
			    *precedente;

} sequenza_numeri_primi_t;

/* dichiarazione delle funzioni */

int                      acquisisci_valida(void);
sequenza_numeri_primi_t *genera_numeri_primi(void);
void                     congettura_gilbreath(congetture_t,
					      congetture_t *);
void                     congettura_goldbach(congetture_t,
					     congetture_t *);
void                     congettura_legendre(congetture_t,
					     congetture_t *);

/* definizione delle funzioni */

int main(void) {

		
	int                      congettura_scelta;
	congetture_t             accesso;
	sequenza_numeri_primi_t *testa_lista;

	/* menu di scelta */
	printf("***********************************************\n");
	printf("*    Seleziona la Congettura da Verificare    *\n");
	printf("*    [0] -- Congettura di Gilbreath --        *\n");
	printf("*    [1] -- Congettura di Goldbach  --        *\n");
	printf("*    [2] -- Congettura di Legendre  --        *\n");
	printf("***********************************************"\n);

	congettura_scelta = acquisisci_valida();
	testa_lista = genera_numeri_primi();

	switch (congettura_scelta) {

		case CONG_GILB_SCELTA:
			congettura_gilbreath(accesso, 
					     testa_lista);
			break;

		case CONG_GOLD_SCELTA:
			congettura_goldbach(accesso, 
					    testa_lista);
			break;

		case CONG_LEGE_SCELTA:
			congettura_legendre(accesso,
					    testa_lista);
			break;

	}

	
	return (0);
}



int acquisisci_valida(void) {

	int          cong_scelta;
	int          acquisizione_errata,
		     valore_scanf,
		     verifica_numero;
	congetture_t accesso;


	do {
		printf("Seleziona una Congettura : \n");
		valore_scanf = scanf("%d", 
				     &cong_scelta);

		switch (cong_scelta) {

			case CONG_GILB_SCELTA:
				printf("Inserisci il numero di sequenze da generare - (n > 0) :  \n");
				valore_scanf = scanf("%d", 
						     &accesso.numero_sequenze);
				break;

			case CONG_GOLD_SCELTA:
				printf("Inserisci un numero dispari e > 5 : \n");
				valore_scanf  = scanf("%d", 
						      &accesso.numero_cong_gold);
				verifica_numero = accesso.numero_cong_gold % 2;
				break;

			case CONG_LEGE_SCELTA:
				printf("Inserisci un numero n naturale >= 1 \n");
				valore_scanf = scanf("%d", 
						     &accesso.numero_cong_lege);
				break;

		}

		acquisizione_errata = valore_scanf != 1 || cong_scelta < CONG_GILB_SCELTA || cong_scelta > CONG_LEGE_SCELTA ||
			              accesso.numero_sequenze < 1 || accesso.numero_cong_gold <= 5 || verifica_numero != 0  ||
				      accesso.numero_cong_lege < 1;

		if (acquisizione_errata)
			printf("Errore, Inserisci nuovamente i valori ! \n");

		while (getchar() != '\n');
	}
	while (acquisizione_errata):


	return (cong_scelta);

}	


sequenza_numeri_primi_t  *genera_numeri_primi(void) {


	sequenza_numeri_primi_t  *testa_lista_concatenata,
				 *oggetto_lista;
	int                       contatore,
				  primo,
				  valore_generato;

	/* generazione dei numeri, verifica di primalita' e memo. in lista concat. */
	testa_lista_concatenata = oggetto_lista = (sequenza_numeri_primi_t *)malloc(sizeof(sequenza_numeri_primi_t));
	oggetto_lista->numero_primo = valore_generato;

	for (valore_generato = 2; (valore_generato <= MAX_NPRIMI_GEN); valore_generato++) {

		for (contatore = 2, primo = 1; (contatore < sqrt(valore_generato)); contatore++)

			if (valore_generato % contatore == 0)
				primo = 0;
		if (primo) {
			
			if (valore_generato != MAX_NUMERO_PRIMO) {

				oggetto_lista = oggetto_lista->successivo = (sequenza_numeri_primi_t *)malloc(sizeof(sequenza_numeri_primi_t));
				oggetto_lista->numero_primo = valore_generato;

			}
		}
	}

	oggetto_lista->successivo  = NULL;

	return (testa_lista_concatenata);

}








