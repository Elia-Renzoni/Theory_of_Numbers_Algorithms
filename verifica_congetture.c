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
#define  MAX_NPRIMI_GEN    1000

typedef struct {

	int  numero_sequenze,
	     numero_cong_gold,
	     numero_cong_lege;

} congetture_t;

typedef struct seq_numeri_p {

	int                  numero_primo;
	struct seq_numeri_p *successivo, *precedente;

} sequenza_numeri_primi_t;

/* dichiarazione delle funzioni */

int                      acquisisci_valida(void);
sequenza_numeri_primi_t *genera_numeri_primi(int *);
void                     congettura_gilbreath(congetture_t, sequenza_numeri_primi_t *, int *);
void                     congettura_goldbach(congetture_t, sequenza_numeri_primi_t *);
void                     congettura_legendre(congetture_t, sequenza_numeri_primi_t *);

/* definizione delle funzioni */

int main(void) {

		
	int                      congettura_scelta;
	int                      numero_elementi;
	congetture_t             accesso;
	sequenza_numeri_primi_t *testa_lista;

	/* menu di scelta */
	printf("***********************************************\n");
	printf("*    Seleziona la Congettura da Verificare    *\n");
	printf("*    [0] -- Congettura di Gilbreath --        *\n");
	printf("*    [1] -- Congettura di Goldbach  --        *\n");
	printf("*    [2] -- Congettura di Legendre  --        *\n");
	printf("***********************************************\n");

	testa_lista = genera_numeri_primi(&numero_elementi);
	congettura_scelta = acquisisci_valida();

	switch (congettura_scelta) {

		case CONG_GILB_SCELTA:
			congettura_gilbreath(accesso, 
					     testa_lista,
					     &numero_elementi);
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

	free(testa_lista);
	
	return (0);
}



int acquisisci_valida(void) {

	int          cong_scelta;
	int          acquisizione_errata,
		     	 valore_scanf,
		     	 verifica_numero = 0;
	congetture_t accesso;


	do {
		printf("Seleziona una Congettura : \n");
		valore_scanf = scanf("%d", &cong_scelta);

		switch (cong_scelta) {

			case CONG_GILB_SCELTA:
				printf("Inserisci il numero di sequenze da generare - (n > 0) :  \n");
				valore_scanf = scanf("%d", &accesso.numero_sequenze);
				acquisizione_errata = valore_scanf != 1 || accesso.numero_sequenze < 1;
				break;

			case CONG_GOLD_SCELTA:
				printf("Inserisci un numero dispari e > 5 : \n");
				valore_scanf  = scanf("%d", &accesso.numero_cong_gold);
				verifica_numero = accesso.numero_cong_gold % 2;
				acquisizione_errata = valore_scanf != 1 || accesso.numero_cong_gold <= 5 || verifica_numero == 0;
				break;

			case CONG_LEGE_SCELTA:
				printf("Inserisci un numero n naturale >= 1 \n");
				valore_scanf = scanf("%d", &accesso.numero_cong_lege);
				acquisizione_errata = valore_scanf != 1 || accesso.numero_cong_lege < 1;
				break;
			default:
				acquisizione_errata = 1;
				break;

		}


		if (acquisizione_errata)
			printf("Errore, Ripeti l'azione ! \n");

		while (getchar() != '\n');
	}
	while (acquisizione_errata);


	return (cong_scelta);

}	


sequenza_numeri_primi_t  *genera_numeri_primi(int *numero_elementi) {


	sequenza_numeri_primi_t  *testa_lista_concatenata,
				 			 *oggetto_lista;
	int                       contatore,
				  			  primo,
				  			  valore_generato;

	/* generazione dei numeri, verifica di primalita' e memo. in lista concat. */
	testa_lista_concatenata = oggetto_lista = (sequenza_numeri_primi_t *)malloc(sizeof(sequenza_numeri_primi_t));
	oggetto_lista->precedente = NULL;
	*numero_elementi = 1;

	for (oggetto_lista->numero_primo = valore_generato = 2; (valore_generato <= MAX_NPRIMI_GEN); valore_generato++, ++(*numero_elementi)) {

		for (contatore = 2, primo = 1; (contatore < sqrt(valore_generato)); contatore++)

			if (valore_generato % contatore == 0)
				primo = 0;
		if (primo == 1) {
			oggetto_lista->precedente = oggetto_lista;
			oggetto_lista = oggetto_lista->successivo = (sequenza_numeri_primi_t *)malloc(sizeof(sequenza_numeri_primi_t));
			oggetto_lista->numero_primo = valore_generato;
		}
	}

	oggetto_lista->successivo = NULL;

	return (testa_lista_concatenata);

}



void congettura_gilbreath(congetture_t accesso, sequenza_numeri_primi_t *testa_lista_dc, int *numero_elementi) {
	
	int 					*elementi_seq_gen, 
	     			 		contatore,
	     			 		indice,
	     			 		tmp,
	     			 		differenza = 0;
	sequenza_numeri_primi_t *oggetto_lista;

	printf("Sequenza numero 1 : \n");

	elementi_seq_gen = (int *)calloc(*numero_elementi, sizeof(int));

	for (oggetto_lista = testa_lista_dc, contatore = indice = 0; (oggetto_lista != NULL); oggetto_lista = oggetto_lista->successivo, contatore++, indice++) {

		if (contatore == 0) 
			tmp = oggetto_lista->numero_primo;
		else {
			differenza = oggetto_lista->numero_primo - tmp;
			contatore = 0;
		}

		elementi_seq_gen[indice] = differenza;

		if (contatore <= 10) 
			printf("%d \n", differenza);

	}

	if (accesso.numero_sequenze > 1) {

		for (contatore = 1; (contatore < accesso.numero_sequenze); contatore++) {

			printf("\n Sequenza numero %d : \n", contatore + 1);

			for (indice = 0; (indice < *numero_elementi); indice++) {
				differenza = elementi_seq_gen[indice] - elementi_seq_gen[indice + 1];
				elementi_seq_gen[indice] = differenza;

				if (indice <= 10)
					printf("%d \n", elementi_seq_gen[indice]);
			}

		}
	}


	free(elementi_seq_gen);

}


void congettura_goldbach(congetture_t accesso, sequenza_numeri_primi_t *testa_lista_dp) {

	int 			 		 tmp_somma,
				 	 		 tmp_pv,
				 	 		 tmp_sv,
				 	 		 tmp_tv, 
				 	 		 contatore;
	int                      riconoscimento = 0;
	sequenza_numeri_primi_t *oggetto_lista;

	for (oggetto_lista = testa_lista_dp; (oggetto_lista != NULL); oggetto_lista = oggetto_lista->successivo) {

		contatore = 0;
		while ((oggetto_lista != NULL) && (contatore <= 2)) {
			
			switch (contatore) {
				case 0:
					tmp_somma += tmp_pv = oggetto_lista->numero_primo;
					break;
				case 1:
					tmp_somma += tmp_sv = oggetto_lista->numero_primo;
					break;
				case 2:
					tmp_somma += tmp_tv = oggetto_lista->numero_primo;
					break;
			}

			if ((contatore == 2) && (tmp_somma == accesso.numero_cong_gold)) {
				printf("Numeri la cui somma e' uguale a %d : %d, %d, %d \n", accesso.numero_cong_gold, tmp_pv, tmp_sv, tmp_tv);
				contatore++;
			}
			
			oggetto_lista = oggetto_lista->successivo;
			riconoscimento++;
		}
		oggetto_lista = oggetto_lista->precedente;
		oggetto_lista = oggetto_lista->precedente;
	}

	if (riconoscimento == 0)
		printf("Non sono presenti numeri la cui somma e' uguale a %d \n", accesso.numero_cong_gold);

}


void congettura_legendre(congetture_t accesso, sequenza_numeri_primi_t *testa_lista_dp) {

	int 			 		 primo_vincolo   = pow(accesso.numero_cong_lege, 2);
	int 			 		 secondo_vincolo = pow(accesso.numero_cong_lege + 1, 2);
	sequenza_numeri_primi_t *oggetto_lista;

	for (oggetto_lista = testa_lista_dp; (oggetto_lista != NULL); oggetto_lista = oggetto_lista->successivo) {
		
		if ((primo_vincolo <= oggetto_lista->numero_primo) && (oggetto_lista->numero_primo <= secondo_vincolo))
			printf("Valore Incluso : %d", oggetto_lista->numero_primo);

	}


}

