all: tp2virtual.c
	g++ tp2virtual.c -o tp2virtual

clean: tp2virtual
	rm -rf tp2virtual