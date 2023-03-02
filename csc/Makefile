all: compile

compile: ./code/Makefile ./code/fibo.c ./code/main.c
	$(MAKE) -C ./code

	gcc -I./include ./code/fibo.c ./code/main.c -o fibo

.PHONY: clean
clean:
	rm -rf ./code/*.o

