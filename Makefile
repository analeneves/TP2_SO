all: main.c funcoes.c
	gcc main.c funcoes.c funcoes.h -o tp2virtual

clean: tp2virtual
	rm -rf tp2virtual