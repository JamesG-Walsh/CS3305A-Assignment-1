CC = gcc

all: external A1

external:
	gcc external_program.c -o external_program.out

A1:
	gcc assignment1.c -o assignment1

test:
	./assignment1 external_program.out

clean:
	@echo "Cleaning up..."
	rm -f external_program.out assignment1

run:
	make clean
	make all
	make test
