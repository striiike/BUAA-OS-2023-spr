all: run

run: test.c
	gcc test.c -o test

.PHONY: clean
clean:
	rm test
