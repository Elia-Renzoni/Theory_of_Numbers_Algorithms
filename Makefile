# Makefile
# Autori : Alessio Biagioli e Elia Renzoni
#
verifica_delle_congetture: verifica_delle_congetture.c Makefile
	gcc -ansi -Wall -O verifica_delle_congetture.c -o verifica_delle_congetture -lm
pulisci:
	rm -f verifica_delle_congetture.o
pulisci_tutto:
	rm -f verifica_delle_congetture verifica_delle_congetture.o
