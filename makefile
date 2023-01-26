all: compile run

compile: Documento Palavra
	gcc -o prog *.o main1.c

run:
	./prog ./small/train.txt 

Documento:
	gcc -c Documento.c

Palavra:
	gcc -c Palavra.c

clean:
	rm -f *.o prog