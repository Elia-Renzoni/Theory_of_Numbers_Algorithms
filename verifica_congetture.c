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









