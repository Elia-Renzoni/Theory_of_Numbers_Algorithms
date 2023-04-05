# Makefile Del Sorgente verifica_congetture.c
verifica_congetture: verifica_congetture.c Makefile
	gcc -ansi -Wall -O verifica_congetture.c -o verifica_congetture -lm
pulisci:
	rm -f verifica_congetture.o
pulisci_tutto:
	rm -f verifica_congetture verifica_congetture.o
