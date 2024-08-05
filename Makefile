all:
	gcc -Wall -g -o main *.c -lm

clean:
	rm -rf main