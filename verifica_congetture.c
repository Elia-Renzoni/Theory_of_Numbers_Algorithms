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

int  acquisisci_valida(void);
void genera_numeri_primi(void);
void congettura_gilbreath(congetture_t);
void congettura_goldbach(congetture_t);
void congettura_legendre(congetture_t);









